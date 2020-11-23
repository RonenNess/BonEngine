#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"
#include <vector>
#include "../../BonEngine/inc/_CAPI/CAPI_Managers_UI.h"

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
			bon::UIWindow intoWindow = UI().CreateUIWindow("../TestAssets/ui/window.ini", _uiRoot, "Button, List, DropDown");
			intoWindow->SetOffset(bon::PointI(100, 50));
			intoWindow->AutoArrangeChildren = true;
			intoWindow->SetSizeInPixels(bon::PointI(intoWindow->GetSize().Width, intoWindow->GetSize().Height + 90));

			// add intro text
			bon::UIText intro = UI().CreateText("../TestAssets/ui/small_text.ini", intoWindow, 
				"This example shows some basic UI elements in the built-in UI system. UI elements are loaded from ini files.");

			// add a button
			bon::UIButton button = UI().CreateButton("../TestAssets/ui/button.ini", intoWindow, "A Button");

			// create dropdown
			UI().CreateText("../TestAssets/ui/small_text.ini", intoWindow, "DropDown Element:");
			bon::UIDropDown uidropdown = UI().CreateDropDown("../TestAssets/ui/dropdown.ini", intoWindow);
			uidropdown->PlaceholderText->SetText("Click here to select");
			for (int i = 1; i <= 15; ++i) {
				uidropdown->AddItem((std::string("Item #") + std::to_string(i)).c_str());
			}

			// add a list
			UI().CreateText("../TestAssets/ui/small_text.ini", intoWindow, "List Element:");
			bon::UIList uilist = UI().CreateList("../TestAssets/ui/list.ini", intoWindow);
			uilist->AddItem("This is a list");
			uilist->AddItem("You can add items");
			uilist->AddItem("And select them");
			for (int i = 1; i <= 15; ++i) {
				uilist->AddItem((std::string("Item #") + std::to_string(i)).c_str());
			}

			// create additional window to show more stuff
			bon::UIWindow checkAndSliderWindow = UI().CreateUIWindow("../TestAssets/ui/window.ini", _uiRoot, "Check, Radio, Slider");
			checkAndSliderWindow->AutoArrangeChildren = true;
			checkAndSliderWindow->SetOffset(bon::PointI(300, 100));

			// create checkboxes
			bon::UICheckBox checkbox1 = UI().CreateCheckbox("../TestAssets/ui/checkbox.ini", checkAndSliderWindow, "Checkbox 1");
			_checkboxShowDebug = UI().CreateCheckbox("../TestAssets/ui/checkbox.ini", checkAndSliderWindow, "Debug Draw UI");

			// add radio buttons
			bon::UIText tempText = UI().CreateText("../TestAssets/ui/small_text.ini", checkAndSliderWindow, "Radio buttons:");
			for (int i = 0; i < 3; ++i)
			{
				bon::UIRadioButton radio = UI().CreateRadioButton("../TestAssets/ui/radiobutton.ini", checkAndSliderWindow, 
					std::string("Radio option " + std::to_string(i+1)).c_str());
			}

			// add slider
			bon::UIText sliderText = UI().CreateText("../TestAssets/ui/small_text.ini", checkAndSliderWindow, "Slider widget:");
			bon::UISlider slider = UI().CreateSlider("../TestAssets/ui/slider.ini", checkAndSliderWindow);

			// create additional window for text inputs
			bon::UIWindow inputsWindow = UI().CreateUIWindow("../TestAssets/ui/window.ini", _uiRoot, "Text Inputs");
			inputsWindow->AutoArrangeChildren = true;
			inputsWindow->SetOffset(bon::PointI(400, 150));

			// add text input
			bon::UITextInput textInput = UI().CreateTextInput("../TestAssets/ui/textinput.ini", inputsWindow, "", "Free text input..");
			textInput->MaxLength = 16;
			
			// add numbers input
			bon::UITextInput numbersInput = UI().CreateTextInput("../TestAssets/ui/textinput.ini", inputsWindow, "", "Numbers input..");
			numbersInput->InputMode = bon::UITextInputMode::NumbersOnly;
			numbersInput->MaxLength = 16;

			// add characters input
			bon::UITextInput alphaInput = UI().CreateTextInput("../TestAssets/ui/textinput.ini", inputsWindow, "", "Alpha input..");
			alphaInput->InputMode = bon::UITextInputMode::AlphaOnly;
			alphaInput->MaxLength = 16;

			// add numbers and alpha input
			bon::UITextInput numbersAlphaInput = UI().CreateTextInput("../TestAssets/ui/textinput.ini", inputsWindow, "", "Numbers & alpha input..");
			numbersAlphaInput->InputMode = bon::UITextInputMode::NumbersOnly | bon::UITextInputMode::AlphaOnly;
			numbersAlphaInput->MaxLength = 16;
			
			// add upper input
			bon::UITextInput upperInput = UI().CreateTextInput("../TestAssets/ui/textinput.ini", inputsWindow, "", "UPPERCASE INPUT..");
			upperInput->InputMode = bon::UITextInputMode::Uppercase;
			upperInput->MaxLength = 16;

			// add lower input
			bon::UITextInput lowerInput = UI().CreateTextInput("../TestAssets/ui/textinput.ini", inputsWindow, "", "lowercase input..");
			lowerInput->InputMode = bon::UITextInputMode::Lowercase;
			lowerInput->MaxLength = 16;

			// add upper alpha input
			bon::UITextInput upperAlphaInput = UI().CreateTextInput("../TestAssets/ui/textinput.ini", inputsWindow, "", "UPPERCASE ALPHA INPUT..");
			upperAlphaInput->InputMode = bon::UITextInputMode::Uppercase | bon::UITextInputMode::AlphaOnly;
			upperAlphaInput->MaxLength = 16;

			// move main window to front
			checkAndSliderWindow->MoveToFront();
			intoWindow->MoveToFront();
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