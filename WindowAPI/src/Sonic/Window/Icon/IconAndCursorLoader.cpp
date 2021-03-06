#include <stb/stb_image.h>
#include <filesystem>
#include "Sonic/Log/Log.h"
#include "Sonic/Window/Window.h"
#include "Sonic/Util/StringUtils.h"
#include "IconAndCursorLoader.h"

using namespace Sonic;


static const size_t CUR_HEADER_SIZE = 22;


static std::vector<String> allStandardCursors = {
	{
		Cursors::Arrow,
		Cursors::Arrow,
		Cursors::Alternate,
		Cursors::IBeam,
		Cursors::Move,
		Cursors::Crosshair,
		Cursors::ResizeHorizontal,
		Cursors::ResizeVertical,
		Cursors::ResizeDiagonalLeft,
		Cursors::ResizeDiagonalRight,
		Cursors::Unavailable,
		Cursors::Pen,
		Cursors::Link,
		Cursors::Help
	}
};

static CursorInfo loadCursorFromCur(BinaryInputFileStream&& file);
static IconInfo loadIconFromIco(BinaryInputFileStream&& file);
static IconInfo loadIconFromPng(const String& file);


std::unordered_map<String, CursorInfo> Util::loadCursors(BinaryInputFileStream& file)
{
	std::unordered_map<String, CursorInfo> cursors;

	for (int i = 0, cursorAmount = file.read<uint16_t>(); i < cursorAmount; i++)
	{
		CursorInfo cursor;

		uint16_t nameSize = file.read<uint16_t>();
		const char* name = file.read<char>(nameSize);

		cursor.width = file.read<uint16_t>();
		cursor.height = file.read<uint16_t>();
		cursor.hotspotX = file.read<uint16_t>();
		cursor.hotspotY = file.read<uint16_t>();

		cursor.bitmap = file.read<uint8_t>(4 * cursor.width * cursor.height);
		
		cursors.emplace(String(name, nameSize), cursor);
		delete[] name;
	}

	return cursors;
}

std::unordered_map<String, CursorInfo> Util::loadCursors(const String& standardCursorSet, const std::unordered_map<String, String> filePaths)
{
	std::unordered_map<String, CursorInfo> cursors;

	for (auto& [name, filePath] : filePaths)
	{
		if (Util::endsWith(filePath, ".cur"))
		{
			if (std::filesystem::exists(filePath))
			{
				cursors.emplace(name, loadCursorFromCur(filePath));
			}
			else if (String resourceDirFilePath = resourceDir() + filePath;
				std::filesystem::exists(resourceDirFilePath))
			{
				cursors.emplace(name, loadCursorFromCur(resourceDirFilePath));
			}
		}
	}

	String standardCursorsDir = standardCursorSetDirs.find(standardCursorSet) != standardCursorSetDirs.end() ?
		standardCursorSetDirs.at(standardCursorSet) : standardCursorSetDirs.at(defaultStandardCursorSet);

	for (auto& standardCursor : allStandardCursors)
	{
		if (cursors.find(standardCursor) == cursors.end())
		{
			String filePath = standardCursorsDir + standardCursor + ".cur";
			cursors.emplace(standardCursor, loadCursorFromCur(filePath));
		}
	}

	return cursors;
}

std::vector<IconInfo> Util::loadIcons(BinaryInputFileStream& file)
{
	std::vector<IconInfo> icons;

	for (int i = 0, iconAmount = file.read<uint16_t>(); i < iconAmount; i++)
	{
		IconInfo icon;

		icon.width = file.read<uint16_t>();
		icon.height = file.read<uint16_t>();
		icon.bitmap = file.read<uint8_t>(4 * icon.width * icon.height);

		icons.push_back(icon);
	}

	return icons;
}

