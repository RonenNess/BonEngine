/*****************************************************************//**
 * \file   Gfx.h
 * \brief  The default gfx manager implemented by BonEngine.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "IGfx.h"
#include "GfxSdlWrapper.h"
#include "GfxSdlEffects.h"

namespace bon
{
	namespace gfx
	{
		/**
		 * Default gfx manager.
		 */
		class BON_DLLEXPORT Gfx : public IGfx
		{
		public:

			/**
			 * The gfx internal implementor class.
			 * Access this only if you must change something internal in the default Gfx manager.
			 */
			GfxSdlWrapper _Implementor;

		protected:

			/**
			 * Initialize manager when engine starts.
			 */
			virtual void _Initialize() override;

			/**
			 * Clear / free this manager's resources.
			 */
			virtual void _Dispose() override;

			/**
			 * Called every frame.
			 */
			virtual void _Update(double deltaTime) override;

			/**
			 * Called when main loop starts.
			 */
			virtual void _Start() override;

			/**
			 * Called on newly loaded asset to init the asset itself.
			 * Only use in managers that uses assets.
			 *
			 * \param asset Newly created asset. Expected to be of the type corresponding to this manager.
			 */
			virtual void _LoadAsset(assets::IAsset* asset) {}

		public:

			/**
			 * Bring the main window forward and focus input on it.
			 */
			virtual void FocusWindow() override;

			/**
			 * Draw an image on screen.
			 *
			 * \param sourceImage Source image to draw.
			 * \param position Image position.
			 * \param size Image target size. Negative values will flip image.
			 * \param blend How to blend the image with previous renders.
			 */
			virtual void DrawImage(const assets::ImageAsset& sourceImage, const framework::PointF& position, const framework::PointI* size = nullptr, BlendModes blend = BlendModes::AlphaBlend) override;

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
			 * \param color Color tint to apply on image.
			 */
			virtual void DrawImage(const assets::ImageAsset& sourceImage, const framework::PointF& position, const framework::PointI* size, BlendModes blend, const framework::RectangleI* sourceRect, const PointF* origin, float rotation, const Color* color) override;

			/**
			 * Draw a sprite.
			 *
			 * \param sprite Sprite to draw.
			 * \param offset Position offset to add without affecting sprite, useful for camera implementation.
			 */
			virtual void DrawSprite(const Sprite& sprite, const framework::PointF* offset = nullptr) override;

			/**
			 * Draw text on screen.
			 *
			 * \param font Font to use.
			 * \param text Text to draw.
			 * \param position Text position.
			 * \param color Text color.
			 * \param fontSize Font size, or 0 to use loaded font native size.
			 * \param maxWidth Max line width (or 0 for no limit).
			 * \param blend Blend mode.
			 * \param origin Text origin.
			 * \param rotation Text rotation.
			 * \param outlineWidth Text outline width (0 for no outline).
			 * \param outlineColor Text outline color.
			 */
			virtual void DrawText(const assets::FontAsset& font, const char* text, const framework::PointF& position, const Color* color = nullptr, int fontSize = 0, int maxWidth = 0, BlendModes blend = BlendModes::AlphaBlend, const PointF* origin = nullptr, float rotation = 0.0f, int outlineWidth = 0, const Color* outlineColor = nullptr) override;

			/**
			 * Calculate and get text bounding box.
			 * 
			 * \param font Font to use.
			 * \param text Text to draw.
			 * \param position Text position.
			 * \param fontSize Font size.
			 * \param maxWidth Text max width.
			 * \param origin Text origin.
			 * \param rotation Text rotation.
			 * \return Rectangle representing the bounding box this text drawing would take.
			 */
			virtual RectangleI GetTextBoundingBox(const assets::FontAsset& font, const char* text, const framework::PointF& position, int fontSize = 0, int maxWidth = 0, const PointF* origin = nullptr, float rotation = 0.0f) override;

			/**
			 * Draws a line.
			 *
			 * \param from Line start.
			 * \param to Line end.
			 * \param color Line color.
			 * \param blendMode Drawing shape blending mode.
			 */
			virtual void DrawLine(const framework::PointI& from, const framework::PointI& to, const framework::Color& color, BlendModes blendMode = BlendModes::AlphaBlend) override;

			/**
			 * Draws a pixel.
			 *
			 * \param position Pixel position.
			 * \param color Pixel color.
			 * \param blendMode Drawing shape blending mode.
			 */
			virtual void DrawPixel(const framework::PointI& position, const framework::Color& color, BlendModes blendMode = BlendModes::AlphaBlend) override;

			/**
			 * Draws a rectangle.
			 *
			 * \param rect Rectangle to draw.
			 * \param color Rectangle color.
			 * \param filled If true, will draw filled rectangle. If false, will draw only outline.
			 * \param blendMode Drawing shape blending mode.
			 * \param origin Rectangle origin.
			 * \param rotation Rectangle rotation.
			 */
			virtual void DrawRectangle(const framework::RectangleI& rect, const framework::Color& color, bool filled, BlendModes blendMode = BlendModes::AlphaBlend, const PointF* origin = nullptr, float rotation = 0.0f) override;

			/**
			 * Draws a circle.
			 *
			 * \param center Circle center.
			 * \param radius Circle radius.
			 * \param color Circle color.
			 * \param filled If true, will draw filled circle. If false, will draw only outline.
			 * \param blendMode Drawing shape blending mode.
			 */
			virtual void DrawCircle(const framework::PointI& center, int radius, const framework::Color& color, bool filled, BlendModes blendMode = BlendModes::AlphaBlend) override;

			/**
			 * Draws a 2d polygon.
			 * Note: only works with OpenGL renderer!
			 *
			 * \param a Polygon point 1.
			 * \param b Polygon point 2.
			 * \param c Polygon point 3.
			 * \param color fill color.
			 * \param blend blend mode.
			 */
			virtual void DrawPolygon(const framework::PointI& a, const framework::PointI& b, const framework::PointI& c, const framework::Color& color, BlendModes blend = BlendModes::AlphaBlend) override;

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
			virtual void DrawQuad(const framework::PointI& a, const framework::PointI& b, const framework::PointI& c, const framework::PointI& d, const framework::Color& color, BlendModes blend = BlendModes::AlphaBlend) override;

			/**
			 * Clear the entire or part of the screen.
			 *
			 * \param color Clear color (will paint whole screen with this color).
			 * \param clearRect Set what part of the screen you want to clear. Leave it 0,0,0,0 for whole screen.
			 */
			virtual void ClearScreen(const Color& color = Color(0, 0, 0, 0), const RectangleI& clearRect = RectangleI(0, 0, 0, 0)) override;

			/**
			 * Get window's size in pixels.
			 *
			 * \return Window size.
			 */
			virtual const framework::PointI& WindowSize() const override;

			/**
			 * Get the size in pixels we can draw on.
			 * - If viewport is set, will return viewport size.
			 * - If target texture is set, will return texture size.
			 * - If none of the above is set, will return window size.
			 * 
			 * \return Renderable size.
			 */
			virtual framework::PointI RenderableSize() const override;

			/**
			 * Set window properties.
			 *
			 * \param title Window title.
			 * \param width Window width. Leave 0 for full desktop size.
			 * \param height Window height. Leave 0 for full desktop size.
			 * \param windowMode How to create the window and if its in fullscreen mode.
			 * \param showCursor Should we show cursor.
			 */
			virtual void SetWindowProperties(const char* title, int width, int height, WindowModes windowMode = WindowModes::Windowed, bool showCursor = true) override;

			/**
			* Set a rendering viewport (will only render inside the given region).
			*
			* \param viewport Viewport to set, or nullptr to remove viewport and render on whole screen.
			*/
			void SetViewport(const framework::RectangleI* viewport) override;

			/**
			 * Set the window's title.
			 *
			 * \param title New title to set.
			 */
			virtual void SetTitle(const char* title) override;

			/**
			 * Set the target we render to.
			 * This enable us to draw on images instead of on screen.
			 *
			 * \param target Target to draw on, or nullptr to clear render target and draw back on screen.
			 */
			virtual void SetRenderTarget(const assets::ImageAsset& target) override;

			/**
			 * Get the currently set render target, or null.
			 *
			 * \return Render target or null.
			 */
			virtual const assets::ImageAsset& GetRenderTarget() const override;

			/**
			 * Start using an effect for next renderings.
			 * 
			 * \param effect Effect to use to null to use default rendering effect.
			 */
			virtual void UseEffect(assets::EffectAsset effect) override;

			/**
			 * Get the currently active effect, or NULL if not set.
			 *
			 * \return Active effect or null if not set.
			 */
			virtual assets::EffectAsset GetActiveEffect() const override;

			/**
			 * Take a screenshot of what's currently presented on screen and return as an image asset.
			 *
			 * \return New image containing whats currently rendered on screen.
			 */
			virtual assets::ImageAsset CreateImageFromScreen() const override;
		};
	}
}