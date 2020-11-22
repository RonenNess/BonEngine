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

			// temp pointer of self to use as parent
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});

			// load overlay image
			RectangleI overlayRect = config->GetRectangleF("slider", "active_slider_rect", RectangleF(-1, -1, -1, -1));
			if (overlayRect.X != -1)
			{
				_activePartOverlay = bon::_GetEngine().UI().CreateImage(nullptr, tempPtrThatDoesntDelete);
				_activePartOverlay->LoadStyleFrom(config);
				_activePartOverlay->SetSizeInPercents(PointI(100, 100));
				_activePartOverlay->SetAnchor(PointF::Zero);
				_activePartOverlay->SetOffset(PointI::Zero);
				_activePartOverlay->Origin = PointF::Zero;
				_activePartOverlay->Interactive = _activePartOverlay->CaptureInput = false;
				_activePartOverlay->SourceRect = _activePartOverlay->SourceRectHighlight = _activePartOverlay->SourceRectPressed = overlayRect;
			}

			// load handle stuff
			const char* hadleStylesheet = config->GetStr("slider", "handle_style", nullptr);
			if (hadleStylesheet)
			{
				_handle = bon::_GetEngine().UI().CreateImage(ToRelativePath(hadleStylesheet).c_str(), tempPtrThatDoesntDelete);
				_handle->Draggable = false;
				_handle->CaptureInput = false;
			}
		}
		
		// set current slider value.
		void _UISlider::SetValue(int value)
		{
			// make sure in range
			if (value < 0) { value = 0; }
			if (value > MaxValue) { value = MaxValue; }

			// value didn't change? skip
			if (_value == value) { return; }
			
			// set value and trigger callback
			_value = value;
			if (OnValueChange) { OnValueChange(*this, nullptr); }
		}

		// update element
		void _UISlider::DoInputUpdatesSelf(const framework::PointI& mousePosition, UIUpdateInputState& updateState)
		{
			// call base update
			_UIImage::DoInputUpdatesSelf(mousePosition, updateState);

			// update handle position
			float pos = (float)_value / (float)MaxValue;
			auto padding = GetPadding();
			auto destRect = GetCalculatedDestRect();
			_handle->SetOffset(bon::PointI((int)(pos * (destRect.Width - padding.Left - padding.Right)), 0));

			// update active part percent
			if (_activePartOverlay != nullptr)
			{
				_activePartOverlay->SetSizeInPercents(PointI((int)(pos * 100), 100));
				_activePartOverlay->Visible = pos > 0;
				_activePartOverlay->Update(0.1, false);
			}

			// set value
			if (bon::_GetEngine().Input().Down(bon::KeyCodes::MouseLeft) && destRect.Contains(mousePosition))
			{
				int startX = (destRect.X + padding.Left);
				float value = (float)(mousePosition.X - startX) / (destRect.Width - padding.Left - padding.Right - _handle->GetCalculatedDestRect().Width / 2);
				if (value < 0) { value = 0; }
				if (value > 1) { value = 1; }
				SetValue((int)std::floor(value * MaxValue));
			}
		}
	}
}