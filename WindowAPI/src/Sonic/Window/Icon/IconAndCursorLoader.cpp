#include "Sonic/Log/Log.h"
#include "Sonic/Window/Window.h"
#include "Sonic/Util/StringUtils.h"
#include "IconAndCursorLoader.h"

using namespace Sonic;


static const uint32_t CUR_HEADER_SIZE = 22;


static std::vector<String> allStandardCursors = {
	{
		StandardCursors::Arrow,
		StandardCursors::Arrow,
		StandardCursors::Alternate,
		StandardCursors::IBeam,
		StandardCursors::Move,
		StandardCursors::Crosshair,
		StandardCursors::ResizeHorizontal,
		StandardCursors::ResizeVertical,
		StandardCursors::ResizeDiagonalLeft,
		StandardCursors::ResizeDiagonalRight,
		StandardCursors::Unavailable,
		StandardCursors::Pen,
		StandardCursors::Link,
		StandardCursors::Help
	}
};

static CursorInfo loadCursorFromCur(InputFileStream&& file);
static CursorInfo loadCursorFromPng(InputFileStream&& file);
static IconInfo loadIconFromIco(InputFileStream&& file);
static IconInfo loadIconFromPng(InputFileStream&& file);


std::unordered_map<String, CursorInfo> Util::loadCursors(InputFileStream& binaryFile)
{

}

std::unordered_map<String, CursorInfo> Util::loadCursors(const String& standardCursorSet, const std::unordered_map<String, String> filePaths)
{
	std::unordered_map<String, CursorInfo> cursors;

	for (auto& [name, filePath] : filePaths)
	{
		if (Util::endsWith(filePath, ".cur"))
			cursors.emplace(filePath, loadCursorFromCur(createBinaryInputFileStream(filePath)));
		else if (Util::endsWith(filePath, ".png"))
			cursors.emplace(filePath, loadCursorFromPng(InputFileStream(filePath)));
	}

	for (auto& standardCursor : allStandardCursors)
	{
		if (cursors.find(standardCursor) == cursors.end())
		{
			String filePath = standardCursorSetFolderPaths.at(standardCursorSet) + standardCursor + ".cur";
			cursors.emplace(standardCursor, loadCursorFromCur(InputFileStream(filePath)));
		}
	}

	return cursors;
}

std::vector<IconInfo> Util::loadIcons(InputFileStream& binaryFile)
{

}

std::vector<IconInfo> Util::loadIcons(const std::vector<String>& filePaths)
{
	std::vector<IconInfo> icons;

	for (auto& filePath : filePaths)
	{
		if (Util::endsWith(filePath, ".ico"))
			icons.push_back(loadIconFromIco(createBinaryInputFileStream(filePath)));
		else if (Util::endsWith(filePath, ".png"))
			icons.push_back(loadIconFromPng(InputFileStream(filePath)));
	}

	return icons;
}

void Util::saveCursors(std::unordered_map<String, CursorInfo> cursors, OutputFileStream& file)
{

}

void Util::saveIcons(std::vector<IconInfo> icons, OutputFileStream& file)
{

}

static CursorInfo loadCursorFromCur(InputFileStream&& file)
{
	CursorInfo cursor;

	file.seekg(4, std::ios::cur);

	uint16_t cursorAmount;
	file.read((char*)&cursorAmount, sizeof(cursorAmount));
	if (cursorAmount != 1)
		SONIC_LOG_WARN("Cursor file contains multiple images. Loading the first one");

	file.read((char*)cursor.width, sizeof(cursor.width));
	file.read((char*)&cursor.height, sizeof(cursor.height));

	file.seekg(2, std::ios::cur);

	file.read((char*)&cursor.hotspotX, sizeof(cursor.hotspotX));
	file.read((char*)&cursor.hotspotY, sizeof(cursor.hotspotY));

	file.seekg(4, std::ios::cur);

	uint32_t bmpOffset;
	file.read((char*)&bmpOffset, sizeof(bmpOffset));

	file.seekg(bmpOffset - CUR_HEADER_SIZE + 14, std::ios::cur);

	uint16_t bitsPerPixel;
	file.read((char*)&bitsPerPixel, sizeof(bitsPerPixel));
	SONIC_LOG_DEBUG_ASSERT(bitsPerPixel == 32, "Error loading cursor bitmap: Bitmap does not use 32 bits per pixel");

	file.seekg(4, std::ios::cur);

	uint32_t bitmapSize;
	file.read((char*)&bitmapSize, sizeof(bitmapSize));

	file.seekg(16, std::ios::cur);

	cursor.bitmap = new uint8_t[bitmapSize];
	file.read((char*)cursor.bitmap, bitmapSize);

	uint8_t* flippedBitmap = new unsigned char[4 * (size_t)cursor.width * (size_t)cursor.height];

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

static CursorInfo loadCursorFromPng(InputFileStream&& file)
{

}

static IconInfo loadIconFromIco(InputFileStream&& file)
{
}

static IconInfo loadIconFromPng(InputFileStream&& file)
{
}

