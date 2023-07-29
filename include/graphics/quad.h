#pragma once

#include "cglm/struct.h"

typedef struct
{   
    vec4 color;
    vec3 rotation;
    vec2 position, size;
} Quad;

int quad_create(Quad* const quad);