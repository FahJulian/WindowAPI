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

	if (json.contains("name"))
		info->title = json["name"].get<String>();

	if (json.contains("size"))
	{
		JSON size = json["size"];
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

	if (json.contains("clearColor"))
	{
		JSON clearColor = json["clearColor"];
		if (clearColor.is_string())
		{
			String clearColorString = clearColor.get<String>();
			if (clearColorString.size() == 10)
				info->clearColor = std::stoul(clearColorString, nullptr, 16);
			else if (clearColorString.size() == 8)
				info->clearColor = std::stoul(clearColorString, nullptr, 16) | 0x000000ff;
		}
		else if (clearColor.is_array())
		{
			info->clearColor.r = clearColor[0].is_number_float() ? clearColor[0].get<float>() : clearColor[0].get<int>() / 255.0f;
			info->clearColor.g = clearColor[1].is_number_float() ? clearColor[1].get<float>() : clearColor[1].get<int>() / 255.0f;
			info->clearColor.b = clearColor[2].is_number_float() ? clearColor[2].get<float>() : clearColor[2].get<int>() / 255.0f;

			if (clearColor.size() > 3)
				info->clearColor.a = clearColor[3].is_number_float() ? clearColor[3].get<float>() : clearColor[3].get<int>() / 255.0f;
		}
		else
		{
			if (clearColor.contains("r"))
				info->clearColor.r = clearColor["r"].is_number_float() ? clearColor["r"].get<float>() : clearColor["r"].get<int>() / 255.0f;
			if (clearColor.contains("g"))
				info->clearColor.g = clearColor["g"].is_number_float() ? clearColor["g"].get<float>() : clearColor["g"].get<int>() / 255.0f;
			if (clearColor.contains("b"))
				info->clearColor.b = clearColor["b"].is_number_float() ? clearColor["b"].get<float>() : clearColor["b"].get<int>() / 255.0f;
			if (clearColor.contains("a"))
				info->clearColor.a = clearColor["a"].is_number_float() ? clearColor["a"].get<float>() : clearColor["a"].get<int>() / 255.0f;
		}
	}

	if (json.contains("name"))
		info->title = json["name"].get<String>();
	if (json.contains("mode"))
		info->mode = toWindowMode(json["mode"].get<String>());
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

	String standardCursorSet = defaultStandardCursorSet;
	if (json.contains("standardCursorSet") && json["standardCursorSet"].is_string())
		String standardCursorSet = json["standardCursorSet"];

	std::unordered_map<String, String> cursorFilePaths;
	if (json.contains("cursors") && json["cursors"].is_object())
		for (auto& [cursorName, cursorFilePath] : json["cursors"].items())
			if (cursorFilePath.is_string())
				cursorFilePaths.emplace(cursorName, cursorFilePath.get<String>());

	info->cursors = Util::loadCursors(standardCursorSet, cursorFilePaths);
	info->icons = Util::loadIcons(iconFilePaths);
}

static void loadBinary(WindowInfo* info, BinaryInputFileStream&& file)
{
	uint16_t nameSize = file.read<uint16_t>();
	const char* name = file.read<char>(nameSize);
	info->title = String(name, nameSize);
	delete[] name;

	info->width = file.read<uint16_t>();
	info->height = file.read<uint16_t>();

	info->mode = file.read<WindowMode>();

	info->clearColor = file.read<uint32_t>();

	info->saveTitle = file.read<bool>();
	info->saveSize = file.read<bool>();
	info->saveMode = file.read<bool>();
	info->saveClearColor = file.read<bool>();
	info->resizable = file.read<bool>();
	info->closeButton = file.read<bool>();
	info->closeOnAltF4 = file.read<bool>();

	info->cursors = Util::loadCursors(file);
	info->icons = Util::loadIcons(file);
}


