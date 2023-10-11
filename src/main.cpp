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

typedef struct
{
    UInt32 vertexArrayObject, vertexBufferObject;
} Global;

Global global;

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

    glGenVertexArrays(1, &global.vertexArrayObject);
    glBindVertexArray(global.vertexArrayObject);

    glGenBuffers(1, &global.vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, global.vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), &VERTICES, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(Float32) * 2, 0);

    printf("W:%d, H:%d\n", Window::GetWidth(), Window::GetHeight());

    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy))
            break; 

        if(Window::GetEvent(Window::Event::KeyDown_M))
            Window::SetPosition(500, 500);

        if(Window::GetEvent(Window::Event::Move))
        {
            printf("X:%d, Y:%d\n", Window::GetX(), Window::GetY());
        }

        if(Window::GetEvent(Window::Event::KeyDown_W))
        {
            Window::SetOutputType(Window::OutputType::Windowed);
            printf("W:%d, H:%d\n", Window::GetWidth(), Window::GetHeight());
        }

        if(Window::GetEvent(Window::Event::KeyDown_S))
        {
            Window::SetSize(1920, 1080);
            glViewport(0, 0, 1920, 1080);
        }

        glClear(GL_COLOR_BUFFER_BIT);        

        glBegin(GL_TRIANGLES);
        glColor3f(0.8, 0.2, 0.3); glVertex2f(-1, -1); 
        glColor3f(0.8, 0.2, 0.3); glVertex2f(0, 1);
        glColor3f(0.8, 0.2, 0.3); glVertex2f(1, -1);
        glEnd();

        Window::SwapBuffer();
    }

    glDeleteVertexArrays(1, &global.vertexArrayObject);
    glDeleteBuffers(1, &global.vertexBufferObject);
    
    Window::Destroy();

    Allocator::Destroy();

    return 0;
}

