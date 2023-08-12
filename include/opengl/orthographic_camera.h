#pragma once

#include "../type/type.h"
#include "../vendor/cglm/cglm.h"

int32 orthographic_camera_calculate_view_2d(mat4 view, const vec2 position, const vec2 scale, const float32 rotation);
int32 orthographic_camera_calculate_projection_2d(mat4 projection, const int32 width, const int32 height);
int32 orthographic_camera_scale_view_2d(mat4 view, const vec2 native_resolution, const vec2 current_resolution);