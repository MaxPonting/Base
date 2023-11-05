#pragma once

#include "opengl.h"
#include "../type/type.h"
#include "../log/log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../io/stb_image.h"

namespace Base::OpenGL::Texture
{
    UInt32 CreateWithFile(const Char* const filepath)
    {
        UInt32 texture;
        Int32 width, height;

        stbi_set_flip_vertically_on_load(1);
        stbi_uc* buffer = stbi_load(filepath, &width, &height, 0, STBI_rgb_alpha);
        if(buffer == 0)
        {
            Log::Print("Image '%s' failed to load", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(buffer);

        return texture;
    }

    UInt32 CreateWithData(const Byte* const data, const Int32 width, const Int32 height)
    {
        UInt32 texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);

        return texture;
    }

    Int32 Destroy(const UInt32 texture)
    {
        glDeleteTextures(1, &texture);

        return 1;
    }

    Int32 Bind(const UInt32 texture, const UInt32 slot)
    {
        glActiveTexture(slot + GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        return 1;
    }
}
