#include <Gfx/GfxSdlWrapper.h>
#include <Log/ILog.h>
#include <Framework/Exceptions.h>
#include <Assets/Defs.h>
#include <Framework/Point.h>
#include <Framework/Rectangle.h>
#include <Framework/Color.h>
#include <Gfx/Defs.h>
#include <BonEngine.h>
#include <unordered_map>

#pragma warning(push, 0)
#include <SDL2-2.0.12/include/SDL.h>
#include <SDL2_image-2.0.5/include/SDL_image.h>
#include <SDL2_ttf-2.0.15/include/SDL_ttf.h>
#pragma warning(pop)

#include <Gfx/FontsCache.h>

using namespace bon::framework;
using namespace bon::assets;

namespace bon
{
	namespace gfx
	{
		// image handle for SDL
		class SDL_ImageHandle : public _ImageHandle
		{
		private:
			// width and height
			int _w;
			int _h;

			// sdl wrapper
			GfxSdlWrapper* _wrapper;

			// if we want to read image pixels - convert it to surface
			SDL_Surface* _asSurface = nullptr;

		public:

			/**
			 * Create SDL image surface.
			 */
			SDL_ImageHandle(SDL_Texture* texture, int w, int h, GfxSdlWrapper* wrapper)
			{
				_w = w;
				_h = h;
				Texture = texture;
				_wrapper = wrapper;
			}

			/**
			 * Delete this image surface.
			 */
			virtual ~SDL_ImageHandle()
			{
				if (Texture) 
				{
					SDL_DestroyTexture((SDL_Texture*)(Texture));
				}
				if (_asSurface)
				{
					SDL_FreeSurface(_asSurface);
				}
			}

			/**
			 * Get image width.
			 *
			 * \return Image width.
			 */
			virtual int Width() const override
			{
				return _w;
			}

			/**
			 * Get image height.
			 *
			 * \return Image height.
			 */
			virtual int Height() const override
			{
				return _h;
			}
			
			/**
			 * Save image asset to file.
			 *
			 * \param filename Filename to save image to.
			 */
			virtual void SaveToFile(const char* filename) const override
			{
				_wrapper->SaveImageToFile((SDL_Texture*)Texture, _w, _h, filename);
			}

			/**
			 * Read pixels into buffer to allow us to query pixels.
			 * You must call this if you want to use 'GetPixel()'.
			 */
			virtual void PrepareReadingBuffer(const framework::RectangleI& sourceRect) override
			{
				// remove previous surface
				if (_asSurface)
				{
					SDL_FreeSurface(_asSurface);
				}

				// get new surface
				_asSurface = _wrapper->TextureToSurface((SDL_Texture*)Texture, _w, _h, sourceRect);
			}

			/**
			 * Free reading buffer previously set using `PrepareReadingBuffer()`.
			 * This happens automatically when asset is released.
			 */
			virtual void FreeReadingBuffer() override
			{
				if (_asSurface)
				{
					SDL_FreeSurface(_asSurface);
					_asSurface = nullptr;
				}
			}

			/**
			 * Clear this image to transparent black pixels.
			 */
			virtual void Clear() override
			{
				_wrapper->ClearTexture((SDL_Texture*)Texture);
			}

			/**
			 * Get pixel from image.
			 * You must first call 'ReadPixelsData' to prepare internal reading buffer.
			 *
			 * \param position Pixel to read.
			 * \return Pixel color.
			 */
			virtual framework::Color GetPixel(const framework::PointI& position) override
			{
				// buffer not prepared? return null
				if (_asSurface == nullptr)
				{
					return framework::Color::TransparentBlack;
				}

				// validate in range
				if (position.X < 0 || position.Y < 0 || position.X >= _asSurface->w || position.Y >= _asSurface->h)
				{
					return framework::Color::TransparentBlack;
				}

				// get bytes per pixel and pixel data
				int bpp = _asSurface->format->BytesPerPixel;
				int buffOffset = position.Y * _asSurface->pitch + position.X * bpp;
				Uint8* p = ((Uint8*)_asSurface->pixels + buffOffset);

				// pixel data based on format
				Uint32 data;

				switch (bpp)
				{
				case 1:
					data = *p;
					break;

				case 2:
					data = *(Uint16*)p;
					break;

				case 3:
					if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
						data = p[0] << 16 | p[1] << 8 | p[2];
					else
						data = p[0] | p[1] << 8 | p[2] << 16;
					break;

				case 4:
					data = *(Uint32*)p;
					break;

				default:
					data = 0;       /* shouldn't happen, but avoids warnings */
				}

				// convert to color and return
				SDL_Color rgb;
				SDL_GetRGBA(data, _asSurface->format, &rgb.r, &rgb.g, &rgb.b, &rgb.a);
				return framework::Color::FromBytes(rgb.r, rgb.g, rgb.b, rgb.a);
			}		

