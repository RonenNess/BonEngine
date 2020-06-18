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
			_cursor = sprite;
		}

		// draw cursor
		void UI::DrawCursor() 		
		{
			PointF mousePosition = GetRelativeCursorPos();
			bon::_GetEngine().Gfx().DrawSprite(_cursor, &mousePosition);
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
		void UI::UpdateUI(UIElement root)
		{
			// first call updates
			root->Update(bon::_GetEngine().Game().DeltaTime());

			// now do input interactions
			auto mousePosition = GetRelativeCursorPos();
			UIUpdateInputState updateState;
			root->DoInputUpdates(mousePosition, updateState);
		}

		// init a new ui element
		void UI::InitNewElement(UIElement element, ConfigAsset stylesheet, UIElement parent)
		{
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
			ret->SetSize(bon::UICoords(100, bon::UICoordsType::PercentOfParent, 100, bon::UICoordsType::PercentOfParent));
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
		UIText UI::CreateText(const char* stylesheet, UIElement parent)
		{
			UIText ret = std::make_shared<_UIText>();
			InitNewElement(ret, stylesheet, parent);
			return ret;
		}
	}
}