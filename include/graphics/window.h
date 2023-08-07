#pragma once

#include "../platform/platform.h"
#include "../type/type.h"

int32 window_create(const uint32 width, const uint32 height, const char* const name);
int32 window_destroy();

int32 window_should_close();
int32 window_swap_buffer();
int32 window_poll_events();
int32 window_get_size(int32* const width, int32* const height);