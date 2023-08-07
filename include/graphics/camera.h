#pragma once

#include "../vendor/cglm/struct.h"
#include "../type/type.h"

typedef struct
{
    vec2 position;
    vec2 scale;
    float rotation;
    vec2 native_resolution;
} Camera;

int32 camera_create(Camera* const camera, const vec2 native_resolution); 