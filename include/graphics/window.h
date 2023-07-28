#pragma once

#include "platform/platform.h"
#include "allocator/allocator.h"
#include "string/string.h"

typedef enum WindowType { WINDOW_TYPE_NULL, WINDOW_TYPE_GLFW } WindowType;

typedef struct window
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