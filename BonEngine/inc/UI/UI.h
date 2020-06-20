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
			 * Create and return a new root element.
			 * \return New element pointer.
			 */
			virtual UIElement CreateRoot() override;

			/**
			 * Create and return an empty container element.
			 *
			 * \param stylesheet Optional stylesheet path to load.
			 * \param parent Optional parent to set.
			 * \return Newly created empty container.
			 */
			virtual UIElement CreateContainer(const char* stylesheet = nullptr, UIElement parent = nullptr) override;

			/**
			 * Create and return an image element.
			 *
			 * \param stylesheet Optional stylesheet path to load.
			 * \param parent Optional parent to set.
			 * \return Newly created image.
			 */
			virtual UIImage CreateImage(const char* stylesheet = nullptr, UIElement parent = nullptr) override;

			/**
			 * Create and return a text element.
			 *
			 * \param stylesheet Optional stylesheet path to load.
			 * \param parent Optional parent to set.
			 * \param text Starting text to set.
			 * \return Newly created text.
			 */
			virtual UIText CreateText(const char* stylesheet = nullptr, UIElement parent = nullptr, const char* text = nullptr) override;

			/**
			 * Create and return a window element.
			 *
			 * \param stylesheet Optional stylesheet path to load.
			 * \param parent Optional parent to set.
			 * \return Newly created window.
			 */
			virtual UIWindow CreateWindow(const char* stylesheet = nullptr, UIElement parent = nullptr, const char* title = nullptr) override;
			
			/**
			 * Create and return a button element.
			 *
			 * \param stylesheet Optional stylesheet path to load.
			 * \param parent Optional parent to set.
			 * \param caption Button caption text.
			 * \return Newly created window.
			 */
			virtual UIButton CreateButton(const char* stylesheet = nullptr, UIElement parent = nullptr, const char* caption = nullptr) override;
			
			/**
			 * Create and return a list element.
			 *
			 * \param stylesheet Optional stylesheet path to load.
			 * \param parent Optional parent to set.
			 * \return Newly created list.
			 */
			virtual UIList CreateList(const char* stylesheet = nullptr, UIElement parent = nullptr) override;

		private:
			
			/**
			 * Get mouse position, relative to current screen / render target / viewport size.
			 */
			PointI GetRelativeCursorPos();

			/**
			 * Init a newly created UI element.
			 */
			void InitNewElement(UIElement element, ConfigAsset stylesheet = nullptr, UIElement parent = nullptr);
			
			/**
			 * Init a newly created UI element.
			 */
			void InitNewElement(UIElement element, const char* stylesheetPath, UIElement parent = nullptr);
			
		};
	}
}