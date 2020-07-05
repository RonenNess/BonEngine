#include <Input/Input.h>
#include <Log/ILog.h>
#include <Input/Defs.h>
#include <BonEngine.h>
#include <string>

#pragma warning(push, 0)
#include <SDL2-2.0.12/include/SDL.h>
#include <SDL2_image-2.0.5/include/SDL_image.h>
#pragma warning(pop)


using namespace bon::framework;

namespace bon
{
	namespace input
	{
		// convert sdl mouse key code to bon key code
		KeyCodes SdlToEzMouseCode(int sdlCode)
		{
			switch (sdlCode)
			{
				case SDL_BUTTON_LEFT: return KeyCodes::MouseLeft;
				case SDL_BUTTON_RIGHT: return KeyCodes::MouseRight;
				case SDL_BUTTON_MIDDLE: return KeyCodes::MouseMiddle;
				case SDL_BUTTON_X1: return KeyCodes::MouseX1;
				case SDL_BUTTON_X2: return KeyCodes::MouseX2;
			}
			return KeyCodes::KeyUnknown;
		}

		// convert sdl key code to bon key code
		KeyCodes SdlToEzKeyCode(int sdlCode)
		{
			switch (sdlCode)
			{
				case SDLK_UNKNOWN: return KeyCodes::KeyUnknown;
				case SDLK_RETURN: return KeyCodes::KeyReturn;
				case SDLK_ESCAPE: return KeyCodes::KeyEscape;
				case SDLK_BACKSPACE: return KeyCodes::KeyBackspace;
				case SDLK_TAB: return KeyCodes::KeyTab;
				case SDLK_SPACE: return KeyCodes::KeySpace;
				case SDLK_EXCLAIM: return KeyCodes::KeyExclaim;
				case SDLK_QUOTEDBL: return KeyCodes::KeyQuotedbl;
				case SDLK_HASH: return KeyCodes::KeyHash;
				case SDLK_PERCENT: return KeyCodes::KeyPercent;
				case SDLK_DOLLAR: return KeyCodes::KeyDollar;
				case SDLK_AMPERSAND: return KeyCodes::KeyAmpersand;
				case SDLK_QUOTE: return KeyCodes::KeyQuote;
				case SDLK_LEFTPAREN: return KeyCodes::KeyLeftparen;
				case SDLK_RIGHTPAREN: return KeyCodes::KeyRightparen;
				case SDLK_ASTERISK: return KeyCodes::KeyAsterisk;
				case SDLK_PLUS: return KeyCodes::KeyPlus;
				case SDLK_COMMA: return KeyCodes::KeyComma;
				case SDLK_MINUS: return KeyCodes::KeyMinus;
				case SDLK_PERIOD: return KeyCodes::KeyPeriod;
				case SDLK_SLASH: return KeyCodes::KeySlash;
				case SDLK_0: return KeyCodes::Key0;
				case SDLK_1: return KeyCodes::Key1;
				case SDLK_2: return KeyCodes::Key2;
				case SDLK_3: return KeyCodes::Key3;
				case SDLK_4: return KeyCodes::Key4;
				case SDLK_5: return KeyCodes::Key5;
				case SDLK_6: return KeyCodes::Key6;
				case SDLK_7: return KeyCodes::Key7;
				case SDLK_8: return KeyCodes::Key8;
				case SDLK_9: return KeyCodes::Key9;
				case SDLK_COLON: return KeyCodes::KeyColon;
				case SDLK_SEMICOLON: return KeyCodes::KeySemicolon;
				case SDLK_LESS: return KeyCodes::KeyLess;
				case SDLK_EQUALS: return KeyCodes::KeyEquals;
				case SDLK_GREATER: return KeyCodes::KeyGreater;
				case SDLK_QUESTION: return KeyCodes::KeyQuestion;
				case SDLK_AT: return KeyCodes::KeyAt;
				case SDLK_LEFTBRACKET: return KeyCodes::KeyLeftbracket;
				case SDLK_BACKSLASH: return KeyCodes::KeyBackslash;
				case SDLK_RIGHTBRACKET: return KeyCodes::KeyRightbracket;
				case SDLK_CARET: return KeyCodes::KeyCaret;
				case SDLK_UNDERSCORE: return KeyCodes::KeyUnderscore;
				case SDLK_BACKQUOTE: return KeyCodes::KeyBackquote;
				case SDLK_a: return KeyCodes::KeyA;
				case SDLK_b: return KeyCodes::KeyB;
				case SDLK_c: return KeyCodes::KeyC;
				case SDLK_d: return KeyCodes::KeyD;
				case SDLK_e: return KeyCodes::KeyE;
				case SDLK_f: return KeyCodes::KeyF;
				case SDLK_g: return KeyCodes::KeyG;
				case SDLK_h: return KeyCodes::KeyH;
				case SDLK_i: return KeyCodes::KeyI;
				case SDLK_j: return KeyCodes::KeyJ;
				case SDLK_k: return KeyCodes::KeyK;
				case SDLK_l: return KeyCodes::KeyL;
				case SDLK_m: return KeyCodes::KeyM;
				case SDLK_n: return KeyCodes::KeyN;
				case SDLK_o: return KeyCodes::KeyO;
				case SDLK_p: return KeyCodes::KeyP;
				case SDLK_q: return KeyCodes::KeyQ;
				case SDLK_r: return KeyCodes::KeyR;
				case SDLK_s: return KeyCodes::KeyS;
				case SDLK_t: return KeyCodes::KeyT;
				case SDLK_u: return KeyCodes::KeyU;
				case SDLK_v: return KeyCodes::KeyV;
				case SDLK_w: return KeyCodes::KeyW;
				case SDLK_x: return KeyCodes::KeyX;
				case SDLK_y: return KeyCodes::KeyY;
				case SDLK_z: return KeyCodes::KeyZ;
				case SDLK_CAPSLOCK: return KeyCodes::KeyCapslock;
				case SDLK_F1: return KeyCodes::KeyF1;
				case SDLK_F2: return KeyCodes::KeyF2;
				case SDLK_F3: return KeyCodes::KeyF3;
				case SDLK_F4: return KeyCodes::KeyF4;
				case SDLK_F5: return KeyCodes::KeyF5;
				case SDLK_F6: return KeyCodes::KeyF6;
				case SDLK_F7: return KeyCodes::KeyF7;
				case SDLK_F8: return KeyCodes::KeyF8;
				case SDLK_F9: return KeyCodes::KeyF9;
				case SDLK_F10: return KeyCodes::KeyF10;
				case SDLK_F11: return KeyCodes::KeyF11;
				case SDLK_F12: return KeyCodes::KeyF12;
				case SDLK_PRINTSCREEN: return KeyCodes::KeyPrintscreen;
				case SDLK_SCROLLLOCK: return KeyCodes::KeyScrolllock;
				case SDLK_PAUSE: return KeyCodes::KeyPause;
				case SDLK_INSERT: return KeyCodes::KeyInsert;
				case SDLK_HOME: return KeyCodes::KeyHome;
				case SDLK_PAGEUP: return KeyCodes::KeyPageup;
				case SDLK_DELETE: return KeyCodes::KeyDelete;
				case SDLK_END: return KeyCodes::KeyEnd;
				case SDLK_PAGEDOWN: return KeyCodes::KeyPagedown;
				case SDLK_RIGHT: return KeyCodes::KeyRight;
				case SDLK_LEFT: return KeyCodes::KeyLeft;
				case SDLK_DOWN: return KeyCodes::KeyDown;
				case SDLK_UP: return KeyCodes::KeyUp;
				case SDLK_NUMLOCKCLEAR: return KeyCodes::KeyNumlockclear;
				case SDLK_KP_DIVIDE: return KeyCodes::KeyKpDivide;
				case SDLK_KP_MULTIPLY: return KeyCodes::KeyKpMultiply;
				case SDLK_KP_MINUS: return KeyCodes::KeyKpMinus;
				case SDLK_KP_PLUS: return KeyCodes::KeyKpPlus;
				case SDLK_KP_ENTER: return KeyCodes::KeyKpEnter;
				case SDLK_KP_1: return KeyCodes::KeyKp1;
				case SDLK_KP_2: return KeyCodes::KeyKp2;
				case SDLK_KP_3: return KeyCodes::KeyKp3;
				case SDLK_KP_4: return KeyCodes::KeyKp4;
				case SDLK_KP_5: return KeyCodes::KeyKp5;
				case SDLK_KP_6: return KeyCodes::KeyKp6;
				case SDLK_KP_7: return KeyCodes::KeyKp7;
				case SDLK_KP_8: return KeyCodes::KeyKp8;
				case SDLK_KP_9: return KeyCodes::KeyKp9;
				case SDLK_KP_0: return KeyCodes::KeyKp0;
				case SDLK_KP_PERIOD: return KeyCodes::KeyKpPeriod;
				case SDLK_APPLICATION: return KeyCodes::KeyApplication;
				case SDLK_POWER: return KeyCodes::KeyPower;
				case SDLK_KP_EQUALS: return KeyCodes::KeyKpEquals;
				case SDLK_F13: return KeyCodes::KeyF13;
				case SDLK_F14: return KeyCodes::KeyF14;
				case SDLK_F15: return KeyCodes::KeyF15;
				case SDLK_F16: return KeyCodes::KeyF16;
				case SDLK_F17: return KeyCodes::KeyF17;
				case SDLK_F18: return KeyCodes::KeyF18;
				case SDLK_F19: return KeyCodes::KeyF19;
				case SDLK_F20: return KeyCodes::KeyF20;
				case SDLK_F21: return KeyCodes::KeyF21;
				case SDLK_F22: return KeyCodes::KeyF22;
				case SDLK_F23: return KeyCodes::KeyF23;
				case SDLK_F24: return KeyCodes::KeyF24;
				case SDLK_EXECUTE: return KeyCodes::KeyExecute;
				case SDLK_HELP: return KeyCodes::KeyHelp;
				case SDLK_MENU: return KeyCodes::KeyMenu;
				case SDLK_SELECT: return KeyCodes::KeySelect;
				case SDLK_STOP: return KeyCodes::KeyStop;
				case SDLK_AGAIN: return KeyCodes::KeyAgain;
				case SDLK_UNDO: return KeyCodes::KeyUndo;
				case SDLK_CUT: return KeyCodes::KeyCut;
				case SDLK_COPY: return KeyCodes::KeyCopy;
				case SDLK_PASTE: return KeyCodes::KeyPaste;
				case SDLK_FIND: return KeyCodes::KeyFind;
				case SDLK_MUTE: return KeyCodes::KeyMute;
				case SDLK_VOLUMEUP: return KeyCodes::KeyVolumeup;
				case SDLK_VOLUMEDOWN: return KeyCodes::KeyVolumedown;
				case SDLK_KP_COMMA: return KeyCodes::KeyKpComma;
				case SDLK_KP_EQUALSAS400: return KeyCodes::KeyKpEqualsas400;
				case SDLK_ALTERASE: return KeyCodes::KeyAlterase;
				case SDLK_SYSREQ: return KeyCodes::KeySysreq;
				case SDLK_CANCEL: return KeyCodes::KeyCancel;
				case SDLK_CLEAR: return KeyCodes::KeyClear;
				case SDLK_PRIOR: return KeyCodes::KeyPrior;
				case SDLK_RETURN2: return KeyCodes::KeyReturn2;
				case SDLK_SEPARATOR: return KeyCodes::KeySeparator;
				case SDLK_OUT: return KeyCodes::KeyOut;
				case SDLK_OPER: return KeyCodes::KeyOper;
				case SDLK_CLEARAGAIN: return KeyCodes::KeyClearagain;
				case SDLK_CRSEL: return KeyCodes::KeyCrsel;
				case SDLK_EXSEL: return KeyCodes::KeyExsel;
				case SDLK_KP_00: return KeyCodes::KeyKp00;
				case SDLK_KP_000: return KeyCodes::KeyKp000;
				case SDLK_THOUSANDSSEPARATOR: return KeyCodes::KeyThousandsseparator;
				case SDLK_DECIMALSEPARATOR: return KeyCodes::KeyDecimalseparator;
				case SDLK_CURRENCYUNIT: return KeyCodes::KeyCurrencyunit;
				case SDLK_CURRENCYSUBUNIT: return KeyCodes::KeyCurrencysubunit;
				case SDLK_KP_LEFTPAREN: return KeyCodes::KeyKpLeftparen;
				case SDLK_KP_RIGHTPAREN: return KeyCodes::KeyKpRightparen;
				case SDLK_KP_LEFTBRACE: return KeyCodes::KeyKpLeftbrace;
				case SDLK_KP_RIGHTBRACE: return KeyCodes::KeyKpRightbrace;
				case SDLK_KP_TAB: return KeyCodes::KeyKpTab;
				case SDLK_KP_BACKSPACE: return KeyCodes::KeyKpBackspace;
				case SDLK_KP_A: return KeyCodes::KeyKpA;
				case SDLK_KP_B: return KeyCodes::KeyKpB;
				case SDLK_KP_C: return KeyCodes::KeyKpC;
				case SDLK_KP_D: return KeyCodes::KeyKpD;
				case SDLK_KP_E: return KeyCodes::KeyKpE;
				case SDLK_KP_F: return KeyCodes::KeyKpF;
				case SDLK_KP_XOR: return KeyCodes::KeyKpXor;
				case SDLK_KP_POWER: return KeyCodes::KeyKpPower;
				case SDLK_KP_PERCENT: return KeyCodes::KeyKpPercent;
				case SDLK_KP_LESS: return KeyCodes::KeyKpLess;
				case SDLK_KP_GREATER: return KeyCodes::KeyKpGreater;
				case SDLK_KP_AMPERSAND: return KeyCodes::KeyKpAmpersand;
				case SDLK_KP_DBLAMPERSAND: return KeyCodes::KeyKpDblampersand;
				case SDLK_KP_VERTICALBAR: return KeyCodes::KeyKpVerticalbar;
				case SDLK_KP_DBLVERTICALBAR: return KeyCodes::KeyKpDblverticalbar;
				case SDLK_KP_COLON: return KeyCodes::KeyKpColon;
				case SDLK_KP_HASH: return KeyCodes::KeyKpHash;
				case SDLK_KP_SPACE: return KeyCodes::KeyKpSpace;
				case SDLK_KP_AT: return KeyCodes::KeyKpAt;
				case SDLK_KP_EXCLAM: return KeyCodes::KeyKpExclam;
				case SDLK_KP_MEMSTORE: return KeyCodes::KeyKpMemstore;
				case SDLK_KP_MEMRECALL: return KeyCodes::KeyKpMemrecall;
				case SDLK_KP_MEMCLEAR: return KeyCodes::KeyKpMemclear;
				case SDLK_KP_MEMADD: return KeyCodes::KeyKpMemadd;
				case SDLK_KP_MEMSUBTRACT: return KeyCodes::KeyKpMemsubtract;
				case SDLK_KP_MEMMULTIPLY: return KeyCodes::KeyKpMemmultiply;
				case SDLK_KP_MEMDIVIDE: return KeyCodes::KeyKpMemdivide;
				case SDLK_KP_PLUSMINUS: return KeyCodes::KeyKpPlusminus;
				case SDLK_KP_CLEAR: return KeyCodes::KeyKpClear;
				case SDLK_KP_CLEARENTRY: return KeyCodes::KeyKpClearentry;
				case SDLK_KP_BINARY: return KeyCodes::KeyKpBinary;
				case SDLK_KP_OCTAL: return KeyCodes::KeyKpOctal;
				case SDLK_KP_DECIMAL: return KeyCodes::KeyKpDecimal;
				case SDLK_KP_HEXADECIMAL: return KeyCodes::KeyKpHexadecimal;
				case SDLK_LCTRL: return KeyCodes::KeyLctrl;
				case SDLK_LSHIFT: return KeyCodes::KeyLshift;
				case SDLK_LALT: return KeyCodes::KeyLalt;
				case SDLK_LGUI: return KeyCodes::KeyLgui;
				case SDLK_RCTRL: return KeyCodes::KeyRctrl;
				case SDLK_RSHIFT: return KeyCodes::KeyRshift;
				case SDLK_RALT: return KeyCodes::KeyRalt;
				case SDLK_RGUI: return KeyCodes::KeyRgui;
				case SDLK_MODE: return KeyCodes::KeyMode;
				case SDLK_AUDIONEXT: return KeyCodes::KeyAudionext;
				case SDLK_AUDIOPREV: return KeyCodes::KeyAudioprev;
				case SDLK_AUDIOSTOP: return KeyCodes::KeyAudiostop;
				case SDLK_AUDIOPLAY: return KeyCodes::KeyAudioplay;
				case SDLK_AUDIOMUTE: return KeyCodes::KeyAudiomute;
				case SDLK_MEDIASELECT: return KeyCodes::KeyMediaselect;
				case SDLK_WWW: return KeyCodes::KeyWww;
				case SDLK_MAIL: return KeyCodes::KeyMail;
				case SDLK_CALCULATOR: return KeyCodes::KeyCalculator;
				case SDLK_COMPUTER: return KeyCodes::KeyComputer;
				case SDLK_AC_SEARCH: return KeyCodes::KeyAcSearch;
				case SDLK_AC_HOME: return KeyCodes::KeyAcHome;
				case SDLK_AC_BACK: return KeyCodes::KeyAcBack;
				case SDLK_AC_FORWARD: return KeyCodes::KeyAcForward;
				case SDLK_AC_STOP: return KeyCodes::KeyAcStop;
				case SDLK_AC_REFRESH: return KeyCodes::KeyAcRefresh;
				case SDLK_AC_BOOKMARKS: return KeyCodes::KeyAcBookmarks;
				case SDLK_BRIGHTNESSDOWN: return KeyCodes::KeyBrightnessdown;
				case SDLK_BRIGHTNESSUP: return KeyCodes::KeyBrightnessup;
				case SDLK_DISPLAYSWITCH: return KeyCodes::KeyDisplayswitch;
				case SDLK_KBDILLUMTOGGLE: return KeyCodes::KeyKbdillumtoggle;
				case SDLK_KBDILLUMDOWN: return KeyCodes::KeyKbdillumdown;
				case SDLK_KBDILLUMUP: return KeyCodes::KeyKbdillumup;
				case SDLK_EJECT: return KeyCodes::KeyEject;
				case SDLK_SLEEP: return KeyCodes::KeySleep;
				case SDLK_APP1: return KeyCodes::KeyApp1;
				case SDLK_APP2: return KeyCodes::KeyApp2;
				case SDLK_AUDIOREWIND: return KeyCodes::KeyAudiorewind;
				case SDLK_AUDIOFASTFORWARD: return KeyCodes::KeyAudiofastforward;
			}
			return KeyCodes::KeyUnknown;
		}

