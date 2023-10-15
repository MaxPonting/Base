#pragma once

#define PLATFORM_WINDOWS 0
#define PLATFORM_MAC 1
#define PLATFORM_LINUX 2
#define PLATFORM_ANDROID 3
#define PLATFORM_IPHONE 4
#define PLATFORM_UNSUPPORTED 5

#if defined(_WIN32)
    #define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #define PLATFORM PLATFORM_MAC
    #elif TARGET_OS_IPHONE
        #define PLATFORM PLATFORM_IPHONE
    #else   
        #define PLATFORM PLATFORM_UNSUPPORTED
    #endif
#elif defined(__linux__)
    #define PLATFORM PLATFORM_LINUX
#elif defined(__ANDROID__)
    #define PLATFORM PLATFORM_ANDROID
#else 
    #define PLATFORM PLATFORM_UNSUPPORTED
#endif
