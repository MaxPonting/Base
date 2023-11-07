#pragma once

#include "opengl.h"

namespace Base::OpenGL::Program
{
    UInt32 Create(const UInt32* const shaderObjects, const Int32 shaderObjectCount)
    {
        UInt32 programObject = glCreateProgram();

        for(Int32 i = 0; i < shaderObjectCount; i++)
            glAttachShader(programObject, shaderObjects[i]);

        glLinkProgram(programObject);
        glValidateProgram(programObject);

        return programObject;
    }

    Int32 Destroy(const UInt32 programObject)
    {
        glDeleteProgram(programObject);

        return 1;
    }

    Int32 Bind(const UInt32 programObject)
    {
        glUseProgram(programObject);

        return 1;
    }

    Int32 SetUniform1I(const UInt32 programObject, const char* const uniformName, const Int32 value)
    {
        Int32 location = glGetUniformLocation(programObject, uniformName);
        if(location == -1)
        {
            Log::Print("Cannot find uniform location", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
        glUniform1i(location, value);

        return 1;
    }

    Int32 SetUniform1IV(const UInt32 programObject, const char* const uniformName, const Int32* value, const Int32 count)
    {
        Int32 location = glGetUniformLocation(programObject, uniformName);
        if(location == -1)
        {
            Log::Print("Cannot find uniform location", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
        glUniform1iv(location, count, value);

        return 1;
    }

    Int32 SetUniform1F(const UInt32 programObject, const char* const uniformName, const Float32 value)
    {
        Int32 location = glGetUniformLocation(programObject, uniformName);
        if(location == -1)
        {
            Log::Print("Cannot find uniform location", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
        glUniform1f(location, value);

        return 1;
    }

    Int32 SetUniform3F(const UInt32 programObject, const char* const uniformName, const Vec3 value)
    {
        Int32 location = glGetUniformLocation(programObject, uniformName);
        if(location == -1)
        {
            Log::Print("Cannot find uniform location", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
        glUniform3f(location, value[0], value[1], value[2]);

        return 1;
    }

    Int32 SetUniformMatrix4FV(const UInt32 programObject, const char* const uniformName, const Mat4 value)
    {
        Int32 location = glGetUniformLocation(programObject, uniformName);
        if(location == -1)
        {
            Log::Print("Cannot find uniform location", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
        glUniformMatrix4fv(location, 1, 0, (Float32*)value);

        return 1;
    }

}