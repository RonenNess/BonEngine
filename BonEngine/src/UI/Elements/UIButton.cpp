#include <UI/Elements/UIButton.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// optional extra initialization code to apply after creating element.
		void _UIButton::_Init()
		{
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
			Caption = bon::_GetEngine().UI().CreateText(nullptr, tempPtrThatDoesntDelete);
		}

		// initialize element style from config file.
		void _UIButton::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIImage::LoadStyleFrom(config);

			// load title stuff
			const char* textStylesheet = config->GetStr("button", "caption_style", nullptr);
			if (textStylesheet) { Caption->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(textStylesheet).c_str())); }
			Caption->SetOffset(config->GetPointF("button", "caption_offset", framework::PointF::Zero));
			framework::PointF anchor = config->GetPointF("button", "caption_anchor", framework::PointF(-1000.0f, -1000.0f));
			if (anchor.X != -1000.0f) { Caption->SetAnchor(anchor); }
		}
	}
}