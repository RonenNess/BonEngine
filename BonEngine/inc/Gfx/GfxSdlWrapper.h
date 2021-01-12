/*****************************************************************//**
 * \file   GfxSdlWrapper.h
 * \brief  A wrapper around SDL for gfx manager.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include <Assets/Defs.h>
#include <Framework/Point.h>
#include <Framework/Rectangle.h>
#include <Framework/Color.h>
#include <Assets/Types/Image.h>
#include <Assets/Types/Effect.h>
#include <Gfx/Defs.h>
#include "GfxSdlEffects.h"

 // forward declare some SDL stuff
struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;
struct SDL_Texture;

namespace bon
{
	namespace gfx
	{
		/**
		 * The gfx implementor class.
		 */
		class BON_DLLEXPORT GfxSdlWrapper
		{
		private:
			// the window we'll be rendering to
			SDL_Window* _window = nullptr;

			// the surface contained by the window
			SDL_Surface* _screenSurface = nullptr;

			// renderer
			SDL_Renderer* _renderer = nullptr;

#pragma warning ( push )
#pragma warning ( disable: 4251 ) 
			// sdl glsl effects manager
			GfxSdlEffects _effectsImpl;

			// currently active effect
			assets::EffectAsset _currentEffect;

#pragma warning (pop)

		public:

			/**
			 * Get currently active effect.
			 */
			inline assets::EffectAsset GetActiveEffect() const { return _currentEffect; }

			/**
			 * Initialize graphics.
			 */
			void Initialize();

			/**
			 * Update window / render.
			 */
			void UpdateWindow();

			/**
			 * Gain access to the currently renderer.
			 * 
			 * \return Renderer pointer.
			 */
			SDL_Renderer* GetRenderer();

			/**
			 * Create game main window.
			 * 
			 * \param title Window title.
			 * \param width Window width.
			 * \param height Window height.
			 * \param windowMode Window mode (fullscreen / windowed).
			 */
			void CreateWindow(const char* title, int width, int height, WindowModes windowMode = WindowModes::Windowed);

			/**
			 * Set currently active effect, or null to remove effects.
			 * 
			 * \param effect Effect to draw with.
			 */
			void SetEffect(const assets::EffectAsset& effect);
			
			/**
			 * Draw an image on screen.
			 *
			 * \param sourceImage Source image to draw.
			 * \param position Image position.
			 * \param size Image target size. Negative values will flip image.
			 * \param blend How to blend the image with previous renders.
			 */
			void DrawImage(const assets::ImageAsset& sourceImage, const framework::PointF& position, const framework::PointI& size = framework::PointI(0, 0), BlendModes blend = BlendModes::AlphaBlend);

			/**
			 * Draw an image on screen.
			 *
			 * \param sourceImage Source image to draw.
			 * \param position Image position.
			 * \param size Image target size. Negative values will flip image.
			 * \param blend How to blend the image with previous renders.
			 * \param sourceRect Source rectangle to copy from texture.
			 * \param origin Drawing origin point.
			 * \param rotation Rotate the image.
			 * \param color Optional tint color.
			 * \param color Color tint to apply on image.
			 */
			void DrawImage(const assets::ImageAsset& sourceImage, const framework::PointF& position, const framework::PointI& size, BlendModes blend, const framework::RectangleI* sourceRect, const framework::PointF& origin, float rotation, framework::Color color);

			/**
			 * Draw text on screen.
			 * 
			 * \param fontAsset Font to draw.
			 * \param text Text to write.
			 * \param position Text position.
			 * \param color Text color.
			 * \param fontSize Font target size, or -1 to use loaded font asset's default.
			 * \param blend Blend mode.
			 * \param origin Drawing origin.
			 * \param rotation Rotation.
			 * \param maxWidth Max line width.
			 * \param outDestRect If provided, will hold calculated destination rect when done.
			 */
			void DrawText(const assets::FontAsset& fontAsset, const char* text, const framework::PointF& position, const framework::Color& color, int fontSize, BlendModes blend, const framework::PointF& origin, float rotation, int maxWidth, framework::RectangleI* outDestRect, bool dryrun = false);

			/**
			 * Save a texture to file.
			 * 
			 * \param texture Texture to save.
			 * \param width Texture width.
			 * \param height Texture height.
			 * \param filename Target filename.
			 */
			void SaveImageToFile(SDL_Texture* texture, int width, int height, const char* filename);
			
			/**
			 * Convert a texture to surface, and read all pixels into it.
			 * 
			 * \param texture Texture to convert.
			 * \param width Texture width.
			 * \param height Texture height.
			 * \param sourceRect Source rect to copy, or empty to copy whole texture.
			 * \return Surface from texture (you need to release it later).
			 */
			SDL_Surface* TextureToSurface(SDL_Texture* texture, int width, int height, framework::RectangleI sourceRect);

			/**
			 * Create a new texture containing everything currently rendered on screen.
			 * 
			 * \return Newly created texture created from screen.
			 */
			assets::_ImageHandle* RenderScreenToImage() const;

			/**
			 * Set textures filtering mode.
			 * 
			 * \param mode Texture filtering mode.
			 */
			void SetTextureFiltering(assets::ImageFilterMode mode);

			/**
			 * Set window's gamma and colors ramp.
			 *
			 * \param brightness Brightness factor.
			 */
			void SetGamma(float brightness);

			/**
			 * Get if we currently have a valid window initialized.
			 */
			inline bool HaveValidWindow() const { return _window != nullptr; }
			
			/**
			 * Change window's title.
			 * 
			 * \param title Window title.
			 */
			void SetTitle(const char* title);

			/**
			 * Set focus on window.
			 */
			void FocusWindow();

			/**
			 * Draws a line.
			 * 
			 * \param from Line start.
			 * \param to Line end.
			 * \param color Line color.
			 * \param blendMode Blending mode.
			 */
			void DrawLine(const framework::PointI& from, const framework::PointI& to, const framework::Color& color, BlendModes blendMode);

			/**
			 * Draws a pixel.
			 * 
			 * \param position Pixel position.
			 * \param color Pixel color.
			 * \param blendMode Blending mode.
			 */
			void DrawPixel(const framework::PointI& position, const framework::Color& color, BlendModes blendMode);

			/**
			 * Draws a rectangle.
			 * 
			 * \param rect Rectangle to draw.
			 * \param color Rectangle color.
			 * \param filled If true, will draw filled rectangle. If false, will draw only outline.
			 * \param blendMode Blending mode.
			 */
			void DrawRectangle(const framework::RectangleI& rect, const framework::Color& color, bool filled, BlendModes blendMode, const framework::PointF& origin, float rotation);
			
			/**
			 * Draws a circle line.
			 * 
			 * \param center Circle center.
			 * \param radius Circle radius.
			 * \param color Circle color.
			 * \param blend Drawing blend mode.
			 */
			void DrawCircleLines(const framework::PointI& center, int radius, const framework::Color& color, BlendModes blend);

			/**
			 * Draws a filled circle.
			 *
			 * \param center Circle center.
			 * \param radius Circle radius.
			 * \param color Circle color.
			 * \param blend Drawing blend mode.
			 */
			void DrawCircleFill(const framework::PointI& center, int radius, const framework::Color& color, BlendModes blend);

			/**
			 * Draws a 2d polygon.
			 *
			 * \param a Polygon vertex #1.
			 * \param b Polygon vertex #2.
			 * \param c Polygon vertex #3.
			 * \param color fill color.
			 * \param blend blend mode.
			 */
			void DrawPolygon(const framework::PointI& a, const framework::PointI& b, const framework::PointI& c, const framework::Color& color, BlendModes blend);
			
			/**
			 * Draws a 2d quad.
			 *
			 * \param a Quad vertex #1.
			 * \param b Quad vertex #2.
			 * \param c Quad vertex #3.
			 * \param d Quad vertex #4.
			 * \param color fill color.
			 * \param blend blend mode.
			 */
			void DrawQuad(const framework::PointI& a, const framework::PointI& b, const framework::PointI& c, const framework::PointI& d, const framework::Color& color, BlendModes blend);

			/**
			 * Show / hide cursor.
			 * 
			 * \param show Should we show the cursor?
			 */
			void ShowCursor(bool show);
			
			/**
			 * Clear screen or a part of it.
			 * 
			 * \param color Color to clear to.
			 * \param clearRect Region to clear.
			 */
			void ClearScreen(const framework::Color& color, const framework::RectangleI& clearRect);

			/**
			 * Clears a texture to 0,0,0,0 - including alpha channel.
			 *
			 * \param texture Texture to clear.
			 */
			void ClearTexture(SDL_Texture* texture, int width, int height);

			/**
			 * Set the target we render to.
			 * This enable us to draw on images instead of on screen.
			 *
			 * \param target Target to draw on, or nullptr to clear render target and draw back on screen.
			 */
			void SetRenderTarget(assets::ImageAsset target);

			/**
			* Set a rendering viewport (will only render inside the given region).
			*
			* \param viewport Viewport to set, or nullptr to remove viewport and render on whole screen.
			*/
			void SetViewport(const framework::RectangleI* viewport);

			/**
			 * Dispose renderer, window ect.
			 */
			void Dispose();

			/**
			 * Destructor.
			 */
			virtual ~GfxSdlWrapper();

			/**
			 * Get window width.
			 */
			inline int WindowWidth() const;

			/**
			 * Get window height.
			 */
			inline int WindowHeight() const;

			/**
			 * Start using the built-in shapes effect.
			 */
			void UseDefaultShapesEffect(bool onlyIfDefault);

			/**
			 * Start using the built-in textures effect.
			 */
			void UseDefaultTexturesEffect(bool onlyIfDefault);

			/**
			 * Set shapes drawing color.
			 */
			void SetShapesColor(const framework::Color& color);

			/**
			 * Stop using effects and restore the default SDL effect.
			 */
			void RestoreDefaultEffect();

			/**
			 * Get current effect handle.
			 */
			void* GetCurrentEffectHandle();

			/**
			 * Set current effect from handle.
			 */
			void SetCurrentEffectFromAsset(const bon::assets::EffectAsset& effect);

		private:

			/**
			 * Handle images without alpha channels by adding alpha of 1.
			 */
			void HandleImagesWithoutAlpha(assets::ImageAsset image);

			/**
			 * Restore default internal states.
			 */
			void RestoreDefaultStates();

			/**
			 * Draw texture directly. Used internally.
			 */
			void DrawTextAsTexture(SDL_Texture* texture, const framework::PointF& position, const framework::PointI& size, BlendModes blend, const framework::RectangleI* sourceRect, const framework::PointF& origin, float rotation, framework::Color color, framework::RectangleI* outDestRect = nullptr, bool dryrun = false, int textW = 0, int textH = 0);
		};
	}
}