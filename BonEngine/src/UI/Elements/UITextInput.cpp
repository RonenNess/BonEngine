#include <UI/Elements/UITextInput.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>
#include <algorithm>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// optional extra initialization code to apply after creating element.
		void _UITextInput::_Init()
		{
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
			
			Text = bon::_GetEngine().UI().CreateText(nullptr, tempPtrThatDoesntDelete, "");
			Text->WordWrap = false;

			PlaceholderText = bon::_GetEngine().UI().CreateText(nullptr, tempPtrThatDoesntDelete, "");
			PlaceholderText->WordWrap = false;
		}

		// initialize element style from config file.
		void _UITextInput::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIImage::LoadStyleFrom(config);

			// load caret character
			CaretCharacter = config->GetStr("text_input", "caret", "|")[0];
			CaretBlinkingInterval = config->GetFloat("text_input", "caret_blink_interval", 1.0f);

			// some flags
			AllowTabs = config->GetBool("text_input", "allow_tabs", true);

			// load text styles
			const char* textStylesheet = config->GetStr("text_input", "text_style", nullptr);
			if (textStylesheet) { Text->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(textStylesheet).c_str())); }
			Text->SetOffset(config->GetPointF("text_input", "text_offset", framework::PointF::Zero));
			Text->ExemptFromAutoArrange = true;
			framework::PointF anchor = config->GetPointF("text_input", "text_anchor", framework::PointF(-1000.0f, -1000.0f));
			if (anchor.X != -1000.0f) { Text->SetAnchor(anchor); }

			// load placeholder styles
			textStylesheet = config->GetStr("text_input", "placeholder_style", nullptr);
			if (textStylesheet) { PlaceholderText->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(textStylesheet).c_str())); }
			PlaceholderText->SetOffset(config->GetPointF("text_input", "placeholder_offset", framework::PointF::Zero));
			PlaceholderText->ExemptFromAutoArrange = true;
			anchor = config->GetPointF("text_input", "placeholder_anchor", framework::PointF(-1000.0f, -1000.0f));
			if (anchor.X != -1000.0f) { PlaceholderText->SetAnchor(anchor); }
		}

		// do text input updates
		void _UITextInput::Update(double deltaTime)
		{
			// check if should finish input
			if (_isReceivingInput)
			{
				// pressed enter
				if (bon::_GetEngine().Input().ReleasedNow(bon::KeyCodes::KeyReturn))
				{
					_isReceivingInput = false;
				}
				// clicked outside
				else if (bon::_GetEngine().Input().PressedNow(bon::KeyCodes::MouseLeft))
				{
					auto mousePosition = bon::_GetEngine().UI()._GetRelativeCursorPos();
					_isReceivingInput = GetCalculatedDestRect().Contains(mousePosition);
				}
			}
			// check if we should start recieving input
			else
			{
				if (_state == UIElementState::PressedDown || _state == UIElementState::AltPressedDown)
				{
					_isReceivingInput = true;
				}
			}

			// set active mode if recieving update
			ForceActiveState = _isReceivingInput;

			// get text input
			if (_isReceivingInput)
			{
				GetTextInput();
			}	

			// call base input updates
			_UIImage::Update(deltaTime);
		}

		// get text input
		void _UITextInput::GetTextInput()
		{
			// get text input
			bool wasChanged = false;
			const bon::TextInputData& textData = bon::_GetEngine().Input().GetTextInput();

			// add input
			if (strlen(textData.Text) > 0)
			{
				_value.append(textData.Text);
				wasChanged = true;
			}

			// add tab
			if (AllowTabs && textData.Tab)
			{
				_value.append("    ");
				wasChanged = true;
			}

			// handle backspace
			if (textData.Backspace && _value.length() > 0)
			{
				_value.pop_back();
				wasChanged = true;
			}

			// update value
			if (wasChanged)
			{
				ValidateValue();
				Text->SetText(_value.c_str());
				if (OnValueChange) { OnValueChange(*this, nullptr); }
			}
		}

		// set text input value
		void _UITextInput::SetValue(const char* value)
		{
			_value = std::string(value);
			ValidateValue();
			Text->SetText(_value.c_str());
			if (OnValueChange) { OnValueChange(*this, nullptr); }
		}

		// get if a text input mode is set
		#define bon_is_text_mode_set(__flag)  (((int)InputMode & (int)__flag) != 0)

		// validate input and fix _value if needed
		void _UITextInput::ValidateValue()
		{
			// only numbers
			if (bon_is_text_mode_set(UITextInputMode::NumbersOnly) && !bon_is_text_mode_set(UITextInputMode::AlphaOnly))
			{
				_value.erase(std::remove_if(std::begin(_value), std::end(_value),
					[](auto ch) { return !std::isdigit(ch); }),
					_value.end());
			}

			// no numbers
			if (bon_is_text_mode_set(UITextInputMode::NoNumbers))
			{
				_value.erase(std::remove_if(std::begin(_value), std::end(_value),
					[](auto ch) { return std::isdigit(ch); }),
					_value.end());
			}

			// uppercase
			if (bon_is_text_mode_set(UITextInputMode::Uppercase))
			{
				std::transform(_value.begin(), _value.end(), _value.begin(), ::toupper);
			}

			// lowercase
			if (bon_is_text_mode_set(UITextInputMode::Lowercase))
			{
				std::transform(_value.begin(), _value.end(), _value.begin(), ::tolower);
			}

			// alpha only
			if (bon_is_text_mode_set(UITextInputMode::AlphaOnly))
			{
				// alpha and numbers combo:
				if (bon_is_text_mode_set(UITextInputMode::NumbersOnly))
				{
					_value.erase(std::remove_if(std::begin(_value), std::end(_value),
						[](auto ch) { return !std::isalnum(ch); }),
						_value.end());
				}
				// alpha only
				else
				{
					_value.erase(std::remove_if(std::begin(_value), std::end(_value),
						[](auto ch) { return !std::isalpha(ch); }),
						_value.end());
				}
			}

			// no line breaks
			_value.erase(std::remove_if(std::begin(_value), std::end(_value),
				[](auto ch) { return ch == '\n' || ch == '\r'; }),
				_value.end());
			
			// validate length
			if (MaxLength && (int)_value.length() > MaxLength)
			{
				_value = _value.substr(0, MaxLength);
			}
		}

		// implement just the drawing of this element
		void _UITextInput::DrawSelf()
		{
			_UIImage::DrawSelf();
			
			// set placeholder visibility
			PlaceholderText->Visible = !_isReceivingInput && (GetValue()[0] == '\0');

			// draw caret mark
			if (_isReceivingInput)
			{
				if (_showCaret)
				{
					bon::RectangleI textDest = Text->GetActualDestRect();
					char caret[2] = { CaretCharacter, '\0' };
					bon::_GetEngine().Gfx().DrawText(Text->Font, caret,
						bon::PointI(textDest.Right(), textDest.Top()),
						&Text->Color, Text->FontSize, 0, bon::BlendModes::AlphaBlend,
						&bon::PointF::Zero, 0, Text->OutlineWidth, &Text->OutlineColor);
				}
				_timeForCaretBlink += (float)bon::_GetEngine().Game().DeltaTime();
				if (_timeForCaretBlink >= CaretBlinkingInterval)
				{
					_timeForCaretBlink = 0.0f;
					_showCaret = !_showCaret;
				}
			}
		}
	}
}