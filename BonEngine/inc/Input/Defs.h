/*****************************************************************//**
 * \file   Defs.h
 * \brief  Misc input-related defs.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"


namespace bon
{
	namespace input
	{
		/**
		 * Store data related to text input.
		 */
		struct BON_DLLEXPORT TextInputData
		{
			/**
			 * Is backspace being pressed in this frame?
			 */
			bool Backspace = false;

			/**
			 * Is delete being pressed in this frame?
			 */
			bool Delete = false;

			/**
			 * Was copy command issued in this frame? (ctrl c).
			 */
			bool Copy = false;

			/**
			 * Was paste command issues in this frame? (ctrl v).
			 */
			bool Paste = false;

			/**
			 * Was tab pressed in this frame?
			 */
			bool Tab = false;

			/**
			 * Was key up pressed this frame?
			 */
			bool Up = false;

			/**
			 * Was key down pressed this frame?
			 */
			bool Down = false;

			/**
			 * Was key left pressed this frame?
			 */
			bool Left = false;

			/**
			 * Was key right pressed this frame?
			 */
			bool Right = false;

			/**
			 * Was key home pressed this frame?
			 */
			bool Home = false;

			/**
			 * Was key end pressed this frame?
			 */
			bool End = false;

			/**
			 * Was key insert pressed this frame?
			 */
			bool Insert = false;

			/**
			 * Text input in current frame.
			 */
			char Text[32] = { '\0' };
		};

		/**
		 * Possible key states.
		 */
		enum class BON_DLLEXPORT KeyStates
		{
			// key is up.
			Released,

			// key is up, but was down last frame.
			ReleasedNow,

			// key is down.
			Pressed,

			// key is down, but was up last frame.
			PressedNow
		};

		/**
		 * All supported keyboard and mouse key codes.
		 */
		enum class BON_DLLEXPORT KeyCodes
		{
				KeyUnknown,
				KeyReturn,
				KeyEscape,
				KeyBackspace,
				KeyTab,
				KeySpace,
				KeyExclaim,
				KeyQuotedbl,
				KeyHash,
				KeyPercent,
				KeyDollar,
				KeyAmpersand,
				KeyQuote,
				KeyLeftparen,
				KeyRightparen,
				KeyAsterisk,
				KeyPlus,
				KeyComma,
				KeyMinus,
				KeyPeriod,
				KeySlash,
				Key0,
				Key1,
				Key2,
				Key3,
				Key4,
				Key5,
				Key6,
				Key7,
				Key8,
				Key9,
				KeyColon,
				KeySemicolon,
				KeyLess,
				KeyEquals,
				KeyGreater,
				KeyQuestion,
				KeyAt,
				KeyLeftbracket,
				KeyBackslash,
				KeyRightbracket,
				KeyCaret,
				KeyUnderscore,
				KeyBackquote,
				KeyA,
				KeyB,
				KeyC,
				KeyD,
				KeyE,
				KeyF,
				KeyG,
				KeyH,
				KeyI,
				KeyJ,
				KeyK,
				KeyL,
				KeyM,
				KeyN,
				KeyO,
				KeyP,
				KeyQ,
				KeyR,
				KeyS,
				KeyT,
				KeyU,
				KeyV,
				KeyW,
				KeyX,
				KeyY,
				KeyZ,
				KeyCapslock,
				KeyF1,
				KeyF2,
				KeyF3,
				KeyF4,
				KeyF5,
				KeyF6,
				KeyF7,
				KeyF8,
				KeyF9,
				KeyF10,
				KeyF11,
				KeyF12,
				KeyPrintscreen,
				KeyScrolllock,
				KeyPause,
				KeyInsert,
				KeyHome,
				KeyPageup,
				KeyDelete,
				KeyEnd,
				KeyPagedown,
				KeyRight,
				KeyLeft,
				KeyDown,
				KeyUp,
				KeyNumlockclear,
				KeyKpDivide,
				KeyKpMultiply,
				KeyKpMinus,
				KeyKpPlus,
				KeyKpEnter,
				KeyKp1,
				KeyKp2,
				KeyKp3,
				KeyKp4,
				KeyKp5,
				KeyKp6,
				KeyKp7,
				KeyKp8,
				KeyKp9,
				KeyKp0,
				KeyKpPeriod,
				KeyApplication,
				KeyPower,
				KeyKpEquals,
				KeyF13,
				KeyF14,
				KeyF15,
				KeyF16,
				KeyF17,
				KeyF18,
				KeyF19,
				KeyF20,
				KeyF21,
				KeyF22,
				KeyF23,
				KeyF24,
				KeyExecute,
				KeyHelp,
				KeyMenu,
				KeySelect,
				KeyStop,
				KeyAgain,
				KeyUndo,
				KeyCut,
				KeyCopy,
				KeyPaste,
				KeyFind,
				KeyMute,
				KeyVolumeup,
				KeyVolumedown,
				KeyKpComma,
				KeyKpEqualsas400,
				KeyAlterase,
				KeySysreq,
				KeyCancel,
				KeyClear,
				KeyPrior,
				KeyReturn2,
				KeySeparator,
				KeyOut,
				KeyOper,
				KeyClearagain,
				KeyCrsel,
				KeyExsel,
				KeyKp00,
				KeyKp000,
				KeyThousandsseparator,
				KeyDecimalseparator,
				KeyCurrencyunit,
				KeyCurrencysubunit,
				KeyKpLeftparen,
				KeyKpRightparen,
				KeyKpLeftbrace,
				KeyKpRightbrace,
				KeyKpTab,
				KeyKpBackspace,
				KeyKpA,
				KeyKpB,
				KeyKpC,
				KeyKpD,
				KeyKpE,
				KeyKpF,
				KeyKpXor,
				KeyKpPower,
				KeyKpPercent,
				KeyKpLess,
				KeyKpGreater,
				KeyKpAmpersand,
				KeyKpDblampersand,
				KeyKpVerticalbar,
				KeyKpDblverticalbar,
				KeyKpColon,
				KeyKpHash,
				KeyKpSpace,
				KeyKpAt,
				KeyKpExclam,
				KeyKpMemstore,
				KeyKpMemrecall,
				KeyKpMemclear,
				KeyKpMemadd,
				KeyKpMemsubtract,
				KeyKpMemmultiply,
				KeyKpMemdivide,
				KeyKpPlusminus,
				KeyKpClear,
				KeyKpClearentry,
				KeyKpBinary,
				KeyKpOctal,
				KeyKpDecimal,
				KeyKpHexadecimal,
				KeyLctrl,
				KeyLshift,
				KeyLalt,
				KeyLgui,
				KeyRctrl,
				KeyRshift,
				KeyRalt,
				KeyRgui,
				KeyMode,
				KeyAudionext,
				KeyAudioprev,
				KeyAudiostop,
				KeyAudioplay,
				KeyAudiomute,
				KeyMediaselect,
				KeyWww,
				KeyMail,
				KeyCalculator,
				KeyComputer,
				KeyAcSearch,
				KeyAcHome,
				KeyAcBack,
				KeyAcForward,
				KeyAcStop,
				KeyAcRefresh,
				KeyAcBookmarks,
				KeyBrightnessdown,
				KeyBrightnessup,
				KeyDisplayswitch,
				KeyKbdillumtoggle,
				KeyKbdillumdown,
				KeyKbdillumup,
				KeyEject,
				KeySleep,
				KeyApp1,
				KeyApp2,
				KeyAudiorewind,
				KeyAudiofastforward,

				MouseLeft,
				MouseMiddle,
				MouseRight,
				MouseX1,
				MouseX2,
		};
	
		/**
		 * Convert string to a key code value.
		 */
		KeyCodes _StrToKeyCode(const char* str);

		/**
		* To convert:
			for i in original_enum.split('\n'):
				name = i.split('=')[0].strip()
				if len(name) > 0:
					print(''.join(word.title() for word in name.replace("SDLK_", "Key_").split('_')) + ' = ' + name + ',')
		*/
	}
}