			/**
			 * Store this texture's last set blending mode.
			 */
			BlendModes CurrentBlendMode = BlendModes::AlphaBlend;

			/**
			 * Store this texture last set color.
			 */
			Color CurrentColor = Color::White;
		};

		// images loader we set in the assets manager during initialize
		void ImagesLoader(bon::assets::IAsset* asset, void* context, void* extraData = nullptr)
		{
			// texture to set
			SDL_Texture* texture = nullptr;
			int width = 0;
			int height = 0;

			// set filtering mode
			((GfxSdlWrapper*)context)->SetTextureFiltering(((bon::assets::_Image*)asset)->FilteringMode());

			// get asset path
			const char* path = asset->Path();
			
			// load texture from file
			if (path != nullptr && path[0] != '\0') {

				// load image and make sure succeed
				BON_DLOG("Load image from file: %s.", path);
				SDL_Surface* surface = nullptr;
				surface = IMG_Load(path);
				if (surface == nullptr)
				{
					printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
					throw AssetLoadError(path);
				}

				// convert to texture
				width = surface->w;
				height = surface->h;
				texture = SDL_CreateTextureFromSurface(((GfxSdlWrapper*)context)->GetRenderer(), surface);
				SDL_FreeSurface(surface);
			}
			// create empty texture
			else {
				path = "<New Texture>";
				if (!extraData) {
					BON_ELOG("Tried to create an empty texture, but the extra data, which supposed to hold the desired size, was null! This might happen if you try to load a texture with empty path.");
					throw AssetLoadError(path);
				}
				framework::PointI* size = (framework::PointI*)extraData;
				width = size->X;
				height = size->Y;
				BON_DLOG("Create new empty image with size %dx%d.", width, height);
				texture = SDL_CreateTexture(((GfxSdlWrapper*)context)->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
			}

			// make sure succeed
			if (texture == nullptr)
			{
				printf("Failed to convert image surface to texture (%s)! SDL Error: %s\n", path, SDL_GetError());
				throw AssetLoadError(path);
			}

			// set handle
			SDL_ImageHandle* handle = new SDL_ImageHandle(texture, width, height, ((GfxSdlWrapper*)context));
			asset->_SetHandle(handle);
		}

		// images disposer we set in the assets manager during asset disposal
		void ImagesDisposer(bon::assets::IAsset* asset, void* context)
		{
			asset->_DestroyHandle<SDL_ImageHandle>();
		}

		// font handle for SDL
		class SDL_FontHandle : public _FontHandle
		{
		private:
			int _fontSize;

		public:

			/**
			 * Create SDL image surface.
			 */
			SDL_FontHandle(TTF_Font* font, int size)
			{
				Font = font;
				_fontSize = size;
			}

			/**
			 * Delete this image surface.
			 */
			virtual ~SDL_FontHandle()
			{
				if (Font) {
					TTF_CloseFont((TTF_Font*)Font);
				}
			}


			/**
			 * Get loaded font native size.
			 */
			virtual int FontSize() const { return _fontSize; }
		};

		// fonts loader we set in the assets manager during initialize
		void FontsLoader(bon::assets::IAsset* asset, void* context, void* extraData = nullptr)
		{
			// get path and log
			const char* path = asset->Path();
			BON_DLOG("Load font from file: %s.", path);

			// load font
			int fontSize = extraData ? *((int*)extraData) : 32;
			TTF_Font* font = TTF_OpenFont(path, fontSize);

			// make sure succeed
			if (font == nullptr)
			{
				printf("Failed to load font (%s)! SDL Error: %s\n", path, SDL_GetError());
				throw AssetLoadError(path);
			}

			// set handle
			SDL_FontHandle* handle = new SDL_FontHandle(font, fontSize);
			asset->_SetHandle(handle);
		}

		// font disposer we set in the assets manager during asset disposal
		void FontsDisposer(bon::assets::IAsset* asset, void* context)
		{
			asset->_DestroyHandle<SDL_FontHandle>();
		}

		// set render target
		void GfxSdlWrapper::SetRenderTarget(ImageAsset target)
		{
			if (target)
			{
				SDL_ImageHandle* handle = (SDL_ImageHandle*)target->Handle();
				SDL_Texture* texture = (SDL_Texture*)handle->Texture;
				SDL_SetRenderTarget(_renderer, texture);
			}
			else
			{
				SDL_SetRenderTarget(_renderer, NULL);
			}
		}

		// cache for drawing texts
		FontsTextureCache fontsTextureCache;

		// initialize graphics
		void GfxSdlWrapper::Initialize()
		{
			// initialize SDL and make sure succeed
			int flags = (bon::Features().EffectsEnabled || bon::Features().ForceOpenGL) ? 
				(SDL_INIT_VIDEO | SDL_VIDEO_OPENGL) : (SDL_INIT_VIDEO);
			if (SDL_Init(flags) < 0)
			{
				BON_ELOG("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
				throw InitializeError("Failed to initialize SDL video drivers.");
			}

			// init fonts
			if (TTF_Init() < 0)
			{
				BON_ELOG("SDL TTF Fonts could not initialize! SDL_Error: %s\n", SDL_GetError());
				throw InitializeError("Failed to initialize SDL fonts.");
			}

			// register the assets initializers
			bon::_GetEngine().Assets()._SetAssetsInitializer(bon::assets::AssetTypes::Image, ImagesLoader, ImagesDisposer, this);
			bon::_GetEngine().Assets()._SetAssetsInitializer(bon::assets::AssetTypes::Font, FontsLoader, FontsDisposer, this);
		}

		// set texture filtering
		void GfxSdlWrapper::SetTextureFiltering(assets::ImageFilterMode mode)
		{
			static assets::ImageFilterMode _lastMode = assets::ImageFilterMode::_Count;
			static const char* modes[] = {
				"nearest",
				"linear",
				"best",
				"0"
			};
			if (_lastMode != mode) {
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, modes[(int)mode]);
				_lastMode = mode;
			}
		}

		// set window title
		void GfxSdlWrapper::SetTitle(const char* title)
		{
			SDL_SetWindowTitle(_window, title);
		}

		// get renderer instance
		SDL_Renderer* GfxSdlWrapper::GetRenderer() 
		{
			return _renderer;
		}

		// convert bon blend mode to sdl blend
		SDL_BlendMode BonBlendToSdlBlend(BlendModes blend)
		{
			switch (blend)
			{
			case BlendModes::Opaque:
				return SDL_BLENDMODE_NONE;
			case BlendModes::AlphaBlend:
				return SDL_BLENDMODE_BLEND;
			case BlendModes::Additive:
				return SDL_BLENDMODE_ADD;
			case BlendModes::Mod:
				return SDL_BLENDMODE_MOD;
			case BlendModes::Multiply:
				return SDL_BLENDMODE_MUL;
			default:
				return SDL_BLENDMODE_INVALID;
			}
		}

		// change drawing color but only if needs to
		void SetShapesRenderColorAndBlend(SDL_Renderer* renderer, const Color& color, BlendModes blendMode)
		{
			// set blend, if changed
			static BlendModes lastBlend = BlendModes::_Count;
			if (blendMode != lastBlend) {
				SDL_SetRenderDrawBlendMode(renderer, BonBlendToSdlBlend(blendMode));
				lastBlend = blendMode;
			}

			// set color, if changed
			static Color lastColor = Color(-1, -1, -1, -1);
			if (color != lastColor) {
				SDL_SetRenderDrawColor(renderer, color.RB(), color.GB(), color.BB(), color.AB());
				lastColor = color;
			}
		}

		// draw a line
		void GfxSdlWrapper::DrawLine(const PointI& from, const PointI& to, const Color& color, BlendModes blendMode)
		{
			SetShapesRenderColorAndBlend(_renderer, color, blendMode);
			SDL_RenderDrawLine(_renderer, from.X, from.Y, to.X, to.Y);
		}

		// draw a pixel
		void GfxSdlWrapper::DrawPixel(const PointI& position, const Color& color, BlendModes blendMode)
		{
			SetShapesRenderColorAndBlend(_renderer, color, blendMode);
			SDL_RenderDrawPoint(_renderer, position.X, position.Y);
		}

		// draw a rectangle
		void GfxSdlWrapper::DrawRectangle(const RectangleI& rect, const Color& color, bool filled, BlendModes blendMode)
		{
			SetShapesRenderColorAndBlend(_renderer, color, blendMode);
			SDL_Rect sdlrect;
			sdlrect.x = rect.X;
			sdlrect.y = rect.Y;
			sdlrect.w = rect.Width;
			sdlrect.h = rect.Height;
			if (filled) {
				SDL_RenderFillRect(_renderer, &sdlrect);
			}
			else {
				SDL_RenderDrawRect(_renderer, &sdlrect);
			}
		}

		// draw circle outlines
		void GfxSdlWrapper::DrawCircleLines(const PointI& center, int radius, const Color& color, BlendModes blend)
		{
			// if the first pixel in the screen is represented by (0,0) (which is in sdl)
			// remember that the beginning of the circle is not in the middle of the pixel
			// but to the left-top from it:

			// set color and blend mode
			SetShapesRenderColorAndBlend(_renderer, color, blend);

			double error = (double)-radius;
			double x = (double)radius - 0.5;
			double y = (double)0.5;
			double cx = center.X - 0.5;
			double cy = center.Y - 0.5;

			while (x >= y)
			{
				SDL_RenderDrawPoint(_renderer, (int)(cx + x), (int)(cy + y));
				SDL_RenderDrawPoint(_renderer, (int)(cx + y), (int)(cy + x));

				if (x != 0)
				{
					SDL_RenderDrawPoint(_renderer, (int)(cx - x), (int)(cy + y));
					SDL_RenderDrawPoint(_renderer, (int)(cx + y), (int)(cy - x));
				}

				if (y != 0)
				{
					SDL_RenderDrawPoint(_renderer, (int)(cx + x), (int)(cy - y));
					SDL_RenderDrawPoint(_renderer, (int)(cx - y), (int)(cy + x));
				}

				if (x != 0 && y != 0)
				{
					SDL_RenderDrawPoint(_renderer, (int)(cx - x), (int)(cy - y));
					SDL_RenderDrawPoint(_renderer, (int)(cx - y), (int)(cy - x));
				}

				error += y;
				++y;
				error += y;

				if (error >= 0)
				{
					--x;
					error -= x;
					error -= x;
				}
			}
		}

		// draw filled circle
		void GfxSdlWrapper::DrawCircleFill(const PointI& center, int radius, const Color& color, BlendModes blend)
		{
			// Note that there is more to altering the bitrate of this 
			// method than just changing this value.  See how pixels are
			// altered at the following web page for tips:
			//   http://www.libsdl.org/intro.en/usingvideo.html
			static const int BPP = 4;

			// set color and blend mode
			SetShapesRenderColorAndBlend(_renderer, color, blend);

			//double ra = (double)radius;

			for (double dy = 1; dy < radius; dy += 1.0)
			{
				// This loop is unrolled a bit, only iterating through half of the
				// height of the circle.  The result is used to draw a scan line and
				// its mirror image below it.

				// The following formula has been simplified from our original.  We
				// are using half of the width of the circle because we are provided
				// with a center and we need left/right coordinates.

				double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
				int x = (int)(center.X - dx);
				SDL_RenderDrawLine(_renderer, (int)(center.X - dx), (int)(center.Y + dy - radius), (int)(center.X + dx - 1), (int)(center.Y + dy - radius));
				SDL_RenderDrawLine(_renderer, (int)(center.X - dx), (int)(center.Y - dy + radius - 1), (int)(center.X + dx - 1), (int)(center.Y - dy + radius - 1));
			}
		}

		// clear screen or parts of it
		void GfxSdlWrapper::ClearScreen(const Color& color, const RectangleI& clearRect)
		{
			// set drawing color
			SetShapesRenderColorAndBlend(_renderer, color, BlendModes::Opaque);

			// clear whole screen using render clear
			if (clearRect.Empty())
			{
				SDL_RenderClear(_renderer);
			}
			// clear region using fill rect
			else
			{
				static SDL_Rect rect;
				rect.x = clearRect.X;
				rect.y = clearRect.Y;
				rect.w = clearRect.Width;
				rect.h = clearRect.Height;
				SDL_RenderFillRect(_renderer, &rect);
			}
		}

		// clear an image to transparent
		void GfxSdlWrapper::ClearTexture(SDL_Texture* texture)
		{
			// get previous render target
			SDL_Texture* prevTarget = SDL_GetRenderTarget(_renderer);

			// set drawing color
			SetShapesRenderColorAndBlend(_renderer, bon::framework::Color(0, 0, 0, 0), BlendModes::Opaque);

			// make render draw to tex
			SDL_SetRenderTarget(_renderer, texture);

			// will make pixels with alpha 0 fully transparent
			// use SDL_SetTextureBlendMode . Not SDL_SetRenderDrawBlendMode
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

			// tell render to use colore with alpha 0
			SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);

			// fill texture with transparent pixels
			SDL_RenderClear(_renderer);

			// make render draw to window
			SDL_SetRenderTarget(_renderer, prevTarget);
		}

