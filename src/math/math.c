#include "math/math.h"
#include <math.h>

static const float32 PI = 3.14159265359f;

float32 math_radians(float32 degree)
{
    return degree * (PI / 180.0f);
}

void math_mat4_identity(vec4* const mat)
{
    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[0][3] = 0;

    mat[1][0] = 0;
    mat[1][1] = 1;
    mat[1][2] = 0;
    mat[1][3] = 0;

    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;
    mat[2][3] = 0;

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
}

void math_mat3_identity(vec3* const mat)
{
    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = 0;

    mat[1][0] = 0;
    mat[1][1] = 1;
    mat[1][2] = 0;

    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;
}

void math_mat2_identity(vec2* const mat)
{
    mat[0][0] = 1;
    mat[0][1] = 0;

    mat[1][0] = 0;
    mat[1][1] = 1;
}

void math_orthographic(vec4* const mat, float32 left, float32 right, float32 bottom, float32 top, float32 near_z, float32 far_z)
{
    mat[0][0] = 2 / (right - left);
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[0][3] = -(right + left) / (right - left);

    mat[1][0] = 0;
    mat[1][1] = 2 / (top - bottom);
    mat[1][2] = 0;
    mat[1][3] = -(top + bottom) / (top - bottom);

    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = -2 / (far_z - near_z);
    mat[2][3] = -(far_z + near_z) / (far_z - near_z);

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
}

void math_mat4_transform_2d(vec4* const mat4, const vec2 translation, const vec2 scale, const float32 rotation)
{
    mat4[3][0] = translation[0]; 
    mat4[3][1] = translation[1]; 

    const float32 cos = cosf(rotation);
    const float32 sin = sinf(rotation);

    mat4[0][0] = scale[0] * cos;
    mat4[1][0] = scale[0] * -sin;
    mat4[0][1] = scale[1] * sin;
    mat4[1][1] = scale[1] * cos;
}

void math_rotate_vec2_2d(float32* const vec, const float32 rotation)
{
    const float32 cos = cosf(rotation);
    const float32 sin = sinf(rotation);
    
    const float32 x = vec[0];
    const float32 y = vec[1];
    
    vec[0] = cos * x - sin * y;
    vec[1] = sin * x + cos * y;
}
