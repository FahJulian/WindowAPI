#pragma once
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <memory>
#include <string>
#include <fstream>

namespace Sonic {

    enum class OperatingSystem
    {
        Windows
    };

    const OperatingSystem OPERATING_SYSTEM = OperatingSystem::Windows;

    using String = std::string;
    using WideString = std::wstring;

    using InputFileStream = std::ifstream;
    using OutputFileStream = std::ofstream;

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    inline Ref<T> createRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    extern const String& resourceDir();

    static const String& coreResourceDir()
    {
        static String coreResourceDir = "C:/dev/Sonic/Sonic/res/";
        return coreResourceDir;
    }

    class BinaryInputFileStream : private InputFileStream
    {
    public:
        BinaryInputFileStream(const String& filePath)
            : InputFileStream(filePath, std::ios::binary | std::ios::in)
        {
        }

        void moveCursor(off_type offset) { seekg(offset, std::ios::cur); }

        template<typename T>
        T read()
        {
            T t;
            InputFileStream::read((char*)&t, sizeof(T));
            return t;
        }

        template<typename T>
        T* read(int elementCount)
        {
            T* t = new T[elementCount];
            InputFileStream::read((char*) t, elementCount * sizeof(T));
            return t;
        }
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
            OutputFileStream::write((const char*)&t, sizeof(T));
        }

        template<typename T>
        void write(const T* t, size_t elementCount)
        {
            OutputFileStream::write((const char*)t, elementCount);
        }

        bool save()
        {
            close();
            return good();
        }
    };

}
