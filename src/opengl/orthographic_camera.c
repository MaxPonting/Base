#include "opengl/orthographic_camera.h"

int32 orthographic_camera_calculate_view_2d(mat4 view, const vec2 position, const vec2 scale, const float32 rotation)
{
    glm_mat4_identity(view);
    glm_translate(view, (vec3){-position[0], -position[1], 0});
    glm_rotate(view, -rotation, (vec3){0.0, 0.0, 1.0});
    glm_scale(view, (vec3){1 / scale[0], 1 / scale[1], 1});

    return 1;
}

int32 orthographic_camera_calculate_projection_2d(mat4 projection, const int32 width, const int32 height)
{
    glm_mat4_identity(projection);
    glm_ortho(-width / 2, width / 2, -height / 2, height / 2, -1, 1, projection);

    return 1;
}

int32 orthographic_camera_scale_view_2d(mat4 view, const vec2 native_resolution, const vec2 current_resolution)
{
    float32 scale = current_resolution[0] / native_resolution[0];
    if (scale > current_resolution[1] / native_resolution[1])
        scale = current_resolution[1] / native_resolution[1];

    glm_scale(view, (vec3){scale, scale, 1});

    return 1;
}