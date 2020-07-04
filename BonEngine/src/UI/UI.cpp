#include <UI/UI.h>
#include <BonEngine.h>
#include <UI/Elements/Defs.h>
#include <UI/Elements/UIElement.h>
using namespace bon::framework;

namespace bon
{
	namespace ui
	{
		// get mouse position, relative to current screen / render target / viewport size.
		PointI UI::GetRelativeCursorPos()
		{
			PointF cp = bon::_GetEngine().Input().CursorPosition();
			auto windowSize = bon::_GetEngine().Gfx().WindowSize();
			auto renderSize = bon::_GetEngine().Gfx().RenderableSize();
			float ratioX = (float)renderSize.X / (float)windowSize.X;
			float ratioY = (float)renderSize.Y / (float)windowSize.Y;
			return PointI((int)(cp.X * ratioX), (int)(cp.Y * ratioY));
		}

		// set cursor to render.
		void UI::SetCursor(const assets::ImageAsset& image, framework::PointI size, framework::PointI offset) 
		{
			SetCursor(Sprite(image, offset, size));
		}

		// set cursor to render from sprite.
		void UI::SetCursor(const gfx::Sprite& sprite) 		
		{
			UIImage cursor = std::make_shared<_UIImage>();
			cursor->Image = sprite.Image;
			cursor->BlendMode = sprite.Blend;
			cursor->Origin = sprite.Origin;
			cursor->SetOffset(sprite.Position);
			cursor->Color = sprite.Color;
			cursor->SourceRect = sprite.SourceRect;
			cursor->SetSizeInPixels(sprite.Size);
			_cursor = cursor;
		}

		void UI::SetCursor(const UIImage& image)
		{
			_cursor = image;
		}

		// draw cursor
		void UI::DrawCursor() 		
		{
			if (_cursor == nullptr) { return; }
			PointF mousePosition = GetRelativeCursorPos();
			PointF screenSize = _GetEngine().Gfx().RenderableSize();
			_cursor->SetAnchor(PointF(mousePosition.X / screenSize.X, mousePosition.Y / screenSize.Y));
			_cursor->Draggable = _cursor->CaptureInput = _cursor->Interactive = false;
			_cursor->Update(0.1);
			_cursor->Draw();
		}

		// draw a UI system or element.
		void UI::Draw(UIElement root, bool drawCursor)
		{
			// draw UI
			root->Draw();

			// draw cursor
			if (drawCursor) {
				DrawCursor();
			}
		}

		// update UI system and do input interactions
		void UI::UpdateUI(UIElement root, UIElement* activeElement)
		{
			// first call updates
			root->Update(bon::_GetEngine().Game().DeltaTime());

			// now do input interactions
			auto mousePosition = GetRelativeCursorPos();
			UIUpdateInputState updateState;
			root->DoInputUpdates(mousePosition, updateState);

			// set active element
			if (activeElement)
			{
				*activeElement = std::shared_ptr<_UIElement>(updateState.ElementPointedOn, [](_UIElement*) {});
			}
		}

		// init a new ui element
		void UI::InitNewElement(UIElement element, ConfigAsset stylesheet, UIElement parent)
		{
			// call element init
			element->_Init();

			// load stylesheet
			if (stylesheet != nullptr)
			{
				element->LoadStyleFrom(stylesheet);
			}

			// add to parent
			if (parent != nullptr)
			{
				parent->AddChild(element);
			}
		}

		// init a new ui element
		void UI::InitNewElement(UIElement element, const char* stylesheetPath, UIElement parent)
		{
			ConfigAsset conf = nullptr;
			if (stylesheetPath) { conf = bon::_GetEngine().Assets().LoadConfig(stylesheetPath); }
			InitNewElement(element, conf, parent);
		}

		// create and return root element
		UIElement UI::CreateRoot()
		{
			UIElement ret = std::make_shared<_UIElement>();
			ret->SetSize(bon::UISize(100, bon::UISizeType::PercentOfParent, 100, bon::UISizeType::PercentOfParent));
			ret->SetPadding(UISides(0, 0, 0, 0));
			return ret;
		}

		// create and return root element
		UIElement UI::CreateContainer(const char* stylesheet, UIElement parent)
		{
			UIElement ret = std::make_shared<_UIElement>();
			InitNewElement(ret, stylesheet, parent);
			return ret;
		}

		// create and return image element
		UIImage UI::CreateImage(const char* stylesheet, UIElement parent)
		{
			UIImage ret = std::make_shared<_UIImage>();
			InitNewElement(ret, stylesheet, parent);
			return ret;
		}

		// create and return a text element
		UIText UI::CreateText(const char* stylesheet, UIElement parent, const char* text)
		{
			UIText ret = std::make_shared<_UIText>();
			InitNewElement(ret, stylesheet, parent);
			if (text) { ret->SetText(text); }
			return ret;
		}

		// create and return a window element
		UIWindow UI::CreateWindow(const char* stylesheet, UIElement parent, const char* title)
		{
			UIWindow ret = std::make_shared<_UIWindow>();
			InitNewElement(ret, stylesheet, parent);
			if (title) { ret->Title->SetText(title); }
			return ret;
		}

		// create and return a button element.
		UIButton UI::CreateButton(const char* stylesheet, UIElement parent, const char* caption)
		{
			UIButton ret = std::make_shared<_UIButton>();
			InitNewElement(ret, stylesheet, parent);
			if (caption) { ret->Caption->SetText(caption); }
			return ret;
		}

		// create and return a text input element
		UITextInput UI::CreateTextInput(const char* stylesheet, UIElement parent, const char* startingValue, const char* placeholder)
		{
			UITextInput ret = std::make_shared<_UITextInput>();
			InitNewElement(ret, stylesheet, parent);
			if (startingValue) { ret->SetValue(startingValue); }
			if (placeholder) { ret->SetPlaceholderText(placeholder); }
			return ret;
		}

		// create and return a checkbox element.
		UICheckBox UI::CreateCheckbox(const char* stylesheet, UIElement parent, const char* caption)
		{
			UICheckBox ret = std::make_shared<_UICheckBox>();
			InitNewElement(ret, stylesheet, parent);
			if (caption) { ret->Caption->SetText(caption); }
			return ret;
		}

		// create and return a slider element.
		UISlider UI::CreateSlider(const char* stylesheet, UIElement parent)
		{
			UISlider ret = std::make_shared<_UISlider>();
			InitNewElement(ret, stylesheet, parent);
			return ret;
		}

		// create and return a radio button element.
		UIRadioButton UI::CreateRadioButton(const char* stylesheet, UIElement parent, const char* caption)
		{
			UIRadioButton ret = std::make_shared<_UIRadioButton>();
			InitNewElement(ret, stylesheet, parent);
			if (caption) { ret->Caption->SetText(caption); }
			return ret;
		}

		// create and return a list element.
		UIList UI::CreateList(const char* stylesheet, UIElement parent)
		{
			UIList ret = std::make_shared<_UIList>();
			InitNewElement(ret, stylesheet, parent);
			return ret;
		}

		// create and return a scrollbar element.
		UIVerticalScrollbar UI::CreateVerticalScrollbar(const char* stylesheet, UIElement parent)
		{
			UIVerticalScrollbar ret = std::make_shared<_UIVerticalScrollbar>();
			InitNewElement(ret, stylesheet, parent);
			return ret;
		}

	}
}