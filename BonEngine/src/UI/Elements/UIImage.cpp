#include <UI/Elements/UIImage.h>
#include <Framework/Exceptions.h>
#include <Framework/Point.h>
#include <Framework/Color.h>
#include <Framework/Rectangle.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// get source rect by current state
		const framework::RectangleI& _UIImage::GetCurrentStateSourceRect() const
		{
			switch (_state)
			{
			case UIElementState::Idle:
				return SourceRect;
			case UIElementState::PointedOn:
				return SourceRectHighlight;
			case UIElementState::PressedDown:
				return SourceRectPressed;
			case UIElementState::AltPressedDown:
				return SourceRectPressed;
			default:
				return SourceRect;
			}
		}

		// initialize element style from config file.
		void _UIImage::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// load basic stylesheet
			_UIElement::LoadStyleFrom(config);

			// load source image
			const char* img = config->GetStr("image", "image_path", nullptr);
			if (img) { Image = bon::_GetEngine().Assets().LoadImage(img); }

			// load colors
			Color = config->GetColor("image", "color", Color::White);
			ColorHighlight = config->GetColor("image", "color_highlight", Color);
			ColorPressed = config->GetColor("image", "color_pressed", Color);

			// load source rects
			SourceRect = config->GetRectangleF("image", "source_rect", RectangleF::Zero);
			SourceRectHighlight = config->GetRectangleF("image", "source_rect_highlight", SourceRect);
			SourceRectPressed = config->GetRectangleF("image", "source_rect_pressed", SourceRect);

			// load blend modes
			BlendMode = (BlendModes)config->GetInt("image", "blend", (int)BlendModes::AlphaBlend);
		}

		// implement just the drawing of this element.
		void _UIImage::DrawSelf()
		{
			_UIElement::DrawSelf();

			// skip if no image is set
			if (Image == nullptr) { return; }

			// draw image
			const bon::Color& color = GetCurrentStateColor();
			const RectangleI sourceRect = GetCurrentStateSourceRect();
			bon::_GetEngine().Gfx().DrawImage(Image, 
				PointF((float)_destRect.X, (float)_destRect.Y),
				&PointI(_destRect.Width, _destRect.Height), 
				BlendMode, 
				&sourceRect, 
				&PointF::Zero, 0.0f, &color);
		}
	}
}