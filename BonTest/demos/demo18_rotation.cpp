#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo18_rotation
{
	/**
	 * Rotation scene.
	 */
	class RotationScene : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

		// cursor image
		bon::ImageAsset _cursorImage;

		// sprite and background
		bon::ImageAsset _spriteImage;
		bon::ImageAsset _backgroundImage;

		// show / hide background
		bool _showBackground = false;

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
			_backgroundImage = Assets().LoadImage("../TestAssets/gfx/background.png");
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			if (Input().Down("exit")) { Game().Exit(); }
			if (Input().ReleasedNow(bon::KeyCodes::KeySpace)) { _showBackground = !_showBackground; }
		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color::Cornflower);

			// get window size
			bon::PointI windowSize = Gfx().WindowSize();

			// draw background
			if (_showBackground) {
				bon::PointF origin(0.5f, 1.0f);
				Gfx().DrawImage(_backgroundImage, bon::PointF((float)windowSize.X / 2.0f, (float)windowSize.Y), &bon::PointI(800, 600), bon::BlendModes::Opaque, nullptr, &origin, 0, nullptr);
			}

			// draw text
			Gfx().DrawText(_font, "Demo #18: Rotation & Origin", bon::PointF(100, 100), nullptr, 0, 0, bon::BlendModes::AlphaBlend, nullptr, 0.0f, 1, &bon::Color::Black);
			Gfx().DrawText(_font, "You can rotate sprites around origin.\n\
In this demo the origin is marked by the red dot.\n\
\nHit escape to exit.", bon::PointF(100, 170), &bon::Color(1, 1, 0, 1), 16);
			
			static float rotation;
			rotation += 0.1f;
			int size = 120;

			// draw top left rotation
			Gfx().DrawImage(_spriteImage, bon::PointI(150, 300), &bon::PointI(size, size), bon::BlendModes::AlphaBlend, nullptr, nullptr, rotation, nullptr);
			Gfx().DrawRectangle(bon::RectangleI(150, 300, size, size), bon::Color::Red, false, bon::BlendModes::Opaque, nullptr, rotation);
			Gfx().DrawCircle(bon::PointI(150, 300), 6, bon::Color::Red, true, bon::BlendModes::Opaque);

			// draw center rotation
			Gfx().DrawImage(_spriteImage, bon::PointI(350, 360), &bon::PointI(size, size), bon::BlendModes::AlphaBlend, nullptr, &bon::PointF::Half, rotation, nullptr);
			Gfx().DrawRectangle(bon::RectangleI(350, 360, size, size), bon::Color::Red, false, bon::BlendModes::Opaque, &bon::PointF::Half, rotation);
			Gfx().DrawCircle(bon::PointI(350, 360), 6, bon::Color::Red, true, bon::BlendModes::Opaque);

			// draw bottom right 
			Gfx().DrawImage(_spriteImage, bon::PointI(550, 420), &bon::PointI(size, size), bon::BlendModes::AlphaBlend, nullptr, &bon::PointF::One, rotation, nullptr);
			Gfx().DrawRectangle(bon::RectangleI(550, 420, size, size), bon::Color::Red, false, bon::BlendModes::Opaque, &bon::PointF::One, rotation);
			Gfx().DrawCircle(bon::PointI(550, 420), 6, bon::Color::Red, true, bon::BlendModes::Opaque);

			// draw cursor
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64), bon::BlendModes::AlphaBlend);
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = RotationScene();
		bon::Start(scene);
	}

}