		// convert key code enum to string
		const char* KeyCodeToString(KeyCodes key)
		{
			switch (key)
			{
				case KeyCodes::KeyUnknown: return "KeyUnknown";
				case KeyCodes::KeyReturn: return "KeyReturn";
				case KeyCodes::KeyEscape: return "KeyEscape";
				case KeyCodes::KeyBackspace: return "KeyBackspace";
				case KeyCodes::KeyTab: return "KeyTab";
				case KeyCodes::KeySpace: return "KeySpace";
				case KeyCodes::KeyExclaim: return "KeyExclaim";
				case KeyCodes::KeyQuotedbl: return "KeyQuotedbl";
				case KeyCodes::KeyHash: return "KeyHash";
				case KeyCodes::KeyPercent: return "KeyPercent";
				case KeyCodes::KeyDollar: return "KeyDollar";
				case KeyCodes::KeyAmpersand: return "KeyAmpersand";
				case KeyCodes::KeyQuote: return "KeyQuote";
				case KeyCodes::KeyLeftparen: return "KeyLeftparen";
				case KeyCodes::KeyRightparen: return "KeyRightparen";
				case KeyCodes::KeyAsterisk: return "KeyAsterisk";
				case KeyCodes::KeyPlus: return "KeyPlus";
				case KeyCodes::KeyComma: return "KeyComma";
				case KeyCodes::KeyMinus: return "KeyMinus";
				case KeyCodes::KeyPeriod: return "KeyPeriod";
				case KeyCodes::KeySlash: return "KeySlash";
				case KeyCodes::Key0: return "Key0";
				case KeyCodes::Key1: return "Key1";
				case KeyCodes::Key2: return "Key2";
				case KeyCodes::Key3: return "Key3";
				case KeyCodes::Key4: return "Key4";
				case KeyCodes::Key5: return "Key5";
				case KeyCodes::Key6: return "Key6";
				case KeyCodes::Key7: return "Key7";
				case KeyCodes::Key8: return "Key8";
				case KeyCodes::Key9: return "Key9";
				case KeyCodes::KeyColon: return "KeyColon";
				case KeyCodes::KeySemicolon: return "KeySemicolon";
				case KeyCodes::KeyLess: return "KeyLess";
				case KeyCodes::KeyEquals: return "KeyEquals";
				case KeyCodes::KeyGreater: return "KeyGreater";
				case KeyCodes::KeyQuestion: return "KeyQuestion";
				case KeyCodes::KeyAt: return "KeyAt";
				case KeyCodes::KeyLeftbracket: return "KeyLeftbracket";
				case KeyCodes::KeyBackslash: return "KeyBackslash";
				case KeyCodes::KeyRightbracket: return "KeyRightbracket";
				case KeyCodes::KeyCaret: return "KeyCaret";
				case KeyCodes::KeyUnderscore: return "KeyUnderscore";
				case KeyCodes::KeyBackquote: return "KeyBackquote";
				case KeyCodes::KeyA: return "KeyA";
				case KeyCodes::KeyB: return "KeyB";
				case KeyCodes::KeyC: return "KeyC";
				case KeyCodes::KeyD: return "KeyD";
				case KeyCodes::KeyE: return "KeyE";
				case KeyCodes::KeyF: return "KeyF";
				case KeyCodes::KeyG: return "KeyG";
				case KeyCodes::KeyH: return "KeyH";
				case KeyCodes::KeyI: return "KeyI";
				case KeyCodes::KeyJ: return "KeyJ";
				case KeyCodes::KeyK: return "KeyK";
				case KeyCodes::KeyL: return "KeyL";
				case KeyCodes::KeyM: return "KeyM";
				case KeyCodes::KeyN: return "KeyN";
				case KeyCodes::KeyO: return "KeyO";
				case KeyCodes::KeyP: return "KeyP";
				case KeyCodes::KeyQ: return "KeyQ";
				case KeyCodes::KeyR: return "KeyR";
				case KeyCodes::KeyS: return "KeyS";
				case KeyCodes::KeyT: return "KeyT";
				case KeyCodes::KeyU: return "KeyU";
				case KeyCodes::KeyV: return "KeyV";
				case KeyCodes::KeyW: return "KeyW";
				case KeyCodes::KeyX: return "KeyX";
				case KeyCodes::KeyY: return "KeyY";
				case KeyCodes::KeyZ: return "KeyZ";
				case KeyCodes::KeyCapslock: return "KeyCapslock";
				case KeyCodes::KeyF1: return "KeyF1";
				case KeyCodes::KeyF2: return "KeyF2";
				case KeyCodes::KeyF3: return "KeyF3";
				case KeyCodes::KeyF4: return "KeyF4";
				case KeyCodes::KeyF5: return "KeyF5";
				case KeyCodes::KeyF6: return "KeyF6";
				case KeyCodes::KeyF7: return "KeyF7";
				case KeyCodes::KeyF8: return "KeyF8";
				case KeyCodes::KeyF9: return "KeyF9";
				case KeyCodes::KeyF10: return "KeyF10";
				case KeyCodes::KeyF11: return "KeyF11";
				case KeyCodes::KeyF12: return "KeyF12";
				case KeyCodes::KeyPrintscreen: return "KeyPrintscreen";
				case KeyCodes::KeyScrolllock: return "KeyScrolllock";
				case KeyCodes::KeyPause: return "KeyPause";
				case KeyCodes::KeyInsert: return "KeyInsert";
				case KeyCodes::KeyHome: return "KeyHome";
				case KeyCodes::KeyPageup: return "KeyPageup";
				case KeyCodes::KeyDelete: return "KeyDelete";
				case KeyCodes::KeyEnd: return "KeyEnd";
				case KeyCodes::KeyPagedown: return "KeyPagedown";
				case KeyCodes::KeyRight: return "KeyRight";
				case KeyCodes::KeyLeft: return "KeyLeft";
				case KeyCodes::KeyDown: return "KeyDown";
				case KeyCodes::KeyUp: return "KeyUp";
				case KeyCodes::KeyNumlockclear: return "KeyNumlockclear";
				case KeyCodes::KeyKpDivide: return "KeyKpDivide";
				case KeyCodes::KeyKpMultiply: return "KeyKpMultiply";
				case KeyCodes::KeyKpMinus: return "KeyKpMinus";
				case KeyCodes::KeyKpPlus: return "KeyKpPlus";
				case KeyCodes::KeyKpEnter: return "KeyKpEnter";
				case KeyCodes::KeyKp1: return "KeyKp1";
				case KeyCodes::KeyKp2: return "KeyKp2";
				case KeyCodes::KeyKp3: return "KeyKp3";
				case KeyCodes::KeyKp4: return "KeyKp4";
				case KeyCodes::KeyKp5: return "KeyKp5";
				case KeyCodes::KeyKp6: return "KeyKp6";
				case KeyCodes::KeyKp7: return "KeyKp7";
				case KeyCodes::KeyKp8: return "KeyKp8";
				case KeyCodes::KeyKp9: return "KeyKp9";
				case KeyCodes::KeyKp0: return "KeyKp0";
				case KeyCodes::KeyKpPeriod: return "KeyKpPeriod";
				case KeyCodes::KeyApplication: return "KeyApplication";
				case KeyCodes::KeyPower: return "KeyPower";
				case KeyCodes::KeyKpEquals: return "KeyKpEquals";
				case KeyCodes::KeyF13: return "KeyF13";
				case KeyCodes::KeyF14: return "KeyF14";
				case KeyCodes::KeyF15: return "KeyF15";
				case KeyCodes::KeyF16: return "KeyF16";
				case KeyCodes::KeyF17: return "KeyF17";
				case KeyCodes::KeyF18: return "KeyF18";
				case KeyCodes::KeyF19: return "KeyF19";
				case KeyCodes::KeyF20: return "KeyF20";
				case KeyCodes::KeyF21: return "KeyF21";
				case KeyCodes::KeyF22: return "KeyF22";
				case KeyCodes::KeyF23: return "KeyF23";
				case KeyCodes::KeyF24: return "KeyF24";
				case KeyCodes::KeyExecute: return "KeyExecute";
				case KeyCodes::KeyHelp: return "KeyHelp";
				case KeyCodes::KeyMenu: return "KeyMenu";
				case KeyCodes::KeySelect: return "KeySelect";
				case KeyCodes::KeyStop: return "KeyStop";
				case KeyCodes::KeyAgain: return "KeyAgain";
				case KeyCodes::KeyUndo: return "KeyUndo";
				case KeyCodes::KeyCut: return "KeyCut";
				case KeyCodes::KeyCopy: return "KeyCopy";
				case KeyCodes::KeyPaste: return "KeyPaste";
				case KeyCodes::KeyFind: return "KeyFind";
				case KeyCodes::KeyMute: return "KeyMute";
				case KeyCodes::KeyVolumeup: return "KeyVolumeup";
				case KeyCodes::KeyVolumedown: return "KeyVolumedown";
				case KeyCodes::KeyKpComma: return "KeyKpComma";
				case KeyCodes::KeyKpEqualsas400: return "KeyKpEqualsas400";
				case KeyCodes::KeyAlterase: return "KeyAlterase";
				case KeyCodes::KeySysreq: return "KeySysreq";
				case KeyCodes::KeyCancel: return "KeyCancel";
				case KeyCodes::KeyClear: return "KeyClear";
				case KeyCodes::KeyPrior: return "KeyPrior";
				case KeyCodes::KeyReturn2: return "KeyReturn2";
				case KeyCodes::KeySeparator: return "KeySeparator";
				case KeyCodes::KeyOut: return "KeyOut";
				case KeyCodes::KeyOper: return "KeyOper";
				case KeyCodes::KeyClearagain: return "KeyClearagain";
				case KeyCodes::KeyCrsel: return "KeyCrsel";
				case KeyCodes::KeyExsel: return "KeyExsel";
				case KeyCodes::KeyKp00: return "KeyKp00";
				case KeyCodes::KeyKp000: return "KeyKp000";
				case KeyCodes::KeyThousandsseparator: return "KeyThousandsseparator";
				case KeyCodes::KeyDecimalseparator: return "KeyDecimalseparator";
				case KeyCodes::KeyCurrencyunit: return "KeyCurrencyunit";
				case KeyCodes::KeyCurrencysubunit: return "KeyCurrencysubunit";
				case KeyCodes::KeyKpLeftparen: return "KeyKpLeftparen";
				case KeyCodes::KeyKpRightparen: return "KeyKpRightparen";
				case KeyCodes::KeyKpLeftbrace: return "KeyKpLeftbrace";
				case KeyCodes::KeyKpRightbrace: return "KeyKpRightbrace";
				case KeyCodes::KeyKpTab: return "KeyKpTab";
				case KeyCodes::KeyKpBackspace: return "KeyKpBackspace";
				case KeyCodes::KeyKpA: return "KeyKpA";
				case KeyCodes::KeyKpB: return "KeyKpB";
				case KeyCodes::KeyKpC: return "KeyKpC";
				case KeyCodes::KeyKpD: return "KeyKpD";
				case KeyCodes::KeyKpE: return "KeyKpE";
				case KeyCodes::KeyKpF: return "KeyKpF";
				case KeyCodes::KeyKpXor: return "KeyKpXor";
				case KeyCodes::KeyKpPower: return "KeyKpPower";
				case KeyCodes::KeyKpPercent: return "KeyKpPercent";
				case KeyCodes::KeyKpLess: return "KeyKpLess";
				case KeyCodes::KeyKpGreater: return "KeyKpGreater";
				case KeyCodes::KeyKpAmpersand: return "KeyKpAmpersand";
				case KeyCodes::KeyKpDblampersand: return "KeyKpDblampersand";
				case KeyCodes::KeyKpVerticalbar: return "KeyKpVerticalbar";
				case KeyCodes::KeyKpDblverticalbar: return "KeyKpDblverticalbar";
				case KeyCodes::KeyKpColon: return "KeyKpColon";
				case KeyCodes::KeyKpHash: return "KeyKpHash";
				case KeyCodes::KeyKpSpace: return "KeyKpSpace";
				case KeyCodes::KeyKpAt: return "KeyKpAt";
				case KeyCodes::KeyKpExclam: return "KeyKpExclam";
				case KeyCodes::KeyKpMemstore: return "KeyKpMemstore";
				case KeyCodes::KeyKpMemrecall: return "KeyKpMemrecall";
				case KeyCodes::KeyKpMemclear: return "KeyKpMemclear";
				case KeyCodes::KeyKpMemadd: return "KeyKpMemadd";
				case KeyCodes::KeyKpMemsubtract: return "KeyKpMemsubtract";
				case KeyCodes::KeyKpMemmultiply: return "KeyKpMemmultiply";
				case KeyCodes::KeyKpMemdivide: return "KeyKpMemdivide";
				case KeyCodes::KeyKpPlusminus: return "KeyKpPlusminus";
				case KeyCodes::KeyKpClear: return "KeyKpClear";
				case KeyCodes::KeyKpClearentry: return "KeyKpClearentry";
				case KeyCodes::KeyKpBinary: return "KeyKpBinary";
				case KeyCodes::KeyKpOctal: return "KeyKpOctal";
				case KeyCodes::KeyKpDecimal: return "KeyKpDecimal";
				case KeyCodes::KeyKpHexadecimal: return "KeyKpHexadecimal";
				case KeyCodes::KeyLctrl: return "KeyLctrl";
				case KeyCodes::KeyLshift: return "KeyLshift";
				case KeyCodes::KeyLalt: return "KeyLalt";
				case KeyCodes::KeyLgui: return "KeyLgui";
				case KeyCodes::KeyRctrl: return "KeyRctrl";
				case KeyCodes::KeyRshift: return "KeyRshift";
				case KeyCodes::KeyRalt: return "KeyRalt";
				case KeyCodes::KeyRgui: return "KeyRgui";
				case KeyCodes::KeyMode: return "KeyMode";
				case KeyCodes::KeyAudionext: return "KeyAudionext";
				case KeyCodes::KeyAudioprev: return "KeyAudioprev";
				case KeyCodes::KeyAudiostop: return "KeyAudiostop";
				case KeyCodes::KeyAudioplay: return "KeyAudioplay";
				case KeyCodes::KeyAudiomute: return "KeyAudiomute";
				case KeyCodes::KeyMediaselect: return "KeyMediaselect";
				case KeyCodes::KeyWww: return "KeyWww";
				case KeyCodes::KeyMail: return "KeyMail";
				case KeyCodes::KeyCalculator: return "KeyCalculator";
				case KeyCodes::KeyComputer: return "KeyComputer";
				case KeyCodes::KeyAcSearch: return "KeyAcSearch";
				case KeyCodes::KeyAcHome: return "KeyAcHome";
				case KeyCodes::KeyAcBack: return "KeyAcBack";
				case KeyCodes::KeyAcForward: return "KeyAcForward";
				case KeyCodes::KeyAcStop: return "KeyAcStop";
				case KeyCodes::KeyAcRefresh: return "KeyAcRefresh";
				case KeyCodes::KeyAcBookmarks: return "KeyAcBookmarks";
				case KeyCodes::KeyBrightnessdown: return "KeyBrightnessdown";
				case KeyCodes::KeyBrightnessup: return "KeyBrightnessup";
				case KeyCodes::KeyDisplayswitch: return "KeyDisplayswitch";
				case KeyCodes::KeyKbdillumtoggle: return "KeyKbdillumtoggle";
				case KeyCodes::KeyKbdillumdown: return "KeyKbdillumdown";
				case KeyCodes::KeyKbdillumup: return "KeyKbdillumup";
				case KeyCodes::KeyEject: return "KeyEject";
				case KeyCodes::KeySleep: return "KeySleep";
				case KeyCodes::KeyApp1: return "KeyApp1";
				case KeyCodes::KeyApp2: return "KeyApp2";
				case KeyCodes::KeyAudiorewind: return "KeyAudiorewind";
				case KeyCodes::KeyAudiofastforward: return "KeyAudiofastforward";
				case KeyCodes::MouseLeft: return "MouseLeft";
				case KeyCodes::MouseRight: return "MouseRight";
				case KeyCodes::MouseMiddle: return "MouseMiddle";
				case KeyCodes::MouseX1: return "MouseX1";
				case KeyCodes::MouseX2: return "MouseX2";
			}
			return "Unknown";
		}

