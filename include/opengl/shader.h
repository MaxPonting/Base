#pragma once

#include "opengl.h"
#include "../type/type.h"
#include "../log/log.h"

namespace Base::OpenGL::Shader
{
    enum class Type
    {
        Vertex      = GL_VERTEX_SHADER,
        Fragment    = GL_FRAGMENT_SHADER,
        Geometry    = GL_GEOMETRY_SHADER,
        Compute     = GL_COMPUTE_SHADER
    };

    UInt32 Create(const char* const source, const Type type)
    {
        unsigned int shaderObject = glCreateShader((UInt32)type);
        glShaderSource(shaderObject, 1, &source, 0);
        glCompileShader(shaderObject);

        Int32 result;
        glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);
        if(!result)
        {
            Char message[256];
            glGetShaderInfoLog(shaderObject, 128, NULL, message);
            Log::Print(message, Log::Type::Error, __LINE__, __FILE__);
            glDeleteShader(shaderObject);
            return 0;
        }

        return shaderObject;
    }

    Int32 Destroy(const UInt32 shaderObject)
    {
        glDeleteShader(shaderObject);

        return 1;
    }
}

