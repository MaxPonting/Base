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

    UInt32 start = Time::Get();

    Allocator::Create(ALLOCATION_SIZE);

    if(!Window::Create("Base Window", Window::OutputType::Windowed, 640, 640))
        return 1; 
    if(!Window::SetGLContext(3, 3))
        return 1;
    if(!Window::Show())
        return 1;

    OpenGL::LoadProcedures();
    OpenGL::EnableErrorLog();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    UInt32 vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    UInt32 vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, 4 * sizeof(Float32), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, 4 * sizeof(Float32), (void*)(2 * sizeof(Float32)));

    UInt32 indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);

    UInt32 program;

    {
        Char vertexSource[256];
        Char fragmentSource[256];

        IO::File::Read("res/shader/colour.vert", vertexSource, 256, false, true);
        IO::File::Read("res/shader/colour.frag", fragmentSource, 256, false, true);

        UInt32 shader[2];
        shader[0] = OpenGL::Shader::Create(vertexSource, OpenGL::Shader::Type::Vertex);
        shader[1] = OpenGL::Shader::Create(fragmentSource, OpenGL::Shader::Type::Fragment);

        program = OpenGL::Program::Create(shader, 2); 

        OpenGL::Shader::Destroy(shader[0]);
        OpenGL::Shader::Destroy(shader[1]);
    }

    OpenGL::Program::Bind(program);


    UInt32 texture = OpenGL::Texture::Create("res/texture/sub_texture_atlas.png");
    OpenGL::Texture::Bind(texture, 0);

    printf("%ums\n", Time::Get() - start);

    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy))
            break; 

        if(Window::GetEvent(Window::Event::Resize))
            glViewport(0, 0, Window::GetWidth(), Window::GetHeight());        

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        Window::SwapBuffer();
    }

    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
    OpenGL::Program::Destroy(program);
    OpenGL::Texture::Destroy(texture);

    Window::Destroy();

    Allocator::Destroy();

    return 0;
}

