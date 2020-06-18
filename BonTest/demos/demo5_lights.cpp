#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo5_lights
{
	/**
	 * Scene with basic lighting.
	 */
	class LightsDemoScene : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

		// cursor image
		bon::ImageAsset _cursorImage;

		// background, light and lightmap
		bon::ImageAsset _backgroundImage;
		bon::ImageAsset _lightImage;
		bon::ImageAsset _lightMap;

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
			// load assets
			_cursorImage = Assets().LoadImage("../TestAssets/gfx/cursor.png");
			_lightImage = Assets().LoadImage("../TestAssets/gfx/light.png");
			_backgroundImage = Assets().LoadImage("../TestAssets/gfx/lights-scene.png");
			_lightMap = Assets().CreateEmptyImage(bon::PointI(800, 600));
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			if (Input().Down("exit")) { Game().Exit(); }
		}

		// drawing
		virtual void _Draw() override
		{
			// set lightsmap as target and paint it black
			Gfx().SetRenderTarget(_lightMap);
			Gfx().ClearScreen(bon::Color::Black);

			// paint light on cursor
			bon::PointF origin(0.5f, 0.5f);
			Gfx().DrawImage(_lightImage, Input().CursorPosition(), &bon::PointI(512, 512), bon::BlendModes::Additive, nullptr, &origin, 0, nullptr);

			// paint extra red light on background blob
			Gfx().DrawImage(_lightImage, bon::PointF(680, 265), &bon::PointI(256, 256), bon::BlendModes::Additive, nullptr, &origin, 0, &bon::Color(1,0,0,1));

			// draw scene background
			Gfx().SetRenderTarget(nullptr);
			Gfx().DrawImage(_backgroundImage, bon::PointF::Zero, &Gfx().WindowSize(), bon::BlendModes::Opaque);

			// draw lightmap
			Gfx().DrawImage(_lightMap, bon::PointF::Zero, &Gfx().WindowSize(), bon::BlendModes::Multiply);

			// draw demo
			Gfx().DrawText(_font, "Demo #5: Lights", bon::PointF(100, 100), nullptr, 0, 0, bon::BlendModes::AlphaBlend, nullptr, 0.0f, 1, &bon::Color::Black);
			Gfx().DrawText(_font, "This demo illustrates basic 2d lighting effect.\n\
It uses a black texture with additive rendering to add lights, then we\n\
paint this texture with multiply over the scene.\n\
Hit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 16);

			// draw cursor
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64));

		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = LightsDemoScene();
		bon::Start(scene);
	}

}