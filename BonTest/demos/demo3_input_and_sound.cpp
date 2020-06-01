#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo3_input_and_sound
{
	/**
	 * Illustrate input and sound.
	 */
	class InputAndSound : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

		// cursor image
		bon::ImageAsset _cursorImage;

		// gnu sprite
		bon::ImageAsset _spriteImage;
		bon::PointF _spritePosition;

		// sound effect for demo
		bon::SoundAsset _soundEffect;
		int _timesPlayedSound = 0;

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
			_soundEffect = Assets().LoadSound("../TestAssets/sfx/phaserUp1.mp3");

			// bind space key
			Input().SetKeyBind(bon::KeyCodes::KeySpace, "play_sound");

			// set sprite starting position
			_spritePosition = Gfx().WindowSize();
			_spritePosition.X -= 200;
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			// exit on escape
			if (Input().Down("exit")) { 
				Game().Exit(); 
			}

			// play sound action
			if (Input().PressedNow("play_sound")) { 
				Sfx().PlaySound(_soundEffect);
				_timesPlayedSound++;
			}

			// move sprite
			double speed = 150.0 * deltaTime;
			if (Input().Down("up")) _spritePosition.Y -= (float)speed;
			if (Input().Down("down")) _spritePosition.Y += (float)speed;
			if (Input().Down("left")) _spritePosition.X -= (float)speed;
			if (Input().Down("right")) _spritePosition.X += (float)speed;

		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color(0.2f, 0.5f, 1.0f));

			// draw text
			Gfx().DrawText(_font, "Demo #3: Input & Sound!", bon::PointF(100, 100));
			Gfx().DrawText(_font, "This demo illustrates simple input and sound effects.\nUse arrows or WASD to move sprite.\nPress Space to play sound.\nHit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 16);
			Gfx().DrawText(_font, (std::string("Times played sound: ") + std::to_string(_timesPlayedSound)).c_str(), bon::PointF(100, 300), &bon::Color(1, 0, 0, 1), 16);
			

			// draw test sprite
			bon::PointF origin(0.5f, 1.0f);
			Gfx().DrawImage(_spriteImage, _spritePosition, &bon::PointI(256, 256), bon::BlendModes::AlphaBlend, nullptr, &origin, 0, nullptr);

			// draw cursor
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64));
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = InputAndSound();
		bon::Start(scene);
	}

}