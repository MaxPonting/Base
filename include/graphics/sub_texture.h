#pragma once

#include "texture.h"
#include "cglm/struct.h"

typedef struct
{
    Texture* texture;
    vec2 index;
    vec2 sprite_size;
} SubTexture;

int sub_texture_create(SubTexture* const sub_texture, Texture* const texture, const vec2 index, const vec2 sprite_size);
