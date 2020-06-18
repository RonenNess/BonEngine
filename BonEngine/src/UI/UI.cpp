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

		// create and return a new element.
		UIElement UI::Create(UIElementTypes type, const char* stylesheetPath, UIElement parent)
		{
			ConfigAsset conf = nullptr;
			if (stylesheetPath) { conf = bon::_GetEngine().Assets().LoadConfig(stylesheetPath); }
			return Create(type, conf, parent);
		}

		// create and return a new element.
		UIElement UI::Create(UIElementTypes type, ConfigAsset stylesheet, UIElement parent)
		{
			// create element
			UIElement ret;
			switch (type)
			{
			case UIElementTypes::Root:
				ret = std::make_shared<_UIElement>();
				ret->SetSize(bon::UICoords(100, bon::UICoordsType::PercentOfParent, 100, bon::UICoordsType::PercentOfParent));
				ret->SetPadding(UISides(0, 0, 0, 0));
				break;

			case UIElementTypes::Container:
				ret = std::make_shared<_UIElement>();
				break;

			case UIElementTypes::Image:
				ret = std::make_shared<UIImage>();
				break;
			}

			// load stylesheet
			if (stylesheet != nullptr)
			{
				ret->LoadStyleFrom(stylesheet);
			}

			// add to parent
			if (parent != nullptr)
			{
				parent->AddChild(ret);
			}

			// return new element
			return ret;
		}
	}
}