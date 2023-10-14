#include "opengl.h"
#include "../type/type.h"
#include "../log/log.h"
#include "../math/struct.h"

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
            char message[100];
            glGetShaderInfoLog(shaderObject, 100, NULL, message);
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

    Int32 SetUniform1I(const UInt32 shaderObject, const char* const uniformName, const Int32 value)
    {
        Int32 location = glGetUniformLocation(shaderObject, uniformName);
        if(!location)
        {
            Log::Print("Cannot find uniform location", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
        glUniform1i(location, value);

        return 1;
    }

    Int32 SetUniform1F(const UInt32 shaderObject, const char* const uniformName, const Float32 value)
    {
        Int32 location = glGetUniformLocation(shaderObject, uniformName);
        if(!location)
        {
            Log::Print("Cannot find uniform location", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
        glUniform1f(location, value);

        return 1;
    }

    Int32 SetUniform3F(const UInt32 shaderObject, const char* const uniformName, const Vec3 value)
    {
        Int32 location = glGetUniformLocation(shaderObject, uniformName);
        if(!location)
        {
            Log::Print("Cannot find uniform location", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
        glUniform3f(location, value[0], value[1], value[2]);

        return 1;
    }

    Int32 SetUniformMatrix4FV(const UInt32 shaderObject, const char* const uniformName, const Mat4 value)
    {
        Int32 location = glGetUniformLocation(shaderObject, uniformName);
        if(!location)
        {
            Log::Print("Cannot find uniform location", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
        glUniformMatrix4fv(location, 1, 0, (Float32*)value);

        return 1;
    }
}

