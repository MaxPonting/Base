#define BASE_DEBUG

#include <allocator/allocator.h>
#include <log/log.h>
#include <math/math.h>
#include <math/collision2D.h>
#include <math/physics2D.h>
#include <math/convert.h>
#include <opengl/opengl.h>
#include <opengl/shader.h>
#include <opengl/program.h>
#include <opengl/texture.h>
#include <window/window.h>
#include <graphics/renderer2D.h>
#include <graphics/convert.h>

#include <stdio.h>

const static UInt64 ALLOCATION_SIZE = 1024 * 1024; // MB
const static Float32 FRICTION = 0.000f;
static Base::Rect camera = { 0, 0, 1, 1, 0 };

Base::SubTexture plain = Base::Renderer2D::CreateSubTexture({128, 128}, {0, 0}, {128, 128});
static Base::Array<Base::Sprite, 2> rectSprites = 
{
    { 0, 0, 64, 64, 0, 255, 255, 255, 255, plain }, 
    { 0, 0, 1024, 128, 0, 0, 255, 0, 255, plain }
};

static Base::Array<Base::RigidBody2D, 2> bodies = 
{
    Base::Math::Physics2D::CreateBody({0, 300}, 0, 30, 34100, 0.25, 0.1f, false),
    Base::Math::Physics2D::CreateBody({0, -200}   , 0, 30, 34100, 0.25, 0.1f, true)
};

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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy)) break; 
        if(Window::GetKeyDown(Window::Key::Escape)) break;
        if(Window::GetEvent(Window::Event::Resize)) glViewport(0, 0, Window::GetWidth(), Window::GetHeight());        

        for(Int32 i = 0; i < bodies.count; i++) 
        {
            bodies[i] = Math::Physics2D::Step(bodies[i], FRICTION);
        }

        for(Int32 i = 0; i < bodies.count; i++)
        {
            for(Int32 j = 0; j < bodies.count; j++)
            {
                if(i == j) continue;

                CollisionManifold2D manifold = Math::Collision2D::RectRectManifold(
                    Math::Convert::RigidBody2DToRect(bodies[i], rectSprites[j].size), 
                    Math::Convert::RigidBody2DToRect(bodies[j], rectSprites[j].size));

                if(!manifold.isCollision) continue;

                printf("%d, %d\n", i, j);

                CollisionResolution2D resolution2D = Math::Physics2D::ResolveCollision(manifold, bodies[i], bodies[j]);
                resolution2D = Math::Physics2D::ResolveImpulse(manifold, resolution2D.a, resolution2D.b);
                bodies[i] = resolution2D.a;
                bodies[j] = resolution2D.b;
            }
        }

        printf("\n");

        for(Int32 i = 0; i < rectSprites.count; i++)
        {
            rectSprites[i].position = bodies[i].position;
            rectSprites[i].rotation = bodies[i].rotation;
        }

        Renderer2D::BeginScene(Window::GetSize(), camera);
        Renderer2D::Draw(rectSprites.memory, 2, 0, Base::CoordinateSpace::World, {0, 0});
        Renderer2D::EndScene();

        Window::SwapBuffer();
    }

    Renderer2D::Destroy();
    Window::Destroy();
    Allocator::Destroy();

    return 0;
}

