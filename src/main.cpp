#define BASE_DEBUG

#include <allocator/allocator.h>
#include <log/log.h>
#include <opengl/opengl.h>
#include <window/window.h>

#include <stdio.h>
#include <time.h>

const static UInt64 ALLOCATION_SIZE = 1024 * 1024; // MB
const static Float32 VERTICES[] = {
     0.0f,  0.5f,
    -0.5f, -0.5f,
     0.5f, -0.5f
};

Int32 main()
{
    using namespace Base;

    Allocator::Create(ALLOCATION_SIZE);

    if(!Window::Create("Base Window", Window::OutputType::Windowed, 1280, 720))
        return 1; 
    if(!Window::SetGLContext(1, 0))
        return 1;
    if(!Window::Show())
        return 1;

    OpenGL::LoadProcedures();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);            

    
    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy))
            break; 

        if(Window::GetEvent(Window::Event::KeyDown_F))
            Window::SetOutputType(Window::OutputType::Fullscreen);

        if(Window::GetEvent(Window::Event::KeyDown_B))
            Window::SetOutputType(Window::OutputType::BorderlessFullscreen);

        if(Window::GetEvent(Window::Event::KeyDown_W))
            Window::SetOutputType(Window::OutputType::Windowed);

        glClear(GL_COLOR_BUFFER_BIT);        

        glBegin(GL_QUADS);
            glColor3f(1., 1., 0.); glVertex3f(-.75, -.75, 0.);
            glColor3f(1., 1., 0.); glVertex3f( .75, -.75, 0.);
            glColor3f(1., 1., 0.); glVertex3f( .75,  .75, 0.);
            glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
        glEnd();

        Window::SwapBuffer();
    }
    
    Window::Destroy();

    Allocator::Destroy();

    return 0;
}
