#include "allocator/allocator.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "graphics/camera.h"
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

    Camera camera;
    if(!camera_create(&camera, (vec2){640, 360}))
        return 0;
    
    while(!window_should_close())
    {
        window_poll_events();

        if(!renderer_start(camera))
            return 1;

        if(!renderer_draw_quad((vec2){0, 0}, (vec2){200, 200}, 0, (vec4){1.0f, 0.0f, 1.0f, 1.0f}))
            return 1;
        
        if(!renderer_end())
            return 1;

        window_swap_buffer();
    }

    shader_destroy(&shader);
    renderer_destroy();
    window_destroy();
    allocator_destroy();
}