		// destructor - cleanup window and quit.
		// note: other subsystems uses SDL too, gfx is responsible to quit for everyone.
		GfxSdlWrapper::~GfxSdlWrapper()
		{
			// destroy window
			Dispose();

			// quit ttf subsystem
			TTF_Quit();

			// quit SDL subsystems
			SDL_Quit();
		}

		// dispose basic stuff
		void GfxSdlWrapper::Dispose()
		{
			if (_window) {
				SDL_DestroyWindow(_window);
				_window = nullptr;
			}
			if (_renderer) {
				SDL_DestroyRenderer(_renderer);
				_renderer = nullptr;
			}
			IMG_Quit();
		}

		// create window
		void GfxSdlWrapper::CreateWindow(const char* title, int width, int height, WindowModes windowMode)
		{
			// sanity - make sure there are no loaded images
			if (bon::_GetEngine().Assets()._GetLoadedAssetsCount(bon::assets::AssetTypes::Image) > 0) {
				BON_ELOG("Cannot change window properties while there are still loaded texture assets!");
				throw new InvalidState("Cannot change window properties while there are still loaded texture assets!");
			}

			// set default sizes
			if (width == 0 || height == 0)
			{
				BON_DLOG("Window width or height was set to 0 - query desktop size to retrieve default window size.");
				SDL_DisplayMode dm;
				SDL_GetCurrentDisplayMode(0, &dm);
				if (width == 0) {
					width = dm.w;
				}
				if (height == 0) {
					height = dm.h;
				}
			}

			// clear previous window and renderer
			Dispose();

			// create window and make sure succeed
			int flags;
			switch (windowMode)
			{
			case WindowModes::Windowed:
				flags = SDL_WINDOW_SHOWN;
				break;
			case WindowModes::Fullscreen:
				flags = SDL_WINDOW_FULLSCREEN;
				break;
			case WindowModes::WindowedBorderless:
				flags = SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS;
				break;
			default:
				flags = SDL_WINDOW_SHOWN;
				break;
			}
			_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
			if (_window == NULL)
			{
				BON_ELOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				throw InitializeError("Failed to create SDL window.");
			}

			// get window surface
			_screenSurface = SDL_GetWindowSurface(_window);

			// start in center
			SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

			// force using opengl
			if (bon::Features().EffectsEnabled || bon::Features().ForceOpenGL)
			{
				SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
			}

			// create renderer
			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

			// init effects manager
			if (bon::Features().EffectsEnabled)
			{
				_effectsImpl.Initialize(_renderer);
			}
		}

