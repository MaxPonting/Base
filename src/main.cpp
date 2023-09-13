#define DEBUG

#include <allocator/allocator.h>
#include <array/array.h>
#include <array/dynamic_array.h>
#include <log/log.h>
#include <math/math.h>
#include <window/window.h>

#include <stdio.h>

const static UInt64 ALLOCATION_SIZE = 1024 * 1024; // MB

static bool running = true;

Int32 main()
{
    using namespace Base;

    Allocator::Create(ALLOCATION_SIZE);

    Window::Create("Base Window", 1280, 720);
    Window::SetGLContext();
    Window::Show();

    while(running)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy))
            running = false;

        if(Window::GetEvent(Window::Event::SpaceKeyDown))
           Log::Print("Key Down", Log::Type::Message, __LINE__, __FILE__); 

        if(Window::GetEvent(Window::Event::SpaceKeyUp))
           Log::Print("Key Up", Log::Type::Message, __LINE__, __FILE__); 

        Window::SwapBuffer();
    }

    Window::Destroy();
    
    Allocator::Destroy();

    return 0;
}
