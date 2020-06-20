#include <UI/Elements/UIWindow.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// optional extra initialization code to apply after creating element.
		void _UIWindow::_Init()
		{
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
			Title = bon::_GetEngine().UI().CreateText(nullptr, tempPtrThatDoesntDelete);
		}

		// initialize element style from config file.
		void _UIWindow::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIImage::LoadStyleFrom(config);

			// load title stuff
			const char* textStylesheet = config->GetStr("window", "title_stylesheet", nullptr);
			if (textStylesheet) { Title->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(textStylesheet)); }
			Title->SetOffset(config->GetPointF("window", "title_offset", framework::PointF::Zero));
			Title->SetAnchor(config->GetPointF("window", "title_anchor", framework::PointF::Zero));
		}
	}
}