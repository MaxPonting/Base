#pragma once

#include "cglm/struct.h"

typedef struct Window Window;

typedef struct Camera
{   
    float rotation;
    vec2 position, scale;
    mat4 view, projection;
    vec2 native_resolution;
} Camera;

int camera_create(Camera* const camera, const Window* const window, const vec2 native_resolution);
int camera_set_view(Camera* const camera, const vec2 window_resolution);
