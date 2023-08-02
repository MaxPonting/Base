#include "graphics/sub_texture.h"

int sub_texture_create(SubTexture* const sub_texture, Texture* const texture, const vec2 index, const vec2 sprite_size)
{
    sub_texture->texture = texture;
    sub_texture->index[0] = index[0];
    sub_texture->index[1] = index[1];
    sub_texture->sprite_size[0] = sprite_size[0];
    sub_texture->sprite_size[1] = sprite_size[1];

    return 1;
}