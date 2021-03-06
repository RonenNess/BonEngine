/*****************************************************************//**
 * \file   IGfx.h
 * \brief  Define the API for the Gfx manager class.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "../IManager.h"
#include "../Assets/Types/Image.h"
#include "../Framework/Point.h"
#include "../Framework/Color.h"
#include "../Framework/Rectangle.h"
#include "Defs.h"
#include "Sprite.h"
#include "SpriteSheet.h"

namespace bon
{
	namespace gfx
	{
		using namespace bon::assets;
		using namespace bon::framework;

		/**
		 * Interface for the GFX rendering manager.
		 * This manager responsible to do all the rendering / graphic jobs.
		 */
		class BON_DLLEXPORT IGfx : public IManager
		{
		public:

			/**
			 * Bring the main window forward and focus input on it.
			 */
			virtual void FocusWindow() = 0;

			/**
			 * Draw an image on screen.
			 *
			 * \param sourceImage Source image to draw.
			 * \param position Image position.
			 * \param size Image target size. Negative values will flip image.
			 * \param blend How to blend the image with previous renders.
			 */
			virtual void DrawImage(const assets::ImageAsset& sourceImage, const framework::PointF& position, const framework::PointI* size = nullptr, BlendModes blend = BlendModes::AlphaBlend) = 0;

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
			virtual void DrawImage(const assets::ImageAsset& sourceImage, const framework::PointF& position, const framework::PointI* size, BlendModes blend, const framework::RectangleI* sourceRect, const PointF* origin, float rotation, const Color* color) = 0;

			/**
			 * Draw a sprite.
			 * 
			 * \param sprite Sprite to draw.
			 * \param offset Position offset to add without affecting sprite, useful for camera implementation.
			 */
			virtual void DrawSprite(const Sprite& sprite, const framework::PointF* offset = nullptr) = 0;

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
			virtual void DrawText(const assets::FontAsset& font, const char* text, const framework::PointF& position, const Color* color = nullptr, int fontSize = 0, int maxWidth = 0, BlendModes blend = BlendModes::AlphaBlend, const PointF* origin = nullptr, float rotation = 0.0f, int outlineWidth = 0, const Color* outlineColor = nullptr) = 0;

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
			virtual RectangleI GetTextBoundingBox(const assets::FontAsset& font, const char* text, const framework::PointF& position, int fontSize = 0, int maxWidth = 0, const PointF* origin = nullptr, float rotation = 0.0f) = 0;

			/**
			 * Draws a line.
			 *
			 * \param from Line start.
			 * \param to Line end.
			 * \param color Line color.
			 * \param blendMode Drawing shape blending mode.
			 */
			virtual void DrawLine(const framework::PointI& from, const framework::PointI& to, const framework::Color& color, BlendModes blendMode = BlendModes::AlphaBlend) = 0;

			/**
			 * Draws a pixel.
			 *
			 * \param position Pixel position.
			 * \param color Pixel color.
			 * \param blendMode Drawing shape blending mode.
			 */
			virtual void DrawPixel(const framework::PointI& position, const framework::Color& color, BlendModes blendMode = BlendModes::AlphaBlend) = 0;

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
			virtual void DrawRectangle(const framework::RectangleI& rect, const framework::Color& color, bool filled, BlendModes blendMode = BlendModes::AlphaBlend, const PointF* origin = nullptr, float rotation = 0.0f) = 0;
			
			/**
			 * Draws a circle.
			 *
			 * \param center Circle center.
			 * \param radius Circle radius.
			 * \param color Circle color.
			 * \param filled If true, will draw filled circle. If false, will draw only outline.
			 * \param blendMode Drawing shape blending mode.
			 */
			virtual void DrawCircle(const framework::PointI& center, int radius, const framework::Color& color, bool filled, BlendModes blendMode = BlendModes::AlphaBlend) = 0;

			/**
			 * Draws a 2d polygon.
			 * 
			 * \param a Polygon vertex #1.
			 * \param b Polygon vertex #2.
			 * \param c Polygon vertex #3.
			 * \param color fill color.
			 * \param blend blend mode.
			 */
			virtual void DrawPolygon(const framework::PointI& a, const framework::PointI& b, const framework::PointI& c, const framework::Color& color, BlendModes blend = BlendModes::AlphaBlend) = 0;

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
			virtual void DrawQuad(const framework::PointI& a, const framework::PointI& b, const framework::PointI& c, const framework::PointI& d, const framework::Color& color, BlendModes blend = BlendModes::AlphaBlend) = 0;

			/**
			 * Clear the entire or part of the screen.
			 * 
			 * \param color Clear color (will paint whole screen with this color).
			 * \param clearRect Set what part of the screen you want to clear. Leave it 0,0,0,0 for whole screen.
			 */
			virtual void ClearScreen(const Color& color = Color(0,0,0,0), const RectangleI& clearRect = RectangleI(0,0,0,0)) = 0;

			/**
			 * Set window properties.
			 * 
			 * \param title Window title.
			 * \param width Window width. Leave 0 for full desktop size.
			 * \param height Window height. Leave 0 for full desktop size.
			 * \param windowMode How to create the window and if its in fullscreen mode.
			 * \param showCursor Should we show cursor.
			 */
			virtual void SetWindowProperties(const char* title, int width, int height, WindowModes windowMode = WindowModes::Windowed, bool showCursor = true) = 0;

			/**
			 * Set the window's title.
			 * 
			 * \param title New title to set.
			 */
			virtual void SetTitle(const char* title) = 0;

			/**
			 * Set the target we render to. 
			 * This enable us to draw on images instead of on screen.
			 * 
			 * \param target Target to draw on, or nullptr to clear render target and draw back on screen.
			 */
			virtual void SetRenderTarget(const assets::ImageAsset& target) = 0;

			/**
			 * Get the currently set render target, or null.
			 * 
			 * \return Render target or null.
			 */
			virtual const assets::ImageAsset& GetRenderTarget() const = 0;

			/**
			* Set a rendering viewport (will only render inside the given region).
			*
			* \param viewport Viewport to set, or nullptr to remove viewport and render on whole screen.
			*/
			virtual void SetViewport(const framework::RectangleI* viewport) = 0;

			/**
			 * Get window's size in pixels.
			 * 
			 * \return Window size.
			 */
			virtual const framework::PointI& WindowSize() const = 0;

			/**
			 * Get the size in pixels we can draw on.
			 * - If viewport is set, will return viewport size.
			 * - If target texture is set, will return texture size.
			 * - If none of the above is set, will return window size.
			 *
			 * \return Renderable size.
			 */
			virtual framework::PointI RenderableSize() const = 0;

			/**
			 * Start using an effect for next renderings.
			 *
			 * \param effect Effect to use to null to use default rendering effect.
			 */
			virtual void UseEffect(assets::EffectAsset effect) = 0;

			/**
			 * Get the currently active effect, or NULL if not set.
			 * 
			 * \return Active effect or null if not set.
			 */
			virtual assets::EffectAsset GetActiveEffect() const = 0;

			/**
			 * Take a screenshot of what's currently presented on screen and return as an image asset.
			 *
			 * \return New image containing whats currently rendered on screen.
			 */
			virtual assets::ImageAsset CreateImageFromScreen() const = 0;

		protected:

			/**
			 * Get manager identifier.
			 */
			virtual const char* _GetId() const override { return "gfx"; }
		};
	}
}