#pragma once
#include "Sonic/Base.h"


namespace Sonic::Util {

    class BinaryInputFileStream : private InputFileStream
    {
    public:
        BinaryInputFileStream(const String& filePath)
            : InputFileStream(filePath, std::ios::binary | std::ios::in)
        {
        }

        void moveCursor(off_type offset) { seekg(offset, std::ios::cur); }

        template<typename T>
        T&& read()
        {
            T t;
            readRaw((uint8_t*)&t, sizeof(T));

            return std::forward<T>(t);
        }

        template<typename T>
        T* read(size_t elementCount)
        {
            T* t = new T[elementCount];
            readRaw((uint8_t*)t, elementCount * sizeof(T));

            return t;
        }

        template<typename T>
        T* readCompressed(int elementCount)
        {
            T* decompressedData = new T[elementCount];
            readRawCompressed((uint8_t*)decompressedData, elementCount * sizeof(T));

            return decompressedData;
        }

    private:
        void readRaw(uint8_t* data, size_t size);
        void readRawCompressed(uint8_t* dst, size_t originalSize);
    };

    class BinaryOutputFileStream : private OutputFileStream
    {
    public:
        BinaryOutputFileStream(const String& filePath)
            : OutputFileStream(filePath, std::ios::binary | std::ios::out)
        {
        }

        template<typename T>
        void write(const T& t)
        {
            writeRaw((uint8_t*)&t, sizeof(T));
        }

        template<typename T>
        void write(const T* t, size_t elementCount)
        {
            writeRaw((uint8_t*)t, elementCount * sizeof(T));
        }

        template<typename T>
        void writeCompressed(const T* t, size_t elementCount)
        {
            writeRawCompressed((uint8_t*)t, elementCount * sizeof(T));
        }

        bool save()
        {
            close();
            return good();
        }

    private:
        void writeRaw(uint8_t* data, size_t size);
        void writeRawCompressed(uint8_t* dst, size_t originalSize);
    };

}