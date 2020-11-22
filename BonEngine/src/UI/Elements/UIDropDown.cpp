#include <UI/Elements/UIDropDown.h>
#include <UI/Elements/UIList.h>
#include <BonEngine.h>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// optional extra initialization code to apply after creating element.
		void _UIDropDown::_Init()
		{
			// init base list stuff
			_UIList::_Init();
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});

			// create selected text element
			SelectedText = bon::_GetEngine().UI().CreateText(nullptr, tempPtrThatDoesntDelete, "");
			SelectedText->WordWrap = false;

			// create selected text background
			SelectedTextBackground = bon::_GetEngine().UI().CreateImage(nullptr, tempPtrThatDoesntDelete);
		}

		// initialize element style from config file.
		void _UIDropDown::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIList::LoadStyleFrom(config);

			// load text styles
			const char* textStylesheet = config->GetStr("selected_text", "text_style", nullptr);
			if (textStylesheet) { SelectedText->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(textStylesheet).c_str())); }
			SelectedText->SetOffset(config->GetPointF("selected_text", "text_offset", framework::PointF::Zero));
			SelectedText->ExemptFromAutoArrange = true;
			framework::PointF anchor = config->GetPointF("selected_text", "text_anchor", framework::PointF(-1000.0f, -1000.0f));
			if (anchor.X != -1000.0f) { SelectedText->SetAnchor(anchor); }

			// load selected text background style
			SelectedTextBackground->LoadStyleFrom(config);
		}
	}
}