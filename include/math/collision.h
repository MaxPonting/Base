#pragma once

#include "struct.h"
#include "math.h"
#include "rect.h"
#include "vector.h"

#include <math.h>

namespace Base::Math::Collision
{
    Bool PointRect(const Vec2 point, const Rect rect)
    {
        if(point[0] < rect.position[0] - rect.size[0] / 2)
            return false;
        
        if(point[0] > rect.position[0] + rect.size[0] / 2)
            return false;

        if(point[1] < rect.position[1] - rect.size[1] / 2)
            return false;

        if(point[1] > rect.position[1] + rect.size[1] / 2)
            return false;

        return true;
    }

    Bool CheckRectProjection(const StaticArray<Vec2, 4> vertices, const Vec2 a, const Vec2 b)
    {
        auto AllNegative = [](const StaticArray<Float32, 4> projections) -> Bool
        {
            for(Int32 i = 0; i < 4; i++)
            {
                if(projections[i] >= 0)
                    return false;
            }

            return true;
        };

        auto AllGreater = [](const StaticArray<Float32, 4> projections, const Float32 magnitude) -> Bool
        {
            for(Int32 i = 0; i < 4; i++)
            {
                if(projections[i] <= magnitude)
                    return false;
            }

            return true;
        };

        const Float32 magnitude = Vector2F::Magnitude(Vector2F::LineSegment(a, b));
        StaticArray<Float32, 4> projections;
        for(Int32 i = 0; i < 4; i++)
            projections[i] = Vector2F::ProjectPointOnLineScalar(vertices[i], a, b);

        if(AllNegative(projections))
            return true;

        if(AllGreater(projections, magnitude))
            return true;

        return false;
    }

    Bool RectRectAxisUnaligned(const Rect a, const Rect b)
    {
        StaticArray<Vec2, 4> aVertices = Rectangle::Vertices(a);
        StaticArray<Vec2, 4> bVertices =  Rectangle::Vertices(b);

        if(CheckRectProjection(aVertices, bVertices[2], bVertices[0]))
            return false;

        if(CheckRectProjection(aVertices, bVertices[2], bVertices[3]))
            return false;

        if(CheckRectProjection(bVertices, aVertices[2], aVertices[0]))
            return false;

        if(CheckRectProjection(bVertices, aVertices[2], aVertices[3]))
            return false;

        return true;        
    }

    Bool RectRect(const Rect a, const Rect b)
    {
        if(a.rotation != 0 || b.rotation != 0)
            return RectRectAxisUnaligned(a, b);

        if(a.position[0] + a.size[0] / 2 < b.position[0] - b.size[0] / 2)
            return false;

        if(a.position[0] - a.size[0] / 2 > b.position[0] + b.size[0] / 2)
            return false;

        if(a.position[1] + a.size[1] / 2 < b.position[1] - b.size[1] / 2)
            return false;

        if(a.position[1] - a.size[1] / 2 > b.position[1] + b.size[1] / 2)
            return false;

        return true;
    }
}
