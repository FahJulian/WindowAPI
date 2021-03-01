#pragma once
#pragma warning(disable:26812)
#include <cstdint>

namespace Sonic {

    using MouseButton = uint8_t;

    const size_t BUTTON_AMOUNT = 5;
    
    namespace MouseButtons {
        
        enum : MouseButton
        {
            Left,
            Right,
            Middle,
            MB_4,
            MB_5,
        };

    }

}
