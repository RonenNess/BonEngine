#include <UI/Elements/UIRectangle.h>
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
		// initialize element style from config file.
		void _UIRectangle::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// load basic stylesheet
			_UIElement::LoadStyleFrom(config);

			// load colors
			Color = config->GetColor("rectangle", "color", Color::White);
			ColorHighlight = config->GetColor("rectangle", "color_highlight", Color);
			ColorPressed = config->GetColor("rectangle", "color_pressed", Color);

			// load blend modes
			static const char* blendOptions[] = { "opaque", "alpha", "mod", "darken", "multiply", "screen", "invert", "difference", "lighten", "additive", "subtract" };
			BlendMode = (BlendModes)config->GetOption("rectangle", "blend", blendOptions, (int)BlendModes::AlphaBlend);

			// load if rect is filled
			Filled = config->GetBool("rectangle", "filled", true);
		}

		// implement just the drawing of this element
		void _UIRectangle::DrawSelf()
		{
			const bon::Color& color = GetCurrentStateColor();
			bon::_GetEngine().Gfx().DrawRectangle(GetCalculatedDestRect(), color, Filled, BlendMode);
		}
	};
};