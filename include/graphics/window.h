#pragma once

#include "../platform/platform.h"
#include "../allocator/allocator.h"
#include "../string/string.h"

typedef enum WindowType { WINDOW_TYPE_NULL, WINDOW_TYPE_GLFW } WindowType;

typedef struct Window
{
    void* ptr;
    int w, h;
    String name;
    WindowType type;
}  Window;

int window_create(Window* const window, Allocator* const allocator, char* const name, const int w, const int h);
int window_destroy();
int window_swap_buffers();
int window_poll_events(Window* const window);
int window_should_close(Window* const window);
int window_get_key(Window* const window, const int key);

#define WINDOW_KEY_RELEASE 1
#define WINDOW_KEY_PRESS 2

#define WINDOW_KEY_SPACE 32
#define WINDOW_KEY_0 48
#define WINDOW_KEY_1 49
#define WINDOW_KEY_2 50
#define WINDOW_KEY_3 51
#define WINDOW_KEY_4 52
#define WINDOW_KEY_5 53
#define WINDOW_KEY_6 54
#define WINDOW_KEY_7 55
#define WINDOW_KEY_8 56
#define WINDOW_KEY_9 57
#define WINDOW_KEY_A 65
#define WINDOW_KEY_B 66
#define WINDOW_KEY_C 67
#define WINDOW_KEY_D 68
#define WINDOW_KEY_E 69
#define WINDOW_KEY_F 70
#define WINDOW_KEY_G 71
#define WINDOW_KEY_H 72
#define WINDOW_KEY_I 73
#define WINDOW_KEY_J 74
#define WINDOW_KEY_K 75
#define WINDOW_KEY_L 76
#define WINDOW_KEY_M 77
#define WINDOW_KEY_N 78
#define WINDOW_KEY_O 79
#define WINDOW_KEY_P 80
#define WINDOW_KEY_Q 81
#define WINDOW_KEY_R 82
#define WINDOW_KEY_S 83
#define WINDOW_KEY_T 84
#define WINDOW_KEY_U 85
#define WINDOW_KEY_V 86
#define WINDOW_KEY_W 87
#define WINDOW_KEY_X 88
#define WINDOW_KEY_Y 89
#define WINDOW_KEY_Z 90
#define WINDOW_KEY_ESCAPE 256
#define WINDOW_KEY_ENTER 257
#define WINDOW_KEY_TAB 258
#define WINDOW_KEY_BACKSPACE 259
#define WINDOW_KEY_DELETE 261
#define WINDOW_KEY_RIGHT 262
#define WINDOW_KEY_LEFT 263
#define WINDOW_KEY_DOWN 264
#define WINDOW_KEY_UP 265