#include <zstd/zstd.h>
#include "BinaryFileUtils.h"

using namespace Sonic;

void Util::BinaryInputFileStream::readRaw(uint8_t* data, size_t size)
{
	InputFileStream::read((char*)data, size);
}

void Util::BinaryInputFileStream::readRawCompressed(uint8_t* dst, size_t originalSize)
{
	size_t compressedSize = (size_t)read<uint32_t>();
	uint8_t* compressedData = read<uint8_t>(compressedSize);

	ZSTD_decompress(dst, originalSize, compressedData, compressedSize);

	delete[] compressedData;
}

void Util::BinaryOutputFileStream::writeRaw(uint8_t* data, size_t size)
{
	OutputFileStream::write((const char*)data, size);
}

void Util::BinaryOutputFileStream::writeRawCompressed(uint8_t* data, size_t dataSize)
{
	size_t compressedSize = ZSTD_compressBound(dataSize);
	uint8_t* compressedData = new uint8_t[compressedSize];

	compressedSize = ZSTD_compress(compressedData, compressedSize, data, dataSize, 1);

	write<uint32_t>((uint32_t)compressedSize);
	write<uint8_t>(compressedData, compressedSize);

	delete[] compressedData;
}
