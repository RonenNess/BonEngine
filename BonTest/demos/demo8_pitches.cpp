#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo8_pitches
{
	/**
	 * Scene to show sound pitches.
	 */
	class PitchesDemoScene : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

		// sound to show pitch
		bon::SoundAsset _sound;

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
			_sound = Assets().LoadSound("../TestAssets/sfx/phaserUp1.mp3");
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			if (Input().Down("exit")) { Game().Exit(); }
			if (Input().PressedNow(bon::KeyCodes::Key1)) { Sfx().PlaySound(_sound, 100, 0, 0.5f); }
			if (Input().PressedNow(bon::KeyCodes::Key2)) { Sfx().PlaySound(_sound, 100, 0, 0.6f); }
			if (Input().PressedNow(bon::KeyCodes::Key3)) { Sfx().PlaySound(_sound, 100, 0, 0.7f); }
			if (Input().PressedNow(bon::KeyCodes::Key4)) { Sfx().PlaySound(_sound, 100, 0, 0.8f); }
			if (Input().PressedNow(bon::KeyCodes::Key5)) { Sfx().PlaySound(_sound, 100, 0, 0.9f); }
			if (Input().PressedNow(bon::KeyCodes::Key6)) { Sfx().PlaySound(_sound, 100, 0, 1.0f); }
			if (Input().PressedNow(bon::KeyCodes::Key7)) { Sfx().PlaySound(_sound, 100, 0, 1.1f); }
			if (Input().PressedNow(bon::KeyCodes::Key8)) { Sfx().PlaySound(_sound, 100, 0, 1.2f); }
			if (Input().PressedNow(bon::KeyCodes::Key9)) { Sfx().PlaySound(_sound, 100, 0, 1.3f); }
			if (Input().PressedNow(bon::KeyCodes::Key0)) { Sfx().PlaySound(_sound, 100, 0, 1.4f); }
		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color::Cornflower);

			// draw text
			Gfx().DrawText(_font, "Demo #8: Sound Effects Pitch", bon::PointF(100, 100), nullptr, 0, 0, bon::BlendModes::AlphaBlend, nullptr, 0.0f, 1, &bon::Color::Black);
			Gfx().DrawText(_font, "Press 1-10 to play the same sound with different pitch.\nHit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 16);
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = PitchesDemoScene();
		bon::Start(scene);
	}

}