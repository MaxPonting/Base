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
}