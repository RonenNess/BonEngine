#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo4_spritesheet
{
	/**
	 * Spritesheet demo scene.
	 */
	class SpritesheetScene : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

		// cursor image
		bon::ImageAsset _cursorImage;

		// player sprite and spritesheet def
		bon::gfx::Sprite _player;
		bon::gfx::SpriteSheet _playerSheet;

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
			_player.Image = Assets().LoadImage("../TestAssets/gfx/player.png");
			_player.Origin.Set(0.5f, 1.0f);
			_player.Position.Set(500, 560);
			_playerSheet.LoadFromConfig(Assets().LoadConfig("../TestAssets/gfx/player_spritesheet.ini"));
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			// was player killed / animation progress
			static bool _wasKilled = false;
			static double _playerAnimationProgress = 0.0;

			// current and previous animation
			static std::string prevAnimation = "stand";
			static std::string currAnimation;

			// should we flip the player direction?
			static bool flip = false;

			// player is alive - do controls
			if (!_wasKilled)
			{
				bool isWalking = false;
				double speed = 150.0 * deltaTime;
				if (Input().Down("up")) { _player.Position.Y -= (float)speed; isWalking = true; }
				if (Input().Down("down")) { _player.Position.Y += (float)speed; isWalking = true; }
				if (Input().Down("left")) { _player.Position.X -= (float)speed; flip = true; isWalking = true; }
				if (Input().Down("right")) { _player.Position.X += (float)speed; flip = false; isWalking = true; }

				// kill player
				if (Input().ReleasedNow(bon::KeyCodes::KeySpace)) { _wasKilled = true; }

				// set animation
				currAnimation = isWalking ? "walk" : "stand";
			}
			// player is dead
			else {
				currAnimation = "die";
			}

			// if animation changed, reset progress
			if (currAnimation != prevAnimation) {
				prevAnimation = currAnimation;
				_playerAnimationProgress = 0.0;
			}

			// animate player
			_playerSheet.Animate(_player, currAnimation.c_str(), _playerAnimationProgress, deltaTime, nullptr, nullptr, 4.0f);
		
			// flip player if walking left
			if (flip) {
				_player.Size.X *= -1;
			}

			// exit on escape
			if (Input().Down("exit")) { Game().Exit(); }
		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color(0.2f, 0.5f, 1.0f));

			// draw example text and fps
			Gfx().DrawText(_font, "Demo #4: Spritesheet", bon::PointF(100, 100));
			Gfx().DrawText(_font, "This demo shows how to use a sprite sheet with animations.\n\
In this demo, the sprite sheet metadata is loaded from config file. \n\
Use WASD or Arrows to walk around. Press Space to kill player. \n\
Hit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 18);
			Gfx().DrawText(_font, (std::string("FPS: ") + std::to_string(Diagnostics().FpsCount())).c_str(), bon::PointF(0, 0), &bon::Color(1, 1, 1, 1), 18);

			// draw test sprite
			bon::PointF origin(1.0f, 1.0f);
			Gfx().DrawSprite(_player);

			// draw cursor
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64));
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = SpritesheetScene();
		bon::Start(scene);
	}

}