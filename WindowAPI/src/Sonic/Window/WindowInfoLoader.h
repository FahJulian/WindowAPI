#pragma once
#include "WindowInfo.h"

namespace Sonic::Util {

	WindowInfo loadWindowInfo(String filePath, bool overrideBinary = false);

	bool saveWindowInfo(WindowInfo& info);

}
