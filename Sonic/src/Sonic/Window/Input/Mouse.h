#pragma once
#include <array>
#include "MouseButtons.h"

namespace Sonic {

	class Mouse
	{
	public:
		static float getX() { return s_X; }
		static float getY() { return s_Y; }

		static bool isButtonPressed(MouseButton button) { return s_Buttons[button]; }

	private:
		static float s_X, s_Y;
		static std::array<bool, HIGHEST_BUTTON + 1> s_Buttons;

		friend class Window;
	};

}
