#include "Mouse.h"

using namespace Sonic;


float Mouse::s_X = 0.0f;
float Mouse::s_Y = 0.0f;
std::array<bool, HIGHEST_BUTTON + 1> Mouse::s_Buttons;
