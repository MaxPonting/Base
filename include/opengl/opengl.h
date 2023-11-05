#pragma once

#include "../type/type.h"
#include "../platform/platform.h"

#if PLATFORM == PLATFORM_WINDOWS
#include <GL/gl.h>
#include <GL/glext.h>
PFNGLACTIVETEXTUREPROC base_glActiveTexture;
#define glActiveTexture base_glActiveTexture
#elif PLATFORM == PLATFORM_LINUX
#include <GL/gl.h>
#include <GL/glext.h>
#elif PLATFORM == PLATFORM_MAC
#include <OpenGL/gl.h>
#include <OpenGl/glext.h>
#endif

PFNGLATTACHSHADERPROC base_glAttachShader;
PFNGLBINDBUFFERPROC base_glBindBuffer;
PFNGLBINDBUFFERBASEPROC base_glBindBufferBase;
PFNGLBINDBUFFERSRANGEPROC base_glBindBufferRange;
PFNGLBINDVERTEXARRAYPROC base_glBindVertexArray;
PFNGLBUFFERDATAPROC base_glBufferData;
PFNGLBUFFERSUBDATAPROC base_glBufferSubData;
PFNGLCOMPILESHADERPROC base_glCompileShader;
PFNGLCREATEPROGRAMPROC base_glCreateProgram;
PFNGLCREATESHADERPROC base_glCreateShader;
PFNGLDELETEBUFFERSPROC base_glDeleteBuffers;
PFNGLDELETEPROGRAMPROC base_glDeleteProgram;
PFNGLDELETESHADERPROC base_glDeleteShader;
PFNGLDELETEVERTEXARRAYSPROC base_glDeleteVertexArrays;
PFNGLDEBUGMESSAGECALLBACKPROC base_glDebugMessageCallback;
PFNGLDETACHSHADERPROC base_glDetachShader;
PFNGLENABLEVERTEXATTRIBARRAYPROC base_glEnableVertexAttribArray;
PFNGLGENBUFFERSPROC base_glGenBuffers;
PFNGLGENVERTEXARRAYSPROC base_glGenVertexArrays;
PFNGLGENERATEMIPMAPPROC base_glGenerateMipmap;
PFNGLGETSHADERIVPROC base_glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC base_glGetShaderInfoLog;
PFNGLGETUNIFORMLOCATIONPROC base_glGetUniformLocation;
PFNGLSHADERSOURCEPROC base_glShaderSource;
PFNGLLINKPROGRAMPROC base_glLinkProgram;
PFNGLUNIFORM1IPROC base_glUniform1i;
PFNGLUNIFORM1FPROC base_glUniform1f;
PFNGLUNIFORM3FPROC base_glUniform3f;
PFNGLUNIFORMMATRIX4FVPROC base_glUniformMatrix4fv;
PFNGLUSEPROGRAMPROC base_glUseProgram;
PFNGLVALIDATEPROGRAMPROC base_glValidateProgram;
PFNGLVERTEXATTRIBPOINTERPROC base_glVertexAttribPointer;

#define glAttachShader base_glAttachShader
#define glBindBuffer base_glBindBuffer
#define glBindBufferBase base_glBindBufferBase
#define glBindBufferRange base_glBindBufferRange
#define glBindVertexArray base_glBindVertexArray
#define glBufferData base_glBufferData
#define glBufferSubData base_glBufferSubData
#define glCompileShader base_glCompileShader
#define glCreateProgram base_glCreateProgram
#define glCreateShader base_glCreateShader
#define glDeleteBuffers base_glDeleteBuffers
#define glDeleteProgram base_glDeleteProgram
#define glDeleteShader base_glDeleteShader
#define glDeleteVertexArrays base_glDeleteVertexArrays
#define glDetachShader base_glDetachShader
#define glEnableVertexAttribArray base_glEnableVertexAttribArray
#define glDebugMessageCallback base_glDebugMessageCallback
#define glGenBuffers base_glGenBuffers
#define glGenVertexArrays base_glGenVertexArrays
#define glGenerateMipMap base_glGenerateMipmap
#define glGetShaderiv base_glGetShaderiv
#define glGetShaderInfoLog base_glGetShaderInfoLog
#define glGetUniformLocation base_glGetUniformLocation
#define glShaderSource base_glShaderSource
#define glLinkProgram base_glLinkProgram
#define glUniform1i base_glUniform1i
#define glUniform1f base_glUniform1f
#define glUniform3f base_glUniform3f
#define glUniformMatrix4fv base_glUniformMatrix4fv
#define glUseProgram base_glUseProgram
#define glValidateProgram base_glValidateProgram
#define glVertexAttribPointer base_glVertexAttribPointer

namespace Base::Window
{
    Int64 GetGLProcAddress(const char* name);
}

