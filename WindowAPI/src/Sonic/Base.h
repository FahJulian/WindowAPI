#pragma once
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <memory>
#include <string>
#include <fstream>

namespace Sonic {

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

    inline InputFileStream createBinaryInputFileStream(const String& fileStream)
    {
        return InputFileStream(fileStream, std::ios::binary | std::ios::in);
    }

    extern const String& resourceDir();

    static const String& coreResourceDir()
    {
        static String coreResourceDir = "C:\\dev\\Sonic\\Sonic\\res\\";
        return coreResourceDir;
    }

}
