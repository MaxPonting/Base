#pragma once

#include "../type/type.h"

typedef struct Texture
{
    uint32 id;
    int32 width, height, bpp;
} Texture;

int32 texture_create_with_file(Texture* const texture, const char* const file_path);
int32 texture_create(Texture* const texture, const uint32 width, const uint32 height, const void* const data);
int32 texture_destroy(Texture* const texture);