#include "graphics/texture.h"
#include "graphics/camera.h"
#include "graphics/renderer.h"
#include "graphics/glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "graphics/std_image/std_image.h"

int texture_create(Texture* const texture, const Renderer renderer, const char* const file_path, const int cell_width, const int cell_height)
{
    if (renderer.type == RENDERER_TYPE_NULL)
    {
        printf("[ERROR][BASE/GRAPHICS/TEXTURE/%d][Renderer type not supported]\n", __LINE__);
        return 0;
    }

    stbi_set_flip_vertically_on_load(1);
    stbi_uc* buffer = stbi_load(file_path, &texture->width, &texture->height, &texture->bits_per_pixel, STBI_rgb_alpha);
    if (buffer == 0)
    {
        printf("[ERROR][BASE/GRAPHICS/TEXTURE/%d][Image failed to load]\n", __LINE__);
        return 0;
    }

    if (renderer.type == RENDERER_TYPE_OPENGL)
    {
        glGenTextures(1, &texture->id);
        glBindTexture(GL_TEXTURE_2D, texture->id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    stbi_image_free(buffer);

    texture->cell_width = cell_width;
    texture->cell_height = cell_height;

    return 1;
}

int texture_destroy(Texture* const texture, const Renderer renderer)
{
    if (texture->id == 0)
    {
        printf("[ERROR][BASE/GRAPHICS/TEXTURE/%d][Cannot destroy null texture]\n", __LINE__);
        return 0;
    }

    if (renderer.type == RENDERER_TYPE_OPENGL)
    {
        glDeleteTextures(1, &texture->id);
    }
    else 
    {
        printf("[ERROR][BASE/GRAPHICS/SHADER/%d][Renderer type not supported]\n", __LINE__);
        return 0;
    }

    return 1;
}