#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo14_switch_scenes
{
	/**
	 * Scene we switch to, internally.
	 */
	class TargetScene : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

	public:

		// on scene start
		virtual void _Start() override
		{
			// load assets
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

			// draw example text and fps
			Gfx().DrawText(_font, "This is a brand new scene!", bon::PointF(100, 100));
			Gfx().DrawText(_font, "Hit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 18);
			Gfx().DrawText(_font, (std::string("FPS: ") + std::to_string(Diagnostics().FpsCount())).c_str(), bon::PointF(0, 0), &bon::Color(1, 1, 1, 1), 18);
		}
	};


	/**
	 * Switching scene demo scene.
	 */
	class SwitchSceneDemoScene : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

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
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			// switch scene
			if (Input().ReleasedNow(bon::KeyCodes::KeySpace)) { 
				static TargetScene nextScene;
				Game().ChangeScene(nextScene);
			}

			// exit
			if (Input().Down("exit")) { Game().Exit(); }
		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color::Cornflower);

			// draw example text and fps
			Gfx().DrawText(_font, "Demo #14: Switch Scenes", bon::PointF(100, 100));
			Gfx().DrawText(_font, "This demo shows basic scene switching.\n\
Press space to switch scene.\n\
Hit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 18);
			Gfx().DrawText(_font, (std::string("FPS: ") + std::to_string(Diagnostics().FpsCount())).c_str(), bon::PointF(0, 0), &bon::Color(1, 1, 1, 1), 18);
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = SwitchSceneDemoScene();
		bon::Start(scene);
	}

}