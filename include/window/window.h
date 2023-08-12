#pragma once

#include "../type/type.h"

typedef enum 
{   
    WINDOW_VERSION_MAJOR_1 = 1,
    WINDOW_VERSION_MAJOR_2 = 2,
    WINDOW_VERSION_MAJOR_3 = 3,
    WINDOW_VERSION_MAJOR_4 = 4
} WindowVersionMajor;

typedef enum
{
    WINDOW_VERSION_MINOR_1 = 1,
    WINDOW_VERSION_MINOR_2 = 2,
    WINDOW_VERSION_MINOR_3 = 3,
    WINDOW_VERSION_MINOR_4 = 4,
    WINDOW_VERSION_MINOR_5 = 5,
    WINDOW_VERSION_MINOR_6 = 6
} WindowVersionMinor;

int32 window_create(const uint32 width, const uint32 height, const char* const name, const WindowVersionMajor version_major, const WindowVersionMinor version_minor);
int32 window_destroy();

int32 window_swap_buffer();
int32 window_poll_events();

int32 window_should_close();
int32 window_is_active();

int32 window_get_size(int32* const width, int32* const height);