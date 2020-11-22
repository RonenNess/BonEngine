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

			// set if opened
			_isOpened = false;
			
			// create selected text background
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
			SelectedTextBackground = bon::_GetEngine().UI().CreateImage(nullptr, tempPtrThatDoesntDelete);

			// create selected text element
			SelectedText = bon::_GetEngine().UI().CreateText(nullptr, SelectedTextBackground, "");
			SelectedText->WordWrap = false;
		}

		// initialize element style from config file.
		void _UIDropDown::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIList::LoadStyleFrom(config);

			// load text styles
			const char* textStylesheet = config->GetStr("selected_text", "text_style", nullptr);
			if (textStylesheet) { 
				SelectedText->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(textStylesheet).c_str())); 
			}
			SelectedText->SetOffset(config->GetPointF("selected_text", "text_offset", framework::PointF::Zero));
			SelectedText->ExemptFromAutoArrange = true;
			framework::PointF anchor = config->GetPointF("selected_text", "text_anchor", framework::PointF(-1000.0f, -1000.0f));
			if (anchor.X != -1000.0f) { SelectedText->SetAnchor(anchor); }

			// load selected text background style
			const char* textBackgroundStylesheet = config->GetStr("selected_text", "background_style", nullptr);
			if (textBackgroundStylesheet) { 
				SelectedTextBackground->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(textBackgroundStylesheet).c_str())); 
			}
		}

		// do self updates
		void _UIDropDown::UpdateSelf(double deltaTime)
		{
			// update selected text
			auto newSelected = SelectedItem();
			auto currentSelected = SelectedText->GetText();
			if ((newSelected && !currentSelected) || (!newSelected && currentSelected) || 
				(newSelected && (strcmp(SelectedText->GetText(), newSelected) != 0))) {
				SelectedText->SetText(newSelected);
			}

			// call base updates
			_UIList::UpdateSelf(deltaTime);
		}

		// draw ui element and children.
		void _UIDropDown::Draw(bool topLayer)
		{
			// draw selected
			SelectedTextBackground->Draw(topLayer);

			// draw list part
			if (DrawAsTopLayer() == topLayer)
			{
				int selectedHeight = SelectedTextBackground->GetActualDestRect().Height;
				Background->_ExtraPixelsOffset.Y = selectedHeight;
				_UIList::Draw(topLayer);
			}
		}
	}
}