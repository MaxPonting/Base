#pragma once

#include "../platform/platform.h"
#include "../type/type.h"

#if PLATFORM == PLATFORM_WINDOWS || PLATFORM == PLATFORM_LINUX
#include <sys/time.h>
#elif PLATFORM == PLATFORM_MAC
#endif

namespace Base::Time
{

struct Timer
{
    Float64 start;
};

#if PLATFORM == PLATFORM_WINDOWS || PLATFORM == PLATFORM_LINUX
 
    // Returns time of day in seconds 
    Float64 Get()
    {
        struct timeval time;
        gettimeofday(&time, 0);

        return (Float64)time.tv_usec / 1000000 + (Float64)time.tv_sec;
    }

    Timer StartTimer()
    {
        Timer timer;
        timer.start = Get();
        return timer;
    }

    Float64 EndTimer(const Timer timer)
    {
        return Get() - timer.start;
    }

#elif PLATFORM == PLATFORM_MAC

    UInt32 Get()
    {
        Log::Print("Not implmented for MACOS", Log::Type::Warning, __LINE__, __FILE__);

        return 0;
    }

#endif
}

