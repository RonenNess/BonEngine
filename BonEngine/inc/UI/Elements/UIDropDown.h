/*****************************************************************//**
 * \file   UIDropDown.h
 * \brief  A UI dropdown you can pick elements from.
 *
 * \author Ronen Ness
 * \date   November 2020
 *********************************************************************/
#pragma once
#include "UIList.h"

namespace bon
{
	namespace ui
	{

#pragma warning ( push )
#pragma warning ( disable: 4251 ) // "..needs to have dll-interface to be used by clients..." it's ok in this case because its private.

		/**
		 * A UI dropdown.
		 * This is just like a UI list, but it collapse to take less room when not used.
		 */
		class BON_DLLEXPORT _UIDropDown : public _UIList
		{
		public:

			/**
			 * Currently selected item text.
			 */
			UIText SelectedText;
			
			/**
			 * Selected text background image.
			 */
			UIImage SelectedTextBackground;

			/**
			 * Placeholder text when no item is selected.
			 */
			const char* PlaceholderText;

			/**
			 * Get element type.
			 */
			virtual UIElementType GetType() const override { return UIElementType::DropDown; }

			/**
			 * Optional extra initialization code to apply after creating element.
			 */
			virtual void _Init() override;

			/**
			 * Get the actual destination rect as calculated by the Update() method.
			 * This would usually be the same as GetCalculatedDestRect(), but might be different for some UI elements.
			 */
			virtual framework::RectangleI GetActualDestRect() const { return SelectedTextBackground->GetActualDestRect(); }

			/**
			 * Initialize element style from config file.
			 *
			 * \param config Config file to init element from.
			 *				* In addition to all the settings from UIElement and UIImage stylesheet files, you can add the following:
			 *				*	[list]
			 *				*		- list_background_style = Stylesheet to use for list background window (UIWindow).
			 *				*		- item_background_style = Stylesheet to use for list item background image (UIImage).
			 *				*		- items_style = Stylesheet to use for text items in list.
			 *				*		- line_height = Height, in pixels, of a single line in list.
			 *				*		- vscrollbar_style = Stylesheet for list vertical scrollbar (UIVerticalScrollbar).
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config) override;

			/**
			 * Draw ui element and children.
			 */
			virtual void Draw(bool topLayer) override;

			/**
			 * Get if this dropdown is currently opened.
			 */
			inline bool IsOpened() const { return _isOpened; }
			
			/**
			 * Set if to draw as top layer this element and all its children, recursively.
			 */
			virtual void SetDrawAsTopLayerRecursive(bool drawTopLayer) override;

			/**
			 * Show / hide the list part of this dropdown.
			 * 
			 * \param show True to show dropdown list, false to hide it.
			 */
			void ShowDropdownList(bool show);

			/**
			 * Selet list item by index.
			 *
			 * \param index Index to select, or -1 to clear selection.
			 */
			virtual void Select(int index) override;

			/**
			 * Selet list item by value (if duplications exist, will select first item found.
			 *
			 * \param item Item value to select, or nullptr to clear selection.
			 */
			virtual void Select(const char* item) override;

			/**
			 * Do input updates to interact with element.
			 * This happens after the regular updates.
			 *
			 * \param mousePosition Mouse position to test.
			 * \param updateState Contains temporary state about UI input updates.
			 * \param topLayer True when we update top layer elements.
			 */
			virtual void DoInputUpdates(const framework::PointI& mousePosition, UIUpdateInputState& updateState, bool topLayer) override;

		protected:

			// is the dropdown currently opened / visible
			bool _isOpened;

			/**
			 * Implement just the updating of this element
			 *
			 * \param deltaTime Update frame delta time.
			 */
			virtual void UpdateSelf(double deltaTime) override;
		};
	}
}