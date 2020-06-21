#include <UI/Elements/UICheckBox.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// optional extra initialization code to apply after creating element.
		void _UICheckBox::_Init()
		{
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
			Caption = bon::_GetEngine().UI().CreateText(nullptr, tempPtrThatDoesntDelete);
		}

		// initialize element style from config file.
		void _UICheckBox::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIImage::LoadStyleFrom(config);

			// load title stuff
			const char* textStylesheet = config->GetStr("checkbox", "caption_style", nullptr);
			if (textStylesheet) { Caption->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(textStylesheet).c_str())); }
			Caption->SetOffset(config->GetPointF("checkbox", "caption_offset", framework::PointF::Zero));
			framework::PointF anchor = config->GetPointF("checkbox", "caption_anchor", framework::PointF(-1000.0f, -1000.0f));
			if (anchor.X != -1000.0f) { Caption->SetAnchor(anchor); }
		}

		// do self updates
		void _UICheckBox::DoInputUpdatesSelf(const framework::PointI& mousePosition, UIUpdateInputState& updateState)
		{
			// call base updates
			_UIImage::DoInputUpdatesSelf(mousePosition, updateState);

			// check if should toggle
			if (_destRect.Contains(mousePosition) && bon::_GetEngine().Input().ReleasedNow(bon::KeyCodes::MouseLeft))
			{
				Toggle();
			}
			
			// change display if checked
			ForceActiveState = _checked;
		}

		// set value
		void _UICheckBox::SetValue(bool checked) 
		{ 
			if (checked != _checked) 
			{ 
				_checked = checked; 
				if (OnValueChange) { OnValueChange(*this, nullptr); }
			} 
			ForceActiveState = checked;
		}
	}
}