		// set currently active effect, or null to remove effects.
		void GfxSdlWrapper::SetEffect(const assets::EffectAsset& effect)
		{
			// skip if no change
			if (effect == _currentEffect) { return; }

			SDL_SetRenderTarget(_renderer, NULL);

			// apply effect
			_effectsImpl.UseEffect(effect);
			_currentEffect = effect;
		}

		// update window / draw.
		void GfxSdlWrapper::UpdateWindow()
		{
			// update effects
			if (bon::Features().EffectsEnabled)
			{
				_effectsImpl.OnFrameStart();
				_currentEffect = nullptr;
			}

			// render screen
			SDL_RenderPresent(_renderer);

			// update cache
			fontsTextureCache.Update();
		}

		// show / hide cursor
		void GfxSdlWrapper::ShowCursor(bool show)
		{
			SDL_ShowCursor(show);
		}

		// set texture blend mode and color properties.
		void SetTextureProperties(SDL_ImageHandle* handle, SDL_Texture* texture, const Color& color, BlendModes blend)
		{
			// set blend mode
			if (handle->CurrentBlendMode != blend) {
				SDL_SetTextureBlendMode(texture, BonBlendToSdlBlend(blend));
				handle->CurrentBlendMode = blend;
			}

			// set alpha
			if (handle->CurrentColor.A != color.A)
			{
				SDL_SetTextureAlphaMod(texture, color.AB());
				handle->CurrentColor.A = color.A;
			}

			// set color
			if (handle->CurrentColor != color)
			{
				SDL_SetTextureColorMod(texture, color.RB(), color.GB(), color.BB());
				handle->CurrentColor = color;
			}
		}

