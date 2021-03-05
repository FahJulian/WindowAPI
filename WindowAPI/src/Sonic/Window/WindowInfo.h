#pragma once
#include "Sonic/Base.h"
#include "WindowMode.h"

namespace Sonic {
	
	struct WindowInfo
	{
		String fileNamePrefix;

		String title = "Sonic Window";
		bool saveTitle = true;

		int width = 848;
		int height = 480;
		bool saveSize = true;

		WindowMode mode = WindowMode::Windowed;
		bool saveMode = true;

		bool resizable = false;
		bool closeButton = true;

		bool closeOnAltF4 = true;
	};

}
