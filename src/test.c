#include "allocator/allocator.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "graphics/resource_manager.h"
#include "graphics/batch.h"
#include "graphics/camera.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#include "graphics/nuklear/nuklear.h"
#include "graphics/nuklear/nuklear_glfw_gl3.h"

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

    //
    // Nuklear
    //

    struct nk_glfw glfw = {0};
    struct nk_context *ctx;
    
    ctx = nk_glfw3_init(&glfw, window.ptr, NK_GLFW3_INSTALL_CALLBACKS);

    {
        struct nk_font_atlas *atlas;
        nk_glfw3_font_stash_begin(&glfw, &atlas);
        nk_glfw3_font_stash_end(&glfw);
    }

    //
    // Nuklear
    //

    while(!window_should_close(&window))
    {   
        window_poll_events(&window);
        renderer_clear(&renderer, &window, &camera);

        batch_clear(&batch);

        if (window_get_key(&window, WINDOW_KEY_W) == WINDOW_KEY_PRESS)        
            camera.position[1] += 2.0f;
        if (window_get_key(&window, WINDOW_KEY_S) == WINDOW_KEY_PRESS)        
            camera.position[1] -= 2.0f;
        if (window_get_key(&window, WINDOW_KEY_D) == WINDOW_KEY_PRESS)       
            camera.position[0] += 2.0f;       
        if (window_get_key(&window, WINDOW_KEY_A) == WINDOW_KEY_PRESS)       
            camera.position[0] -= 2.0f;
            
        if(!batch_push(&batch, &quad_1))
            return 0;
        if(!batch_push(&batch, &quad_2))
            return 0;

        if(!renderer_draw(&renderer, &camera, &batch))
            return 0;

        //
        // Nuklear
        //

        nk_glfw3_new_frame(&glfw);
 
        if (nk_begin(ctx, "Debug", nk_rect(50, 50, 230, 250),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {   
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_value_float(ctx, "Camera position x:", camera.position[0]);

            nk_layout_row_dynamic(ctx, 20, 1);
            nk_value_float(ctx, "Camera position y:", camera.position[1]);
        }
        nk_end(ctx);
        nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

        //
        // Nuklear
        //

        window_swap_buffers(&window);
    }

    //
    // Nuklear
    //

    nk_glfw3_shutdown(&glfw);

    //
    // Nuklear
    //

    renderer_destroy(&renderer);
    window_destroy(&window);
    allocator_destroy(&allocator);
}