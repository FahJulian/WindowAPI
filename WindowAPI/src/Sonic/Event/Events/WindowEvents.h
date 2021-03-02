#pragma once

namespace Sonic {

    struct WindowClosedEvent
    {
    };

    struct WindowResizedEvent
    {
        float width;
        float height;

        WindowResizedEvent(float width, float height)
            : width(width), height(height)
        {
        }
    };

}
