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
			virtual void Draw(UIElement root, bool drawCursor) override;

			/**
			 * Update a UI system and to all interactions.
			 *
			 * \param root Root UI element to update.
			 */
			virtual void UpdateUI(UIElement root) override;

			/**
			 * Create and return a new element.
			 *
			 * \param type Element type.
			 * \param stylesheet Optional config asset to load styles from.
			 * \param parent Optional parent to attach element to.
			 * \return New element pointer.
			 */
			virtual UIElement Create(UIElementTypes type, ConfigAsset stylesheet = nullptr, UIElement parent = nullptr) override;

			/**
			 * Create and return a new element.
			 *
			 * \param type Element type.
			 * \param stylesheetPath Optional config asset path to load styles from.
			 * \param parent Optional parent to attach element to.
			 * \return New element pointer.
			 */
			virtual UIElement Create(UIElementTypes type, const char* stylesheetPath, UIElement parent = nullptr) override;

		private:
			/**
			 * Get mouse position, relative to current screen / render target / viewport size.
			 */
			PointI GetRelativeCursorPos();
		};
	}
}