#pragma once
#include "Sonic/Base.h"
#include "Icon/Cursors.h"
#include "WindowMode.h"
#include "Icon/IconInfo.h"
#include "Icon/CursorInfo.h"

namespace Sonic {
	
	struct WindowInfo
	{
		String fileNamePrefix;
		bool isLoadedFromJson;

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

		std::vector<IconInfo> icons;
		std::unordered_map<String, CursorInfo> cursors;
	};

}
