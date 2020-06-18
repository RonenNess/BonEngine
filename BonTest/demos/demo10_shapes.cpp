#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo10_shapes
{
	/**
	 * Drawing shapes scene.
	 */
	class ShapesDemoScene : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

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
			// clear screen
			Gfx().ClearScreen(bon::Color::Cornflower);

			// draw text
			Gfx().DrawText(_font, "Demo #10: Drawing Shapes", bon::PointF(100, 100), nullptr, 0, 0, bon::BlendModes::AlphaBlend, nullptr, 0.0f, 1, &bon::Color::Black);
			Gfx().DrawText(_font, "In this demo you see how to draw shapes, lines and pixels on screen.\nHit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 18);

			// draw pixels
			for (int i = 0; i < 500; ++i) {
				bon::Color color = bon::Color(0, 1, 0, 1);
				Gfx().DrawPixel(bon::PointI(100 + rand() % 100, 400 + rand() % 100), color);
			}

			// draw rect outline
			Gfx().DrawRectangle(bon::RectangleI(250, 400, 100, 100), bon::Color(0, 1, 0, 1), false);

			// draw rect fill
			Gfx().DrawRectangle(bon::RectangleI(400, 400, 100, 100), bon::Color(0, 1, 0, 1), true);

			// draw circle outline
			Gfx().DrawCircle(bon::PointI(600, 300), 25, bon::Color(1, 1, 0, 1), false);
			Gfx().DrawCircle(bon::PointI(675, 300), 25, bon::Color(1, 0, 1, 1), true);
			Gfx().DrawCircle(bon::PointI(750, 300), 25, bon::Color(1, 0, 1, 0.5f), true);


			// draw line
			double elapsed = Game().ElapsedTime() * 3;
			Gfx().DrawLine(bon::PointI(50, 400 + (int)(sin(elapsed) * 25)), bon::PointI(600, 400 + (int)(cos(elapsed) * 25)), bon::Color(1, 0, 0, 1));

		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = ShapesDemoScene();
		bon::Start(scene);
	}

}