		// init input manager
		void Input::_Initialize()
		{
		}

		// dispose input resources
		void Input::_Dispose()
		{
			SDL_StopTextInput();
		}

		// do updates
		void Input::_Update(double deltaTime)
		{
			// reset current frame's text input data
			_textInputData = TextInputData();

			// copy current cursor position to previous frame cursor position
			_prevCursorPosition = _cursorPosition;

			// get new cursor position
			SDL_GetMouseState(&_cursorPosition.X, &_cursorPosition.Y);
			
			// calculate mouse delta
			_cursorMovement.Set(_cursorPosition.X - _prevCursorPosition.X, _cursorPosition.Y - _prevCursorPosition.Y);

			// reset mouse wheel delta
			_scrollDelta.Reset();
		}

		// called on main loop start
		void Input::_Start()
		{
			// if started and user didn't do any maps, do default mappings
			if (_keyBinds.empty()) {
				BON_ILOG("Set default key bindings.");
				SetDefaultKeyBinds();
			}
			else {
				BON_ILOG("Skip setting default key bindings, because user defined his own map.");
			}

			// enable text input
			SDL_StartTextInput();
		}

		// set default keys
		void Input::SetDefaultKeyBinds()
		{
			SetKeyBind(KeyCodes::KeyLeft, "left");
			SetKeyBind(KeyCodes::KeyA, "left");

			SetKeyBind(KeyCodes::KeyRight, "right");
			SetKeyBind(KeyCodes::KeyD, "right");

			SetKeyBind(KeyCodes::KeyUp, "up");
			SetKeyBind(KeyCodes::KeyW, "up");

			SetKeyBind(KeyCodes::KeyDown, "down");
			SetKeyBind(KeyCodes::KeyS, "down");

			SetKeyBind(KeyCodes::KeyZ, "action");
			SetKeyBind(KeyCodes::MouseLeft, "action");

			SetKeyBind(KeyCodes::KeyX, "alt_action");
			SetKeyBind(KeyCodes::MouseRight, "alt_action");

			SetKeyBind(KeyCodes::KeySpace, "jump");

			SetKeyBind(KeyCodes::KeyE, "interact");
			SetKeyBind(KeyCodes::MouseMiddle, "interact");

			SetKeyBind(KeyCodes::KeyF4, "quickload");
			SetKeyBind(KeyCodes::KeyF5, "quicksave");

			SetKeyBind(KeyCodes::KeyEscape, "exit");

			SetKeyBind(KeyCodes::KeyLshift, "shift");
			SetKeyBind(KeyCodes::KeyRshift, "shift");

			SetKeyBind(KeyCodes::KeyLctrl, "ctrl");
			SetKeyBind(KeyCodes::KeyRctrl, "ctrl");

			SetKeyBind(KeyCodes::Key1, "quickbar1");
			SetKeyBind(KeyCodes::Key2, "quickbar2");
			SetKeyBind(KeyCodes::Key3, "quickbar3");
			SetKeyBind(KeyCodes::Key4, "quickbar4");
			SetKeyBind(KeyCodes::Key5, "quickbar5");
			SetKeyBind(KeyCodes::Key6, "quickbar6");
			SetKeyBind(KeyCodes::Key7, "quickbar7");
			SetKeyBind(KeyCodes::Key8, "quickbar8");
			SetKeyBind(KeyCodes::Key9, "quickbar9");
			SetKeyBind(KeyCodes::Key0, "quickbar10");

		}

