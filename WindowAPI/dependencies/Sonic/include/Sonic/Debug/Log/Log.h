#pragma once
#include <assert.h>
#include <iostream>

namespace Sonic {

    class Log
    {
    public:
        template<typename Arg, typename... Args>
        static void debugAssert(bool b, Arg&& arg, Args&&... args)
        {
            if (!b)
            {
                Log::debug(std::forward<Arg>(arg), std::forward<Args>(args)...);
                assert(false);
            }
        }

        template<typename Arg, typename... Args>
        static void debug(Arg&& arg, Args&&... args)
        {
            std::cout << "[DEBUG] ";
            std::cout << std::forward<Arg>(arg);
            ((std::cout << std::forward<Args>(args)), ...);
            std::cout << std::endl;
        }
    };

}

#ifdef SONIC_DEBUG
#define SONIC_LOG_DEBUG(...) Sonic::Log::debug(__VA_ARGS__)
#define SONIC_LOG_DEBUG_ASSERT(b, ...) Sonic::Log::debugAssert(b, __VA_ARGS__)
#define SONIC_LOG_ERROR(...) SONIC_LOG_DEBUG(__VA_ARGS__)
#define SONIC_LOG_WARN(...) SONIC_LOG_DEBUG(__VA_ARGS__)    
#else
#define SONIC_LOG_DEBUG(...) 
#define SONIC_LOG_DEBUG_ASSERT(b, ...)
#define SONIC_LOG_ERROR(...)
#define SONIC_LOG_WARN(...)   
#endif
