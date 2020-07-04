#include <UI/Elements/UITextInput.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>

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
			PlaceholderText = bon::_GetEngine().UI().CreateText(nullptr, tempPtrThatDoesntDelete, "");
		}

		// initialize element style from config file.
		void _UITextInput::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIImage::LoadStyleFrom(config);

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
		void _UITextInput::DoInputUpdatesSelf(const framework::PointI& mousePosition, UIUpdateInputState& updateState)
		{
			// call base input updates
			_UIImage::DoInputUpdatesSelf(mousePosition, updateState);

			// check if should finish input
			if (IsReceivingInput)
			{
				// pressed enter
				if (bon::_GetEngine().Input().ReleasedNow(bon::KeyCodes::KeyReturn))
				{
					IsReceivingInput = false;
				}
				// clicked outside
				else if (updateState.ElementPointedOn != this && bon::_GetEngine().Input().ReleasedNow(bon::KeyCodes::MouseLeft))
				{
					IsReceivingInput = false;
				}
			}
			// check if we should start recieving input
			else
			{
				if (_state == UIElementState::PressedDown || _state == UIElementState::AltPressedDown)
				{
					IsReceivingInput = true;
				}
			}

			// set active mode if recieving update
			ForceActiveState = IsReceivingInput;
		}

		// implement just the drawing of this element
		void _UITextInput::DrawSelf()
		{
			_UIImage::DrawSelf();
			
			// set placeholder visibility
			PlaceholderText->Visible = !IsReceivingInput && (GetValue()[0] == '\0');
		}
	}
}