/*****************************************************************//**
 * \file   UITextInput.h
 * \brief  A one-liner UI text input.
 *
 * \author Ronen Ness
 * \date   July 2020
 *********************************************************************/
#pragma once
#include "UIImage.h"
#include "UIText.h"

namespace bon
{
	namespace ui
	{

#pragma warning ( push )
#pragma warning ( disable: 4251 ) // "..needs to have dll-interface to be used by clients..." it's ok in this case because its private.

		/**
		 * A UI text input element to get single-line texts from users.
		 */
		class BON_DLLEXPORT _UITextInput : public _UIImage
		{
		public:

			/**
			 * Get element type.
			 */
			virtual UIElementType GetType() const override { return UIElementType::TextInput; }

			/**
			 * Text element.
			 */
			UIText Text;

			/**
			 * Optional extra initialization code to apply after creating element.
			 */
			virtual void _Init() override;

			/**
			 * Initialize element style from config file.
			 *
			 * \param config Config file to init element from.
			 *				* In addition to all the settings from UIElement and UIImage stylesheet files, you can add the following:
			 *				*	[text_input]
			 *				*		- text_style = Stylesheet to use for text element.
			 *				*		- text_offset = text offset (x,y).
			 *				*		- text_anchor = if provided, will override text's text anchor (x,y).
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config);
		};
	}
}