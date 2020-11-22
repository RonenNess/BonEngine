/*****************************************************************//**
 * \file   CAPI_Managers_UI.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for ui manager.
 *
 * \author Ronen Ness Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "CAPI_Defs.h"
#include "../Assets/Defs.h"
#include "../UI/IUI.h"
#include "../Framework/Point.h"
#include "../Framework/Rectangle.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Release a UI element.
	*/
	BON_DLLEXPORT void BON_UI_ReleaseElement(bon::UIElement* element);

	/**
	* Set cursor to render.
	*/
	BON_DLLEXPORT void BON_UI_SetCursorEx(const bon::assets::ImageAsset* image, int width, int height, int offsetX, int offsetY);

	/**
	* Set cursor to render from image element.
	*/
	BON_DLLEXPORT void BON_UI_SetCursor(const bon::UIImage* image);

	/**
	* Draw cursor, based on what set with SetCursor().
	*/
	BON_DLLEXPORT void BON_UI_DrawCursor();

	/**
	* Draw a UI system or element.
	*/
	BON_DLLEXPORT void BON_UI_Draw(bon::UIElement* root, bool drawCursor);

	/**
	* Update a UI system and to all interactions.
	*/
	BON_DLLEXPORT bon::UIElement* BON_UI_UpdateUI(bon::UIElement* root);

	/**
	* Create and return a new root element.
	*/
	BON_DLLEXPORT bon::UIElement* BON_UI_CreateRoot();

	/**
	* Create and return an empty container element.
	*/
	BON_DLLEXPORT bon::UIElement* BON_UI_CreateContainer(const char* stylesheet, bon::UIElement* parent);

	/**
	* Create and return an image element.
	*/
	BON_DLLEXPORT bon::UIImage* BON_UI_CreateImage(const char* stylesheet, bon::UIElement* parent);

	/**
	* Create and return a text element.
	*/
	BON_DLLEXPORT bon::UIText* BON_UI_CreateText(const char* stylesheet, bon::UIElement* parent, const char* text);

	/**
	* Create and return a window element.
	*/
	BON_DLLEXPORT bon::UIWindow* BON_UI_CreateWindow(const char* stylesheet, bon::UIElement* parent, const char* title);

	/**
	* Create and return a button element.
	*/
	BON_DLLEXPORT bon::UIButton* BON_UI_CreateButton(const char* stylesheet, bon::UIElement* parent, const char* caption);

	/**
	* Create and return a text input element.
	*/
	BON_DLLEXPORT bon::UITextInput* BON_UI_CreateTextInput(const char* stylesheet, bon::UIElement* parent, const char* startingVal, const char* placeholder);

	/**
	* Create and return a checkbox element.
	*/
	BON_DLLEXPORT bon::UICheckBox* BON_UI_CreateCheckbox(const char* stylesheet, bon::UIElement* parent, const char* caption);

	/**
	* Create and return a radio button element.
	*/
	BON_DLLEXPORT bon::UIRadioButton* BON_UI_CreateRadioButton(const char* stylesheet, bon::UIElement* parent, const char* caption);

	/**
	* Create and return a list element.
	*/
	BON_DLLEXPORT bon::UIList* BON_UI_CreateList(const char* stylesheet, bon::UIElement* parent);

	/**
	* Create and return a dropdown element.
	*/
	BON_DLLEXPORT bon::UIDropDown* BON_UI_CreateDropDown(const char* stylesheet, bon::UIElement* parent);

	/**
	* Create and return a slider element.
	*/
	BON_DLLEXPORT bon::UISlider* BON_UI_CreateSlider(const char* stylesheet, bon::UIElement* parent);

	/**
	* Create and return a vertical scrollbar element.
	*/
	BON_DLLEXPORT bon::UIVerticalScrollbar* BON_UI_CreateVerticalScrollbar(const char* stylesheet, bon::UIElement* parent);

#ifdef __cplusplus
}
#endif