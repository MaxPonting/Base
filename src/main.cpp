#define BASE_DEBUG

#include <allocator/allocator.h>
#include <log/log.h>
#include <file/file.h>
#include <opengl/opengl.h>
#include <opengl/shader.h>
#include <opengl/program.h>
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
    UInt32 vertexArrayObject, vertexBufferObject, programObject;
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

    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);            

    glGenVertexArrays(1, &global.vertexArrayObject);
    glBindVertexArray(global.vertexArrayObject);

    glGenBuffers(1, &global.vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, global.vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), &VERTICES, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(Float32) * 2, 0);

    {
        char vertexShaderSource[256];
        char fragmentShaderSource[256];
        File::Read("res/shader/colour.vert", vertexShaderSource, sizeof(vertexShaderSource)); 
        File::Read("res/shader/colour.frag", fragmentShaderSource, sizeof(fragmentShaderSource));

        UInt32 shaderObjects[2];
        shaderObjects[0] = OpenGL::Shader::Create(vertexShaderSource, OpenGL::Shader::Type::Vertex);
        shaderObjects[1] = OpenGL::Shader::Create(fragmentShaderSource, OpenGL::Shader::Type::Fragment);

        global.programObject = OpenGL::Program::Create(shaderObjects, 2);

        OpenGL::Shader::Destroy(shaderObjects[0]);
        OpenGL::Shader::Destroy(shaderObjects[1]);
    }

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

    glDeleteVertexArrays(1, &global.vertexArrayObject);
    glDeleteBuffers(1, &global.vertexBufferObject);
    
    Window::Destroy();

    Allocator::Destroy();

    return 0;
}

