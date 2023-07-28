#include "allocator/allocator.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "graphics/resource_manager.h"

const size_t ALLOCATOR_SIZE = 1000000; // 1 MB

int main()
{
    Allocator allocator;
    if(!allocator_create(&allocator, ALLOCATOR_SIZE))
        return 0;

    Window window;
    if(!window_create(&window, &allocator, "Base Window", 800, 600))
        return 0;

    Renderer renderer;
    if(!renderer_create(&renderer, &allocator, &window, 10))
        return 0;

    ResourceManager resource_manager;
    if(!resource_manager_create(&resource_manager, &allocator, 200, 2000))
        return 0;
    if(!resource_manager_load_shader(&resource_manager, "../../res/shader/vertex.vert", "../../res/shader/fragment.frag"))
        return 0;

    Quad quad_1;
    quad_1.position[0] = 0; quad_1.position[1] = 0;
    quad_1.size[0] = 50; quad_1.size[1] = 50;
    quad_1.rotation = 0;
    quad_1.color[0] = 1; quad_1.color[3] = 1;
    quad_1.layer = 0;

    Quad quad_2;
    quad_2.position[0] = 0; quad_2.position[1] = 0;
    quad_2.size[0] = 100; quad_2.size[1] = 100;
    quad_2.rotation = 0;
    quad_2.color[1] = 1; quad_2.color[3] = 0.5f;
    quad_2.layer = 0;

    Batch batch;
    if(!batch_create(&batch, &allocator, 10))
        return 0;
    if(!shader_create(&batch.shader, &renderer, resource_manager.vertex_buffer, resource_manager.fragment_buffer))
        return 0;
    if(!batch_push(&batch, &quad_1))
        return 0;
    if(!batch_push(&batch, &quad_2))
        return 0;
    
    

    while(!window_should_close(&window))
    {   
        window_poll_events(&window);
        renderer_clear(&renderer);
        renderer_draw(&renderer, &batch);
        window_swap_buffers(&window);
    }

    allocator_destroy(&allocator);
}