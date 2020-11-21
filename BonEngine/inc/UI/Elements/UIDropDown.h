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
		private:

		public:

			/**
			 * Get element type.
			 */
			virtual UIElementType GetType() const override { return UIElementType::DropDown; }

			/**
			 * Optional extra initialization code to apply after creating element.
			 */
			virtual void _Init() override;

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
		};
	}
}