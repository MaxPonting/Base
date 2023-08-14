#pragma once

#include "../type/type.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "../vendor/nuklear/nuklear_native.h"
#include "../vendor/nuklear/nuklear_glfw_gl3.h"

struct nk_context* nuklear_ctx;

int32 nuklear_create();
int32 nuklear_destroy();

int32 nuklear_new_frame();
int32 nuklear_render();