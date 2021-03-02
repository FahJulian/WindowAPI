#include <array>
#include "MouseButtons.h"

using namespace Sonic;


static std::array<const char*, HIGHEST_BUTTON + 1> getButtonNames()
{
    std::array<const char*, HIGHEST_BUTTON + 1> buttonNames;

    buttonNames[MouseButtons::Left] = "MB_Left";
    buttonNames[MouseButtons::Right] = "MB_Right";
    buttonNames[MouseButtons::Middle] = "MB_Middle";
    buttonNames[MouseButtons::MB_4] = "MB_4";
    buttonNames[MouseButtons::MB_5] = "MB_5";

    return buttonNames;
}


std::ostream& ::operator<<(std::ostream& ostream, MouseButton button)
{
    static std::array<const char*, HIGHEST_BUTTON + 1> buttonNames = getButtonNames();

    ostream << buttonNames[button.code];
    return ostream;
}
