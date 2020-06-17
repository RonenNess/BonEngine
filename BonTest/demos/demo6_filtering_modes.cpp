#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo6_filtering_modes
{
	/**
	 * Basic hello world scene.
	 */
	class FilteringModeScene : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

		// cursor image
		bon::ImageAsset _cursorImage;

		// gnu sprite
		bon::ImageAsset _nearest;
		bon::ImageAsset _linear;
		bon::ImageAsset _anis;

	public:
		// on scene load
		virtual void _Load() override
		{
			if (IsFirstScene())
				Game().LoadConfig("../TestAssets/config.ini");
		}

		// on scene start
		virtual void _Start() override
		{
			// load assets
			_cursorImage = Assets().LoadImage("../TestAssets/gfx/cursor.png");
			_nearest = Assets().LoadImage("../TestAssets/gfx/gnu.png", bon::ImageFilterMode::Nearest, false);
			_linear = Assets().LoadImage("../TestAssets/gfx/gnu.png", bon::ImageFilterMode::Linear, false);
			_anis = Assets().LoadImage("../TestAssets/gfx/gnu.png", bon::ImageFilterMode::Anisotropic, false);
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			if (Input().Down("exit")) { Game().Exit(); }
		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color::Cornflower);

			// draw text
			Gfx().DrawText(_font, "Demo #6: Filtering Modes", bon::PointF(100, 100));
			Gfx().DrawText(_font, "Image filtering modes determine how to render an image when scaled.\n\
Here we see 3 types of filtering (left to right): Anisotropic, Linear, and Nearest.\n\
The default filtering mode is nearest, which is best for pixel art.\n\
\nHit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 18);

			// draw test sprite
			bon::PointF origin(1.0f, 1.0f);
			Gfx().DrawImage(_nearest, Gfx().WindowSize(), &bon::PointI(256, 256), bon::BlendModes::AlphaBlend, nullptr, &origin, 0, nullptr);
			Gfx().DrawImage(_linear, Gfx().WindowSize() - bon::PointF(256, 0), &bon::PointI(256, 256), bon::BlendModes::AlphaBlend, nullptr, &origin, 0, nullptr);
			Gfx().DrawImage(_anis, Gfx().WindowSize() - bon::PointF(512, 0), &bon::PointI(256, 256), bon::BlendModes::AlphaBlend, nullptr, &origin, 0, nullptr);

			// draw cursor
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64));
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = FilteringModeScene();
		bon::Start(scene);
	}

}