		// draw text on screen
		void GfxSdlWrapper::DrawText(const FontAsset& fontAsset, const char* text, const PointF& position, const Color& color, int fontSize, BlendModes blend, const PointF& origin, float rotation, int maxWidth, RectangleI* outDestRect, bool dryrun)
		{
			// wrap text as string
			std::string asString(text);

			// first try to fetch texture from cache
			SDL_FontHandle* fontHandle = (SDL_FontHandle*)fontAsset->Handle();
			TTF_Font* font = (TTF_Font*)(fontHandle->Font);
			CachedTexture& fromCache = fontsTextureCache.GetFromCache(font, asString);
			
			// not found in cache? generate it!
			if (!fromCache.Texture) {
				static SDL_Color white = { 255,255,255,255 };
				SDL_Surface* tempSurface = nullptr;
				if (maxWidth == 0) { maxWidth = 0xFFF; }
				tempSurface = TTF_RenderText_Blended_Wrapped(font, text, white, maxWidth);
				if (tempSurface) {
					SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
					int width = tempSurface->w; int height = tempSurface->h;
					fromCache = fontsTextureCache.AddToCache(font, asString, texture, width, height);
					SDL_FreeSurface(tempSurface);
				}
			}

			// calculate size factor
			float sizeFactor = fontSize ? ((float)fontSize / (float)fontAsset->FontSize()) : 1.0f;

			// draw text
			PointI size((int)(fromCache.Width * sizeFactor), (int)(fromCache.Height * sizeFactor));
			static RectangleI srcRect;
			DrawTexture(fromCache.Texture, position, size, blend, srcRect, origin, rotation, color, outDestRect, dryrun, fromCache.Width, fromCache.Height);
		}

