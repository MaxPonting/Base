#pragma once

#include "struct.h"
#include "math.h"
#include "rect.h"
#include "vector.h"
#include "polygon.h"

#include <vector>

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

    GJK2DManifold GJK2D(const Poly a, const Poly b)
    {
        GJK2DManifold manifold;
        manifold.isCollision = false;

        Vec2 support = Polygon::FurthestPoint(a, {1, 0}) - Polygon::FurthestPoint(b, {-1, 0});

        Array<Vec2, 3> simplex;
        simplex.Push(support);

        Vec2 direction = -support;

        while(true)
        {
            support = Polygon::FurthestPoint(a, direction) - Polygon::FurthestPoint(b, -direction);

            if(Vector2F::DotProduct(support, direction) < 0) return manifold;

            simplex.Push(support);

            switch(simplex.count)
            {
                case 2: 
                {
                    const Vec2 cb = simplex[1] - simplex[0];
                    const Vec2 co = -simplex[0];
                    direction = Vector2F::TripleCrossProduct(cb, co, cb);
                    break;
                }
                case 3: 
                {
                    const Vec2 ab = simplex[1] - simplex[2];
                    const Vec2 ac = simplex[0] - simplex[2];
                    const Vec2 ao = -simplex[2];
                    const Vec2 abPerpendicular = Vector2F::TripleCrossProduct(ac, ab, ab);
                    const Vec2 acPerpendicular = Vector2F::TripleCrossProduct(ab, ac, ac);

                    if(Vector2F::DotProduct(abPerpendicular, ao) > 0)
                    {
                        simplex = { simplex[1], simplex[2] };
                        direction = abPerpendicular;
                    }
                    else if(Vector2F::DotProduct(acPerpendicular, ao) > 0)
                    {
                        simplex = { simplex[0], simplex[2] };
                        direction = acPerpendicular;
                    }
                    else
                    {
                        manifold.isCollision = true;
                        manifold.simplex = simplex;
                        return manifold;
                    }

                    break;
                }
            }       
        }
    }

    Edge FindClosestEdge(const std::vector<Vec2> vertices, const Bool clockwiseWinding)
    {
        Vec2 edge = vertices[1] - vertices[0];
        Vec2 closestNormal = clockwiseWinding ? (Vec2){ edge[1], -edge[0] } : (Vec2){ -edge[1], edge[0] };
        Float32 closestDistance = Vector2F::DotProduct(closestNormal, vertices[0]);
        Int32 closestIndex = 1;

        for(Int32 i = 1; i < vertices.size(); i++)
        {
            Int32 j = i + 1;
            if(j >= vertices.size()) j = 0;

            edge = vertices[j] - vertices[i];

            Vec2 normal = clockwiseWinding ? (Vec2){ edge[1], -edge[0] } : (Vec2){ -edge[1], edge[0] };
            normal = Vector2F::Normalize(normal);

            Float32 distance = Vector2F::DotProduct(normal, vertices[i]);
            if(distance >= closestDistance) continue;

            closestDistance = distance;
            closestNormal = normal;
            closestIndex = j;
        }

        return { closestDistance, closestNormal, closestIndex };
    }

    CollisionManifold EPA2D(const Poly a, const Poly b, const Array<Vec2, 3> simplex)
    {
        CollisionManifold manifold;
        manifold.isCollision = true;

        const Float32 e0 = simplex[1][0] - simplex[0][0] * simplex[1][1] * simplex[0][1];
        const Float32 e1 = simplex[2][0] - simplex[1][0] * simplex[2][1] * simplex[1][1];
        const Float32 e2 = simplex[0][0] - simplex[2][0] * simplex[0][1] * simplex[2][1];
        const Bool clockwiseWinding = e0 + e1 + e2 >= 0;

        std::vector<Vec2> vertices = { simplex[0], simplex[1], simplex[2] };

        for(Int32 i = 0; i < 64; i++)
        {
            const Edge edge = FindClosestEdge(vertices, clockwiseWinding);
            const Vec2 support = Polygon::FurthestPoint(a, edge.normal) - Polygon::FurthestPoint(b, -edge.normal);
            const Float32 distance = Vector2F::DotProduct(support, edge.normal);

            if(abs(distance - edge.distance) <= 0.00000001f)
            {
                manifold.normal = edge.normal;
                manifold.depth *= distance;
                return manifold;
            }
            
            vertices.insert(vertices.begin() + edge.index, support);
        }

        return manifold;
    }
 
    Bool PolygonPolygon(const Poly a, const Poly b)
    {
        return GJK2D(a, b).isCollision;
    }

    CollisionManifold PolygonPolygonManifold(const Poly a, const Poly b)
    {
        CollisionManifold manifold;
        manifold.isCollision = false;

        GJK2DManifold gjkManifold = GJK2D(a, b);
        if(!gjkManifold.isCollision) return manifold;
        
        return EPA2D(a, b, gjkManifold.simplex);
    }

    Bool RectRect(const Rect a, const Rect b)
    {
        Array<Vec2, 4> aVertices = Rectangle::Vertices(a);
        Array<Vec2, 4> bVertices = Rectangle::Vertices(b);
        return PolygonPolygon({aVertices.memory, 4}, {bVertices.memory, 4});
    }

    CollisionManifold RectRectManifold(const Rect a, const Rect b)
    {
        Array<Vec2, 4> aVertices = Rectangle::Vertices(a);
        Array<Vec2, 4> bVertices = Rectangle::Vertices(b);
        return PolygonPolygonManifold({aVertices.memory, 4}, {bVertices.memory, 4});
    }

}
