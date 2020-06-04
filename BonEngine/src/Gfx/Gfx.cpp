#include <Gfx/Gfx.h>
#include <Framework/Point.h>
#include <BonEngine.h>
#include <Diagnostics/IDiagnostics.h>


namespace bon
{
	namespace gfx
	{
		// init gfx manager
		void Gfx::_Initialize()
		{
			_Implementor.Initialize();
		}

		// dispose gfx resources
		void Gfx::_Dispose()
		{
		}

		// do updates
		void Gfx::_Update(double deltaTime)
		{
			// on update start, display previous frame
			_Implementor.UpdateWindow();
		}

		// called on main loop start
		void Gfx::_Start()
		{
			// if main loop started and user didn't set his own window, create a default one
			if (!_Implementor.HaveValidWindow())
			{
				SetWindowProperties("BonEngine Application", 800, 600, WindowModes::Windowed, true);
			}
		}

		// draw image
		void Gfx::DrawImage(const ImageAsset& sourceImage, const PointF& position, const PointI* size, BlendModes blend)
		{
			static PointI defaultSize(0, 0);
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawImage(sourceImage, position, size ? *size : defaultSize, blend);
		}

		// draw image
		void Gfx::DrawImage(const ImageAsset& sourceImage, const PointF& position, const PointI* size, BlendModes blend, const framework::RectangleI* sourceRect, const PointF* origin, float rotation, const Color* color)
		{
			static PointI defaultSize(0, 0);
			static RectangleI defaultRect(0, 0, 0, 0);
			static PointF defaultOrigin(0, 0);
			static Color defaultColor(1, 1, 1, 1);
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawImage(sourceImage, position, size ? *size : defaultSize, blend, sourceRect ? *sourceRect : defaultRect, origin ? *origin : defaultOrigin, rotation, color ? *color : defaultColor);
		}

		// draw sprite
		void Gfx::DrawSprite(const Sprite& sprite, const framework::PointF* offset)
		{
			if (offset) {
				framework::PointF position = sprite.Position + *offset;
				DrawImage(sprite.Image, position, &sprite.Size, sprite.Blend, &sprite.SourceRect, &sprite.Origin, sprite.Rotation, &sprite.Color);
			}
			else {
				DrawImage(sprite.Image, sprite.Position, &sprite.Size, sprite.Blend, &sprite.SourceRect, &sprite.Origin, sprite.Rotation, &sprite.Color);
			}
		}

		// draw text
		void Gfx::DrawText(const FontAsset& font, const char* text, const framework::PointF& position, const Color* color, int fontSize, int maxWidth, BlendModes blend, const PointF* origin, float rotation)
		{
			static Color defaultColor(1, 1, 1, 1);
			static PointF defaultOrigin(0, 0);
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawText(font, text, position, color ? *color : defaultColor, fontSize, blend, origin ? *origin : defaultOrigin, rotation, maxWidth);
		}

		// draw line
		void Gfx::DrawLine(const framework::PointI& from, const framework::PointI& to, const framework::Color& color, BlendModes blendMode)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawLine(from, to, color, blendMode);
		}
		
		// draw pixel
		void Gfx::DrawPixel(const framework::PointI& position, const framework::Color& color, BlendModes blendMode)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawPixel(position, color, blendMode);
		}
		
		// draw rectangle
		void Gfx::DrawRectangle(const framework::RectangleI& rect, const framework::Color& color, bool filled, BlendModes blendMode)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawRectangle(rect, color, filled, blendMode);
		}

		// get window size
		const PointI& Gfx::WindowSize() const
		{
			static PointI ret;
			ret.X = _Implementor.WindowWidth();
			ret.Y = _Implementor.WindowHeight();
			return ret;
		}

		void Gfx::SetTitle(const char* title)
		{
			_Implementor.SetTitle(title);
		}

		// set render target
		void Gfx::SetRenderTarget(const ImageAsset& target)
		{
			// current render target. we only store it to make sure asset is not lost by accident while set (its a shared ptr).
			static ImageAsset _renderTarget;

			// set render target
			_Implementor.SetRenderTarget(target);
			_renderTarget = target;
		}

		// clear the entire screen or part of it
		void Gfx::ClearScreen(const Color& color, const RectangleI& clearRect)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.ClearScreen(color, clearRect);
		}

		// set window properties
		void Gfx::SetWindowProperties(const char* title, int width, int height, WindowModes windowMode, bool showCursor)
		{
			_Implementor.CreateWindow(title, width, height, windowMode);
			_Implementor.ShowCursor(showCursor);
		}
	}
}