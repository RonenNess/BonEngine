#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo17_effects
{
	/**
	 * Scene with basic effects.
	 */
	class EffectsScene : public bon::engine::Scene
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

		// cell and grayscale effects
		bon::EffectAsset _celEffect;
		bon::EffectAsset _grayscaleEffect;
		bon::EffectAsset _shakeEffect;

		// last screenshot taken
		bon::ImageAsset _screenshot;

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
			_cursorImage = Assets().LoadImage("../TestAssets/gfx/cursor_with_pad.png");
			_lightImage = Assets().LoadImage("../TestAssets/gfx/light.png");
			_backgroundImage = Assets().LoadImage("../TestAssets/gfx/lights-scene.png");
			_lightMap = Assets().CreateEmptyImage(bon::PointI(800, 600));
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");

			// load cel effect for lightmap
			_grayscaleEffect = Assets().LoadEffect("../TestAssets/effects/grayscale/effect.ini");
			_celEffect = Assets().LoadEffect("../TestAssets/effects/cel/effect.ini");
			_shakeEffect = Assets().LoadEffect("../TestAssets/effects/wavey/effect.ini");
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			if (Input().Down("exit")) { 
				Game().Exit(); 
			}
			if (Input().ReleasedNow(bon::input::KeyCodes::KeyP)) { 
				_screenshot = Gfx().CreateImageFromScreen(); 
			}
		}

		// drawing
		virtual void _Draw() override
		{	
			// clear screen
			Gfx().ClearScreen(bon::Color::Black);

			// set lightsmap as target and paint it black
			Gfx().SetRenderTarget(_lightMap);
			Gfx().ClearScreen(bon::Color::Black);
			Gfx().UseEffect(nullptr);

			// paint light on cursor
			bon::PointF origin(0.5f, 0.5f);
			Gfx().DrawImage(_lightImage, Input().CursorPosition(), &bon::PointI(512, 512), bon::BlendModes::Additive, nullptr, &origin, 0, nullptr);

			// paint extra red light on background blob
			Gfx().DrawImage(_lightImage, bon::PointF(680, 265), &bon::PointI(256, 256), bon::BlendModes::Additive, nullptr, &origin, 0, &bon::Color(1, 0, 0, 1));

			// draw scene background
			Gfx().SetRenderTarget(nullptr);
			bool grayscale = Input().Down(bon::input::KeyCodes::KeySpace);
			if (grayscale)
			{
				Gfx().UseEffect(_grayscaleEffect);
			}
			auto windowSize = Gfx().WindowSize();
			Gfx().DrawImage(_backgroundImage, bon::PointF::Zero, &windowSize, bon::BlendModes::AlphaBlend);
			Gfx().UseEffect(nullptr);

			// draw lightmap with cel effect
			Gfx().UseEffect(_celEffect);
			if (!grayscale) { 
				windowSize.Y *= -1; 
			}
			Gfx().DrawImage(_lightMap, bon::PointF::Zero, &windowSize, bon::BlendModes::Multiply);
			Gfx().UseEffect(nullptr);

			// draw screenshot
			if (_screenshot != NULL)
			{
				Gfx().DrawImage(_screenshot, bon::PointF(800, 600), &(bon::PointI(800, 600) / 3), bon::BlendModes::Opaque, NULL, &bon::PointF(1, 1), 0, NULL);
			}

			// draw demo text
			Gfx().DrawText(_font, "Demo #17: Effects", bon::PointF(60, 100), nullptr, 0, 0, bon::BlendModes::AlphaBlend, nullptr, 0.0f, 1, &bon::Color::Black);
			Gfx().DrawText(_font, "This demo illustrates Effects.\n\
Its like the lights demo, but there's a CEL effect on the lightmap. \n\
Also the cursor is drawn with wavey effect. \n\
Hold down Space to draw in grayscale effect. \n\
Press 'P' to take a screenshot. \n\
Hit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 16);

			// draw cursor
			Gfx().UseEffect(_shakeEffect);
			_shakeEffect->SetUniformFloat("time", (float)Game().ElapsedTime());
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64), bon::BlendModes::AlphaBlend);
			Gfx().UseEffect(nullptr);
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		bon::BonFeatures features;
		features.EffectsEnabled = true;
		auto scene = EffectsScene();
		bon::Start(scene, features);
	}

}