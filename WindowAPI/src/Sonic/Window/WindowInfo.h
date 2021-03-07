#pragma once
#include "Sonic/Base.h"
#include "Sonic/Graphics/Color.h"
#include "Icon/IconInfo.h"
#include "Icon/CursorInfo.h"
#include "WindowMode.h"

namespace Sonic {
	
	struct WindowInfo
	{
		String fileNamePrefix;
		bool isLoadedFromJson;

		String title = "Sonic Window";
		bool saveTitle = true;

		Color clearColor = 0x333333ff;
		bool saveClearColor = true;

		int width = 848;
		int height = 480;
		bool saveSize = true;

		WindowMode mode = WindowMode::Windowed;
		bool saveMode = true;

		bool resizable = false;
		bool closeButton = true;

		bool closeOnAltF4 = true;

		bool minimized = false;
		bool maximized = false;

		bool saveMinimized = false;
		bool saveMaximized = true;

		std::vector<IconInfo> icons;
		std::unordered_map<String, CursorInfo> cursors;
	};

}
