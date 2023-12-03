#pragma once

#include "struct.h"
#include "vector.h"

namespace Base::Math::Polygon
{
    Vec2 FurthestPoint(const Poly polygon, const Vec2 direction)
    {
        Int32 maxPointIndex = 0;
        Float32 maxDistance = Vector2F::DotProduct(polygon.vertices[0], direction);

        for(Int32 i = 1; i < polygon.count; i++)
        {
            Float32 distance = Vector2F::DotProduct(polygon.vertices[i], direction);
            if(distance <= maxDistance)
                continue;

            maxDistance = distance;
            maxPointIndex = i;
        }

        return polygon.vertices[maxPointIndex];
    }
}