#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo7_fake_resolution
{
	/**
	 * Draw to texture demo
	 */
	class FakeResolutionScene : public bon::engine::Scene
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
			_target = Assets().CreateEmptyImage(bon::PointI(400, 300));

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

			// draw test sprite
			static bon::PointF origin(0.0f, 1.0f);
			Gfx().DrawImage(_spriteImage, bon::PointF(100, 300), &bon::PointI(160, 160), bon::BlendModes::AlphaBlend, nullptr, &origin, 0, nullptr);

			// clear render target and present texture on screen
			Gfx().SetRenderTarget(nullptr);
			Gfx().ClearScreen(bon::Color::Cornflower);
			auto targetSize = Gfx().WindowSize();
			float ratio = (float)_target->Height() / (float)_target->Width();
			targetSize.X = (int)(targetSize.X * ratio);
			Gfx().DrawImage(_target, bon::PointF(0, 0), &targetSize, bon::BlendModes::Opaque);

			// draw text
			Gfx().DrawText(_font, "Demo #7: Fake Resolution", bon::PointF(100, 100));
			Gfx().DrawText(_font, "This demo is using your desktop native resolution, but the scene itself is only 400x300 pixels (except for the text and cursor which are high res).\n\
This is done by drawing everything on a 400x300 texture, then stretching that texture to fit screen. The sprite below is only 160x160 pixels, but will always take about half the screen height.\n\
Fake resolution is useful for when you want to set a constant low resolution, but want your game to run in windowed mode / windowed fullscreen.\n\
This is also useful if you want to use an unorthodox resolution, but remember that if your ratio is too weird some parts of your scene will have to be outside of screen.\n\
\n\nHit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 18);

			// draw cursor
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64));

		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = FakeResolutionScene();
		bon::Start(scene);
	}

}