		// set gamma
		void GfxSdlWrapper::SetGamma(float brightness)
		{
			SDL_SetWindowBrightness(_window, brightness);
		}

		// get window width
		int GfxSdlWrapper::WindowWidth() const
		{
			int w; int h;
			SDL_GetWindowSize(_window, &w, &h);
			return w;
		}

		// get window height
		int GfxSdlWrapper::WindowHeight() const
		{
			int w; int h;
			SDL_GetWindowSize(_window, &w, &h);
			return h;
		}

		// convert texture to surface
		SDL_Surface* GfxSdlWrapper::TextureToSurface(SDL_Texture* texture, int width, int height, framework::RectangleI sourceRect)
		{
			// get current render target and set texture as the new render target
			SDL_Texture* target = SDL_GetRenderTarget(_renderer);
			SDL_SetRenderTarget(_renderer, texture);

			// calc source rect
			SDL_Rect rect;
			rect.x = sourceRect.X;
			rect.y = sourceRect.Y;
			rect.w = (sourceRect.Width != 0) ? sourceRect.Width : (width - sourceRect.X);
			rect.h = (sourceRect.Height != 0) ? sourceRect.Height : (height - sourceRect.Y);

			// create surface
			SDL_Surface* surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
			
			// read pixels into new surface
			SDL_RenderReadPixels(_renderer, &rect, surface->format->format, surface->pixels, surface->pitch);

			// recover previous render target and return
			SDL_SetRenderTarget(_renderer, target);
			return surface;
		}

