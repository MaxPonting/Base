#pragma once

#include "../type/type.h"
#include "../platform/platform.h"

#if PLATFORM == PLATFORM_WINDOWS
#include <GL/gl.h>
#include <GL/glext.h>
PFNGLACTIVETEXTUREPROC glActiveTexture;
#elif PLATFORM == PLATFORM_LINUX
#include <GL/gl.h>
#include <GL/glext.h>
#elif PLATFORM == PLATFORM_MAC
#include <OpenGL/gl.h>
#include <OpenGl/glext.h>
#endif

PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDBUFFERBASEPROC glBindBufferBase;
PFNGLBINDBUFFERSRANGEPROC glBindBufferRange;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLBUFFERSUBDATAPROC glBufferSubData;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM3FPROC glUniform3f;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLVALIDATEPROGRAMPROC glValidateProgram;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

namespace Base::Window
{
    Int64 GetGLProcAddress(const char* name);
}

namespace Base::OpenGL
{
    Int32 LoadProcedures()
    {
#if PLATFORM == PLATFORM_WINDOWS
        glActiveTexture             = (PFNGLACTIVETEXTUREPROC)Window::GetGLProcAddress("glActiveTexture");
#endif
        glAttachShader              = (PFNGLATTACHSHADERPROC)Window::GetGLProcAddress("glAttachShader");
        glBindBuffer                = (PFNGLBINDBUFFERPROC)Window::GetGLProcAddress("glBindBuffer");
        glBindBufferBase            = (PFNGLBINDBUFFERBASEPROC)Window::GetGLProcAddress("glBindBufferBase");
        glBindVertexArray           = (PFNGLBINDVERTEXARRAYPROC)Window::GetGLProcAddress("glBindVertexArray");
        glBufferData                = (PFNGLBUFFERDATAPROC)Window::GetGLProcAddress("glBufferData");
        glBufferSubData             = (PFNGLBUFFERSUBDATAPROC)Window::GetGLProcAddress("glBufferSubData");
        glCompileShader             = (PFNGLCOMPILESHADERPROC)Window::GetGLProcAddress("glCompileShader");
        glCreateProgram             = (PFNGLCREATEPROGRAMPROC)Window::GetGLProcAddress("glCreateProgram");
        glCreateShader              = (PFNGLCREATESHADERPROC)Window::GetGLProcAddress("glCreateShader");
        glDeleteBuffers             = (PFNGLDELETEBUFFERSPROC)Window::GetGLProcAddress("glDeleteBuffers");
        glDeleteProgram             = (PFNGLDELETEPROGRAMPROC)Window::GetGLProcAddress("glDeleteProgram");
        glDeleteShader              = (PFNGLDELETESHADERPROC)Window::GetGLProcAddress("glDeleteShader");
        glDeleteVertexArrays        = (PFNGLDELETEVERTEXARRAYSPROC)Window::GetGLProcAddress("glDeleteVertexArrays");
        glDetachShader              = (PFNGLDETACHSHADERPROC)Window::GetGLProcAddress("glDetachShader");
        glEnableVertexAttribArray   = (PFNGLENABLEVERTEXATTRIBARRAYPROC)Window::GetGLProcAddress("glEnableVertexAttribArray");
        glGenBuffers                = (PFNGLGENBUFFERSPROC)Window::GetGLProcAddress("glGenBuffers");
        glGenVertexArrays           = (PFNGLGENVERTEXARRAYSPROC)Window::GetGLProcAddress("glGenVertexArrays");
        glGenerateMipmap            = (PFNGLGENERATEMIPMAPPROC)Window::GetGLProcAddress("glGenerateMipmap");
        glGetShaderiv               = (PFNGLGETSHADERIVPROC)Window::GetGLProcAddress("glGetShaderiv");
        glGetShaderInfoLog          = (PFNGLGETSHADERINFOLOGPROC)Window::GetGLProcAddress("glGetShaderInfoLog");
        glGetUniformLocation        = (PFNGLGETUNIFORMLOCATIONPROC)Window::GetGLProcAddress("glGetUniformLocation");
        glShaderSource              = (PFNGLSHADERSOURCEPROC)Window::GetGLProcAddress("glShaderSource");
        glLinkProgram               = (PFNGLLINKPROGRAMPROC)Window::GetGLProcAddress("glLinkProgram");
        glUniform1i                 = (PFNGLUNIFORM1IPROC)Window::GetGLProcAddress("glUniform1i");
        glUniform1f                 = (PFNGLUNIFORM1FPROC)Window::GetGLProcAddress("glUniform1f");
        glUniform3f                 = (PFNGLUNIFORM3FPROC)Window::GetGLProcAddress("glUniform3f");
        glUniformMatrix4fv          = (PFNGLUNIFORMMATRIX4FVPROC)Window::GetGLProcAddress("glUniformMatrix4fv");
        glValidateProgram           = (PFNGLVALIDATEPROGRAMPROC)Window::GetGLProcAddress("glValidateProgram");
        glVertexAttribPointer       = (PFNGLVERTEXATTRIBPOINTERPROC)Window::GetGLProcAddress("glVertexAttribPointer");

        return 1;
    }
}
