#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo1_hello_world
{
	/**
	 * Basic hello world scene.
	 */
	class HelloWorldScene : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

		// cursor image
		bon::ImageAsset _cursorImage;

		// gnu sprite
		bon::ImageAsset _spriteImage;

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
			_spriteImage = Assets().LoadImage("../TestAssets/gfx/gnu.png");
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
			Gfx().UseEffect(nullptr);

			// clear screen
			Gfx().ClearScreen(bon::Color::Cornflower);

			// draw example text and fps
			Gfx().DrawText(_font, "Demo #1: Hello World!", bon::PointF(100, 100), nullptr, 0, 0, bon::BlendModes::AlphaBlend, nullptr, 0.0f, 1, &bon::Color::Black);
			Gfx().DrawText(_font, "This is just a basic demo where we render 3 sprites with color tint.\nNote: colors can go above 1.0 to emphasize colors.\nHit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 18);
			Gfx().DrawText(_font, (std::string("FPS: ") + std::to_string(Diagnostics().FpsCount())).c_str(), bon::PointF(0, 0), &bon::Color(1, 1, 1, 1), 18);

			// draw test sprite
			bon::PointF origin(1.0f, 1.0f);
			auto winSize = Gfx().WindowSize();
			Gfx().DrawImage(_spriteImage, winSize, &bon::PointI(256, 256), bon::BlendModes::AlphaBlend, nullptr, &origin, 0, nullptr);
			Gfx().DrawImage(_spriteImage, bon::PointI(winSize.X - 256, winSize.Y), &bon::PointI(256, 256), bon::BlendModes::AlphaBlend, nullptr, &origin, 0, &bon::Color::Red);
			Gfx().DrawImage(_spriteImage, bon::PointI(winSize.X - 512, winSize.Y), &bon::PointI(256, 256), bon::BlendModes::AlphaBlend, nullptr, &origin, 0, &bon::Color(1,1,5,1));

			// draw cursor
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64));
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = HelloWorldScene();
		bon::Start(scene);
	}

}