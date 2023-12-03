#pragma once

#include "struct.h"
#include "vector.h"

namespace Base::Math::Polygon
{
    Vec2 FurthestPoint(const Poly polygon, const Vec2 direction)
    {
        Vec2 maxPoint;
        Float32 maxDistance;

        for(Int32 i = 0; i < polygon.count; i++)
        {
            Float32 distance = Vector2F::DotProduct(polygon.vertices[i], direction);
            if(distance <= maxDistance)
                continue;

            maxDistance = distance;
            maxPoint = polygon.vertices[i];
        }

        return maxPoint;
    }
}