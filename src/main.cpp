#define BASE_DEBUG

#include <allocator/allocator.h>
#include <log/log.h>
#include <io/file.h>
#include <math/math.h>
#include <time/time.h>
#include <opengl/opengl.h>
#include <opengl/shader.h>
#include <opengl/program.h>
#include <opengl/texture.h>
#include <window/window.h>
#include <renderer/renderer2D.h>

#include <stdio.h>
#include <time.h>

const static UInt64 ALLOCATION_SIZE = 1024 * 1024; // MB

const static Float32 VERTICES[] = {
     -1.0f, -1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
     -1.0f,  1.0f, 0.0f, 1.0f,
      1.0f,  1.0f, 1.0f, 1.0f
};

const static UInt32 INDICES[] = {
    0, 1, 2,
    1, 3, 2
};

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
    OpenGL::EnableErrorLog();

    Renderer2D::Create(10);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    Renderer2D::Quad quad = {0, 0, 100, 100, 0, 1.0f, 0.0f, 0.0f, 1.0f};

    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy))
            break; 

        if(Window::GetEvent(Window::Event::Resize))
            glViewport(0, 0, Window::GetWidth(), Window::GetHeight());        

        Renderer2D::BeginScene(Window::GetWidth(), Window::GetHeight());
        Renderer2D::DrawBatch(&quad, 1);
        Renderer2D::EndScene();

        Window::SwapBuffer();

        //break;
    }

    Renderer2D::Destroy();
    Window::Destroy();
    Allocator::Destroy();

    return 0;
}