WindowInfo Util::loadWindowInfo(String filePath, bool overrideBinary)
{
	WindowInfo info;

	size_t i_fileEnding = filePath.find('.');
	info.fileNamePrefix = i_fileEnding != String::npos ? filePath.substr(0, i_fileEnding) : filePath;

	if (!overrideBinary && std::filesystem::exists(info.fileNamePrefix + ".sonicwindow"))
	{
		info.isLoadedFromJson = false;
		loadBinary(&info, BinaryInputFileStream(info.fileNamePrefix + ".sonicwindow"));
	}
	else if (String resourceDirFilePath = resourceDir() + info.fileNamePrefix;
		!overrideBinary && std::filesystem::exists(resourceDirFilePath + ".sonicwindow"))
	{
		info.isLoadedFromJson = false;
		info.fileNamePrefix = resourceDirFilePath;
		loadBinary(&info, BinaryInputFileStream(info.fileNamePrefix + ".sonicwindow"));
	}
	else if (std::filesystem::exists(info.fileNamePrefix + ".sonicwindow.json"))
	{
		info.isLoadedFromJson = true;
		loadJson(&info, InputFileStream(info.fileNamePrefix + ".sonicwindow.json"));
	}
	else if (String resourceDirFilePath = resourceDir() + info.fileNamePrefix;
		std::filesystem::exists(resourceDirFilePath + ".sonicwindow.json"))
	{
		info.isLoadedFromJson = true;
		info.fileNamePrefix = resourceDirFilePath;
		loadJson(&info, InputFileStream(info.fileNamePrefix + ".sonicwindow.json"));
	}

	return info;
}

bool Util::saveWindowInfo(WindowInfo& info)
{
	BinaryOutputFileStream file = BinaryOutputFileStream(info.fileNamePrefix + ".sonicwindow");

	uint16_t sizeOfName = (uint16_t)(info.title.size());
	file.write((const char*)&sizeOfName, sizeof(sizeOfName));
	file.write((const char*)info.title.c_str(), sizeOfName);

	uint16_t width = (uint16_t)info.width;
	file.write((const char*)&width, sizeof(width));

	uint16_t height = (uint16_t)info.height;
	file.write((const char*)&height, sizeof(height));

	file.write((const char*)&info.mode, sizeof(WindowMode));

	file.write<uint8_t>((uint8_t)(info.clearColor.a * 255.0f));
	file.write<uint8_t>((uint8_t)(info.clearColor.b * 255.0f));
	file.write<uint8_t>((uint8_t)(info.clearColor.g * 255.0f));
	file.write<uint8_t>((uint8_t)(info.clearColor.r * 255.0f));

	file.write((const char*)&info.saveTitle, sizeof(info.saveTitle));
	file.write((const char*)&info.saveSize, sizeof(info.saveSize));
	file.write((const char*)&info.saveMode, sizeof(info.saveMode));
	file.write((const char*)&info.saveClearColor, sizeof(info.saveClearColor));

	file.write((const char*)&info.resizable, sizeof(info.resizable));
	file.write((const char*)&info.closeButton, sizeof(info.closeButton));

	file.write((const char*)&info.closeOnAltF4, sizeof(info.closeOnAltF4));

	saveCursors(info.cursors, file);
	saveIcons(info.icons, file);

	return file.save();
}

/*
* File format:
* 2 bytes: size of Name
* ? bytes: name
* 2 bytes: initial width
* 2 bytes: initial height
* 1 byte: initial mode
* 4 bytes: initial clear color
* 1 byte: save name
* 1 byte: save size
* 1 byte: save mode
* 1 byte: save clear color
* 1 byte: resizable
* 1 byte: closeButton
* 1 byte: closeOnAltF4
* 2 bytes: amount of cursors
* 2 bytes: cursor width		\
* 2 bytes: cursor height	 \
* 2 bytes: cursor hotpotX	  > ? times
* 2 bytes: cursor hotspotY   /
* ? bytes: cursor bitmap	/
* 2 bytes: amount of icons
* 2 bytes: icon width		\
* 2 bytes: icon height		 > ? times
* ? bytes: icon bitmap		/
*/
