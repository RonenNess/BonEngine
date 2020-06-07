/*****************************************************************//**
 * \file   CAPI_Managers_Gfx.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for gfx manager.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include <BonEngine.h>

#ifdef __cplusplus
extern "C" {
#endif

	// CAPI export of diagnostic counters
	BON_DLLEXPORT enum BON_BlendModes
	{
		BON_BlendModes_Additive = bon::BlendModes::Additive,
		BON_BlendModes_AlphaBlend = bon::BlendModes::AlphaBlend,
		BON_BlendModes_Mod = bon::BlendModes::Mod,
		BON_BlendModes_Multiply = bon::BlendModes::Multiply,
		BON_BlendModes_Opaque = bon::BlendModes::Opaque,
		BON_BlendModes__Count = bon::BlendModes::_Count,
	};

	// CAPI export of diagnostic counters
	BON_DLLEXPORT enum BON_WindowModes
	{
		BON_WindowModes_Fullscreen = bon::WindowModes::Fullscreen,
		BON_WindowModes_Windowed = bon::WindowModes::Windowed,
		BON_WindowModes_WindowedBorderless = bon::WindowModes::WindowedBorderless,
	};

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
	* Draws a rectangle.
	*/
	BON_DLLEXPORT void BON_Gfx_DrawRectangle(int x, int y, int w, int h, float r, float g, float b, float a, bool filled, BON_BlendModes blend);

	/**
	* Clear part or whole screen.
	*/
	BON_DLLEXPORT void BON_Gfx_ClearScreen(float r, float g, float b, float a, int x, int y, int w, int h);

#ifdef __cplusplus
}
#endif