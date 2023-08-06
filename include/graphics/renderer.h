#pragma once

#include "../type/type.h"

int32 renderer_create();
int32 renderer_destroy();

int32 renderer_start();
int32 renderer_draw_quad();
int32 renderer_end();