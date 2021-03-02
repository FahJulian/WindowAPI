#include <array>
#include "Keys.h"

using namespace Sonic;


static std::array<const char*, HIGHEST_KEY + 1> getKeyNames()
{
    std::array<const char*, HIGHEST_KEY + 1> keyNames;

    keyNames[Keys::Backspace] = "BACKSPACE";
    keyNames[Keys::Tab] = "TAB";
    keyNames[Keys::Clear] = "CLEAR";
    keyNames[Keys::Enter] = "ENTER";
    keyNames[Keys::NumpadEnter] = "NUMPAD_ENTER";
    keyNames[Keys::LeftShift] = "SHIFT";
    keyNames[Keys::LeftControl] = "CONTROL";
    keyNames[Keys::LeftAlt] = "ALT";
    keyNames[Keys::Pause] = "PAUSE";
    keyNames[Keys::CapsLock] = "CAPS_LOCK";
    keyNames[Keys::ImeKana] = "IME_KANA";
    keyNames[Keys::ImeHangul] = "IME_HANGUL";
    keyNames[Keys::ImeOn] = "IME_ON";
    keyNames[Keys::ImeJunja] = "IME_JUNJA";
    keyNames[Keys::ImeFinal] = "IME_FINAL";
    keyNames[Keys::ImeHanja] = "IME_HANJA";
    keyNames[Keys::ImeKanji] = "IME_KANJI";
    keyNames[Keys::ImeOff] = "IME_OFF";
    keyNames[Keys::Escape] = "ESCAPE";
    keyNames[Keys::ImeConvert] = "IME_CONVERT";
    keyNames[Keys::ImeNonconvert] = "IME_NONCONVERT";
    keyNames[Keys::ImeAccept] = "IME_ACCEPT";
    keyNames[Keys::ImeModeChange] = "IME_MODE_CHANGE";
    keyNames[Keys::Space] = "SPACE";
    keyNames[Keys::PageUp] = "PAGE_UP";
    keyNames[Keys::PageDown] = "PAGE_DOWN";
    keyNames[Keys::End] = "END";
    keyNames[Keys::Home] = "HOME";
    keyNames[Keys::ArrowLeft] = "ARROW_LEFT";
    keyNames[Keys::ArrowUp] = "ARROW_UP";
    keyNames[Keys::ArrowRight] = "ARROW_RIGHT";
    keyNames[Keys::ArrowDown] = "ARROW_DOWN";
    keyNames[Keys::Select] = "SELECT";
    keyNames[Keys::Print] = "PRINT";
    keyNames[Keys::Execute] = "EXECUTE";
    keyNames[Keys::PrintScreen] = "PRINT_SCREEN";
    keyNames[Keys::Insert] = "INSERT";
    keyNames[Keys::Delete] = "DELETE";
    keyNames[Keys::Help] = "HELP";

    keyNames[Keys::_0] = "0";
    keyNames[Keys::_1] = "1";
    keyNames[Keys::_2] = "2";
    keyNames[Keys::_3] = "3";
    keyNames[Keys::_4] = "4";
    keyNames[Keys::_5] = "5";
    keyNames[Keys::_6] = "6";
    keyNames[Keys::_7] = "7";
    keyNames[Keys::_8] = "8";
    keyNames[Keys::_9] = "9";

    keyNames[Keys::A] = "A";
    keyNames[Keys::B] = "B";
    keyNames[Keys::C] = "C";
    keyNames[Keys::D] = "D";
    keyNames[Keys::E] = "E";
    keyNames[Keys::F] = "F";
    keyNames[Keys::G] = "G";
    keyNames[Keys::H] = "H";
    keyNames[Keys::I] = "I";
    keyNames[Keys::J] = "J";
    keyNames[Keys::K] = "K";
    keyNames[Keys::L] = "L";
    keyNames[Keys::M] = "M";
    keyNames[Keys::N] = "N";
    keyNames[Keys::O] = "O";
    keyNames[Keys::P] = "P";
    keyNames[Keys::Q] = "Q";
    keyNames[Keys::R] = "R";
    keyNames[Keys::S] = "S";
    keyNames[Keys::T] = "T";
    keyNames[Keys::U] = "U";
    keyNames[Keys::V] = "V";
    keyNames[Keys::W] = "W";
    keyNames[Keys::X] = "X";
    keyNames[Keys::Y] = "Y";
    keyNames[Keys::Z] = "Z";

    keyNames[Keys::LeftWindows] = "WINDOWS";
    keyNames[Keys::RightWindows] = "WINDOWS_RIGHT";
    keyNames[Keys::Apps] = "APPS";
    keyNames[Keys::Sleep] = "SLEEP";

    keyNames[Keys::Numpad0] = "NUMPAD_0";
    keyNames[Keys::Numpad1] = "NUMPAD_1";
    keyNames[Keys::Numpad2] = "NUMPAD_2";
    keyNames[Keys::Numpad3] = "NUMPAD_3";
    keyNames[Keys::Numpad4] = "NUMPAD_4";
    keyNames[Keys::Numpad5] = "NUMPAD_5";
    keyNames[Keys::Numpad6] = "NUMPAD_6";
    keyNames[Keys::Numpad7] = "NUMPAD_7";
    keyNames[Keys::Numpad8] = "NUMPAD_8";
    keyNames[Keys::Numpad9] = "NUMPAD_9";

    keyNames[Keys::NumpadMultiply] = "NUMPAD_MULTIPLY";
    keyNames[Keys::NumpadAdd] = "NUMPAD_ADD";

    keyNames[Keys::Seperator] = "SEPERATOR";

    keyNames[Keys::NumpadSubstract] = "NUMPAD_SUBSTRACT";
    keyNames[Keys::NumpadDecimal] = "NUMPAD_DECIMAL";
    keyNames[Keys::NumpadDivide] = "NUMPAD_DIVIDE";

    keyNames[Keys::F1] = "F1";
    keyNames[Keys::F2] = "F2";
    keyNames[Keys::F3] = "F3";
    keyNames[Keys::F4] = "F4";
    keyNames[Keys::F5] = "F5";
    keyNames[Keys::F6] = "F6";
    keyNames[Keys::F7] = "F7";
    keyNames[Keys::F8] = "F8";
    keyNames[Keys::F9] = "F9";
    keyNames[Keys::F10] = "F10";
    keyNames[Keys::F11] = "F11";
    keyNames[Keys::F12] = "F12";
    keyNames[Keys::F13] = "F13";
    keyNames[Keys::F14] = "F14";
    keyNames[Keys::F15] = "F15";
    keyNames[Keys::F16] = "F16";
    keyNames[Keys::F17] = "F17";
    keyNames[Keys::F18] = "F18";
    keyNames[Keys::F19] = "F19";
    keyNames[Keys::F20] = "F20";
    keyNames[Keys::F21] = "F21";
    keyNames[Keys::F22] = "F22";
    keyNames[Keys::F23] = "F23";
    keyNames[Keys::F24] = "F24";

    keyNames[Keys::NumLock] = "NUM_LOCK";
    keyNames[Keys::Scroll] = "SCROLL";

    keyNames[Keys::RightControl] = "CONTROL_RIGHT";

    keyNames[Keys::RightAlt] = "ALT_RIGHT";

    keyNames[Keys::BrowserBack] = "BROWSER_BACK";
    keyNames[Keys::BrowserForward] = "BROWSER_FORWARD";
    keyNames[Keys::BrowserRefresh] = "BROWSER_REFRESH";
    keyNames[Keys::BrowserStop] = "BROWSER_STOP";
    keyNames[Keys::BrowserSearch] = "BROWSER_SEARCH";
    keyNames[Keys::BrowserFavorites] = "BROWSER_FAVORITES";
    keyNames[Keys::BrowserHome] = "BROWSER_HOME";

    keyNames[Keys::VolumeMute] = "VOLUME_MUTE";
    keyNames[Keys::VolumeDown] = "VOLUME_DOWN";
    keyNames[Keys::VolumeUp] = "VOLUME_UP";

    keyNames[Keys::MediaNextTrack] = "MEDIA_NEXT_TRACK";
    keyNames[Keys::MediaPreviousTrack] = "MEDIA_PREVIOUS_TRACK";
    keyNames[Keys::MediaStop] = "MEDIA_STOP";
    keyNames[Keys::MediaPlay] = "MEDIA_PLAY";
    keyNames[Keys::MediaPause] = "MEDIA_PAUSE";

    keyNames[Keys::StartMail] = "START_MAIL";
    keyNames[Keys::SelectMedia] = "SELECT_MEDIA";
    keyNames[Keys::StartApp1] = "START_APP1";
    keyNames[Keys::StartApp2] = "START_APP2";

    keyNames[Keys::Oem1] = "OEM_1";

    keyNames[Keys::Plus] = "PLUS";
    keyNames[Keys::Comma] = "COMMA";
    keyNames[Keys::Minus] = "MINUS";
    keyNames[Keys::Period] = "PERIOD";

    keyNames[Keys::Oem2] = "OEM_2";
    keyNames[Keys::Oem3] = "OEM_3";
    keyNames[Keys::Oem4] = "OEM_4";
    keyNames[Keys::Oem5] = "OEM_5";
    keyNames[Keys::Oem6] = "OEM_6";
    keyNames[Keys::Oem7] = "OEM_7";
    keyNames[Keys::Oem8] = "OEM_8";
    keyNames[Keys::Oem102] = "OEM_102";

    keyNames[Keys::ImeProcess] = "IME_PROCESS";
    keyNames[Keys::Attn] = "ATTN";
    keyNames[Keys::Crsel] = "CRSEL";
    keyNames[Keys::ExSel] = "EX_SEL";
    keyNames[Keys::EraseEOF] = "ERASE_EOF";
    keyNames[Keys::Play] = "PLAY";
    keyNames[Keys::Zoom] = "ZOOM";
    keyNames[Keys::PA1] = "PA1";

    keyNames[Keys::OemClear] = "OEM_CLEAR";

    return keyNames;
}

std::ostream& ::operator<<(std::ostream& ostream, Key button)
{
    static std::array<const char*, HIGHEST_KEY + 1> buttonNames = getKeyNames();

    ostream << buttonNames[button.code];
    return ostream;
}
