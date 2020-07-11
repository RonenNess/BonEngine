#include <_CAPI/CAPI_Managers_Gfx.h>
#include <BonEngine.h>

/**
* Draw an image on screen.
*/
void BON_Gfx_DrawImage(const bon::assets::ImageAsset* image, float x, float y, int width, int height, BON_BlendModes blend)
{
	bon::_GetEngine().Gfx().DrawImage(*image, bon::PointF(x, y), &bon::PointI(width, height), (bon::BlendModes)blend);
}

/**
* Draw an image on screen.
*/
void BON_Gfx_DrawImageEx(const bon::assets::ImageAsset* image, float x, float y, int width, int height, BON_BlendModes blend, int sx, int sy, int swidth, int sheight, float originX, float originY, float rotation, float r, float g, float b, float a)
{
	bon::_GetEngine().Gfx().DrawImage(*image, bon::PointF(x, y), &bon::PointI(width, height), (bon::BlendModes)blend, &bon::RectangleI(sx, sy, swidth, sheight), &bon::PointF(originX, originY), rotation, &bon::Color(r,g,b,a));
}

/**
* Draw text on screen.
*/
void BON_Gfx_DrawText(const bon::assets::FontAsset* font, const char* text, float x, float y, float r, float g, float b, float a, int fontSize, int maxWidth, BON_BlendModes blend, float originX, float originY, float rotation)
{
	bon::_GetEngine().Gfx().DrawText(*font, text, bon::PointF(x, y), &bon::Color(r, g, b, a), fontSize, maxWidth, (bon::BlendModes)blend, &bon::PointF(originX, originY), rotation);
}

/**
* Draw text with outline on screen.
*/
BON_DLLEXPORT void BON_Gfx_DrawTextWithOutline(const bon::assets::FontAsset* font, const char* text, float x, float y, float r, float g, float b, float a, int fontSize, int maxWidth, BON_BlendModes blend, float originX, float originY, float rotation, int outlineWidth, float outlineR, float outlineG, float outlineB, float outlineA)
{
	bon::_GetEngine().Gfx().DrawText(*font, text, bon::PointF(x, y), &bon::Color(r, g, b, a), fontSize, maxWidth, (bon::BlendModes)blend, &bon::PointF(originX, originY), rotation, outlineWidth, &bon::Color(outlineR, outlineG, outlineB, outlineA));
}

/**
* Draws a line.
*/
void BON_Gfx_DrawLine(int x1, int y1, int x2, int y2, float r, float g, float b, float a, BON_BlendModes blend)
{
	bon::_GetEngine().Gfx().DrawLine(bon::PointI(x1, y1), bon::PointI(x2, y2), bon::Color(r, g, b, a), (bon::BlendModes)blend);
}

/**
* Draws a pixel.
*/
void BON_Gfx_DrawPixel(int x, int y, float r, float g, float b, float a, BON_BlendModes blend)
{
	bon::_GetEngine().Gfx().DrawPixel(bon::PointI(x, y), bon::Color(r, g, b, a), (bon::BlendModes)blend);
}

/**
* Set window properties.
*/
void BON_Gfx_SetWindowProperties(const char* title, int width, int height, BON_WindowModes windowMode, bool showCursor)
{
	bon::_GetEngine().Gfx().SetWindowProperties(title, width, height, (bon::WindowModes)windowMode, showCursor);
}

/**
* Set the window's title.
*/
void BON_Gfx_SetTitle(const char* title)
{
	bon::_GetEngine().Gfx().SetTitle(title);
}

/**
* Get window's size
*/
void BON_Gfx_WindowSize(int* x, int* y)
{
	*x = bon::_GetEngine().Gfx().WindowSize().X;
	*y = bon::_GetEngine().Gfx().WindowSize().Y;
}

/**
* Get renderable region size
*/
void BON_Gfx_RenderableSize(int* x, int* y)
{
	bon::PointI ret = bon::_GetEngine().Gfx().RenderableSize();
	*x = ret.X;
	*y = ret.Y;
}

/**
* Get window's width in pixels.
*/
int BON_Gfx_WindowSizeX()
{
	return bon::_GetEngine().Gfx().WindowSize().X;
}

/**
* Get window's height in pixels.
*/
int BON_Gfx_WindowSizeY()
{
	return bon::_GetEngine().Gfx().WindowSize().Y;
}

/**
 * Set render target.
 */
void BON_Gfx_SetRenderTarget(const bon::assets::ImageAsset* target)
{
	bon::_GetEngine().Gfx().SetRenderTarget(target ? *target : nullptr);
}

/**
 * Get render target.
 */
bon::assets::ImageAsset* BON_Gfx_GetRenderTarget()
{	
	return (bon::assets::ImageAsset*)(&bon::_GetEngine().Gfx().GetRenderTarget());
}

/**
* Draws a rectangle.
*/
void BON_Gfx_DrawRectangle(int x, int y, int w, int h, float r, float g, float b, float a, bool filled, BON_BlendModes blend)
{
	bon::_GetEngine().Gfx().DrawRectangle(bon::RectangleI(x, y, w, h), bon::Color(r, g, b, a), filled, (bon::BlendModes)blend);
}

/**
* Draws a circle.
*/
void BON_Gfx_DrawCircle(int x, int y, int radius, float r, float g, float b, float a, bool filled, BON_BlendModes blend)
{
	bon::_GetEngine().Gfx().DrawCircle(bon::PointI(x, y), radius, bon::Color(r, g, b, a), filled, (bon::BlendModes)blend);
}

/**
* Clear part or whole screen.
*/
void BON_Gfx_ClearScreen(float r, float g, float b, float a, int x, int y, int w, int h)
{
	bon::_GetEngine().Gfx().ClearScreen(bon::Color(r, g, b, a), bon::RectangleI(x, y, w, h));
}

/**
* Set viewport to draw on, or 0, 0, 0, 0 to clear viewport.
*/
void BON_Gfx_SetViewport(int x, int y, int w, int h)
{
	if (w == 0 && h == 0) {
		bon::_GetEngine().Gfx().SetViewport(nullptr);
	}
	else {
		bon::_GetEngine().Gfx().SetViewport(&bon::framework::RectangleI(x, y, w, h));
	}
}

/**
* Get text bounding box.
*/
void BON_Gfx_GetTextBoundingBox(const bon::assets::FontAsset* font, const char* text, float x, float y, int fontSize, int maxWidth, float originX, float originY, float rotation, int* outX, int* outY, int* outWidth, int* outHeight)
{
	auto ret = bon::_GetEngine().Gfx().GetTextBoundingBox(*font, text, bon::framework::PointF(x, y), fontSize, maxWidth, &bon::PointF(originX, originY), rotation);
	*outX = ret.X;
	*outY = ret.Y;
	*outWidth = ret.Width;
	*outHeight = ret.Height;
}