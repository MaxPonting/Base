#include "allocator/allocator.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "graphics/resource_manager.h"
#include "graphics/batch.h"
#include "graphics/camera.h"

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

    Camera camera;
    if(!camera_create(&camera, &window))
        return 0;

    ResourceManager resource_manager;
    if(!resource_manager_create(&resource_manager, &allocator, 200, 2000))
        return 0;
    if(!resource_manager_load_shader(&resource_manager, "../../res/shader/vertex.vert", "../../res/shader/fragment.frag"))
        return 0;

    Quad quad_1;
    quad_create(&quad_1);
    quad_1.position[0] = -350; quad_1.position[1] = 0;
    quad_1.size[0] = 20; quad_1.size[1] = 100;

    Quad quad_2;
    quad_create(&quad_2);
    quad_2.position[0] = 350; quad_2.position[1] = 0;
    quad_2.size[0] = 20; quad_2.size[1] = 100;

    Batch batch;
    if(!batch_create(&batch, &allocator, 10))
        return 0;
    if(!shader_create(&batch.shader, &renderer, resource_manager.vertex_buffer, resource_manager.fragment_buffer))
        return 0;
    
    while(!window_should_close(&window))
    {   
        window_poll_events(&window);
        renderer_clear(&renderer, &window, &camera);

        batch_clear(&batch);

        if (window_get_key(&window, WINDOW_KEY_W) == WINDOW_KEY_PRESS)
        {
            camera.position[1] += 2.0f;
        }
        if (window_get_key(&window, WINDOW_KEY_S) == WINDOW_KEY_PRESS)
        {
            camera.position[1] -= 2.0f;
        }
        if (window_get_key(&window, WINDOW_KEY_D) == WINDOW_KEY_PRESS)
        {
            camera.position[0] += 2.0f;
        }
        if (window_get_key(&window, WINDOW_KEY_A) == WINDOW_KEY_PRESS)
        {
            camera.position[0] -= 2.0f;
        }
        if (window_get_key(&window, WINDOW_KEY_SPACE) == WINDOW_KEY_PRESS)
        {
            camera.scale[0] += 0.02f;
            camera.scale[1] += 0.02f;
        }
        if (window_get_key(&window, WINDOW_KEY_BACKSPACE) == WINDOW_KEY_PRESS)
        {
            camera.scale[0] -= 0.02f;
            camera.scale[1] -= 0.02f;
        }
        if (window_get_key(&window, WINDOW_KEY_Q) == WINDOW_KEY_PRESS)
        {
            camera.rotation += 0.04f;
        }
        if (window_get_key(&window, WINDOW_KEY_E) == WINDOW_KEY_PRESS)
        {
            camera.rotation -= 0.04f;
        }
            
        if(!batch_push(&batch, &quad_1))
            return 0;
        if(!batch_push(&batch, &quad_2))
            return 0;

        if(!renderer_draw(&renderer, &camera, &batch))
            return 0;

        window_swap_buffers(&window);
    }

    allocator_destroy(&allocator);
}