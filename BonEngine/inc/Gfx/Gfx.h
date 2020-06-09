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
			 */
			virtual void DrawText(const assets::FontAsset& font, const char* text, const framework::PointF& position, const Color* color = nullptr, int fontSize = 0, int maxWidth = 0, BlendModes blend = BlendModes::AlphaBlend, const PointF* origin = nullptr, float rotation = 0.0f) override;

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
			 */
			virtual void DrawRectangle(const framework::RectangleI& rect, const framework::Color& color, bool filled, BlendModes blendMode = BlendModes::AlphaBlend) override;

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
			virtual const framework::PointI& WindowSize() const;

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
		};
	}
}