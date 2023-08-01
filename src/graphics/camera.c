#include "graphics/camera.h"
#include "graphics/window.h"

int camera_create(Camera* const camera, const Window* const window)
{
    camera->position[0] = 0;
    camera->position[1] = 0;

    camera->scale[0] = 1;
    camera->scale[1] = 1;

    camera->rotation = 0;

    glm_mat4_identity(camera->view);
    glm_ortho(-window->w / 2, window->w / 2, -window->h / 2, window->h / 2, -1, 1, camera->projection);

    return 1;
}

int camera_set_view(Camera* const camera)
{
    glm_mat4_identity(camera->view);
    glm_scale(camera->view, (vec4){1 / camera->scale[0], 1/ camera->scale[1], 0, 0});
    glm_translate(camera->view, (vec4){-camera->position[0], -camera->position[1], 0, 0});
    glm_rotate(camera->view, -camera->rotation, (vec3){0.0f, 0.0f, 1.0f});
    
    return 1;
}

