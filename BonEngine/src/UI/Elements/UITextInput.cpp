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
			Text = bon::_GetEngine().UI().CreateText(nullptr, tempPtrThatDoesntDelete);
		}

		// initialize element style from config file.
		void _UITextInput::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIImage::LoadStyleFrom(config);

			// load title stuff
			const char* textStylesheet = config->GetStr("text_input", "text_style", nullptr);
			if (textStylesheet) { Text->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(textStylesheet).c_str())); }
			Text->SetOffset(config->GetPointF("text_input", "text_offset", framework::PointF::Zero));
			Text->ExemptFromAutoArrange = true;
			framework::PointF anchor = config->GetPointF("text_input", "text_anchor", framework::PointF(-1000.0f, -1000.0f));
			if (anchor.X != -1000.0f) { Text->SetAnchor(anchor); }
		}
	}
}