#include "allocator/allocator.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "file/file.h"

#include <stdio.h>

static const uint64 ALLOCATOR_SIZE = 1000000; // 1 MB

int main()
{   
    if(!allocator_create(ALLOCATOR_SIZE))
        return 1;

    if(!window_create(1920, 1080, "Base Window"))
        return 1;
    
    if(!renderer_create())
        return 1;
        
    Shader shader;
    {
        char vertex_source[1000];
        char fragment_source[1000];

        if(!file_read("../../res/shader/colour.vert", vertex_source, 1000))
            return 1;
        if(!file_read("../../res/shader/colour.frag", fragment_source, 1000))
            return 1; 

        if(!shader_create(&shader, vertex_source, fragment_source))
            return 1;
    }
    
    while(!window_should_close())
    {
        window_poll_events();

        renderer_start();
        
        // Render

        renderer_end();

        window_swap_buffer();
    }

    shader_destroy(&shader);
    renderer_destroy();
    window_destroy();
    allocator_destroy();
}