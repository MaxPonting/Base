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
#include <graphics/renderer2D.h>
#include <graphics/convert.h>

#include <stdio.h>

const static UInt64 ALLOCATION_SIZE = 1024 * 1024; // MB
static Base::Rect camera = { 0, 0, 1, 1, 0 };

Int32 main()
{
    using namespace Base;

    Allocator::Create(ALLOCATION_SIZE);

    if(!Window::Create("Base Window", Window::OutputType::Windowed, 1280, 720)) return 1; 
    if(!Window::SetGLContext(3, 3)) return 1;
    if(!Window::Show()) return 1;

    OpenGL::LoadProcedures();
    OpenGL::EnableErrorLog();

    Renderer2D::Create({ 1280, 720 }, 10);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    UInt32 texture = OpenGL::Texture::CreateWithFile("res/texture/sub_texture_atlas.png");
    Base::SubTexture plain = Renderer2D::CreateSubTexture({64, 64}, {0, 32}, {32, 32});

    Base::Sprite sprites[] = 
    {
        {0, 0, 128, 128, 0, 255, 255, 255, 255, plain}, 
        {0, 0, 128, 128, 0, 255, 255, 255, 255, plain}, 
    };

    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy)) break; 
        if(Window::GetKeyDown(Window::Key::Escape)) break;
        if(Window::GetEvent(Window::Event::Resize)) glViewport(0, 0, Window::GetWidth(), Window::GetHeight());        

        sprites[0].position = Renderer2D::WindowToWorldPoint(Window::GetMousePosition(), Window::GetSize(), camera);
        if(Window::GetMouseButton(Window::MouseButton::Left)) sprites[0].rotation += 0.4f;

        CollisionManifold manifold = Math::Collision::RectRectManifold(Graphics::Convert::SpriteToRect(sprites[0]), Graphics::Convert::SpriteToRect(sprites[1]));

        if(manifold.isCollision)
        {
            sprites[0].colour = {0, 0, 255, 255};
            sprites[1].colour = {0, 0, 255, 255};
            printf("%f, %f\n", manifold.normal[0], manifold.normal[1]);
        }
        else
        {
            sprites[0].colour = {255, 255, 255, 255};
            sprites[1].colour = {255, 255, 255, 255};
        }

        Renderer2D::BeginScene(Window::GetSize(), camera);
        Renderer2D::Draw(sprites, 2, texture, Base::CoordinateSpace::World, {0, 0});
        Renderer2D::EndScene();

        Window::SwapBuffer();
    }

    Renderer2D::Destroy();
    Window::Destroy();
    Allocator::Destroy();

    return 0;
}