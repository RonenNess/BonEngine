#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo2_draw_to_texture
{
	/**
	 * Draw to texture demo
	 */
	class DrawToTextureScene : public bon::engine::Scene
	{
	private:

		// target texture
		bon::ImageAsset _target;

		// default font
		bon::FontAsset _font;

		// cursor image
		bon::ImageAsset _cursorImage;

		// gnu sprite
		bon::ImageAsset _spriteImage;

		// rotate whole screen
		float _rotation = 0.0f;

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
			// create target texture
			_target = Assets().CreateEmptyImage(Gfx().WindowSize());

			// load assets
			_cursorImage = Assets().LoadImage("../TestAssets/gfx/cursor.png");
			_spriteImage = Assets().LoadImage("../TestAssets/gfx/gnu.png");
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			if (Input().Down("exit")) { Game().Exit(); }
			_rotation += (float)deltaTime;
		}

		// drawing
		virtual void _Draw() override
		{
			// set target texture
			Gfx().SetRenderTarget(_target);

			// clear screen
			Gfx().ClearScreen(bon::Color::Cornflower);

			// draw text
			Gfx().DrawText(_font, "Demo #2: Drawing To Texture", bon::PointF(100, 100));
			Gfx().DrawText(_font, "Here we render everything to texutre, then we render it on screen.\nThis is a useful technique for post-render effects.\n\nHit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 18);

			// get window size
			const bon::PointI& windowSize = Gfx().WindowSize();

			// draw test sprite
			static bon::PointF origin(1.0f, 1.0f);
			Gfx().DrawImage(_spriteImage, windowSize, &bon::PointI(256, 256), bon::BlendModes::AlphaBlend, nullptr, &origin, 0, nullptr);

			// clear render target and present texture
			static bon::PointF originHalf(0.5f, 0.5f);
			bon::PointI drawingSize = windowSize;
			drawingSize.X += (int)(sin(Game().ElapsedTime() * 2.0) * 60.0);
			Gfx().SetRenderTarget(nullptr);
			Gfx().ClearScreen(bon::Color::Cornflower);
			Gfx().DrawImage(_target, bon::PointF(windowSize.X / 2.0f, windowSize.Y / 2.0f), &drawingSize, bon::BlendModes::Opaque, nullptr, &originHalf, sin(_rotation) * 5.0f, nullptr);

			// draw cursor
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64));
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = DrawToTextureScene();
		bon::Start(scene);
	}

}