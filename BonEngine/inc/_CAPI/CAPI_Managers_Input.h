/*****************************************************************//**
 * \file   CAPI_Managers_Input.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for input manager.
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
	* Get if a given game action is down.
	*/
	BON_DLLEXPORT bool BON_Input_Down(const char* actionId);

	/**
	* Get if a given game action was released this frame
	*/
	BON_DLLEXPORT bool BON_Input_ReleasedNow(const char* actionId);

	/**
	* Get if a given game action was pressed this frame
	*/
	BON_DLLEXPORT bool BON_Input_PressedNow(const char* actionId);

	/**
	* Get if a key code is down.
	*/
	BON_DLLEXPORT bool BON_Input_KeyDown(BON_KeyCodes key);

	/**
	* Get if a key code was released this frame
	*/
	BON_DLLEXPORT bool BON_Input_KeyReleasedNow(BON_KeyCodes key);

	/**
	* Get if a key code was pressed this frame
	*/
	BON_DLLEXPORT bool BON_Input_KeyPressedNow(BON_KeyCodes key);

	/**
	* Get scrolling delta X.
	*/
	BON_DLLEXPORT int BON_Input_ScrollDeltaX();
	
	/**
	* Get scrolling delta Y.
	*/
	BON_DLLEXPORT int BON_Input_ScrollDeltaY();

	/**
	* Get cursor position X.
	*/
	BON_DLLEXPORT int BON_Input_CursorPositionX();

	/**
	* Get cursor position Y.
	*/
	BON_DLLEXPORT int BON_Input_CursorPositionY();

	/**
	* Get cursor movement from last frame X.
	*/
	BON_DLLEXPORT int BON_Input_CursorDeltaX();
	
	/**
	* Get cursor movement from last frame Y.
	*/
	BON_DLLEXPORT int BON_Input_CursorDeltaY();

	/**
	* Bind a key to an action id.
	*/
	BON_DLLEXPORT void BON_Input_SetKeyBind(BON_KeyCodes keyCode, const char* actionId);

	/**
	* Get list of key codes assigned to given action id.
	*/
	BON_DLLEXPORT int* BON_Input_GetAssignedKeys(const char* actionId, int* retLength);

	/**
	* Get clipboard content.
	*/
	BON_DLLEXPORT const char* BON_Input_GetClipboard();

	/**
	* Set clipboard content.
	*/
	BON_DLLEXPORT void BON_Input_SetClipboard(const char* value);

	/**
	* Get text input data.
	*/
	BON_DLLEXPORT BON_TextInputData BON_Input_GetTextInput(const char* value);

	/**
	* Load key binds from config asset.
	*/
	BON_DLLEXPORT void BON_Input_LoadControlsFromConfig(bon::ConfigAsset* config, bool replaceExisting);

#ifdef __cplusplus
}
#endif