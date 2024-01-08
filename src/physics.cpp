#define BASE_DEBUG

#include <allocator/allocator.h>
#include <log/log.h>
#include <io/file.h>
#include <math/math.h>
#include <math/collision2D.h>
#include <math/physics2D.h>
#include <math/convert.h>
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
const static Float32 MOVE_FORCE = 10;
const static Float32 FRICTION = 0.005f;
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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    UInt32 texture = OpenGL::Texture::CreateWithFile("res/texture/collider.png");
    Base::SubTexture plain = Renderer2D::CreateSubTexture({128, 128}, {0, 0}, {128, 128});

    Sprite sprites[] = 
    {
        {0, 0, 64, 64, 0, 255, 255, 255, 255, plain}, 
        {0, 0, 64, 64, 0, 255, 255, 255, 255, plain},
        {0, 0, 16, 16, 0, 0, 255, 0, 255, plain},
        {0, 0, 16, 16, 0, 0, 255, 0, 255, plain}
    };

    RigidBody2D bodies[] = 
    {
        Base::Math::Physics2D::CreateBody({-400, 0}, 0, 30, 34100, 0.25, false),
        Base::Math::Physics2D::CreateBody({0, 0}   , 0, 30, 34100, 0.25, true)
    };


    //bodies[0] = Math::Physics2D::AddForce(bodies[0], {10, 0});
    //bodies[1] = Math::Physics2D::AddForce(bodies[1], {-500, 0});

    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy)) break; 
        if(Window::GetKeyDown(Window::Key::Escape)) break;
        if(Window::GetEvent(Window::Event::Resize)) glViewport(0, 0, Window::GetWidth(), Window::GetHeight());        

        if(Window::GetKey(Window::Key::W)) bodies[0] = Math::Physics2D::AddForce(bodies[0], {0, MOVE_FORCE});
        if(Window::GetKey(Window::Key::S)) bodies[0] = Math::Physics2D::AddForce(bodies[0], {0, -MOVE_FORCE});
        if(Window::GetKey(Window::Key::D)) bodies[0] = Math::Physics2D::AddForce(bodies[0], {MOVE_FORCE, 0});
        if(Window::GetKey(Window::Key::A)) bodies[0] = Math::Physics2D::AddForce(bodies[0], {-MOVE_FORCE, 0});
        if(Window::GetKey(Window::Key::E)) bodies[0] = Math::Physics2D::AddTorque(bodies[0], 10);

        bodies[0] = Math::Physics2D::Step(bodies[0], FRICTION);
        bodies[1] = Math::Physics2D::Step(bodies[1], FRICTION);

        CollisionManifold2D manifold = Math::Collision2D::RectRectManifold(Math::Convert::RigidBody2DToRect(bodies[1], {64, 64}), 
            Math::Convert::RigidBody2DToRect(bodies[0], { 64, 64 }));

        if(manifold.isCollision)
        {
            CollisionResolution2D resolution2D = Math::Physics2D::ResolveCollision(manifold, bodies[0], bodies[1]);
            resolution2D = Math::Physics2D::ResolveImpulse(manifold, resolution2D.a, resolution2D.b);
            bodies[0] = resolution2D.a;
            bodies[1] = resolution2D.b;
            //sprites[0].colour = { 255, 0, 0, 255 };
            //sprites[1].colour = { 255, 0, 0, 255 };
            //break;
        }
        else
        {
            sprites[0].colour = { 255, 255, 255, 255 };
            sprites[1].colour = { 255, 255, 255, 255 };
        }

        sprites[0].position = bodies[0].position;
        sprites[1].position = bodies[1].position;
        sprites[0].rotation = bodies[0].rotation;
        sprites[1].rotation = bodies[1].rotation;

        sprites[2].position = manifold.contactPoints[0]; 
        sprites[3].position = manifold.contactPoints[1];

        Renderer2D::BeginScene(Window::GetSize(), camera);
        Renderer2D::Draw(sprites, 2, texture, Base::CoordinateSpace::World, {0, 0});
        if(manifold.isCollision)
            Renderer2D::Draw(&sprites[2], 0, 0, Base::CoordinateSpace::World, {0, 0});
        Renderer2D::EndScene();

        Window::SwapBuffer();
    }

    Renderer2D::Destroy();
    Window::Destroy();
    Allocator::Destroy();

    return 0;
}

