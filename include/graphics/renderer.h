#pragma once

#include "../allocator/allocator.h"
#include "cglm/struct.h"
#include "window.h"
#include "quad.h"
#include "shader.h"
#include "batch.h"
#include "camera.h"

typedef struct
{
    float position[2];
    float color[4];
} Vertex;

typedef enum RendererType { RENDERER_TYPE_NULL, RENDERER_TYPE_OPENGL } RendererType;

typedef struct Renderer
{
    unsigned int vertex_array_id, vertex_buffer_id, index_buffer_id;
    int max_quads_per_draw;
    RendererType type;
    Vertex* vertices;
} Renderer;

int renderer_create(Renderer* const renderer, Allocator* const allocator, const Window* const window, const int max_quads_per_draw);
int renderer_destroy(Renderer* const renderer);
int renderer_clear(Renderer* const renderer, Window* const window, Camera* const camera);
int renderer_draw(Renderer* const renderer, Camera* const camera, Batch* const batch);