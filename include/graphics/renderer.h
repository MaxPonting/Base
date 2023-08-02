#pragma once

#include "../allocator/allocator.h"
#include "../array/array.h"
#include "../array/smart_array.h"
#include "cglm/struct.h"
#include "window.h"
#include "shader.h"
#include "texture.h"
#include "sub_texture.h"
#include "camera.h"

typedef enum RendererType { RENDERER_TYPE_NULL, RENDERER_TYPE_OPENGL } RendererType;

typedef struct Renderer
{   
    RendererType type;

    unsigned int vertex_array_id;
    unsigned int vertex_buffer_id;
    unsigned int index_buffer_id;

    Shader shader_color;
    Shader shader_texture;

    unsigned int last_shader_id;

    double render_time_s;
    unsigned int quad_count;
    unsigned int shader_swap_count;
} Renderer;

int renderer_create(Renderer* const renderer, Allocator* const allocator, Window const window);
int renderer_destroy(Renderer* const renderer);
int renderer_clear(Renderer* const renderer, Window* const window, Camera* const camera);
int renderer_present(Renderer* const renderer, Camera* const camera);

int renderer_draw_color(
    Renderer* const renderer, 
    Camera* const camera, 
    const vec2 position, 
    const vec2 size, 
    const float rotation,
    const vec4 color
);

int renderer_draw_texture(
    Renderer* const renderer, 
    Camera* const camera, 
    const vec2 position, 
    const vec2 size, 
    const float rotation,
    const vec4 color,
    const SubTexture sub_texture
);

int renderer_set_native_resolution(Renderer* const renderer, const vec2 resolution);