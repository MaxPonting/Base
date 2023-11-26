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

#include <stdio.h>

const static UInt64 ALLOCATION_SIZE = 1024 * 1024; // MB
static Vec2 cameraPosition = {0, 0};
static Vec2 cameraScale = {1, 1};
static Float32 cameraRotation = 0;

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
        {0, 256, 128, 128, 0, 1.0f, 1.0f, 1.0f, 1.0f, plain}, 
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

        if(Math::Collision::RectRectAxisUnaligned({quads[0].position[0], quads[0].position[1], quads[0].size[0], quads[0].size[1], quads[0].rotation},
            {quads[1].position[0], quads[1].position[1], quads[1].size[0], quads[1].size[1], quads[0].rotation}))
        {
            quads[0].colour[1] = 0;
            quads[1].colour[1] = 0;
        }
        else
        {
            quads[0].colour[1] = 1;
            quads[1].colour[1] = 1;
        }

        if(Window::GetKey(Window::Key::Left))
            quads[0].rotation += 0.5f;
        if(Window::GetKey(Window::Key::Right))
            quads[0].rotation -= 0.5f;

        if(Window::GetKey(Window::Key::W))
            quads[0].position[1] += 2;
        if(Window::GetKey(Window::Key::S))
            quads[0].position[1] -= 2;
        if(Window::GetKey(Window::Key::D))
            quads[0].position[0] += 2;
        if(Window::GetKey(Window::Key::A))
            quads[0].position[0] -= 2;

        quads[1].position = { (Float32)Window::GetMousePosition()[0], (Float32)Window::GetMousePosition()[1] };

        Renderer2D::BeginScene({ Window::GetWidth(), Window::GetHeight() }, { cameraPosition, cameraScale, Math::F32::Radians(cameraRotation) });
        Renderer2D::Draw(quads, 2, texture, Renderer2D::CoordinateSpace::World, {0, 0});
//        Renderer2D::Draw(quads, 1, texture, Renderer2D::CoordinateSpace::Screen, { -1, 0});
        Renderer2D::EndScene();

        Window::SwapBuffer();
    }

    Renderer2D::Destroy();
    Window::Destroy();
    Allocator::Destroy();

    return 0;
}