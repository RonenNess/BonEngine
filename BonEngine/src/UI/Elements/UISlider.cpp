#include <UI/Elements/UISlider.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// initialize element style from config file.
		void _UISlider::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIImage::LoadStyleFrom(config);

			// load handle stuff
			const char* hadleStylesheet = config->GetStr("slider", "handle_style", nullptr);
			if (hadleStylesheet)
			{
				UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
				_handle = bon::_GetEngine().UI().CreateImage(ToRelativePath(hadleStylesheet).c_str(), tempPtrThatDoesntDelete);
				_handle->Draggable = true;
				_handle->LimitDragToParentArea = true;
			}
			SetValue(0);
		}
		
		// set current slider value.
		void _UISlider::SetValue(int value)
		{
			// make sure in range
			if (value < 0) { value = 0; }
			if (value > MaxValue) { value = MaxValue; }
			
			// set value and position
			_value = value;
			float pos = (float)_value / (float)MaxValue;
			const RectangleI& handlerect = _handle->GetCalculatedDestRect();
			_handle->SetOffset(bon::PointI((int)(pos * (float)(_destRect.Width - GetPadding().Left - GetPadding().Right - handlerect.Width)), 0));

			// make sure in valid range
			_handle->ValidateOffsetInsideParent();
		}

		// update element
		void _UISlider::Update(double deltaTime)
		{
			// call base update
			_UIImage::Update(deltaTime);

			// this will make slider snap to values and validate max
			SetValue(_value);

			// no handle? skip
			if (_handle == nullptr) { return; }

			// on mouse down, set handle
			if (_prevState == UIElementState::PressedDown)
			{
				int x = bon::_GetEngine().Input().CursorPosition().X - _destRect.X - GetPadding().Left;
				_handle->SetOffset(bon::PointI(x, 0));
			}

			// calculate current value
			const RectangleI& handlerect = _handle->GetCalculatedDestRect();
			int newVal = (int)std::ceil(((float)(_handle->GetOffset().X) / (float)(_destRect.Width - handlerect.Width)) * (float)MaxValue);
			SetValue(newVal);
		}
	}
}