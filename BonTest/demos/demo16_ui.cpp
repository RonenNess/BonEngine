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

		// ui root
		bon::UIElement _uiRoot;

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
			// set ui cursor
			bon::ImageAsset cursor = Assets().LoadImage("../TestAssets/gfx/cursor.png");
			UI().SetCursor(cursor, bon::PointI(64, 64), bon::PointI::Zero);

			// create UI root
			_uiRoot = UI().CreateRoot();
			
			// create test image
			bon::UIImage appleImage = UI().CreateImage("../TestAssets/ui/apple_image.ini", _uiRoot);

			// create text to count apples
			bon::UIText text = UI().CreateText("../TestAssets/ui/default_text.ini", _uiRoot);
			text->SetText("Apples clicked: 0");
			text->SetPosition(bon::PointF(100, 20));

			// count how many times we clicked the apple
			static int clicksCount = 0;
			appleImage->OnMouseReleased = [text](bon::_UIElement& element, void* data) 
			{
				clicksCount++;
				text->SetText(std::string(("Apples clicked: ") + std::to_string(clicksCount)).c_str());
			};

			// create test tiled image
			bon::UIImage tiledImage = UI().CreateImage("../TestAssets/ui/window.ini", _uiRoot);
			tiledImage->SetPosition(bon::PointI(100, 100));
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			// exit up
			if (Input().Down("exit")) { Game().Exit(); }

			// update UI
			UI().UpdateUI(_uiRoot);
		}

		// drawing ui
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color::Cornflower);

			// draw ui
			// note: for this demo we separate the ui drawing and cursor drawing calls just to show its possible.
			// set second param to true to draw cursor at the same call.
			UI().Draw(_uiRoot, false);

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