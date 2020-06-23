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
			const char* textStylesheet = config->GetStr("window", "title_style", nullptr);
			if (textStylesheet) { Title->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(textStylesheet).c_str())); }
			Title->SetOffset(config->GetPointF("window", "title_offset", framework::PointF::Zero));
			Title->ExemptFromAutoArrange = true;
			framework::PointF anchor = config->GetPointF("window", "title_anchor", framework::PointF(-1000.0f, -1000.0f));
			if (anchor.X != -1000.0f) { Title->SetAnchor(anchor); }
		}
	}
}