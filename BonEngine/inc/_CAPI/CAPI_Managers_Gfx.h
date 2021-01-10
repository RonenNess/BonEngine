/*****************************************************************//**
 * \file   CAPI_Managers_Gfx.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for gfx manager.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "CAPI_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Draw an image on screen.
	*/
	BON_DLLEXPORT void BON_Gfx_DrawImage(const bon::assets::ImageAsset* image, float x, float y, int width, int height, BON_BlendModes blend);

	/**
	* Draw an image on screen.
	*/
	BON_DLLEXPORT void BON_Gfx_DrawImageEx(const bon::assets::ImageAsset* image, float x, float y, int width, int height, BON_BlendModes blend, int sx, int sy, int swidth, int sheight, float originX, float originY, float rotation, float r, float g, float b, float a);

	/**
	* Draw text on screen.
	*/
	BON_DLLEXPORT void BON_Gfx_DrawText(const bon::assets::FontAsset* font, const char* text, float x, float y, float r, float g, float b, float a, int fontSize, int maxWidth, BON_BlendModes blend, float originX, float originY, float rotation);

	/**
	* Draw text with outline on screen.
	*/
	BON_DLLEXPORT void BON_Gfx_DrawTextWithOutline(const bon::assets::FontAsset* font, const char* text, float x, float y, float r, float g, float b, float a, int fontSize, int maxWidth, BON_BlendModes blend, float originX, float originY, float rotation, int outlineWidth, float outlineR, float outlineG, float outlineB, float outlineA);
	
	/**
	* Draws a line.
	*/
	BON_DLLEXPORT void BON_Gfx_DrawLine(int x1, int y1, int x2, int y2, float r, float g, float b, float a, BON_BlendModes blend);

	/**
	* Draws a pixel.
	*/
	BON_DLLEXPORT void BON_Gfx_DrawPixel(int x, int y, float r, float g, float b, float a, BON_BlendModes blend);
	
	/**
	* Set window properties.
	*/
	BON_DLLEXPORT void BON_Gfx_SetWindowProperties(const char* title, int width, int height, BON_WindowModes windowMode, bool showCursor);

	/**
	* Set the window's title.
	*/
	BON_DLLEXPORT void BON_Gfx_SetTitle(const char* title);

	/**
	* Get window's size
	*/
	BON_DLLEXPORT void BON_Gfx_WindowSize(int* x, int* y);

	/**
	* Get renderable region size
	*/
	BON_DLLEXPORT void BON_Gfx_RenderableSize(int* x, int* y);

	/**
	* Get window's width in pixels.
	*/
	BON_DLLEXPORT int BON_Gfx_WindowSizeX();

	/**
	* Get window's height in pixels.
	*/
	BON_DLLEXPORT int BON_Gfx_WindowSizeY();

	/**
	* Set the target we render to.
	*/
	BON_DLLEXPORT void BON_Gfx_SetRenderTarget(const bon::assets::ImageAsset* target);
	
	/**
	 * Get render target or null.
	 */
	BON_DLLEXPORT bon::assets::ImageAsset* BON_Gfx_GetRenderTarget();
	
	/**
	 * Create image asset from screen.
	 */
	BON_DLLEXPORT bon::assets::ImageAsset* BON_Gfx_CreateImageFromScreen();

	/**
	 * Set effect to use.
	 */
	BON_DLLEXPORT void BON_Gfx_UseEffect(const bon::assets::EffectAsset* effect);

	/**
	* Draws a rectangle.
	*/
	BON_DLLEXPORT void BON_Gfx_DrawRectangle(int x, int y, int w, int h, float r, float g, float b, float a, bool filled, BON_BlendModes blend, float originX, float originY, float rotation);

	/**
	* Draws a circle.
	*/
	BON_DLLEXPORT void BON_Gfx_DrawCircle(int x, int y, int radius, float r, float g, float b, float a, bool filled, BON_BlendModes blend);

	/**
	 * Draws a polygon.
	 */
	BON_DLLEXPORT void BON_Gfx_DrawPolygon(int x1, int y1, int x2, int y2, int x3, int y3, float r, float g, float b, float a, BON_BlendModes blend);
	
	/**
	 * Draws a quad.
	 */
	BON_DLLEXPORT void BON_Gfx_DrawQuad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, float r, float g, float b, float a, BON_BlendModes blend);


	/**
	* Clear part or whole screen.
	*/
	BON_DLLEXPORT void BON_Gfx_ClearScreen(float r, float g, float b, float a, int x, int y, int w, int h);

	/**
	* Set viewport to draw on, or 0,0,0,0 to clear viewport.
	*/
	BON_DLLEXPORT void BON_Gfx_SetViewport(int x, int y, int w, int h);

	/**
	 * Get the estimated bounding box of a text drawing.
	 */
	BON_DLLEXPORT void BON_Gfx_GetTextBoundingBox(const bon::assets::FontAsset* font, const char* text, float x, float y, int fontSize, int maxWidth, float originX, float originY, float rotation, int* outX, int* outY, int* outWidth, int* outHeight);

#ifdef __cplusplus
}
#endif