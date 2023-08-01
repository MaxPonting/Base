#pragma once

#include "cglm/struct.h"

typedef struct Window Window;

typedef struct Camera
{   
    float rotation;
    vec2 position, scale;
    mat4 view, projection;
} Camera;

int camera_create(Camera* const camera, const Window* const window);
int camera_set_view(Camera* const camera);
