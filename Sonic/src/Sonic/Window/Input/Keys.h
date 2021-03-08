#pragma once
#include <cstdint>

namespace Sonic {

    using Key = uint8_t;

    namespace Keys {

        // Windows

        const Key Backspace = 0x08;
        const Key Tab = 0x09;
        const Key Clear = 0x0c;

        const Key Enter = 0x0d;
        const Key LeftEnter = Enter;
        const Key NumpadEnter = 0x0f;

        const Key Shift = 0x10;
        const Key LeftShift = Shift;

        const Key Control = 0x11;
        const Key LeftControl = Control;

        const Key Alt = 0x12;
        const Key LeftAlt = Alt;

        const Key Pause = 0x13;

        const Key CapsLock = 0x14;

        const Key ImeKana = 0x15;
        const Key ImeHangul = 0x15;
        const Key ImeOn = 0x16;
        const Key ImeJunja = 0x17;
        const Key ImeFinal = 0x18;
        const Key ImeHanja = 0x19;
        const Key ImeKanji = 0x19;
        const Key ImeOff = 0x1a;

        const Key Escape = 0x1b;

        const Key ImeConvert = 0x01c;
        const Key ImeNonconvert = 0x1d;
        const Key ImeAccept = 0x1e;
        const Key ImeModeChange = 0x1f;

        const Key Space = 0x20;

        const Key PageUp = 0x21;
        const Key PageDown = 0x22;
        const Key End = 0x23;
        const Key Home = 0x24;
        const Key Pos1 = Home;

        const Key Left = 0x25;
        const Key ArrowLeft = Left;
        const Key Up = 0x26;
        const Key ArrowUp = Up;
        const Key Right = 0x27;
        const Key ArrowRight = Right;
        const Key Down = 0x28;
        const Key ArrowDown = Down;
        const Key Select = 0x29;
        const Key Print = 0x2a;
        const Key Execute = 0x2b;
        const Key PrintScreen = 0x2c;
        const Key Insert = 0x2d;
        const Key Delete = 0x2e;
        const Key Help = 0x2f;

        const Key _0 = 0x30;
        const Key _1 = 0x31;
        const Key _2 = 0x32;
        const Key _3 = 0x33;
        const Key _4 = 0x34;
        const Key _5 = 0x35;
        const Key _6 = 0x36;
        const Key _7 = 0x37;
        const Key _8 = 0x38;
        const Key _9 = 0x39;

        const Key A = 0x41;
        const Key B = 0x42;
        const Key C = 0x43;
        const Key D = 0x44;
        const Key E = 0x45;
        const Key F = 0x46;
        const Key G = 0x47;
        const Key H = 0x48;
        const Key I = 0x49;
        const Key J = 0x4a;
        const Key K = 0x4b;
        const Key L = 0x4c;
        const Key M = 0x4d;
        const Key N = 0x4e;
        const Key O = 0x4f;
        const Key P = 0x50;
        const Key Q = 0x51;
        const Key R = 0x52;
        const Key S = 0x53;
        const Key T = 0x54;
        const Key U = 0x55;
        const Key V = 0x56;
        const Key W = 0x57;
        const Key X = 0x58;
        const Key Y = 0x59;
        const Key Z = 0x5a;

        const Key Windows = 0x5b;
        const Key LeftWindows = Windows;
        const Key RightWindows = 0x5c;

        const Key Apps = 0x5d;
        const Key Sleep = 0x5f;

        const Key Numpad0 = 0x60;
        const Key Numpad1 = 0x61;
        const Key Numpad2 = 0x62;
        const Key Numpad3 = 0x63;
        const Key Numpad4 = 0x64;
        const Key Numpad5 = 0x65;
        const Key Numpad6 = 0x66;
        const Key Numpad7 = 0x67;
        const Key Numpad8 = 0x68;
        const Key Numpad9 = 0x69;

        const Key NumpadMultiply = 0x6a;
        const Key NumpadAdd = 0x6b;

        const Key Seperator = 0x6c;

        const Key NumpadSubstract = 0x6d;
        const Key NumpadDecimal = 0x6e;
        const Key NumpadDivide = 0x6f;

        const Key F1 = 0x70;
        const Key F2 = 0x71;
        const Key F3 = 0x72;
        const Key F4 = 0x73;
        const Key F5 = 0x74;
        const Key F6 = 0x75;
        const Key F7 = 0x76;
        const Key F8 = 0x77;
        const Key F9 = 0x78;
        const Key F10 = 0x79;
        const Key F11 = 0x7a;
        const Key F12 = 0x7b;
        const Key F13 = 0x7c;
        const Key F14 = 0x7d;
        const Key F15 = 0x7e;
        const Key F16 = 0x7f;
        const Key F17 = 0x80;
        const Key F18 = 0x81;
        const Key F19 = 0x82;
        const Key F20 = 0x83;
        const Key F21 = 0x84;
        const Key F22 = 0x85;
        const Key F23 = 0x86;
        const Key F24 = 0x87;

        const Key NumLock = 0x90;
        const Key Scroll = 0x91;

        const Key RightShift = Shift; // They appear to be the same, at least on windows
        // 0xa2 is another left shift?

        const Key RightControl = 0xa3;
        // 0xa2 is another left control?

        const Key RightAlt = 0xa5;
        // 0xa2 is another left alt?

        const Key BrowserBack = 0xa6;
        const Key BrowserForward = 0xa7;
        const Key BrowserRefresh = 0xa8;
        const Key BrowserStop = 0xa9;
        const Key BrowserSearch = 0xaa;
        const Key BrowserFavorites = 0xab;
        const Key BrowserHome = 0xac;

        const Key VolumeMute = 0xad;
        const Key VolumeDown = 0xae;
        const Key VolumeUp = 0xaf;

        const Key MediaNextTrack = 0xb0;
        const Key MediaPreviousTrack = 0xb1;
        const Key MediaStop = 0xb2;
        const Key MediaPlay = 0xb3;
        const Key MediaPause = 0xb3;

        const Key StartMail = 0xb5;
        const Key SelectMedia = 0xb5;
        const Key StartApp1 = 0xb6;
        const Key StartApp2 = 0xb7;
            
        const Key Oem1 = 0xba;

        const Key Plus = 0xbb;
        const Key Comma = 0xbc;
        const Key Minus = 0xbd;
        const Key Period = 0xbe;

        const Key Oem2 = 0xbf;
        const Key Oem3 = 0xc0;
        const Key Oem4 = 0xdb;
        const Key Oem5 = 0xdc;
        const Key Oem6 = 0xdd;
        const Key Oem7 = 0xde;
        const Key Oem8 = 0xdf;
        const Key Oem102 = 0xe2;
        
        const Key ImeProcess = 0xe5;
        const Key Attn = 0xf6;
        const Key Crsel = 0xf7;
        const Key ExSel = 0xf8;
        const Key EraseEOF = 0xf9;
        const Key Play = 0xfa;
        const Key Zoom = 0xfb;
        const Key PA1 = 0xfd;
            
        const Key OemClear = 0xfe;
    }

    const Key HIGHEST_KEY = 0xfe;
}
