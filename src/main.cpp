#define BASE_DEBUG

#include <allocator/allocator.h>
#include <log/log.h>
#include <opengl/opengl.h>
#include <window/window.h>

#include <stdio.h>

const static UInt64 ALLOCATION_SIZE = 1024 * 1024; // MB

Int32 main()
{
    using namespace Base;

    Allocator::Create(ALLOCATION_SIZE);

    if(!Window::Create("Base Window", 1280, 720))
        return 1;
    if(!Window::SetGLContext(3, 0))
        return 1;
        
    Window::Show();

    printf("%s\n", glGetString(GL_VERSION));

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

        glBegin(GL_TRIANGLES);
			glColor3f(  1.0f,  0.0f, 0.0f);
			glVertex3f( 0.0f,  1.0f, 0.0f);
			glColor3f(  0.0f,  1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glColor3f(  0.0f,  0.0f, 1.0f);
			glVertex3f( 1.0f, -1.0f, 0.0f);
		glEnd();

        Window::SwapBuffer();
    }
    
    Window::Destroy();

    Allocator::Destroy();

    return 0;
}
