#pragma once

#include "struct.h"
#include "math.h"
#include "rect.h"
#include "vector.h"
#include "polygon.h"

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

    Bool CheckRectProjection(const Array<Vec2, 4> vertices, const Vec2 a, const Vec2 b)
    {
        auto AllNegative = [](const Array<Float32, 4> projections) -> Bool
        {
            for(Int32 i = 0; i < 4; i++)
            {
                if(projections[i] >= 0)
                    return false;
            }

            return true;
        };

        auto AllGreater = [](const Array<Float32, 4> projections, const Float32 magnitude) -> Bool
        {
            for(Int32 i = 0; i < 4; i++)
            {
                if(projections[i] <= magnitude)
                    return false;
            }

            return true;
        };

        const Float32 magnitude = Vector2F::Magnitude(Vector2F::LineSegment(a, b));
        Array<Float32, 4> projections;
        for(Int32 i = 0; i < 4; i++)
            projections[i] = Vector2F::ProjectPointOnLineScalar(vertices[i], a, b);

        if(AllNegative(projections))
            return true;

        if(AllGreater(projections, magnitude))
            return true;

        return false;
    }

    Bool RectRectUnaligned(const Rect a, const Rect b)
    {
        Array<Vec2, 4> aVertices = Rectangle::Vertices(a);
        Array<Vec2, 4> bVertices =  Rectangle::Vertices(b);

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
            return RectRectUnaligned(a, b);

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

    CollisionManifold PolygonPolygonManifold(const Poly a, const Poly b)
    {
        CollisionManifold manifold;
        manifold.isCollision = false;

        Vec2 support = Polygon::FurthestPoint(a, {1, 0}) - Polygon::FurthestPoint(b, {-1, 0});

        Array<Vec2, 3> simplex;
        simplex.Push(support);

        Vec2 direction = -support;

        while(true)
        {
            support = Polygon::FurthestPoint(a, direction) - Polygon::FurthestPoint(b, -direction);

            if(Vector2F::DotProduct(support, direction) <= 0)
                return manifold;

            simplex.Push(support);

            switch(simplex.count)
            {
                case 2: 
                {
                    Vec2 ab = simplex[1] - simplex[0];
                    Vec2 ao = -simplex[0];
                    break;
                }
                case 3: 
                {
                    break;
                }
            }
        }

        return manifold;
    }

    CollisionManifold RectRectManifold(const Rect a, const Rect b)
    {
        Array<Vec2, 4> aVertices = Rectangle::Vertices(a);
        Array<Vec2, 4> bVertices = Rectangle::Vertices(b);
        return PolygonPolygonManifold({aVertices.memory, 4}, {bVertices.memory, 4});
    }

}
