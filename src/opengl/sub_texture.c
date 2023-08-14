#include "opengl/sub_texture.h"

int32 sub_texture_create(SubTexture* const sub_texture, const vec2 texture_size, const vec2 cell_size, const vec2 position, const vec2 size)
{
    sub_texture->min[0] = (position[0] * cell_size[0]) / texture_size[0];
    sub_texture->min[1] = (position[1] * cell_size[1]) / texture_size[1];

    sub_texture->max[0] = ((position[0] + size[0]) * cell_size[0]) / texture_size[0];
    sub_texture->max[1] = ((position[1] + size[1]) * cell_size[1]) / texture_size[1];

    return 1;
}