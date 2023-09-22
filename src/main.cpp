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

    if(!Window::Create("Base Window", 1280, 720))
        return 1; 

    Int64 before = clock();

    if(!Window::SetGLContext(1, 0))
        return 1;

    printf("Time taken(ms):%lld\n", (clock() - before) * 1000 / CLOCKS_PER_SEC);

    OpenGL::LoadProcedures();

    Window::Show();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy))
            break; 

        if(Window::GetEvent(Window::Event::KeyDown_Space))
            printf("Space\n");

        if(Window::GetEvent(Window::Event::KeyDown_A))
            printf("A\n");

        if(Window::GetEvent(Window::Event::KeyDown_H))
            printf("H\n");

        glClear(GL_COLOR_BUFFER_BIT);        

        glBegin(GL_QUADS);
            glColor3f(1., 1., 0.); glVertex3f(-.75, -.75, 0.);
            glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
            glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
            glColor3f(1., 0., 0.); glVertex3f(-.75,  .75, 0.);
        glEnd();

        Window::SwapBuffer();
    }
    
    Window::Destroy();

    Allocator::Destroy();

    return 0;
}
