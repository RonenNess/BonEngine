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

		// checkbox to debug draw ui
		bon::UICheckBox _checkboxShowDebug;

	public:

		// on scene load
		virtual void _Load() override
		{
			if (IsFirstScene())
				Game().LoadConfig("../TestAssets/config.ini");
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf", 36);
		}
		
		// on scene start
		virtual void _Start() override
		{
			// set ui cursor
			UI().SetCursor(UI().CreateImage("../TestAssets/ui/cursor.ini"));

			// create UI root
			_uiRoot = UI().CreateRoot();
			
			// create test image
			bon::UIImage appleImage = UI().CreateImage("../TestAssets/ui/apple_image.ini", _uiRoot);

			// create text to count apples click
			{
				bon::UIText text = UI().CreateText("../TestAssets/ui/default_text.ini", _uiRoot);
				text->SetText("Apples clicked: 0");
				text->SetOffset(bon::PointF(100, 00));

				// count how many times we clicked the apple
				static int clicksCount = 0;
				appleImage->OnMouseReleased = [text](bon::_UIElement& element, void* data)
				{
					clicksCount++;
					text->SetText(std::string(("Apples clicked: ") + std::to_string(clicksCount)).c_str());
				};
			}

			// create text to count apples mouse enter
			{
				bon::UIText text = UI().CreateText("../TestAssets/ui/default_text.ini", _uiRoot);
				text->SetText("Apples mouse enter: 0");
				text->SetOffset(bon::PointF(100, 30));

				// count how many times we clicked the apple
				static int enterCount = 0;
				appleImage->OnMouseEnter = [text](bon::_UIElement& element, void* data)
				{
					enterCount++;
					text->SetText(std::string(("Apples mouse enter: ") + std::to_string(enterCount)).c_str());
				};
			}

			// create text to count apples mouse leave
			{
				bon::UIText text = UI().CreateText("../TestAssets/ui/default_text.ini", _uiRoot);
				text->SetText("Apples mouse leave: 0");
				text->SetOffset(bon::PointF(100, 60));

				// count how many times we clicked the apple
				static int leaveCount = 0;
				appleImage->OnMouseLeave = [text](bon::_UIElement& element, void* data)
				{
					leaveCount++;
					text->SetText(std::string(("Apples mouse leave: ") + std::to_string(leaveCount)).c_str());
				};
			}

			// create main test window
			bon::UIWindow window = UI().CreateWindow("../TestAssets/ui/window.ini", _uiRoot, "Demo #16: UI");
			window->SetOffset(bon::PointI(100, 50));

			// add intro text
			bon::UIText intro = UI().CreateText("../TestAssets/ui/small_text.ini", window, 
				"This example shows some basic UI elements in the built-in UI system. UI elements are loaded from ini files.");

			// add a button
			bon::UIButton button = UI().CreateButton("../TestAssets/ui/button.ini", window, "A Button");
			button->SetOffset(bon::PointI(0, 120));

			// add a list
			bon::UIList uilist = UI().CreateList("../TestAssets/ui/list.ini", window);
			uilist->SetOffset(bon::PointI(0, 165));
			uilist->AddItem("This is a list");
			uilist->AddItem("You can add items");
			uilist->AddItem("And select them");
			for (int i = 1; i <= 15; ++i) {
				uilist->AddItem((std::string("Item #") + std::to_string(i)).c_str());
			}

			// add text to show selected item on change
			bon::UIText listSelectedText = UI().CreateText("../TestAssets/ui/small_text.ini", window, "Selected: ");
			listSelectedText->SetOffset(bon::PointI(0, 342));
			uilist->OnValueChange = [uilist, listSelectedText](bon::_UIElement& self, void*)
			{
				listSelectedText->SetText((std::string("Selected: " + std::string(uilist->SelectedItem())).c_str()));
			};

			// create additional window to show more stuff
			bon::UIWindow extraStuffWindow = UI().CreateWindow("../TestAssets/ui/window.ini", _uiRoot, "More Elements");
			extraStuffWindow->SetOffset(bon::PointI(300, 150));

			// create checkboxes
			bon::UICheckBox checkbox1 = UI().CreateCheckbox("../TestAssets/ui/checkbox.ini", extraStuffWindow, "Checkbox 1");
			_checkboxShowDebug = UI().CreateCheckbox("../TestAssets/ui/checkbox.ini", extraStuffWindow, "Debug Draw UI");
			_checkboxShowDebug->SetOffset(bon::PointI(0, 50));

			// add radio buttons
			bon::UIText tempText = UI().CreateText("../TestAssets/ui/small_text.ini", extraStuffWindow, "Radio buttons:");
			tempText->SetOffset(bon::PointI(0, 110));
			for (int i = 0; i < 3; ++i)
			{
				bon::UIRadioButton radio = UI().CreateRadioButton("../TestAssets/ui/radiobutton.ini", extraStuffWindow, 
					std::string("Radio option " + std::to_string(i+1)).c_str());
				radio->SetOffset(bon::PointI(0, 140 + 50 * i));
			}

			// add slider
			bon::UIText sliderText = UI().CreateText("../TestAssets/ui/small_text.ini", extraStuffWindow, "Slider widget:");
			sliderText->SetOffset(bon::PointI(0, 300));
			bon::UISlider slider = UI().CreateSlider("../TestAssets/ui/slider.ini", extraStuffWindow);
			slider->SetOffset(bon::PointI(0, 335));

			// move main window to front
			window->MoveToFront();
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

			// debug draw UI
			if (_checkboxShowDebug->Checked())
			{
				_uiRoot->DebugDraw(true);
			}

			// show draw calls count (doing it last to include everything)
			Gfx().DrawText(_font, (std::string("Draw Calls: ") + std::to_string(Diagnostics().GetCounter(bon::DiagnosticsCounters::DrawCalls))).c_str(), 
				bon::PointI(4, Gfx().WindowSize().Y - 40), &bon::Color::White, 22);

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