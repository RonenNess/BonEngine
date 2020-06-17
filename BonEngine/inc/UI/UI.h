/*****************************************************************//**
 * \file   UI.h
 * \brief  The default ui manager implemented by BonEngine.
 *
 * \author Ronen Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "IUI.h"


namespace bon
{
	namespace ui
	{
		/**
		 * Default ui manager.
		 */
		class BON_DLLEXPORT UI : public IUI
		{
		private:
			// cursor sprite to draw
			gfx::Sprite _cursor;

		public:

			/**
			 * Set cursor to render.
			 *
			 * \param image Cursor image.
			 * \param size Cursor drawing size.
			 * \param offset Cursor image offset from cursor position.
			 */
			virtual void SetCursor(const assets::ImageAsset& image, framework::PointI size, framework::PointI offset) override;

			/**
			 * Set cursor to render from sprite.
			 *
			 * \param sprite Sprite to draw as cursor.
			 */
			virtual void SetCursor(const gfx::Sprite& sprite) override;

			/**
			 * Draw cursor, based on what set with SetCursor().
			 */
			virtual void DrawCursor() override;

			/**
			 * Draw a UI system or element.
			 *
			 * \param root Root UI element to draw.
			 * \param drawCursor Set to true to draw cursor (will just call DrawCursor() internally).
			 */
			virtual void Draw(UIElementPtr root, bool drawCursor) override;

		private:
			/**
			 * Get mouse position, relative to current screen / render target / viewport size.
			 */
			PointI GetRelativeCursorPos();
		};
	}
}