#include <UI/Elements/UIVerticalScrollbar.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// initialize element style from config file.
		void _UIVerticalScrollbar::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIImage::LoadStyleFrom(config);

			// load handle stuff
			const char* hadleStylesheet = config->GetStr("scrollbar", "handle_style", nullptr);
			if (hadleStylesheet) 
			{
				UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
				_handle = bon::_GetEngine().UI().CreateImage(ToRelativePath(hadleStylesheet).c_str(), tempPtrThatDoesntDelete);
				_handle->Draggable = true;
				_handle->LimitDragToParentArea = true;
			}
		}

		// update element
		void _UIVerticalScrollbar::Update(double deltaTime)
		{
			// call base update
			_UIImage::Update(deltaTime);

			// no handle? skip
			if (_handle == nullptr) { return; }

			// get dest rect
			auto destRect = GetCalculatedDestRect();

			// on mouse down, set handle
			if (_prevState == UIElementState::PressedDown)
			{
				int y = bon::_GetEngine().Input().CursorPosition().Y - destRect.Y - GetPadding().Top - _handle->GetCalculatedDestRect().Height / 2;
				_handle->SetOffset(bon::PointI(0, y));
				_handle->ValidateOffsetInsideParent();
			}

			// calculate current value
			const RectangleI& handlerect = _handle->GetCalculatedDestRect();
			_value = (int)std::ceil(((float)(_handle->GetOffset().Y) / (float)(destRect.Height - handlerect.Height)) * (float)MaxValue);
		}
	}
}