#include "allocator/allocator.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "graphics/resource_manager.h"
#include "graphics/camera.h"

//
// Nuklear
//

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

//
// Nuklear
//

const size_t ALLOCATOR_SIZE = 1000000; // 1 MB
const int QUAD_COUNT = 20;

#include <time.h>

int main()
{   
    Allocator allocator;
    if(!allocator_create(&allocator, ALLOCATOR_SIZE))
        return 0;

    Window window;
    if(!window_create(&window, &allocator, "Base Window", 1920, 1080))
        return 0;
    if(!window_vsync(&window, 1))
        return 0;

    Renderer renderer;
    if(!renderer_create(&renderer, &allocator, window))
        return 0;

    Camera camera;
    if(!camera_create(&camera, &window, (vec2){640, 360}))
        return 0;

    Texture texture;
    texture_create(&texture, renderer, "../../res/texture/sub_texture_atlas.png", 32, 32);

    SubTexture texture_plain;
    sub_texture_create(&texture_plain, &texture, (vec2){0, 1}, (vec2){32, 32});

    SubTexture texture_forest;
    sub_texture_create(&texture_forest, &texture, (vec2){0, 0}, (vec2){32, 32});

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

        if (window_get_key(&window, WINDOW_KEY_W) == WINDOW_KEY_PRESS)        
            camera.position[1] += 200.0f * renderer.render_time_s;
        if (window_get_key(&window, WINDOW_KEY_S) == WINDOW_KEY_PRESS)        
            camera.position[1] -= 200.0f * renderer.render_time_s;
        if (window_get_key(&window, WINDOW_KEY_D) == WINDOW_KEY_PRESS)       
            camera.position[0] += 200.0f * renderer.render_time_s;
        if (window_get_key(&window, WINDOW_KEY_A) == WINDOW_KEY_PRESS)       
            camera.position[0] -= 200.0f * renderer.render_time_s;
        if (window_get_key(&window, WINDOW_KEY_SPACE) == WINDOW_KEY_PRESS)    
        {
            camera.scale[0] += 1.0f * renderer.render_time_s;     
            camera.scale[1] += 1.0f * renderer.render_time_s;     
        }   
        if (window_get_key(&window, WINDOW_KEY_BACKSPACE) == WINDOW_KEY_PRESS)       
        {
            camera.scale[0] -= 1.0f * renderer.render_time_s;
            camera.scale[1] -= 1.0f * renderer.render_time_s;
        }

        if(!renderer_draw_texture(&renderer, &camera, (vec2){-64, 0}, (vec2){32, 32}, 0, (vec4){1, 1, 1, 1}, texture_forest))
            return 0;

        if(!renderer_draw_texture(&renderer, &camera, (vec2){0, 0}, (vec2){32, 32}, 0, (vec4){1, 1, 1, 1}, texture_plain))
            return 0;

        if(!renderer_draw_texture(&renderer, &camera, (vec2){-320, 0}, (vec2){32, 32}, 0, (vec4){1, 1, 1, 1}, texture_plain))
            return 0;
        
        //
        // Nuklear
        //

        int window_width = window.w;
        int window_height = window.h;

        nk_glfw3_new_frame(&glfw);
        if (nk_begin(ctx, "Debug", nk_rect(50, 50, 230, 300),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {   
            nk_layout_row_dynamic(ctx, 15, 1);
            nk_label(ctx, "Renderer Profiling", NK_TEXT_CENTERED);
            nk_layout_row_dynamic(ctx, 15, 1);
            nk_value_float(ctx, "FPS", 1 / renderer.render_time_s);
            nk_layout_row_dynamic(ctx, 15, 1);
            nk_value_float(ctx, "Render Time(ms)", renderer.render_time_s * 1000);
            nk_layout_row_dynamic(ctx, 15, 1);
            nk_value_float(ctx, "Quads Drawn", renderer.quad_count);
            nk_layout_row_dynamic(ctx, 15, 1);
            nk_value_float(ctx, "Shader Swaps", renderer.shader_swap_count);
            nk_layout_row_dynamic(ctx, 15, 1);

            nk_label(ctx, "Window", NK_TEXT_CENTERED);
            nk_layout_row_dynamic(ctx, 15, 1);
            nk_property_int(ctx, "Width", 320, &window_width, 2400, 8, 8);
            nk_layout_row_dynamic(ctx, 15, 1);
            nk_property_int(ctx, "Height", 180, &window_height, 1200, 8, 8);
        }
        nk_end(ctx);
        nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

        //
        // Nuklear
        //

        window_swap_buffers(&window);
        window_set_size(&window, window_width, window_height);
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