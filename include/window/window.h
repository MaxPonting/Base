#pragma once

#include "../type/type.h"

typedef enum WindowVersionMajor WindowVersionMajor;
typedef enum WindowVersionMinor WindowVersionMinor;
typedef enum WindowKey WindowKey;
typedef enum WindowKeyState WindowKeyState;

int32 window_create(const uint32 width, const uint32 height, const char* const name, const WindowVersionMajor version_major, const WindowVersionMinor version_minor);
int32 window_destroy();

int32 window_set_size(const int32 width, const int32 height);

int32 window_swap_buffer();
int32 window_poll_events();

int32 window_should_close();
int32 window_is_active();

int32 window_get_ptr(void** const ptr);
int32 window_get_size(int32* const width, int32* const height);
WindowKeyState window_get_key(const WindowKey key);
uint64 window_get_timer_value();
uint64 window_get_timer_frequency();

enum WindowVersionMajor
{   
    WINDOW_VERSION_MAJOR_1 = 1,
    WINDOW_VERSION_MAJOR_2 = 2,
    WINDOW_VERSION_MAJOR_3 = 3,
    WINDOW_VERSION_MAJOR_4 = 4
};

enum WindowVersionMinor
{
    WINDOW_VERSION_MINOR_1 = 1,
    WINDOW_VERSION_MINOR_2 = 2,
    WINDOW_VERSION_MINOR_3 = 3,
    WINDOW_VERSION_MINOR_4 = 4,
    WINDOW_VERSION_MINOR_5 = 5,
    WINDOW_VERSION_MINOR_6 = 6
};

enum WindowKey
{
    WINDOW_KEY_SPACE = 32,
    WINDOW_KEY_0 = 48,
    WINDOW_KEY_1 = 49,
    WINDOW_KEY_2 = 50,
    WINDOW_KEY_3 = 51,
    WINDOW_KEY_4 = 52,
    WINDOW_KEY_5 = 53,
    WINDOW_KEY_6 = 54,
    WINDOW_KEY_7 = 55,
    WINDOW_KEY_8 = 56,
    WINDOW_KEY_9 = 57,
    WINDOW_KEY_A = 65,
    WINDOW_KEY_B = 66,
    WINDOW_KEY_C = 67,
    WINDOW_KEY_D = 68,
    WINDOW_KEY_E = 69,
    WINDOW_KEY_F = 70,
    WINDOW_KEY_G = 71,
    WINDOW_KEY_H = 72,
    WINDOW_KEY_I = 73,
    WINDOW_KEY_J = 74,
    WINDOW_KEY_K = 75,
    WINDOW_KEY_L = 76,
    WINDOW_KEY_M = 77,
    WINDOW_KEY_N = 78,
    WINDOW_KEY_O = 79,
    WINDOW_KEY_P = 80,
    WINDOW_KEY_Q = 81,
    WINDOW_KEY_R = 82,
    WINDOW_KEY_S = 83,
    WINDOW_KEY_T = 84,
    WINDOW_KEY_U = 85,
    WINDOW_KEY_V = 86,
    WINDOW_KEY_W = 87,
    WINDOW_KEY_X = 88,
    WINDOW_KEY_Y = 89,
    WINDOW_KEY_Z = 90,
    WINDOW_KEY_ESCAPE = 256,
    WINDOW_KEY_ENTER = 257,
    WINDOW_KEY_TAB = 258,
    WINDOW_KEY_BACKSPACE = 259,
    WINDOW_KEY_INSERT = 260,
    WINDOW_KEY_DELETE = 261,
    WINDOW_KEY_RIGHT = 262,
    WINDOW_KEY_LEFT = 263,
    WINDOW_KEY_DOWN = 264,
    WINDOW_KEY_UP = 265,
    WINDOW_KEY_LEFT_SHIFT = 340,
    WINDOW_KEY_LEFT_CONTROL = 341,
    WINDOW_KEY_LEFT_ALT = 342,
    WINDOW_KEY_RIGHT_SHIFT = 344,
    WINDOW_KEY_RIGHT_CONTROL = 345,
    WINDOW_KEY_RIGHT_ALT = 346
};

enum WindowKeyState
{
    WINDOW_KEY_STATE_NULL = 0,
    WINDOW_KEY_STATE_PRESS = 1,
    WINDOW_KEY_STATE_RELEASE = 2
};