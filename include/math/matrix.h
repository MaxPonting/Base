#pragma once

#include "math.h"

namespace Base::Math::Matrix4
{
    Mat4 Identity()
    {
        Mat4 mat;

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

        return mat;
    }

    Mat4 Orthographic(const Float32 left, const Float32 right, const Float32 bottom, const Float32 top, const Float32 near_z, const Float32 far_z)
    {
        Mat4 mat;

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

        return mat;
    }

    Mat4 Transform2D(const Vec2 translation, const Vec2 scale, const Float32 rotation)
    {
        Mat4 mat = Identity();

        mat[3][0] = translation[0]; 
        mat[3][1] = translation[1]; 

        const Float32 cos = cosf(rotation);
        const Float32 sin = sinf(rotation);

        mat[0][0] = scale[0] * cos;
        mat[1][0] = scale[0] * -sin;
        mat[0][1] = scale[1] * sin;
        mat[1][1] = scale[1] * cos;

        return mat;
    }

}

namespace Base::Math::Matrix3
{
    Mat3 Identity()
    {
        Mat3 mat;

        mat[0][0] = 1;
        mat[0][1] = 0;
        mat[0][2] = 0;

        mat[1][0] = 0;
        mat[1][1] = 1;
        mat[1][2] = 0;

        mat[2][0] = 0;
        mat[2][1] = 0;
        mat[2][2] = 1;

        return mat;
    }
}

namespace Base::Math::Matrix2
{
    Mat2 Identity()
    {
        Mat2 mat;

        mat[0][0] = 1;
        mat[0][1] = 0;

        mat[1][0] = 0;
        mat[1][1] = 1;

        return mat;
    }

}
