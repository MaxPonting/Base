#pragma once

#include "../type/type.h"

typedef Float32 Vec2[2];
typedef Float32 Vec3[3];
typedef Float32 Vec4[4];

typedef Int32 IVec2[2];
typedef Int32 IVec3[3];
typedef Int32 IVec4[4];

typedef Vec2 Mat2[2];
typedef Vec3 Mat3[3];
typedef Vec4 Mat4[4];

struct Quad
{
    Vec2 position;
    Vec2 size;
};