#define BASE_DEBUG


#include <allocator/allocator.h>
#include <log/log.h>
#include <io/file.h>
#include <math/math.h>
#include <math/collision.h>
#include <time/time.h>
#include <time/sleep.h>
#include <time/performance_counter.h>
#include <opengl/opengl.h>
#include <opengl/shader.h>
#include <opengl/program.h>
#include <opengl/texture.h>
#include <window/window.h>
#include <renderer/renderer2D.h>
#include <game/point.h>

#include <stdio.h>

const static UInt64 ALLOCATION_SIZE = 1024 * 1024; // MB
static Rect camera = { 0, 0, 1, 1, 0 };

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

    Renderer2D::Create({ 1280, 720 }, 10);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    UInt32 texture = OpenGL::Texture::CreateWithFile("res/texture/sub_texture_atlas.png");
    Renderer2D::SubTexture plain = Renderer2D::CreateSubTexture({64, 64}, {0, 32}, {32, 32});

    Renderer2D::Quad quads[] = 
    {
        {0, 0, 128, 128, 0, 1.0f, 1.0f, 1.0f, 1.0f, plain}, 
        {0, 128, 128, 128, 0, 1.0f, 1.0f, 1.0f, 1.0f, plain}, 
        {0, 0, 128, 128, 0, 1.0f, 1.0f, 1.0f, 1.0f, plain}, 
    };

    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy))
            break; 

        if(Window::GetKeyDown(Window::Key::Escape))
            break;

        if(Window::GetEvent(Window::Event::Resize))
            glViewport(0, 0, Window::GetWidth(), Window::GetHeight());        

        if(Window::GetKey(Window::Key::W))
            camera.position[1] += 2;
        if(Window::GetKey(Window::Key::S))
            camera.position[1] -= 2;
        if(Window::GetKey(Window::Key::D))
            camera.position[0] += 2;
        if(Window::GetKey(Window::Key::A))
            camera.position[0] -= 2;

        if(Window::GetKey(Window::Key::Space))
        {
            camera.size[0] += 0.1f;
            camera.size[1] += 0.1f;
        }

        if(Window::GetKey(Window::Key::Right))
            camera.rotation += 0.01f;

        quads[0].position = { (Float32)Window::GetMousePosition()[0], (Float32)Window::GetMousePosition()[1] };
        quads[0].position = Renderer2D::ScreenToWorldPoint(quads[0].position, Window::GetSize(), camera);

        Renderer2D::BeginScene(Window::GetSize(), camera);
        Renderer2D::Draw(quads, 2, texture, Renderer2D::CoordinateSpace::World, {0, 0});
        Renderer2D::EndScene();

        Window::SwapBuffer();
    }

    Renderer2D::Destroy();
    Window::Destroy();
    Allocator::Destroy();

    return 0;
}