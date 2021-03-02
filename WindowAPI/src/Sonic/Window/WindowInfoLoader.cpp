#pragma once
#include <algorithm>
#include <filesystem>
#include <json/json.hpp>
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

	if (json.contains("initialName"))
		info->initialName = json["initialName"].get<String>();

	if (json.contains("initialSize"))
	{
		JSON size = json["initialSize"];
		if (size.is_array())
		{
			info->initialWidth = size[0].get<int>();
			info->initialHeight = size[1].get<int>();
		}
		else if (size.is_object())
		{
			info->initialWidth = size["width"].get<int>();
			info->initialHeight = size["height"].get<int>();
		}
		else if (size.is_string())
		{
			String sizeString = size.get<String>();
			size_t seperatorIndex = sizeString.find('x');

			info->initialWidth = std::stoi(sizeString, 0);
			info->initialHeight = std::stoi(sizeString.substr(seperatorIndex + 1), 0);
		}
	}

	if (json.contains("initialName"))
		info->initialName = json["initialName"].get<String>();
	if (json.contains("initialMode"))
		info->initialMode = toWindowMode(json["initialMode"].get<String>());
	if (json.contains("saveName"))
		info->saveName = json["saveName"].get<bool>();
	if (json.contains("saveSize"))
		info->saveSize = json["saveSize"].get<bool>();
	if (json.contains("saveMode"))
		info->saveMode = json["saveMode"].get<bool>();
	if (json.contains("resizable"))
		info->resizable = json["resizable"].get<bool>();
}

static void loadBinary(WindowInfo* info, InputFileStream file)
{
	uint16_t sizeOfName;
	file.read((char*)&sizeOfName, sizeof(sizeOfName));
	
	char* name = new char[sizeOfName + 1] { 0 };
	file.read(name, sizeOfName);
	info->initialName = String(name);
	delete name;

	file.read((char*)&info->initialWidth, 2);
	file.read((char*)&info->initialHeight, 2);

	file.read((char*)&info->initialMode, 1);

	file.read((char*)&info->saveName, 1);
	file.read((char*)&info->saveSize, 1);
	file.read((char*)&info->saveMode, 1);
	file.read((char*)&info->resizable, 1);
}


WindowInfo Util::loadWindowInfo(String filePath, bool overrideBinary)
{
	WindowInfo info;

	std::replace(filePath.begin(), filePath.end(), '/', '\\');

	size_t i_fileEnding = filePath.find('.');
	info.fileNamePrefix = i_fileEnding != String::npos ? filePath.substr(0, i_fileEnding) : filePath;

	if (!std::filesystem::exists(info.fileNamePrefix + ".sonicwindow") || overrideBinary)
	{
		loadJson(&info, InputFileStream(info.fileNamePrefix + ".sonicwindow.json", std::ios::in | std::ios::binary));
	}
	else
	{
		loadBinary(&info, InputFileStream(info.fileNamePrefix + ".sonicwindow"));
	}

	return info;
}

bool Util::saveWindowInfo(const WindowInfo& info)
{
	OutputFileStream file = OutputFileStream(info.fileNamePrefix + ".sonicwindow", std::ios::out | std::ios::binary);

	uint16_t sizeOfName = (uint16_t)(info.saveName ? info.currentName.size() : info.initialName.size());
	file.write((const char*)&sizeOfName, sizeof(sizeOfName));
	file.write((const char*)(info.saveName ? info.currentName : info.initialName).c_str(), sizeOfName);

	uint16_t width = (uint16_t)(info.saveSize ? info.currentWidth : info.initialWidth);
	file.write((const char*)&width, sizeof(width));

	uint16_t height = (uint16_t)(info.saveSize ? info.currentHeight : info.initialHeight);
	file.write((const char*)&height, sizeof(height));

	file.write((const char*)(info.saveMode ? &info.currentMode : &info.initialMode), sizeof(WindowMode));

	file.write((const char*)&info.saveName, sizeof(info.saveName));
	file.write((const char*)&info.saveSize, sizeof(info.saveSize));
	file.write((const char*)&info.saveMode, sizeof(info.saveMode));

	file.write((const char*)&info.resizable, sizeof(info.resizable));

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
*/
