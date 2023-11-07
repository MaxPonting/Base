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

    UInt32 texture = OpenGL::Texture::CreateWithFile("res/texture/sub_texture_atlas.png");

    IVec2 parentSize = {64, 64};
    IVec2 position = {0, 32};
    IVec2 size = {32, 32};

    Renderer2D::SubTexture plain = Renderer2D::CreateSubTexture(parentSize, position, size);

    Renderer2D::Quad quads[] = 
    {
        {0, 0, 128, 128, 0, 1.0f, 1.0f, 1.0f, 1.0f, plain}, 
        {200, 0, 128, 128, 0, 1.0f, 1.0f, 1.0f, 1.0f, plain},       
        {0, -200, 128, 128, 0, 1.0f, 1.0f, 1.0f, 1.0f, plain},        
    };

    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy))
            break; 

        if(Window::GetEvent(Window::Event::Resize))
            glViewport(0, 0, Window::GetWidth(), Window::GetHeight());        

        if(Window::GetKey(Window::Key::W))
            quads[0].position[1] += 5.0f;
        if(Window::GetKey(Window::Key::S))
            quads[0].position[1] -= 5.0f;
        if(Window::GetKey(Window::Key::D))
            quads[0].position[0] += 5.0f;
        if(Window::GetKey(Window::Key::A))
            quads[0].position[0] -= 5.0f;

        Renderer2D::BeginScene(Window::GetWidth(), Window::GetHeight());
        Renderer2D::DrawBatch(quads, 3, texture);
        Renderer2D::EndScene();

        Window::SwapBuffer();
    }

    Renderer2D::Destroy();
    Window::Destroy();
    Allocator::Destroy();

    return 0;
}

