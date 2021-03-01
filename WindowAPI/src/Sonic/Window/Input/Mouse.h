#pragma once
#include "MouseButtons.h"

namespace Sonic {

	class Mouse
	{
		static float getX() { return s_X; }
		static float getY() { return s_Y; }

		static bool isButtonPressed(MouseButton button) { return s_Buttons[(uint8_t)button]; }

	private:
		static float s_X, s_Y;
		static bool s_Buttons[BUTTON_AMOUNT];

		friend class Window;
	};

}