		// set a key binding
		void Input::SetKeyBind(KeyCodes keyCode, const char* actionId)
		{
			// log
			BON_DLOG("Bind key: %s --> '%s'.", KeyCodeToString(keyCode), actionId);

			// set key
			(_keyBinds)[keyCode] = std::string(actionId);
		}

		// handle events
		void Input::_HandleEvent(SDL_Event& event)
		{
			// check event type
			switch (event.type) {

				// mouse wheel events
				case SDL_MOUSEWHEEL:
					_scrollDelta.Set(event.wheel.x, event.wheel.y);
					break;

				// key down
				case SDL_KEYDOWN:
					HandleTextInput(event);
					SetKeyState(SdlToEzKeyCode((int)(event.key.keysym.sym)), true);
					break;

				// key up
				case SDL_KEYUP:	
					SetKeyState(SdlToEzKeyCode((int)(event.key.keysym.sym)), false);
					break;

				// mouse button down
				case SDL_MOUSEBUTTONDOWN:
					SetKeyState(SdlToEzMouseCode((int)(event.button.button)), true);
					break;

				// mouse button up
				case SDL_MOUSEBUTTONUP:
					SetKeyState(SdlToEzMouseCode((int)(event.button.button)), false);
					break;

				// text input event
				case SDL_TEXTINPUT:
					HandleTextInput(event);
					break;
			}
		}

