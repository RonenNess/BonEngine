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
			 * Text to show when input is empty.
			 */
			UIText PlaceholderText;

			/**
			 * Is this element currently accepting text input?
			 */
			bool IsReceivingInput = false;

			/**
			 * Set text input value.
			 * 
			 * \param value Text input value.
			 */
			inline void SetValue(const char* value) { Text->SetText(value); }

			/**
			 * Get text input value.
			 */
			inline const char* GetValue() const { return Text->GetText(); }

			/**
			 * Set placeholder text.
			 *
			 * \param value Placeholder text.
			 */
			inline void SetPlaceholderText(const char* value) { PlaceholderText->SetText(value); }

			/**
			 * Get placeholder text.
			 */
			inline const char* GetPlaceholderText() const { return PlaceholderText->GetText(); }

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
			 *				*		- placeholder_style = Stylesheet to use for text placeholder element.
			 *				*		- placeholder_offset = text placeholder offset (x,y).
			 *				*		- placeholder_anchor = if provided, will override text's placeholder anchor (x,y).
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config);

		protected:

			/**
			 * Implement just the drawing of this element
			 */
			virtual void DrawSelf() override;

			/**
			 * Do input updates to interact with element of this specific element.
			 * This happens after the regular updates.
			 *
			 * \param mousePosition Mouse position to test.
			 * \param updateState Contains temporary state about UI input updates.
			 */
			virtual void DoInputUpdatesSelf(const framework::PointI& mousePosition, UIUpdateInputState& updateState) override;
		};
	}
}