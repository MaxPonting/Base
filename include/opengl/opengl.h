#pragma once

#include "../type/type.h"
#include "../platform/platform.h"
#include "../window/window.h"

#include <GL/gl.h>
#include "glext.h"

PFNGLCREATEBUFFERSPROC glCreateBuffers; 

namespace Base::OpenGL
{
    Int32 LoadProcedures()
    {
        glCreateBuffers = (PFNGLCREATEBUFFERSPROC)Window::GetGLProcAddress("glCreateBuffers");
        return 1;
    }
}