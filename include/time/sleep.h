
#pragma once

#include "../platform/platform.h"
#include "../type/type.h"

#if PLATFORM == PLATFORM_WINDOWS
#include <windows.h>
#elif PLATFORM == PLATFORM_LINUX
#include <time.h> 
#endif

#include <stdio.h>

namespace Base::Time
{
#if PLATFORM == PLATFORM_WINDOWS

    void ThreadSleep(const Int32 microseconds)
    {
        const Int32 milliseconds = (Float64)microseconds / 1000;

        if(milliseconds <= 0)
            return;

        timeBeginPeriod(1);
        Sleep(milliseconds);
        timeEndPeriod(1);
    }

#elif PLATFORM == PLATFORM_LINUX

    void ThreadSleep(const Int32 microseconds)
    {
        if(microseconds <= 0)
            return;
        
        struct timespec time;
        time.tv_sec = microseconds / 1000000;
        time.tv_nsec = (microseconds % 1000000) * 1000;

        nanosleep(&time, NULL);
    }

#endif
}