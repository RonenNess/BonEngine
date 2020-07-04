#include <UI/Elements/UIText.h>
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
		// destroy the text.
		_UIText::~_UIText()
		{
			if (_text) { free(_text); }
		}

		// initialize element style from config file.
		void _UIText::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// load basic stylesheet
			_UIElement::LoadStyleFrom(config);

			// load font image
			const char* font = config->GetStr("text", "font_path", nullptr);
			if (font)
			{
				int fontSize = config->GetInt("text", "font_native_size", 24);
				Font = bon::_GetEngine().Assets().LoadFont(ToRelativePath(font).c_str(), fontSize);
			}

			// load font size and alignment
			FontSize = config->GetInt("text", "font_size", 24);
			static const char* alignments[] = { "left", "right", "center" };
			Alignment = (UITextAlignment)config->GetOption("text", "alignment", alignments, 0);

			// load colors
			Color = config->GetColor("text", "color", Color::White);
			ColorHighlight = config->GetColor("text", "color_highlight", Color);
			ColorPressed = config->GetColor("text", "color_pressed", Color);

			// load outline colors
			OutlineColor = config->GetColor("text", "outline_color", Color::White);
			OutlineColorHighlight = config->GetColor("text", "outline_color_highlight", Color);
			OutlineColorPressed = config->GetColor("text", "outline_color_pressed", Color);

			// load outline width
			OutlineWidth = config->GetInt("text", "outline_width", 1);
			OutlineWidthHighlight = config->GetInt("text", "outline_width_highlight", 1);
			OutlineWidthPressed = config->GetInt("text", "outline_width_pressed", 1);
		}

		// set text to draw.
		void _UIText::SetText(const char* text)
		{
			// special case - delete text
			if (!text)
			{
				if (_text) {
					free(_text);
					_text = nullptr;
				}
				return;
			}

			// special case - empty text
			if (text[0] == '\0')
			{
				_text = (char*)realloc(_text, sizeof(char) * 1);
				_text[0] = '\0';
				return;
			}

			// get new string len
			size_t len = strlen(text);

			// realloc / alloc previous buffer and copy string
			_text = (char*)realloc(_text, sizeof(char) * (len + 1));
			strcpy_s(_text, len+1, text);
		}

		// get text we draw.
		const char* _UIText::GetText() const
		{
			return _text;
		}

		// get outline color based on element state.
		const framework::Color& _UIText::GetCurrentStateOutlineColor() const
		{
			switch (_state)
			{
			case UIElementState::Idle:
				return OutlineColor;
			case UIElementState::PointedOn:
				return OutlineColorHighlight;
			case UIElementState::PressedDown:
				return OutlineColorPressed;
			case UIElementState::AltPressedDown:
				return OutlineColorPressed;
			default:
				return Color;
			}
		}

		// get outline width based on current state
		int _UIText::GetCurrentStateOutlineWidth() const
		{
			switch (_state)
			{
			case UIElementState::Idle:
				return OutlineWidth;
			case UIElementState::PointedOn:
				return OutlineWidthHighlight;
			case UIElementState::PressedDown:
				return OutlineWidthPressed;
			case UIElementState::AltPressedDown:
				return OutlineWidthPressed;
			default:
				return OutlineWidth;
			}
		}

		// do updates
		void _UIText::Update(double deltaTime)
		{
			_UIElement::Update(deltaTime);
			DrawOrCalcActualRect(false, true);
		}

		// implement just the drawing of this element
		void _UIText::DrawSelf()
		{
			_UIElement::DrawSelf();
			DrawOrCalcActualRect(true, false);
		}

		// draw text or calc actual dest rect
		void _UIText::DrawOrCalcActualRect(bool draw, bool calcActualRect)
		{
			// skip if no text, font, or empty
			if (_text == nullptr || Font == nullptr || _text[0] == '\0')
			{
				if (calcActualRect) { _actualDestRect.Set(0, 0, 0, 0); }
				return;
			}

			// get color, origin and position
			const framework::Color& color = GetCurrentStateColor();
			PointF origin;
			PointF position((float)_destRect.X, (float)_destRect.Y);

			// set alignment
			switch (Alignment)
			{
			case UITextAlignment::Center:
				origin.X = 0.5f;
				position.X += _destRect.Width / 2;
				break;

			case UITextAlignment::Right:
				origin.X = 1.0f;
				position.X += _destRect.Width;
				break;
			}

			// get outline width
			const framework::Color& outlineColor = GetCurrentStateOutlineColor();
			int outlineWidth = GetCurrentStateOutlineWidth();

			// draw text
			if (draw)
			{
				bon::_GetEngine().Gfx().DrawText(Font,
					_text,
					position,
					&color,
					FontSize,
					_destRect.Width,
					BlendModes::AlphaBlend, &origin,
					0.0f, outlineWidth, &outlineColor);
			}

			// calculate actual dest rect
			if (calcActualRect) {
				_actualDestRect = bon::_GetEngine().Gfx().GetTextBoundingBox(Font, _text, position, FontSize, _destRect.Width, &origin, 0.0f);
			}
		}
	}
}