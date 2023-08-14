#pragma once

#include "struct.h"

float32 math_radians(const float32 degrees);

void math_mat4_identity(vec4* const mat);
void math_mat3_identity(vec3* const mat);
void math_mat2_identity(vec2* const mat);

void math_orthographic(vec4* const mat, float32 left, float32 right, float32 bottom, float32 top, float32 near_z, float32 far_z);

void math_mat4_transform_2d(vec4* const mat4, const vec2 translation, const vec2 scale, const float32 rotation);

void math_rotate_vec2_2d(float32* const vec, const float32 rotation);
