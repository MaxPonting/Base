#include "opengl/texture.h"
#include "vendor/glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/std_image/std_image.h"
#include "log/log.h"

int32 texture_create(Texture* const texture, const uint32 width, const uint32 height, const void* const data)
{
    if (texture == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/TEXTURE", "Texture ptr is null", __LINE__);
        return 0;
    }

    if (width == 0 || height == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/TEXTURE", "Width or Height must be larger than 0", __LINE__);
        return 0;
    }

    texture->width = width;
    texture->height = height;
    texture->bpp = 4;

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    return 1;
}

int32 texture_create_with_file(Texture* const texture, const char* const file_path)
{
    if (texture == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/TEXTURE", "Texture ptr is null", __LINE__);
        return 0;
    }

    stbi_set_flip_vertically_on_load(1);
    stbi_uc* buffer = stbi_load(file_path, &texture->width, &texture->height, &texture->bpp, STBI_rgb_alpha);
    if (buffer == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/RENDERER/TEXTURE", "Texture failed to load", __LINE__);
        return 0;
    }

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(buffer);
        
    return 1;
}

int32 texture_destroy(Texture* const texture)
{
    if (texture == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/TEXTURE", "Texture ptr is null", __LINE__);
        return 0;
    }

    if (texture->id == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/TEXTURE", "Texture is null", __LINE__);
        return 0;
    }

    glDeleteTextures(GL_TEXTURE_2D, &texture->id);

    return 1;
}