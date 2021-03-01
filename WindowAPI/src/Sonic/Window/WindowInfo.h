#pragma once
#include "Sonic/Base.h"
#include "WindowMode.h"

namespace Sonic {
	
	struct WindowInfo
	{
		String fileNamePrefix;

		String initialName = "Sonic Window";
		bool saveName = true;

		int initialWidth = 848;
		int initialHeight = 480;
		bool saveSize = true;

		WindowMode initialMode = WindowMode::Windowed;
		bool saveMode = true;

		bool resizable = false;

		String currentName;

		int currentWidth = 0;
		int currentHeight = 0;

		WindowMode currentMode = WindowMode::Windowed;
	};

}
