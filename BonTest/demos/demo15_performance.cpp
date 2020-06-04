#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"
#include <vector>

namespace demo15_performance
{
	/**
	 * Basic performance test scene.
	 */
	class PerformanceTestScene : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

		// cursor image
		bon::ImageAsset _cursorImage;

		// gnu sprite
		bon::ImageAsset _spriteImage;

		// sprites vector
		std::vector<bon::Sprite*> _sprites;

		// are sprites rotating
		bool _rotating = false;

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
			_spriteImage = Assets().LoadImage("../TestAssets/gfx/perf.png");
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf", 36);

			// create start of 1000 sprites
			for (int i = 0; i < 1000; ++i) {
				CreateSprite();
			}
		}

		// create a new sprite
		void CreateSprite()
		{
			bon::Sprite* sprite = new bon::Sprite();
			static auto windowSize = Gfx().WindowSize();
			sprite->Image = _spriteImage;
			sprite->Position.Set((float)(rand() % windowSize.X), (float)(rand() % windowSize.Y));
			sprite->Origin.Set(0.5f, 0.5f);
			if (_rotating) { sprite->Rotation = (float)(rand() % 360); }
			_sprites.push_back(sprite);
		}

		// on scene unload
		virtual void _Unload() override
		{
			for (auto sp : _sprites)
			{
				delete sp;
			}
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			// exit up
			if (Input().Down("exit")) { Game().Exit(); }

			// add sprites
			if (Input().Down(bon::KeyCodes::KeySpace)) 
			{ 
				for (int i = 0; i < 100; ++i) {
					CreateSprite();
				}
			}

			// rotate
			if (Input().ReleasedNow(bon::KeyCodes::KeyZ))
			{
				for (auto sp : _sprites)
				{
					sp->Rotation = (float)(rand() % 360);					
				}
				_rotating = true;
			}
		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color(0.2f, 0.5f, 1.0f));

			// draw sprites
			double dt = Game().DeltaTime();
			for (auto sp : _sprites)
			{
				if (_rotating) {
					sp->Rotation += (float)(dt * 160.0);
				}
				Gfx().DrawSprite(*sp);
			}

			// draw text data and FPS
			Gfx().DrawText(_font, "Demo #15: Performance Test", bon::PointF(100, 120));
			Gfx().DrawText(_font, "Performance test, drawing lots of sprites.\nPress Space to add sprites.\nPress 'Z' to rotate sprites (slower).\nHit escape to exit.", bon::PointF(100, 220), &bon::Color::White, 24);
			Gfx().DrawText(_font, (std::string("FPS: ") + std::to_string(Diagnostics().FpsCount())).c_str(), bon::PointF(0, 0), &bon::Color::White, 22);
			Gfx().DrawText(_font, (std::string("Sprites: ") + std::to_string(_sprites.size())).c_str(), bon::PointF(0, 35), &bon::Color::White, 22);

			// draw cursor
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64));

			// show draw calls count (doing it last to include everything)
			Gfx().DrawText(_font, (std::string("Draw Calls: ") + std::to_string(Diagnostics().GetCounter(bon::DiagnosticsCounters::DrawCalls))).c_str(), bon::PointF(0, 70), &bon::Color::White, 22);
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = PerformanceTestScene();
		bon::Start(scene);
	}

}