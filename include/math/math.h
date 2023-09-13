#pragma once

#include "struct.h"

#include <math.h>

namespace Base::Math
{
    const Float32 PI = 3.14159265359f;

    Float32 Radians(const Float32 rotation)
    {
        return rotation * (PI / 180.0f);
    }

    void Mat4Identity(Mat4& mat)
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
    
    void Mat3Identity(Mat3& mat)
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

    void Mat2Identity(Mat2& mat)
    {
        mat[0][0] = 1;
        mat[0][1] = 0;

        mat[1][0] = 0;
        mat[1][1] = 1;
    }

    void Orthographic(Mat4& mat, const Float32 left, const Float32 right, const Float32 bottom, const Float32 top, const Float32 near_z, const Float32 far_z)
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

    void Mat4Transform2D(Mat4& mat4, const Vec2 translation, const Vec2 scale, const Float32 rotation)
    {
        mat4[3][0] = translation[0]; 
        mat4[3][1] = translation[1]; 

        const Float32 cos = cosf(rotation);
        const Float32 sin = sinf(rotation);

        mat4[0][0] = scale[0] * cos;
        mat4[1][0] = scale[0] * -sin;
        mat4[0][1] = scale[1] * sin;
        mat4[1][1] = scale[1] * cos;
    }

    void Vec2Rotate2D(Vec2& vec, const Float32 rotation)
    {
        const Float32 cos = cosf(rotation);
        const Float32 sin = sinf(rotation);

        const Float32 x = vec[0];
        const Float32 y = vec[1];
    
        vec[0] = cos * x - sin * y;
        vec[1] = sin * x + cos * y;
    }
}