namespace Base::OpenGL
{
    Int32 LoadProcedures()
    {
#if PLATFORM == PLATFORM_WINDOWS
        base_glActiveTexture             = (PFNGLACTIVETEXTUREPROC)Window::GetGLProcAddress("glActiveTexture");
#endif
        base_glAttachShader              = (PFNGLATTACHSHADERPROC)Window::GetGLProcAddress("glAttachShader");
        base_glBindBuffer                = (PFNGLBINDBUFFERPROC)Window::GetGLProcAddress("glBindBuffer");
        base_glBindBufferBase            = (PFNGLBINDBUFFERBASEPROC)Window::GetGLProcAddress("glBindBufferBase");
        base_glBindVertexArray           = (PFNGLBINDVERTEXARRAYPROC)Window::GetGLProcAddress("glBindVertexArray");
        base_glBufferData                = (PFNGLBUFFERDATAPROC)Window::GetGLProcAddress("glBufferData");
        base_glBufferSubData             = (PFNGLBUFFERSUBDATAPROC)Window::GetGLProcAddress("glBufferSubData");
        base_glCompileShader             = (PFNGLCOMPILESHADERPROC)Window::GetGLProcAddress("glCompileShader");
        base_glCreateProgram             = (PFNGLCREATEPROGRAMPROC)Window::GetGLProcAddress("glCreateProgram");
        base_glCreateShader              = (PFNGLCREATESHADERPROC)Window::GetGLProcAddress("glCreateShader");
        base_glDeleteBuffers             = (PFNGLDELETEBUFFERSPROC)Window::GetGLProcAddress("glDeleteBuffers");
        base_glDeleteProgram             = (PFNGLDELETEPROGRAMPROC)Window::GetGLProcAddress("glDeleteProgram");
        base_glDeleteShader              = (PFNGLDELETESHADERPROC)Window::GetGLProcAddress("glDeleteShader");
        base_glDeleteVertexArrays        = (PFNGLDELETEVERTEXARRAYSPROC)Window::GetGLProcAddress("glDeleteVertexArrays");
        base_glDetachShader              = (PFNGLDETACHSHADERPROC)Window::GetGLProcAddress("glDetachShader");
        base_glEnableVertexAttribArray   = (PFNGLENABLEVERTEXATTRIBARRAYPROC)Window::GetGLProcAddress("glEnableVertexAttribArray");
        base_glDebugMessageCallback      = (PFNGLDEBUGMESSAGECALLBACKPROC)Window::GetGLProcAddress("glDebugMessageCallback");
        base_glGenBuffers                = (PFNGLGENBUFFERSPROC)Window::GetGLProcAddress("glGenBuffers");
        base_glGenVertexArrays           = (PFNGLGENVERTEXARRAYSPROC)Window::GetGLProcAddress("glGenVertexArrays");
        base_glGenerateMipmap            = (PFNGLGENERATEMIPMAPPROC)Window::GetGLProcAddress("glGenerateMipmap");
        base_glGetShaderiv               = (PFNGLGETSHADERIVPROC)Window::GetGLProcAddress("glGetShaderiv");
        base_glGetShaderInfoLog          = (PFNGLGETSHADERINFOLOGPROC)Window::GetGLProcAddress("glGetShaderInfoLog");
        base_glGetUniformLocation        = (PFNGLGETUNIFORMLOCATIONPROC)Window::GetGLProcAddress("glGetUniformLocation");
        base_glShaderSource              = (PFNGLSHADERSOURCEPROC)Window::GetGLProcAddress("glShaderSource");
        base_glLinkProgram               = (PFNGLLINKPROGRAMPROC)Window::GetGLProcAddress("glLinkProgram");
        base_glUniform1i                 = (PFNGLUNIFORM1IPROC)Window::GetGLProcAddress("glUniform1i");
        base_glUniform1f                 = (PFNGLUNIFORM1FPROC)Window::GetGLProcAddress("glUniform1f");
        base_glUniform3f                 = (PFNGLUNIFORM3FPROC)Window::GetGLProcAddress("glUniform3f");
        base_glUniformMatrix4fv          = (PFNGLUNIFORMMATRIX4FVPROC)Window::GetGLProcAddress("glUniformMatrix4fv");
        base_glUseProgram                = (PFNGLUSEPROGRAMPROC)Window::GetGLProcAddress("glUseProgram");
        base_glValidateProgram           = (PFNGLVALIDATEPROGRAMPROC)Window::GetGLProcAddress("glValidateProgram");
        base_glVertexAttribPointer       = (PFNGLVERTEXATTRIBPOINTERPROC)Window::GetGLProcAddress("glVertexAttribPointer");

        return 1;
    }

    void APIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
    {
        Log::Print(msg, Log::Type::Error, __LINE__, __FILE__);
        source = type + id + severity + length + (UInt64)msg + (UInt64)data;
        type = source;
    }

    Int32 EnableErrorLog()
    {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(OpenGLDebugCallback, 0);

        return 1;
    }

}
