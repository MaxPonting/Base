#pragma once

#include "struct.h"

namespace Base::Math
{
    const Float32 PI = 3.14159265359f;

    Float32 Radians(const Float32 rotation);

    void Mat4Identity(Mat4& mat);
    void Mat3Identity(Mat3& mat);
    void Mat2Identity(Mat2& mat);

    void Orthographic(Mat4& mat, const Float32 left, const Float32 right, const Float32 bottom, const Float32 top, const Float32 near_z, const Float32 far_z);

    void Mat4Transform2D(Mat4& mat, const Vec2 translation, const Vec2 scale, const Float32 rotation);

    void Vec2Rotate2D(Vec2& vec, const Float32 rotation);
}

