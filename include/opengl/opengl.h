#pragma once

#include "../type/type.h"
#include "../platform/platform.h"

#if PLATFORM == PLATFORM_WINDOWS
#include <GL/gl.h>
#include <GL/glext.h>
PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDBUFFERBASEPROC glBindBufferBase;
PFNGLBINDBUFFERSRANGEPROC glBindBufferRange;
#elif PLATFORM == PLATFORM_LINUX
#include <GL/gl.h>
#include <GL/glext.h>
#elif PLATFORM == PLATFORM_MAC
#include <OpenGL/gl.h>
#include <OpenGl/glext.h>
#endif


namespace Base::Window
{
    Int64 GetGLProcAddress(const char* name);
}

namespace Base::OpenGL
{
    Int32 LoadProcedures()
    {

        
        return 1;
    }
}
