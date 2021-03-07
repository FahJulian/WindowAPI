#pragma once
#include "Sonic/Util/BinaryFileUtils.h"
#include "IconInfo.h"
#include "CursorInfo.h"

namespace Sonic {

	const std::unordered_map<String, String> standardCursorSetDirs = {
		{
			{ "Dark", coreResourceDir() + "cursors" + "/dark/" },
			{ "DarkShadow", coreResourceDir() + "cursors" + "/dark_shadow/" },
			{ "White", coreResourceDir() + "cursors" + "/white/" },
			{ "WhiteShadow", coreResourceDir() + "cursors" + "/white_shadow/" },
		}
	};

	const String defaultStandardCursorSet = "Dark";
	
	namespace Util {

		std::unordered_map<String, CursorInfo> loadCursors(BinaryInputFileStream& binaryFile);
		std::unordered_map<String, CursorInfo> loadCursors(const String& standardCursorSet, const std::unordered_map<String, String> filePaths);

		std::vector<IconInfo> loadIcons(BinaryInputFileStream& binaryFile);
		std::vector<IconInfo> loadIcons(const std::vector<String>& filePaths);

		void saveCursors(std::unordered_map<String, CursorInfo>& cursors, BinaryOutputFileStream& file);
		void saveIcons(std::vector<IconInfo>& icons, BinaryOutputFileStream& file);

	}

}