		// save image asset to file
		void GfxSdlWrapper::SaveImageToFile(SDL_Texture* texture, int width, int height, const char* filename)
		{
			// get current render target and set texture as the new render target
			SDL_Texture* target = SDL_GetRenderTarget(_renderer);
			SDL_SetRenderTarget(_renderer, texture);

			// create surface the size of the texture and read texture into it
			SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
			SDL_RenderReadPixels(_renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
			
			// save to file and free surface
			IMG_SavePNG(surface, filename);
			SDL_FreeSurface(surface);

			// recover previous render target
			SDL_SetRenderTarget(_renderer, target);
		}

		// draw texture on screen
		void GfxSdlWrapper::DrawTexture(SDL_Texture* texture, const PointF& position, const PointI& size, BlendModes blend, const RectangleI& sourceRect, const PointF& origin, float rotation, Color color, RectangleI* outDestRect, bool dryrun, int textW, int textH)
		{
			// set blend mode and color
			if (!dryrun)
			{
				SDL_SetTextureBlendMode(texture, BonBlendToSdlBlend(blend));
				SDL_SetTextureColorMod(texture, color.RB(), color.GB(), color.BB());
				SDL_SetTextureAlphaMod(texture, color.AB());
			}

			// source rect
			static SDL_Rect sdlSrcRect;
			SDL_Rect* sdlSrcRectPtr = NULL;
			if (!sourceRect.Empty())
			{
				sdlSrcRect.x = sourceRect.X;
				sdlSrcRect.y = sourceRect.Y;
				sdlSrcRect.w = sourceRect.Width;
				sdlSrcRect.h = sourceRect.Height;
				sdlSrcRectPtr = &sdlSrcRect;
			}

			// calculate destination rect
			static SDL_Rect dest;
			dest.x = (int)floor(position.X);
			dest.y = (int)floor(position.Y);
			dest.w = (int)floor(size.X);
			dest.h = (int)floor(size.Y);

			// do flipping
			int flip = SDL_RendererFlip::SDL_FLIP_NONE;
			if (dest.w < 0) {
				flip |= SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
				dest.w = -dest.w;
			}
			if (dest.h < 0) {
				flip |= SDL_RendererFlip::SDL_FLIP_VERTICAL;
				dest.h = -dest.h;
			}

			// draw with effect
			if (_currentEffect != nullptr)
			{
				_effectsImpl.DrawTexture(&dest, sdlSrcRectPtr, texture, color, textW, textH);
				return;
			}

			// draw texture with rotation
			if ((rotation != 0) || (flip != SDL_RendererFlip::SDL_FLIP_NONE) || (!origin.IsZero())) 
			{
				SDL_Point sdlOrigin;
				sdlOrigin.x = (int)(origin.X * dest.w);
				sdlOrigin.y = (int)(origin.Y * dest.h);
				dest.x -= sdlOrigin.x;
				dest.y -= sdlOrigin.y;
				if (outDestRect) {
					outDestRect->X = dest.x;
					outDestRect->Y = dest.y;
					outDestRect->Width = dest.w;
					outDestRect->Height = dest.h;
				}
				if (!dryrun) {
					SDL_RenderCopyEx(_renderer, texture, sdlSrcRectPtr, &dest, rotation, &sdlOrigin, (SDL_RendererFlip)flip);
				}
			}
			// draw texture without rotation
			else 
			{
				if (outDestRect) {
					outDestRect->X = dest.x;
					outDestRect->Y = dest.y;
					outDestRect->Width = dest.w;
					outDestRect->Height = dest.h;
				}
				if (!dryrun) {
					SDL_RenderCopy(_renderer, texture, sdlSrcRectPtr, &dest);
				}
			}
		}

		// set rendering viewport
		void GfxSdlWrapper::SetViewport(const framework::RectangleI* viewport)
		{
			if (viewport)
			{
				SDL_Rect rect;
				rect.x = viewport->X;
				rect.y = viewport->Y;
				rect.w = viewport->Width;
				rect.h = viewport->Height;
				SDL_RenderSetViewport(_renderer, &rect);
			}
			else
			{
				SDL_RenderSetViewport(_renderer, nullptr);
			}
		}

		// draw image on screen
		void GfxSdlWrapper::DrawImage(const ImageAsset& sourceImage, const PointF& position, const PointI& size, BlendModes blend, const RectangleI& sourceRect, const PointF& origin, float rotation, Color color)
		{
			// get image handle
			SDL_ImageHandle* handle = (SDL_ImageHandle*)sourceImage->Handle();

			// get texture
			SDL_Texture* texture = (SDL_Texture*)handle->Texture;

			// set blend mode and color
			SetTextureProperties(handle, texture, color, blend);

			// source rect
			static SDL_Rect sdlSrcRect;
			SDL_Rect* sdlSrcRectPtr = NULL;
			if (!sourceRect.Empty())
			{
				sdlSrcRect.x = sourceRect.X;
				sdlSrcRect.y = sourceRect.Y;
				sdlSrcRect.w = sourceRect.Width;
				sdlSrcRect.h = sourceRect.Height;
				sdlSrcRectPtr = &sdlSrcRect;
			}

			// calculate destination rect. first position
			static SDL_Rect dest;
			dest.x = (int)floor(position.X);
			dest.y = (int)floor(position.Y);

			// calc dest rect width
			if (size.X == 0) {
				dest.w = sdlSrcRectPtr ? sdlSrcRectPtr->w : sourceImage->Width();
			}
			else{
				dest.w = (int)floor(size.X);
			}

			// calc dest rect height
			if (size.Y == 0) {
				dest.h = sdlSrcRectPtr ? sdlSrcRectPtr->h : sourceImage->Height();
			}
			else {
				dest.h = (int)floor(size.Y);
			}

			// do flipping
			int flip = SDL_RendererFlip::SDL_FLIP_NONE;
			if (dest.w < 0) {
				flip |= SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
				dest.w = -dest.w;
			}
			if (dest.h < 0) {
				flip |= SDL_RendererFlip::SDL_FLIP_VERTICAL;
				dest.h = -dest.h;
			}

			// draw with effect
			if (_currentEffect != nullptr)
			{
				_effectsImpl.DrawTexture(&dest, sdlSrcRectPtr, texture, color, handle->Width(), handle->Height());
				return;
			}

			// draw texture with rotation
			if ((rotation != 0) || (flip != SDL_RendererFlip::SDL_FLIP_NONE) || (!origin.IsZero())) {
				SDL_Point sdlOrigin;
				sdlOrigin.x = (int)(origin.X * dest.w);
				sdlOrigin.y = (int)(origin.Y * dest.h);
				dest.x -= sdlOrigin.x;
				dest.y -= sdlOrigin.y;
				SDL_RenderCopyEx(_renderer, texture, sdlSrcRectPtr, &dest, rotation, &sdlOrigin, (SDL_RendererFlip)flip);
			}
			// draw texture without rotation
			else {
				SDL_RenderCopy(_renderer, texture, sdlSrcRectPtr, &dest);
			}
		}

		// draw image on screen
		void GfxSdlWrapper::DrawImage(const ImageAsset& sourceImage, const PointF& position, const PointI& size, BlendModes blend)
		{
			// calculate destination rect
			static SDL_Rect dest;
			dest.x = (int)floor(position.X);
			dest.y = (int)floor(position.Y);
			dest.w = (int)floor(size.X ? size.X : sourceImage->Width());
			dest.h = (int)floor(size.Y ? size.Y : sourceImage->Height());

			// get image handle
			SDL_ImageHandle* handle = (SDL_ImageHandle*)sourceImage->Handle();

			// get texture
			SDL_Texture* texture = (SDL_Texture*)handle->Texture;

			// do flipping
			int flip = SDL_RendererFlip::SDL_FLIP_NONE;
			if (dest.w < 0) {
				flip |= SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
				dest.w = -dest.w;
			}
			if (dest.h < 0) {
				flip |= SDL_RendererFlip::SDL_FLIP_VERTICAL;
				dest.h = -dest.h;
			}

			// draw with effect
			static Color color(1, 1, 1, 1);
			if (_currentEffect != nullptr)
			{
				_effectsImpl.DrawTexture(&dest, nullptr, texture, color, handle->Width(), handle->Height());
				return;
			}

			// set blend mode and color
			SetTextureProperties(handle, texture, color, blend);

			// draw texture with rotation
			if (flip != SDL_RendererFlip::SDL_FLIP_NONE) {
				SDL_RenderCopyEx(_renderer, texture, NULL, &dest, 0, NULL, (SDL_RendererFlip)flip);
			}
			// draw texture without rotation
			else {
				SDL_RenderCopy(_renderer, texture, NULL, &dest);
			}
		}
	}
}