#pragma once
#include <array>
#include "Keys.h"

namespace Sonic {
	
	class Keyboard
	{
	public:
		static bool isKeyPressed(Key key) 
		{ 
			return s_Keys[key]; 
		}

	private:
		static std::array<bool, HIGHEST_KEY + 1> s_Keys;

		friend class Window;
	};

}
