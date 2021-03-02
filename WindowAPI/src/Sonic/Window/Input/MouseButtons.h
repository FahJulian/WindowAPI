#pragma once
#include <cstdint>
#include <iostream>

namespace Sonic {

    struct MouseButton
    {
        uint8_t code;

        MouseButton(uint8_t code)
            : code(code)
        {
        }

        inline bool operator==(MouseButton other) const { return code == other.code; }
        inline bool operator!=(MouseButton other) const { return code != other.code; }

        inline operator size_t() const { return (size_t)code; }
        inline operator uint8_t() const { return (uint8_t)code; }
        inline operator int() const { return (int)code; }
    };
    
    namespace MouseButtons {
        
        const MouseButton Left = 0x00;
        const MouseButton Right = 0x01;
        const MouseButton Middle = 0x02;
        const MouseButton MB_4 = 0x03;
        const MouseButton MB_5 = 0x04;

    }

    const size_t HIGHEST_BUTTON = 0x04;

    std::ostream& operator<<(std::ostream& ostream, MouseButton button);
}
