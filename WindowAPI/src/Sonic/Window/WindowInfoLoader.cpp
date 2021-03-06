#pragma once
#include <algorithm>
#include <filesystem>
#include <json/json.hpp>
#include "Icon/IconAndCursorLoader.h"
#include "WindowInfoLoader.h"

#include <iostream>

using namespace Sonic;

static WindowMode toWindowMode(const String& name)
{
	if (name == "Fullscreen")
		return WindowMode::Fullscreen;
	else if (name == "WindowedBorderless")
		return WindowMode::WindowedBorderless;
	else if (name == "WindowedFullscreen")
		return WindowMode::WindowedFullscreen;
	else
		return WindowMode::Windowed;
}

static Cursors::StandardCursorSet toStandardCursorSet(const String& name)
{
	if (name == "DarkShadow")
		return Cursors::StandardCursorSet::DarkShadow;
	else if (name == "White")
		return Cursors::StandardCursorSet::White;
	else if (name == "WhiteShadow")
		return Cursors::StandardCursorSet::WhiteShadow;
	else
		return Cursors::StandardCursorSet::Dark;
}

static void loadJson(WindowInfo* info, InputFileStream file)
{
	JSON json;

	try
	{
		file >> json;
	}
	catch (nlohmann::detail::parse_error)
	{
		// TODO: Print error
		return;
	}

	if (json.contains("initialName"))
		info->title = json["initialName"].get<String>();

	if (json.contains("initialSize"))
	{
		JSON size = json["initialSize"];
		if (size.is_array())
		{
			info->width = size[0].get<int>();
			info->height = size[1].get<int>();
		}
		else if (size.is_object())
		{
			info->width = size["width"].get<int>();
			info->height = size["height"].get<int>();
		}
		else if (size.is_string())
		{
			String sizeString = size.get<String>();
			size_t seperatorIndex = sizeString.find('x');

			info->width = std::stoi(sizeString, 0);
			info->height = std::stoi(sizeString.substr(seperatorIndex + 1), 0);
		}
	}

	if (json.contains("initialName"))
		info->title = json["initialName"].get<String>();
	if (json.contains("initialMode"))
		info->mode = toWindowMode(json["initialMode"].get<String>());
	if (json.contains("saveName"))
		info->saveTitle = json["saveName"].get<bool>();
	if (json.contains("saveSize"))
		info->saveSize = json["saveSize"].get<bool>();
	if (json.contains("saveMode"))
		info->saveMode = json["saveMode"].get<bool>();
	if (json.contains("resizable"))
		info->resizable = json["resizable"].get<bool>();
	if (json.contains("closeButton"))
		info->closeButton = json["closeButton"].get<bool>();
	if (json.contains("closeOnAltF4"))
		info->closeOnAltF4 = json["closeOnAltF4"].get<bool>();

	std::vector<String> iconFilePaths;
	if (json.contains("icons") && json["icons"].is_array())
		for (JSON& iconFilePath : json["icons"])
			if (iconFilePath.is_string())
				iconFilePaths.push_back(iconFilePath.get<String>());
	
	String standardCursors;
	if (json.contains("standardCursorSet") && json["standardCursorSet"].is_string())
	{
		String standardCursorSet = json["standardCursorSet"];
		if (standardCursorSetFolderPaths.find(standardCursorSet) != standardCursorSetFolderPaths.end())
			standardCursors = standardCursorSetFolderPaths.at(standardCursorSet);
		else
			standardCursors = defaultStandardCursorSet;
	}

	std::unordered_map<String, String> cursorFilePaths;
	if (json.contains("cursors") && json["cursors"].is_object())
		for (auto& [cursorName, cursorFilePath] : json["cursors"].items())
			if (cursorFilePath.is_string())
				cursorFilePaths.emplace(cursorName, cursorFilePath.get<String>());

	info->icons = Util::loadIcons(iconFilePaths);
	info->cursors = Util::loadCursors(standardCursors, cursorFilePaths);
}

static void loadBinary(WindowInfo* info, InputFileStream file)
{
	uint16_t sizeOfName;
	file.read((char*)&sizeOfName, sizeof(sizeOfName));
	
	char* name = new char[sizeOfName + 1] { 0 };
	file.read(name, sizeOfName);
	info->title = String(name);
	delete name;

	file.read((char*)&info->width, 2);
	file.read((char*)&info->height, 2);

	file.read((char*)&info->mode, 1);

	file.read((char*)&info->saveTitle, 1);
	file.read((char*)&info->saveSize, 1);
	file.read((char*)&info->saveMode, 1);
	file.read((char*)&info->resizable, 1);
	file.read((char*)&info->closeButton, 1);
	file.read((char*)&info->closeOnAltF4, 1);

	info->cursors = Util::loadCursors(file);
	info->icons = Util::loadIcons(file);
}


WindowInfo Util::loadWindowInfo(String filePath, bool overrideBinary)
{
	WindowInfo info;

	std::replace(filePath.begin(), filePath.end(), '/', '\\');

	size_t i_fileEnding = filePath.find('.');
	info.fileNamePrefix = i_fileEnding != String::npos ? filePath.substr(0, i_fileEnding) : filePath;

	if (!std::filesystem::exists(info.fileNamePrefix + ".sonicwindow") || overrideBinary)
	{
		info.isLoadedFromJson = true;
		loadJson(&info, InputFileStream(info.fileNamePrefix + ".sonicwindow.json", std::ios::in | std::ios::binary));
	}
	else
	{
		info.isLoadedFromJson = false;
		loadBinary(&info, InputFileStream(info.fileNamePrefix + ".sonicwindow"));
	}

	return info;
}

bool Util::saveWindowInfo(const WindowInfo& info)
{
	OutputFileStream file = OutputFileStream(info.fileNamePrefix + ".sonicwindow", std::ios::out | std::ios::binary);

	uint16_t sizeOfName = (uint16_t)(info.title.size());
	file.write((const char*)&sizeOfName, sizeof(sizeOfName));
	file.write((const char*)info.title.c_str(), sizeOfName);

	uint16_t width = (uint16_t)info.width;
	file.write((const char*)&width, sizeof(width));

	uint16_t height = (uint16_t)info.height;
	file.write((const char*)&height, sizeof(height));

	file.write((const char*)&info.mode, sizeof(WindowMode));

	file.write((const char*)&info.saveTitle, sizeof(info.saveTitle));
	file.write((const char*)&info.saveSize, sizeof(info.saveSize));
	file.write((const char*)&info.saveMode, sizeof(info.saveMode));

	file.write((const char*)&info.resizable, sizeof(info.resizable));
	file.write((const char*)&info.closeButton, sizeof(info.closeButton));

	file.write((const char*)&info.closeOnAltF4, sizeof(info.closeOnAltF4));

	if (info.isLoadedFromJson)
	{
		saveCursors(info.cursors, file);
		saveIcons(info.icons, file);
	}

	file.close();
	return file.good();
}

/*
* File format:
* 2 bytes: size of Name
* ? bytes: name
* 2 bytes: initial width
* 2 bytes: initial height
* 1 byte: initial mode
* 1 byte: save name
* 1 byte: save size
* 1 byte: save mode
* 1 byte: resizable
* 1 byte: closeButton
* 1 byte: closeOnAltF4
*/
