#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo12_layered_scenes
{ 
	/**
	 * HUD scene - the scene we use internally by the demo scene to draw HUD.
	 */
	class HudScene : public bon::engine::Scene
	{
	private:
		// assets
		bon::ImageAsset _cursorImage;
		bon::ImageAsset _hudImage;
		bon::ImageAsset _skillsImage;

	public:
		// on scene start
		virtual void _Start() override
		{
			// load assets
			_hudImage = Assets().LoadImage("../TestAssets/gfx/hud.png");
			_skillsImage = Assets().LoadImage("../TestAssets/gfx/skills.png");
			_cursorImage = Assets().LoadImage("../TestAssets/gfx/cursor.png");
		}

		// drawing - draw the HUD
		virtual void _Draw() override
		{
			Gfx().DrawImage(_hudImage, bon::PointI(6, 6), &bon::PointI(250, 80));
			Gfx().DrawImage(_skillsImage, bon::PointI(6, Gfx().WindowSize().Y - 66), &bon::PointI(200, 60));
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64));
		}
	};

	/**
	 * Layered scene demo - base scene.
	 */
	class LayeredSceneDemo : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

		// gnu sprite
		bon::ImageAsset _spriteImage;

		// internal hud scene
		HudScene _hud;

	public:
		// on scene load
		virtual void _Load() override
		{
			// load config and call the hud scene's _Load() method
			if (IsFirstScene())
				Game().LoadConfig("../TestAssets/config.ini");
			_hud._Load();
		}

		// on scene start
		virtual void _Start() override
		{
			// load assets and call the hud scene's _Start() method
			_spriteImage = Assets().LoadImage("../TestAssets/gfx/gnu.png");
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");
			_hud._Start();
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			if (Input().Down("exit")) { Game().Exit(); }
			_hud._Update(deltaTime);
		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color::Cornflower);

			// draw example text and fps
			Gfx().DrawText(_font, "Demo #12: Layered Scene", bon::PointF(100, 100), nullptr, 0, 0, bon::BlendModes::AlphaBlend, nullptr, 0.0f, 1, &bon::Color::Black);
			Gfx().DrawText(_font, "This demo shows a scene that uses an internal scene to handle HUD elements.\n\
With this technique we can combine scenes together.\n\
\nHit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 18);

			// draw test sprite
			bon::PointF origin(1.0f, 1.0f);
			Gfx().DrawImage(_spriteImage, Gfx().WindowSize(), &bon::PointI(256, 256), bon::BlendModes::AlphaBlend, nullptr, &origin, 0, nullptr);

			// draw hud scene
			_hud._Draw();
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = LayeredSceneDemo();
		bon::Start(scene);
	}

}