#pragma once
#include <cstdint>

namespace Sonic {

    using MouseButton = uint8_t;

    namespace MouseButtons {
        
        const MouseButton Left = 0x00;
        const MouseButton Right = 0x01;
        const MouseButton Middle = 0x02;
        const MouseButton MB_4 = 0x03;
        const MouseButton MB_5 = 0x04;

    }

    const MouseButton HIGHEST_BUTTON = 0x04;
}
