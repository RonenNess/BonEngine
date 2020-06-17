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
		void UI::Draw(UIElementPtr root, bool drawCursor)
		{
			// draw UI
			root->Draw();

			// draw cursor
			if (drawCursor) {
				DrawCursor();
			}
		}
	}
}