#include "graphics/camera.h"
#include "graphics/window.h"

int camera_create(Camera* const camera, const Window* const window, const vec2 native_resolution)
{
    camera->position[0] = 0;
    camera->position[1] = 0;

    camera->scale[0] = 1;
    camera->scale[1] = 1;

    camera->rotation = 0;

    camera->native_resolution[0] = native_resolution[0];
    camera->native_resolution[1] = native_resolution[1];

    glm_mat4_identity(camera->view);
    glm_ortho(-window->w / 2, window->w / 2, -window->h / 2, window->h / 2, -1, 1, camera->projection);

    return 1;
}

int camera_set_view(Camera* const camera, const vec2 window_resolution)
{
    const float scale_x = camera->native_resolution[0] / window_resolution[0];
    const float scale_y = camera->native_resolution[1] / window_resolution[1];

    float scale = scale_x;
    if (scale_y > scale_x)
        scale = scale_y;

    glm_mat4_identity(camera->view);
    glm_scale(camera->view, (vec4){1 / (camera->scale[0] * scale), 1 / (camera->scale[1] * scale), 0, 0});
    glm_translate(camera->view, (vec4){-camera->position[0], -camera->position[1], 0, 0});
    glm_rotate(camera->view, -camera->rotation, (vec3){0.0f, 0.0f, 1.0f});
    
    return 1;
}

