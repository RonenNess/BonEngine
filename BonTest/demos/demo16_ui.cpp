#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"
#include <vector>

namespace demo16_ui
{
	/**
	 * UI test scene.
	 */
	class UITestScene : public bon::engine::Scene
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
			bon::ImageAsset cursor = Assets().LoadImage("../TestAssets/gfx/cursor.png");
			UI().SetCursor(cursor, bon::PointI(64, 64), bon::PointI::Zero);
		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color::Cornflower);

			// draw cursor
			UI().DrawCursor();
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = UITestScene();
		bon::Start(scene);
	}
}