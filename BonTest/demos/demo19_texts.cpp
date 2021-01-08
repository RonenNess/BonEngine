#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo19_texts
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
			Gfx().DrawText(_font, "Demo #19: Texts", bon::PointF(100, 100), nullptr, 0, 0, bon::BlendModes::AlphaBlend, nullptr, 0.0f, 1, &bon::Color::Black);
			Gfx().DrawText(_font, "This demo shows some advanced text options.\n\
Press 'space' to toggle background. \n\
\nHit escape to exit.", bon::PointF(100, 170), &bon::Color(1, 1, 0, 1), 16);

			static float _rotateAnim;
			_rotateAnim += 1.0f;

			// rotating text
			Gfx().DrawText(_font, "Rotating Text", bon::PointF(100, 400), &bon::Color::Red, 0, 0, bon::BlendModes::AlphaBlend, &bon::PointF::Half, (float)_rotateAnim);

			// text anchors
			float anchoredRotation = (float)sin(_rotateAnim / 50.0) * 7.0f;
			Gfx().DrawText(_font, "Anchored left", bon::PointF(400, 300), &bon::Color::Yellow, 0, 0, bon::BlendModes::AlphaBlend, &bon::PointF(0, 0.5f), anchoredRotation);
			Gfx().DrawText(_font, "Anchored center", bon::PointF(400, 350), &bon::Color::Yellow, 0, 0, bon::BlendModes::AlphaBlend, &bon::PointF(0.5f, 0.5f), anchoredRotation);
			Gfx().DrawText(_font, "Anchored right", bon::PointF(400, 400), &bon::Color::Yellow, 0, 0, bon::BlendModes::AlphaBlend, &bon::PointF(1.0f, 0.5f), anchoredRotation);

			// additive
			Gfx().DrawText(_font, "Additive Blend", bon::PointF(550, 500), &bon::Color::Green, 0, 0, bon::BlendModes::AdditiveAlpha, &bon::PointF(1.0f, 0.5f), 0);
			Gfx().DrawText(_font, "Additive Blend", bon::PointF(550 - 10, 500 - 10), &bon::Color::Red, 0, 0, bon::BlendModes::AdditiveAlpha, &bon::PointF(1.0f, 0.5f), 0);

			// text max width
			Gfx().DrawText(_font, "This text have limited line width. It will wrap automatically.", bon::PointF(600, 400), &bon::Color::White, 16, 220);

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