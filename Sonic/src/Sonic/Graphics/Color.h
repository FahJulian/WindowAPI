#pragma once

namespace Sonic {

    using ColorCode = unsigned int;

    struct Color
    {
        float r;
        float g;
        float b;
        float a;

        Color()
            : r(0.0f), g(0.0f), b(0.0f), a(0.0)
        {
        }

        Color(float r, float g, float b, float a)
            : r(r), g(g), b(b), a(a)
        {
        }

        Color(int r, int g, int b, int a)
            : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f)
        {
        }

        Color(ColorCode colorCode)
            : Color(((colorCode >> 24) & 255) / 255.0f, ((colorCode >> 16) & 255) / 255.0f,
                ((colorCode >> 8) & 255) / 255.0f, (colorCode & 255) / 255.0f)
        {
        }
    };

    namespace Colors {

        const Color Transparent = 0x00000000;
        const Color White = 0xffffffff;
        const Color Black = 0x000000ff;
        const Color DarkGray = 0x555555ff;
        const Color LightGray = 0x999999ff;

        const Color Red = 0xff0000ff;
        const Color Green = 0x00ff00ff;
        const Color Blue = 0x0000ffff;
        const Color Magenta = 0xff00ffff;
        const Color Cyan = 0x00ffffff;
        const Color Yellow = 0xffff00ff;

        const Color LightGreen = 0x12db13ff;
        const Color DarkGreen = 0x084d08ff;
        const Color LightRed = 0xf42828ff;
        const Color DarkRed = 0x810707ff;
        const Color LightBlue = 0x4ab8f7ff;
        const Color DarkBlue = 0x071463ff;

        const Color Orange = 0xff8c00ff;

    }

}