std::vector<IconInfo> Util::loadIcons(const std::vector<String>& filePaths)
{
	std::vector<IconInfo> icons;

	for (auto& filePath : filePaths)
	{
		if (Util::endsWith(filePath, ".ico"))
		{
			if (std::filesystem::exists(filePath))
			{
				icons.push_back(loadIconFromIco(filePath));
			}
			else if (String resourceDirFilePath = resourceDir() + filePath;
				std::filesystem::exists(resourceDirFilePath))
			{
				icons.push_back(loadIconFromIco(filePath));
			}
		}
		else if (Util::endsWith(filePath, ".png"))
		{
			if (std::filesystem::exists(filePath))
			{
				icons.push_back(loadIconFromPng(filePath));
			}
			else if (String resourceDirFilePath = resourceDir() + filePath;
				std::filesystem::exists(resourceDirFilePath))
			{
				icons.push_back(loadIconFromPng(resourceDirFilePath));
			}
		}
	}

	return icons;
}

void Util::saveCursors(std::unordered_map<String, CursorInfo>& cursors, BinaryOutputFileStream& file)
{
	file.write<uint16_t>((uint16_t)cursors.size());

	for (auto& [cursorName, cursor] : cursors)
	{
		file.write<uint16_t>((uint16_t)cursorName.size());
		file.write(cursorName.c_str(), cursorName.size());

		file.write<uint16_t>(cursor.width);
		file.write<uint16_t>(cursor.height);
		file.write<uint16_t>(cursor.hotspotX);
		file.write<uint16_t>(cursor.hotspotY);

		file.write(cursor.bitmap, 4 * cursor.width * cursor.height);

		delete[] cursor.bitmap;
	}

	cursors.clear();
}

void Util::saveIcons(std::vector<IconInfo>& icons, BinaryOutputFileStream& file)
{
	file.write<uint16_t>((uint16_t)icons.size());

	for (auto& icon : icons)
	{
		file.write<uint16_t>(icon.width);
		file.write<uint16_t>(icon.height);
		file.write(icon.bitmap, 4 * icon.width * icon.height);

		delete[] icon.bitmap;
	}

	icons.clear();
}

static CursorInfo loadCursorFromCur(BinaryInputFileStream&& file)
{
	CursorInfo cursor;

	file.moveCursor(4);

	uint16_t cursorAmount = file.read<uint16_t>();
	if (cursorAmount != 1)
	{
		SONIC_LOG_WARN("Cursor file contains multiple images. Loading the first one");
	}

	cursor.width = file.read<uint8_t>();
	cursor.height = file.read<uint8_t>();

	file.moveCursor(2);

	cursor.hotspotX = file.read<uint16_t>();
	cursor.hotspotY = file.read<uint16_t>();

	file.moveCursor(4);

	size_t bitmapOffset = (size_t)file.read<uint32_t>();
	file.moveCursor(bitmapOffset - CUR_HEADER_SIZE + (size_t)14);

	uint16_t bitsPerPixel = file.read<uint16_t>();
	SONIC_LOG_DEBUG_ASSERT(bitsPerPixel == 32, "Error loading cursor bitmap: Bitmap does not use 32 bits per pixel");

	file.moveCursor(4);

	uint32_t bitmapSize = file.read<uint32_t>();

	file.moveCursor(16);

	cursor.bitmap = file.read<uint8_t>(bitmapSize);

	uint8_t* flippedBitmap = new uint8_t[4 * (size_t)cursor.width * (size_t)cursor.height];
	for (int y = 0; y < cursor.height; y++)
	{
		for (int x = 0; x < cursor.width; x++)
		{
			uint32_t* pixel = reinterpret_cast<uint32_t*>(cursor.bitmap + 4 * (x + y * (size_t)cursor.width));
			uint32_t* flippedPixel = reinterpret_cast<uint32_t*>(flippedBitmap + 4 * (x + ((size_t)cursor.height - 1 - y) * (size_t)cursor.width));

			*flippedPixel = *pixel;
		}
	}

	delete[] cursor.bitmap;
	cursor.bitmap = flippedBitmap;

	return cursor;
}

static IconInfo loadIconFromIco(BinaryInputFileStream&& file)
{
	return { 0, 0, nullptr };
}

static IconInfo loadIconFromPng(const String& file)
{
	stbi_set_flip_vertically_on_load(true);

	IconInfo icon;
	icon.bitmap = stbi_load(file.c_str(), &icon.width, &icon.height, NULL, 4);
	return icon;
}
