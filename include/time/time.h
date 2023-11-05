#pragma once

#include "../platform/platform.h"
#include "../type/type.h"


namespace Base::Time
{

#if PLATFORM == PLATFORM_WINDOWS || PLATFORM == PLATFORM_LINUX
#include <sys/time.h>

    // Returns time (ms) since January 1st 1970 
    Int32 Get()
    {
        struct timeval time;
        gettimeofday(&time, 0);

        return time.tv_usec / 1000;
    }

#elif PLATFORM == PLATFORM_MAC

    UInt32 Get()
    {
        Log::Print("Not implmented for MACOS", Log::Type::Warning, __LINE__, __FILE__);

        return 0;
    }

#endif
}

