#define BASE_DEBUG

#include <allocator/allocator.h>
#include <array/array.h>
#include <array/dynamic_array.h>
#include <log/log.h>
#include <math/math.h>
#include <opengl/opengl.h>
#include <window/window.h>

#include <stdio.h>

const static UInt64 ALLOCATION_SIZE = 1024 * 1024; // MB

Int32 main()
{
    using namespace Base;

    Allocator::Create(ALLOCATION_SIZE);

    if(!Window::Create("Base Window", 1280, 720))
        return 1;
        
    Window::Show();

    while(true)
    {
        Window::PollEvents();

        if(Window::GetEvent(Window::Event::Destroy))
            break; 

        Window::SwapBuffer();
    }

    Window::Destroy();
    
    Allocator::Destroy();

    printf("App qutting\n");

    return 0;
}
