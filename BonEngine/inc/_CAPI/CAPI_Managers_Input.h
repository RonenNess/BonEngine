/*****************************************************************//**
 * \file   CAPI_Managers_Input.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for input manager.
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

	/**
	 * All supported keyboard and mouse key codes.
	 */
	BON_DLLEXPORT enum BON_KeyCodes
	{
		BON_Key_Unknown,
		BON_Key_Return,
		BON_Key_Escape,
		BON_Key_Backspace,
		BON_Key_Tab,
		BON_Key_Space,
		BON_Key_Exclaim,
		BON_Key_Quotedbl,
		BON_Key_Hash,
		BON_Key_Percent,
		BON_Key_Dollar,
		BON_Key_Ampersand,
		BON_Key_Quote,
		BON_Key_Leftparen,
		BON_Key_Rightparen,
		BON_Key_Asterisk,
		BON_Key_Plus,
		BON_Key_Comma,
		BON_Key_Minus,
		BON_Key_Period,
		BON_Key_Slash,
		BON_Key_0,
		BON_Key_1,
		BON_Key_2,
		BON_Key_3,
		BON_Key_4,
		BON_Key_5,
		BON_Key_6,
		BON_Key_7,
		BON_Key_8,
		BON_Key_9,
		BON_Key_Colon,
		BON_Key_Semicolon,
		BON_Key_Less,
		BON_Key_Equals,
		BON_Key_Greater,
		BON_Key_Question,
		BON_Key_At,
		BON_Key_Leftbracket,
		BON_Key_Backslash,
		BON_Key_Rightbracket,
		BON_Key_Caret,
		BON_Key_Underscore,
		BON_Key_Backquote,
		BON_Key_A,
		BON_Key_B,
		BON_Key_C,
		BON_Key_D,
		BON_Key_E,
		BON_Key_F,
		BON_Key_G,
		BON_Key_H,
		BON_Key_I,
		BON_Key_J,
		BON_Key_K,
		BON_Key_L,
		BON_Key_M,
		BON_Key_N,
		BON_Key_O,
		BON_Key_P,
		BON_Key_Q,
		BON_Key_R,
		BON_Key_S,
		BON_Key_T,
		BON_Key_U,
		BON_Key_V,
		BON_Key_W,
		BON_Key_X,
		BON_Key_Y,
		BON_Key_Z,
		BON_Key_Capslock,
		BON_Key_F1,
		BON_Key_F2,
		BON_Key_F3,
		BON_Key_F4,
		BON_Key_F5,
		BON_Key_F6,
		BON_Key_F7,
		BON_Key_F8,
		BON_Key_F9,
		BON_Key_F10,
		BON_Key_F11,
		BON_Key_F12,
		BON_Key_Printscreen,
		BON_Key_Scrolllock,
		BON_Key_Pause,
		BON_Key_Insert,
		BON_Key_Home,
		BON_Key_Pageup,
		BON_Key_Delete,
		BON_Key_End,
		BON_Key_Pagedown,
		BON_Key_Right,
		BON_Key_Left,
		BON_Key_Down,
		BON_Key_Up,
		BON_Key_Numlockclear,
		BON_Key_KpDivide,
		BON_Key_KpMultiply,
		BON_Key_KpMinus,
		BON_Key_KpPlus,
		BON_Key_KpEnter,
		BON_Key_Kp1,
		BON_Key_Kp2,
		BON_Key_Kp3,
		BON_Key_Kp4,
		BON_Key_Kp5,
		BON_Key_Kp6,
		BON_Key_Kp7,
		BON_Key_Kp8,
		BON_Key_Kp9,
		BON_Key_Kp0,
		BON_Key_KpPeriod,
		BON_Key_Application,
		BON_Key_Power,
		BON_Key_KpEquals,
		BON_Key_F13,
		BON_Key_F14,
		BON_Key_F15,
		BON_Key_F16,
		BON_Key_F17,
		BON_Key_F18,
		BON_Key_F19,
		BON_Key_F20,
		BON_Key_F21,
		BON_Key_F22,
		BON_Key_F23,
		BON_Key_F24,
		BON_Key_Execute,
		BON_Key_Help,
		BON_Key_Menu,
		BON_Key_Select,
		BON_Key_Stop,
		BON_Key_Again,
		BON_Key_Undo,
		BON_Key_Cut,
		BON_Key_Copy,
		BON_Key_Paste,
		BON_Key_Find,
		BON_Key_Mute,
		BON_Key_Volumeup,
		BON_Key_Volumedown,
		BON_Key_KpComma,
		BON_Key_KpEqualsas400,
		BON_Key_Alterase,
		BON_Key_Sysreq,
		BON_Key_Cancel,
		BON_Key_Clear,
		BON_Key_Prior,
		BON_Key_Return2,
		BON_Key_Separator,
		BON_Key_Out,
		BON_Key_Oper,
		BON_Key_Clearagain,
		BON_Key_Crsel,
		BON_Key_Exsel,
		BON_Key_Kp00,
		BON_Key_Kp000,
		BON_Key_Thousandsseparator,
		BON_Key_Decimalseparator,
		BON_Key_Currencyunit,
		BON_Key_Currencysubunit,
		BON_Key_KpLeftparen,
		BON_Key_KpRightparen,
		BON_Key_KpLeftbrace,
		BON_Key_KpRightbrace,
		BON_Key_KpTab,
		BON_Key_KpBackspace,
		BON_Key_KpA,
		BON_Key_KpB,
		BON_Key_KpC,
		BON_Key_KpD,
		BON_Key_KpE,
		BON_Key_KpF,
		BON_Key_KpXor,
		BON_Key_KpPower,
		BON_Key_KpPercent,
		BON_Key_KpLess,
		BON_Key_KpGreater,
		BON_Key_KpAmpersand,
		BON_Key_KpDblampersand,
		BON_Key_KpVerticalbar,
		BON_Key_KpDblverticalbar,
		BON_Key_KpColon,
		BON_Key_KpHash,
		BON_Key_KpSpace,
		BON_Key_KpAt,
		BON_Key_KpExclam,
		BON_Key_KpMemstore,
		BON_Key_KpMemrecall,
		BON_Key_KpMemclear,
		BON_Key_KpMemadd,
		BON_Key_KpMemsubtract,
		BON_Key_KpMemmultiply,
		BON_Key_KpMemdivide,
		BON_Key_KpPlusminus,
		BON_Key_KpClear,
		BON_Key_KpClearentry,
		BON_Key_KpBinary,
		BON_Key_KpOctal,
		BON_Key_KpDecimal,
		BON_Key_KpHexadecimal,
		BON_Key_Lctrl,
		BON_Key_Lshift,
		BON_Key_Lalt,
		BON_Key_Lgui,
		BON_Key_Rctrl,
		BON_Key_Rshift,
		BON_Key_Ralt,
		BON_Key_Rgui,
		BON_Key_Mode,
		BON_Key_Audionext,
		BON_Key_Audioprev,
		BON_Key_Audiostop,
		BON_Key_Audioplay,
		BON_Key_Audiomute,
		BON_Key_Mediaselect,
		BON_Key_Www,
		BON_Key_Mail,
		BON_Key_Calculator,
		BON_Key_Computer,
		BON_Key_AcSearch,
		BON_Key_AcHome,
		BON_Key_AcBack,
		BON_Key_AcForward,
		BON_Key_AcStop,
		BON_Key_AcRefresh,
		BON_Key_AcBookmarks,
		BON_Key_Brightnessdown,
		BON_Key_Brightnessup,
		BON_Key_Displayswitch,
		BON_Key_Kbdillumtoggle,
		BON_Key_Kbdillumdown,
		BON_Key_Kbdillumup,
		BON_Key_Eject,
		BON_Key_Sleep,
		BON_Key_App1,
		BON_Key_App2,
		BON_Key_Audiorewind,
		BON_Key_Audiofastforward,
		BON_Mouse_Left,
		BON_Mouse_Middle,
		BON_Mouse_Right,
		BON_Mouse_X1,
		BON_Mouse_X2,
	};

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

#ifdef __cplusplus
}
#endif