		// set clipboard value.
		void Input::SetClipboard(const char* text)
		{
			SDL_SetClipboardText(text);
		}

		// get clipboard value.
		std::string Input::GetClipboard() const
		{
			char* temp = SDL_GetClipboardText();
			std::string ret = std::string(temp);
			SDL_free(temp);
			return ret;
		}

		// get text input data.
		const TextInputData& Input::GetTextInput() const
		{
			return _textInputData;
		}

		// handle text input
		void Input::HandleTextInput(SDL_Event& e)
		{
			// keydown events - handle backspace and copy-paste events
			if (e.type == SDL_KEYDOWN)
			{
				// handle backspace
				if (e.key.keysym.sym == SDLK_BACKSPACE)
				{
					_textInputData.Backspace = true;
				}
				// handle delete
				else if (e.key.keysym.sym == SDLK_DELETE)
				{
					_textInputData.Delete = true;
				}
				// handle tab
				else if (e.key.keysym.sym == SDLK_TAB)
				{
					_textInputData.Tab = true;
				}
				// handle down
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					_textInputData.Down = true;
				}
				// handle up
				else if (e.key.keysym.sym == SDLK_UP)
				{
					_textInputData.Up = true;
				}
				// handle left
				else if (e.key.keysym.sym == SDLK_LEFT)
				{
					_textInputData.Left = true;
				}
				// handle right
				else if (e.key.keysym.sym == SDLK_RIGHT)
				{
					_textInputData.Right = true;
				}
				// handle home
				else if (e.key.keysym.sym == SDLK_HOME)
				{
					_textInputData.Home = true;
				}
				// handle end
				else if (e.key.keysym.sym == SDLK_END)
				{
					_textInputData.End = true;
				}
				// handle insert
				else if (e.key.keysym.sym == SDLK_INSERT)
				{
					_textInputData.Insert = true;
				}
				// handle copy command
				else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
				{
					_textInputData.Copy = true;
				}
				// handle paste command
				else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					_textInputData.Paste = true;
				}
			}
			else if (e.type == SDL_TEXTINPUT)
			{
				// only if not copy or paste event, add character
				if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
				{
					strcpy_s(_textInputData.Text, e.text.text);
				}
			}
		}

		// set key state
		void Input::SetKeyState(KeyCodes key, bool value)
		{
			// get existing value
			bool currVal = (_currKeyStates)[key].IsDown;

			// if didn't change, stop here!
			if (value == currVal) {
				return;
			}

			// set key state
			_ActionStates state;
			state.IsDown = value;
			state.UpdateFrameId = _GetEngine().UpdatesCount();
			state.FixedUpdateFrameId = _GetEngine().FixedUpdatesCount();
			(_currKeyStates)[key] = state;

			// check if this key is bound to action, and if so set action as well
			if (_keyBinds.find(key) != _keyBinds.end()) 
			{
				const char* action = (_keyBinds)[key].c_str();
				(_actionStates)[std::move(action)] = state;
			}
		}

		// get if given action is down
		bool Input::Down(const char* actionId) const
		{
			auto state = GetState(actionId);
			return state == KeyStates::PressedNow || state == KeyStates::Pressed;
		}

		// get if a given game action was released this frame
		bool Input::ReleasedNow(const char* actionId) const
		{
			auto state = GetState(actionId);
			return state == KeyStates::ReleasedNow;
		}

		// get if a given game action was pressed this frame
		bool Input::PressedNow(const char* actionId) const
		{
			auto state = GetState(actionId);
			return state == KeyStates::PressedNow;
		}

		// get if a key is currently down
		bool Input::Down(KeyCodes key) const
		{
			auto state = GetState(key);
			return state == KeyStates::PressedNow || state == KeyStates::Pressed;
		}

		// get if a key was released this frame
		bool Input::ReleasedNow(KeyCodes key) const
		{
			auto state = GetState(key);
			return state == KeyStates::ReleasedNow;
		}

		// get if a key was pressed this frame
		bool Input::PressedNow(KeyCodes key) const
		{
			auto state = GetState(key);
			return state == KeyStates::PressedNow;
		}

		// get action state
		KeyStates Input::GetState(const char* actionId) const
		{
			_ActionStates state = ((Input*)(this))->_actionStates[std::move(actionId)];
			bool wasUpdateNow = (_GetEngine().CurrentState() == engine::EngineStates::Update && _GetEngine().UpdatesCount() == state.UpdateFrameId) ||
				(_GetEngine().CurrentState() == engine::EngineStates::FixedUpdate && _GetEngine().FixedUpdatesCount() == state.FixedUpdateFrameId);
			if (state.IsDown) {
				return wasUpdateNow ? KeyStates::PressedNow : KeyStates::Pressed;
			}
			else {
				return wasUpdateNow ? KeyStates::ReleasedNow : KeyStates::Released;
			}
		}

		// get key state
		KeyStates Input::GetState(KeyCodes keyCode) const
		{
			_ActionStates state = ((Input*)(this))->_currKeyStates[keyCode];
			bool wasUpdateNow = (_GetEngine().CurrentState() == engine::EngineStates::Update && _GetEngine().UpdatesCount() == state.UpdateFrameId) ||
				(_GetEngine().CurrentState() == engine::EngineStates::FixedUpdate && _GetEngine().FixedUpdatesCount() == state.FixedUpdateFrameId);
			if (state.IsDown) {
				return wasUpdateNow ? KeyStates::PressedNow : KeyStates::Pressed;
			}
			else {
				return wasUpdateNow ? KeyStates::ReleasedNow : KeyStates::Released;
			}
		}
		
		// get keys assigned to action id
		std::vector<KeyCodes> Input::GetAssignedKeys(const char* actionId) const
		{
			std::vector<KeyCodes> ret;
			std::string actionIdStr(actionId);
			for (auto x : _keyBinds)
			{
				if (x.second == actionIdStr)
				{
					ret.push_back(x.first);
				}
			}
			return ret;
		}
	}
}