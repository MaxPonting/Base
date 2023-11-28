#pragma once

#include "../platform/platform.h"
#include "../type/type.h"

#if PLATFORM == PLATFORM_WINDOWS
#include <windows.h>
#elif PLATFORM == PLATFORM_LINUX
#include <time.h>
#endif

namespace Base::PerformanceCounter
{
    struct Timer
    {
        Int64 startValue1;
        Int64 startValue2;
    };

#if PLATFORM == PLATFORM_WINDOWS

    // Returns high resolution counter in seconds
    Float64 Get()
    {
        LARGE_INTEGER count, frequency;
        QueryPerformanceCounter(&count);
        QueryPerformanceFrequency(&frequency);

        return (Float64)count.QuadPart / frequency.QuadPart;
    }

    Timer StartTimer()
    {
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);

        Timer timer;
        timer.startValue1 = count.QuadPart;

        return timer;
    }

    // Returns the difference between the start and end times in seconds
    Float64 EndTimer(const Timer timer)
    {
        LARGE_INTEGER count, frequency;
        QueryPerformanceCounter(&count);
        QueryPerformanceFrequency(&frequency);

        return (Float64)(count.QuadPart - timer.startValue1) / frequency.QuadPart;
    }

#elif PLATFORM == PLATFORM_LINUX

    // Returns high resolution counter in seconds
    Float64 Get()
    {
        struct timespec time;
        clock_gettime(CLOCK_MONOTONIC, &time);
        return (Float64)time.tv_nsec / 1000000000 + (Float64)time.tv_sec;
    }

    Timer StartTimer()
    {
        timespec time;
        clock_gettime(CLOCK_MONOTONIC, &time);

        Timer timer;
        timer.startValue1 = time.tv_sec;
        timer.startValue2 = time.tv_nsec;

        return timer;
    }

    // Returns the difference between the start and end times in seconds
    Float64 EndTimer(const Timer timer)
    {
        timespec end;
        clock_gettime(CLOCK_MONOTONIC, &end);

        timespec difference;
        if(end.tv_nsec - timer.startValue2 < 0)
        {
            difference.tv_sec = end.tv_sec - timer.startValue1 - 1;
            difference.tv_nsec = 1000000000 + end.tv_nsec - timer.startValue2;
        }
        else
        {
            difference.tv_sec = end.tv_sec - timer.startValue1;
            difference.tv_nsec = end.tv_nsec - timer.startValue2;
        }

        return (Float64)difference.tv_nsec / 1000000000 + (Float64)difference.tv_sec;
    }

#endif

}