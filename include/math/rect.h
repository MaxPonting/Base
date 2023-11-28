#pragma once

#include "math.h"
#include "vector.h"
#include "../array/static_array.h"

namespace Base::Math::Rectangle
{
    StaticArray<Vec2, 4> Vertices(const Rect rect)
    {
        StaticArray<Vec2, 4> vertices;

        vertices[0] = {rect.position[0] + rect.size[0] / 2, rect.position[1] + rect.size[1] / 2};
        vertices[1] = {rect.position[0] + rect.size[0] / 2, rect.position[1] - rect.size[1] / 2};
        vertices[2] = {rect.position[0] - rect.size[0] / 2, rect.position[1] + rect.size[1] / 2};
        vertices[3] = {rect.position[0] - rect.size[0] / 2, rect.position[1] - rect.size[1] / 2};

        if(rect.rotation == 0)
            return vertices;

        const Float32 rotation = F32::Radians(rect.rotation);
        const Float32 sin = sinf(rotation);
        const Float32 cos = cosf(rotation);

        for(Int32 i = 0; i < 4; i++)
            vertices[i] = Vector2F::RotateAroundPointCache(vertices[i], rect.position, sin, cos);

        return vertices;
    }
}  
