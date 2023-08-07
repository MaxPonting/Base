#include "graphics/camera.h"

int32 camera_create(Camera* const camera, const vec2 native_resolution)
{
    camera->position[0] = 0;
    camera->position[1] = 0;

    camera->scale[0] = 0;
    camera->scale[1] = 0;

    camera->rotation = 0;

    camera->native_resolution[0] = native_resolution[0];
    camera->native_resolution[1] = native_resolution[1];

    return 1;
} 