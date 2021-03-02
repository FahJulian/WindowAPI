#pragma once
#include "Sonic/Window/Input/Keys.h"

namespace Sonic {

    struct KeyPressedEvent
    {
        Key key;
        wchar_t character;

        KeyPressedEvent(Key key, wchar_t character)
            : key(key), character(character)
        {
        }
    };

    struct KeyReleasedEvent
    {
        Key key;

        KeyReleasedEvent(Key key)
            : key(key)
        {
        }
    };

}