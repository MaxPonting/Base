#pragma once

#define PLATFORM_TYPE_WINDOWS 0
#define PLATFORM_TYPE_MAC_OS 1
#define PLATFORM_TYPE_LINUX 2
#define PLATFORM_TYPE_ANDROID 3
#define PLATFORM_TYPE_IPHONE 4
#define PLATFORM_TYPE_UNSUPPORTED 5

#if defined(_WIN32)
    #define PLATFORM PLATFORM_TYPE_WINDOWS
#elif defined(__APPLE__)
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #define PLATFORM PLATFORM_TYPE_MAC_OS
    #elif TARGET_OS_IPHONE
        #define PLATFORM PLATFORM_TYPE_IPHONE
    #else   
        #define PLATFORM PLATFORM_TYPE_UNSUPPORTED
    #endif
#elif defined(__linux__)
    #define PLATFORM PLATFORM_TYPE_LINUX
#elif defined(__ANDROID__)
    #define PLATFORM PLATFORM_TYPE_ANDROID
#endif
