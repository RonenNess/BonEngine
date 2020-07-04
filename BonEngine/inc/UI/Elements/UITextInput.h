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
#include "../../Input/Defs.h"

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
			 * Character to use for caret position.
			 */
			char CaretCharacter = '|';

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
			 * Determine the speed of the caret blinking animation.
			 */
			float CaretBlinkingInterval = 1.0f;

			/**
			 * Is this element currently accepting text input?
			 */
			bool IsReceivingInput = false;

			/**
			 * Set text input value.
			 * 
			 * \param value Text input value.
			 */
			inline void SetValue(const char* value) { Text->SetText(value); _value = std::string(value); }

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
			 *				*		- caret = Caret character to use to indicate text position.
			 *				*		- caret_blink_interval = Caret blinking animation interval.
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

			/**
			 * Implement the part of getting text input from user.
			 * You can use this to support different languages or change the way you recieve input.
			 */
			virtual void GetTextInput();

			/**
			 * Check key input.
			 * This also implement short delay after first press and following characters while holding key down.
			 */
			virtual bool CheckKeyInput(bon::input::KeyCodes key);

		private:

			// store value as string to optimize setting it
			std::string _value;

			// for caret blinking animation
			bool _showCaret = true;
			float _timeForCaretBlink = 0.0f;
		};
	}
}