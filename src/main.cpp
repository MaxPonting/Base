#define BASE_DEBUG

#include <allocator/allocator.h>
#include <log/log.h>
#include <io/file.h>
#include <io/png.h>
#include <math/math.h>
#include <opengl/opengl.h>
#include <opengl/shader.h>
#include <opengl/program.h>
#include <window/window.h>

#include <stdio.h>
#include <time.h>

const static UInt64 ALLOCATION_SIZE = 1024 * 1024; // MB

Int32 main()
{
    using namespace Base;

    Allocator::Create(ALLOCATION_SIZE);

    if(!Window::Create("Base Window", Window::OutputType::Windowed, 1280, 720))
        return 1; 
    if(!Window::SetGLContext(3, 3))
        return 1;
    if(!Window::Show())
        return 1;

    OpenGL::LoadProcedures();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    IO::PNG::Read("res/texture/test.png", 0, 0);

    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy))
            break; 

        if(Window::GetEvent(Window::Event::Resize))
            glViewport(0, 0, Window::GetWidth(), Window::GetHeight());        

        glClear(GL_COLOR_BUFFER_BIT);

        Window::SwapBuffer();
    }

    Window::Destroy();

    Allocator::Destroy();

    return 0;
}

