/*****************************************************************//**
 * \file   CAPI_Defs.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for general defs.
 *
 * \author Ronen Ness Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "../BonEngine.h"

#pragma warning( push )
#pragma warning(disable: 4091)

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * Define callback without arguments.
	 */
	BON_DLLEXPORT typedef void(__stdcall* BON_CallbackNoArgs)();

	/**
	 * Define callback with double argument.
	 */
	BON_DLLEXPORT typedef void(__stdcall* BON_CallbackDoubleArg)(double);

	/**
	* Store data related to text input.
	*/
	struct BON_DLLEXPORT BON_TextInputData
	{
		bool Backspace;
		bool Delete;
		bool Copy;
		bool Paste;
		bool Tab;
		bool Up;
		bool Down;
		bool Left;
		bool Right;
		bool Home;
		bool End;
		bool Insert;
		char Text[32];
	};

	/**
	 * CAPI export of text input modes.
	 */
	BON_DLLEXPORT enum BON_UITextInputMode
	{
		BON_UITextInputMode_AnyText = bon::UITextInputMode::AnyText,
		BON_UITextInputMode_AlphaOnly = bon::UITextInputMode::AlphaOnly,
		BON_UITextInputMode_Lowercase = bon::UITextInputMode::Lowercase,
		BON_UITextInputMode_Uppercase = bon::UITextInputMode::Uppercase,
		BON_UITextInputMode_NoNumbers = bon::UITextInputMode::NoNumbers,
		BON_UITextInputMode_NumbersOnly = bon::UITextInputMode::NumbersOnly,
	};

	/**
	 * CAPI export of image filters.
	 */
	BON_DLLEXPORT enum BON_ImageFilterMode
	{
		BON_Filter_Nearest = bon::ImageFilterMode::Nearest,
		BON_Filter_Linear = bon::ImageFilterMode::Linear,
		BON_Filter_Anisotropic = bon::ImageFilterMode::Anisotropic,
		BON_Filter__Count = bon::ImageFilterMode::_Count,
	};

	/**
	 * CAPI export of engine states.
	 */
	BON_DLLEXPORT enum BON_Engine_States
	{
		BON_State_BeforeInitialize = bon::engine::EngineStates::BeforeInitialize,
		BON_State_Initialize = bon::engine::EngineStates::Initialize,
		BON_State_InternalUpdate = bon::engine::EngineStates::InternalUpdate,
		BON_State_FixedUpdate = bon::engine::EngineStates::FixedUpdate,
		BON_State_Update = bon::engine::EngineStates::Update,
		BON_State_Draw = bon::engine::EngineStates::Draw,
		BON_State_MainLoopInBetweens = bon::engine::EngineStates::MainLoopInBetweens,
		BON_State_HandleEvents = bon::engine::EngineStates::HandleEvents,
		BON_State_Stopping = bon::engine::EngineStates::Stopping,
		BON_State_Destroyed = bon::engine::EngineStates::Destroyed,
		BON_State_SwitchScene = bon::engine::EngineStates::SwitchScene
	};

	/**
	 * CAPI export of diagnostic counters.
	 */
	BON_DLLEXPORT enum BON_DiagnosticCounters
	{
		BON_Counters_DrawCalls = bon::DiagnosticsCounters::DrawCalls,
		BON_Counters_PlaySoundCalls = bon::DiagnosticsCounters::PlaySoundCalls,
		BON_Counters_LoadedAssets = bon::DiagnosticsCounters::LoadedAssets,
		BON_Counters__BuiltInCounterCount = bon::DiagnosticsCounters::_BuiltInCounterCount,
		BON_Counters__MaxCounters = bon::DiagnosticsCounters::_MaxCounters,
	};

	/**
	 * CAPI export of diagnostic counters.
	 */
	BON_DLLEXPORT enum BON_BlendModes
	{
		BON_BlendModes_Additive = bon::BlendModes::Additive,
		BON_BlendModes_AlphaBlend = bon::BlendModes::AlphaBlend,
		BON_BlendModes_Mod = bon::BlendModes::Mod,
		BON_BlendModes_Multiply = bon::BlendModes::Multiply,
		BON_BlendModes_Opaque = bon::BlendModes::Opaque,
		BON_BlendModes__Count = bon::BlendModes::_Count,
	};

	/**
	 * CAPI export of diagnostic counters.
	 */
	BON_DLLEXPORT enum BON_WindowModes
	{
		BON_WindowModes_Fullscreen = bon::WindowModes::Fullscreen,
		BON_WindowModes_Windowed = bon::WindowModes::Windowed,
		BON_WindowModes_WindowedBorderless = bon::WindowModes::WindowedBorderless,
	};

	/**
	* Log levels.
	*/
	BON_DLLEXPORT enum BON_LogLevel
	{
		BON_LogLevel_None = bon::LogLevel::None,
		BON_LogLevel_Debug = bon::LogLevel::Debug,
		BON_LogLevel_Info = bon::LogLevel::Info,
		BON_LogLevel_Warn = bon::LogLevel::Warn,
		BON_LogLevel_Error = bon::LogLevel::Error,
		BON_LogLevel_Crit = bon::LogLevel::Critical,
	};

	/**
	 * CAPI export of diagnostic counters.
	 */
	BON_DLLEXPORT enum BON_AudioFormats
	{
		BON_AudioFormats_S16LSB = bon::AudioFormats::S16LSB,
		BON_AudioFormats_S16MSB = bon::AudioFormats::S16MSB,
		BON_AudioFormats_S8 = bon::AudioFormats::S8,
		BON_AudioFormats_U16LSB = bon::AudioFormats::U16LSB,
		BON_AudioFormats_U16MSB = bon::AudioFormats::U16MSB,
		BON_AudioFormats_U8 = bon::AudioFormats::U8,
	};

	/**
	 * CAPI export of ui element types.
	 */
	BON_DLLEXPORT enum BON_UIElementType
	{
		BON_UIElement = bon::UIElementType::Element,
		BON_UIButton = bon::UIElementType::Button,
		BON_UICheckbox = bon::UIElementType::Checkbox,
		BON_UIRadio = bon::UIElementType::Radio,
		BON_UIImage = bon::UIElementType::Image,
		BON_UIList = bon::UIElementType::List,
		BON_UIText = bon::UIElementType::Text,
		BON_UIScrollbar = bon::UIElementType::Scrollbar,
		BON_UISlider = bon::UIElementType::Slider,
		BON_UIWindow = bon::UIElementType::Window,
	};

	/**
	 * CAPI export of ui element size modes.
	 */
	BON_DLLEXPORT enum BON_UISizeType
	{
		BON_UISizeType_Pixels = bon::UISizeType::Pixels,
		BON_UISizeType_PercentOfParent = bon::UISizeType::PercentOfParent,
	};

	/**
	 * CAPI export of UI image types.
	 */
	BON_DLLEXPORT enum BON_UIImageTypes
	{
		BON_UIImageTypes_Single = bon::UIImageTypes::Single,
		BON_UIImageTypes_Sliced = bon::UIImageTypes::Sliced,
		BON_UIImageTypes_Stretch = bon::UIImageTypes::Stretch,
		BON_UIImageTypes_Tiled = bon::UIImageTypes::Tiled,
	};

	/**
	 * CAPI export of text alignment.
	 */
	BON_DLLEXPORT enum BON_UITextAlignment
	{
		BON_UITextAlignment_Left = bon::UITextAlignment::Left,
		BON_UITextAlignment_Right = bon::UITextAlignment::Right,
		BON_UITextAlignment_Center = bon::UITextAlignment::Center,
	};

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

#ifdef __cplusplus
}
#endif

#pragma warning( pop )