#pragma once

#include "../allocator/allocator.h"
#include "../array/array.h"
#include "../array/smart_array.h"
#include "cglm/struct.h"
#include "window.h"
#include "shader.h"
#include "camera.h"

typedef enum RendererType { RENDERER_TYPE_NULL, RENDERER_TYPE_OPENGL } RendererType;

typedef struct Renderer
{   
    RendererType type;

    unsigned int vertex_array_id;
    unsigned int vertex_buffer_id;
    unsigned int index_buffer_id;

    unsigned int last_shader_id;

    unsigned int quad_count;
    unsigned int shader_swap_count;
} Renderer;

int renderer_create(Renderer* const renderer, Allocator* const allocator, Window const window);
int renderer_destroy(Renderer* const renderer);
int renderer_clear(Renderer* const renderer, Window* const window, Camera* const camera);
int renderer_present(Renderer* const renderer, Camera* const camera);

int renderer_draw(
    Renderer* const renderer, 
    Camera* const camera, 
    const vec2 position, 
    const vec2 size, 
    const float rotation,
    const vec4 color,
    const Shader shader
);