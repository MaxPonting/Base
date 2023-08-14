#pragma once

#include "texture.h"
#include "../math/struct.h"

typedef struct 
{
    vec2 max;
    vec2 min;
} SubTexture;

int32 sub_texture_create(SubTexture* const sub_texture, const vec2 texture_size, const vec2 cell_size, const vec2 position, const vec2 size);