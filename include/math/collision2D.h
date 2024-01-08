#pragma once

#include "struct.h"
#include "math.h"
#include "rect.h"
#include "vector.h"
#include "polygon.h"
#include "../array/heap_array.h"

#include <vector>

namespace Base::Math::Collision2D
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

    Array<Vec2, 3> PolygonCollisionEdge(const Vec2 normal, const Poly a)
    {
        Float32 maxProjection = Vector2F::DotProduct(normal, a.vertices[0]);
        Int32 maxIndex = 0;
        for(Int32 i = 1; i < a.count; i++)
        {
            Float32 projection = Vector2F::DotProduct(normal, a.vertices[i]);

            if(projection <= maxProjection) continue;

            maxProjection = projection;
            maxIndex = i;
        }

        Vec2 v2 = a.vertices[maxIndex];
        Vec2 v3 = a.vertices[(maxIndex + 1) % a.count];
        Vec2 v1 = a.vertices[(maxIndex + a.count - 1) % a.count];
        
        Vec2 l = Vector2F::Normalize(v2 - v3);
        Vec2 r = Vector2F::Normalize(v2 - v1);

        if(Vector2F::DotProduct(r, normal) <= Vector2F::DotProduct(l, normal)) return { v2, v1, v2 };
        else return { v2, v2, v3 };
    }

    Array<Vec2, 2> ClipPoints(Vec2 v1, Vec2 v2, Vec2 normal, Float32 o)
    {
        Array<Vec2, 2> clippedPoints;

        Float32 d1 = Vector2F::DotProduct(normal, v1) - o;
        Float32 d2 = Vector2F::DotProduct(normal, v2) - o;

        if(d1 >= 0) clippedPoints.Push(v1);
        if(d2 >= 0) clippedPoints.Push(v2);

        if(d1 * d2 >= 0) return clippedPoints;

        Vec2 e = v2 - v1;
        Float32 u = d1 / (d1 - d2);
        e *= u;
        e += v1;

        clippedPoints.Push(e);

        return clippedPoints;
    }

    CollisionManifold2D ContactPointsPolygonPolygon(CollisionManifold2D manifold, const Poly a, const Poly b)
    {
        Array<Vec2, 3> e1 = PolygonCollisionEdge(manifold.normal, a);
        Array<Vec2, 3> e2 = PolygonCollisionEdge(-manifold.normal, b);

        Array<Vec2, 3> reference, incident;
        Bool flip = false;

        if(abs(Vector2F::DotProduct(e1[2] - e1[1], manifold.normal)) <= abs(Vector2F::DotProduct(e2[2] - e2[1], manifold.normal)))
        {
            reference = e1;
            incident = e2;
        }
        else
        {
            reference = e2;
            incident = e1;
            flip = true;
        }

        Vec2 referenceVertex = Vector2F::Normalize(reference[2] - reference[1]);
        Float32 o1 = Vector2F::DotProduct(referenceVertex, reference[1]);
        Array<Vec2, 2> contactPoints = ClipPoints(incident[1], incident[2], referenceVertex, o1);

        if(contactPoints.count < 2) return manifold;

        Float32 o2 = Vector2F::DotProduct(referenceVertex, reference[2]);
        contactPoints = ClipPoints(contactPoints[0], contactPoints[1], -referenceVertex, -o2);

        if(contactPoints.count < 2) return manifold;       

        //Vec2 referenceNormal = { referenceVertex[1], -referenceVertex[0] };
        //if(flip) referenceNormal = -referenceNormal;
        Vec2 referenceNormal = -manifold.normal;
        if(flip) referenceNormal = manifold.normal;

        Float32 max = Vector2F::DotProduct(referenceNormal, reference[0]);

        if(Vector2F::DotProduct(referenceNormal, contactPoints[0]) - max < 0)
        {
            contactPoints[0] = contactPoints[1];
            contactPoints.count--;
        }
        if(Vector2F::DotProduct(referenceNormal, contactPoints[1]) - max < 0)
        {
            contactPoints.count--;
        }

        manifold.contactPoints = contactPoints;
        return manifold;
    }

    CollisionManifold2D ContactPointsCirclePolygon(CollisionManifold2D manifold, const Circle a, const Poly b)
    {
        Vec2 closestPoint;
        Float32 minimumDistanceSqr = 0;

        for(Int32 i = 0; i < b.count; i++)
        {
            Vec2 va = b.vertices[i];
            Vec2 vb = b.vertices[(i + 1) % b.count];

            Vec2 ab = vb - va;
            Vec2 ap = a.center - va;

            Float32 projection = Vector2F::DotProduct(ap, ab);
            Float32 d = projection / Vector2F::MagnitudeSquared(ab);

            Vec2 contact;

            if(d <= 0) contact = va;
            else if(d >= 1) contact = vb;
            else contact = va + ab * d;

            Vec2 heading = a.center - contact;
            Float32 distanceSqr = Vector2F::MagnitudeSquared(heading);

            if(distanceSqr < minimumDistanceSqr || i == 0)
            {
                closestPoint = contact;
                minimumDistanceSqr = distanceSqr;
            }
        }

        manifold.contactPoints = { closestPoint };

        return manifold;
    }

    GJKManifold2D GJK(const Poly a, const Poly b)
    {
        GJKManifold2D manifold;
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

    GJKManifold2D GJKCircle(const Circle a, const Poly b)
    {
        GJKManifold2D manifold;
        manifold.isCollision = false;

        Vec2 support = a.center + (Vec2){1, 0} * a.radius - Polygon::FurthestPoint(b, {-1, 0});

        Array<Vec2, 3> simplex;
        simplex.Push(support);

        Vec2 direction = -support;

        while(true)
        {
            support = a.center + Vector2F::Normalize(direction) * a.radius - Polygon::FurthestPoint(b, -direction);

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

    CollisionManifold2D EPA(const Poly a, const Poly b, const Array<Vec2, 3> simplex)
    {
        CollisionManifold2D manifold;
        manifold.isCollision = true;

        const Float32 e0 = (simplex[1][0] - simplex[0][0]) * (simplex[1][1] + simplex[0][1]);
        const Float32 e1 = (simplex[2][0] - simplex[1][0]) * (simplex[2][1] + simplex[1][1]);
        const Float32 e2 = (simplex[0][0] - simplex[2][0]) * (simplex[0][1] + simplex[2][1]);
        const Bool clockwiseWinding = e0 + e1 + e2 >= 0;

        HeapArray<Vec2> vertices = HeapArray<Vec2>(35);
        vertices.Push(simplex[0]);
        vertices.Push(simplex[1]);
        vertices.Push(simplex[2]);

        for(Int32 i = 0; i < 32; i++)
        {
            Vec2 edge = vertices[1] - vertices[0];
            Vec2 minNormal = clockwiseWinding ? (Vec2){ edge[1], -edge[0] } : (Vec2){ -edge[1], edge[0] };
            Float32 minDistance = Vector2F::DotProduct(minNormal, vertices[0]);
            Int32 minIndex = 1;

            for(Int32 i = 1; i < vertices.count; i++)
            {
                Int32 j = i + 1;
                if(j >= vertices.count) j = 0;

                edge = vertices[j] - vertices[i];

                Vec2 normal = clockwiseWinding ? (Vec2){ edge[1], -edge[0] } : (Vec2){ -edge[1], edge[0] };
                normal = Vector2F::Normalize(normal);

                Float32 distance = Vector2F::DotProduct(normal, vertices[i]);
                if(distance >= minDistance) continue;

                minDistance = distance;
                minNormal = normal;
                minIndex = j;
            }

            const Vec2 support = Polygon::FurthestPoint(a, minNormal) - Polygon::FurthestPoint(b, -minNormal);
            const Float32 distance = Vector2F::DotProduct(support, minNormal);

            if(abs(distance - minDistance) <= 0.001f)
            {
                manifold.normal = minNormal;
                manifold.depth = distance + 0.01f;
                manifold = ContactPointsPolygonPolygon(manifold, a, b);
                vertices.Deallocate();
                return manifold;
            }
            
            vertices.Insert(minIndex, support);
        }

        vertices.Deallocate();
        return manifold;
    }

    CollisionManifold2D EPACircle(const Circle a, const Poly b, const Array<Vec2, 3> simplex)
    {
        CollisionManifold2D manifold;
        manifold.isCollision = true;

        const Float32 e0 = (simplex[1][0] - simplex[0][0]) * (simplex[1][1] + simplex[0][1]);
        const Float32 e1 = (simplex[2][0] - simplex[1][0]) * (simplex[2][1] + simplex[1][1]);
        const Float32 e2 = (simplex[0][0] - simplex[2][0]) * (simplex[0][1] + simplex[2][1]);
        const Bool clockwiseWinding = e0 + e1 + e2 >= 0;

        HeapArray<Vec2> vertices = HeapArray<Vec2>(35);
        vertices.Push(simplex[0]);
        vertices.Push(simplex[1]);
        vertices.Push(simplex[2]);

        for(Int32 i = 0; i < 32; i++)
        {
            Vec2 edge = vertices[1] - vertices[0];
            Vec2 minNormal = clockwiseWinding ? (Vec2){ edge[1], -edge[0] } : (Vec2){ -edge[1], edge[0] };
            Float32 minDistance = Vector2F::DotProduct(minNormal, vertices[0]);
            Int32 minIndex = 1;

            for(Int32 i = 1; i < vertices.count; i++)
            {
                Int32 j = i + 1;
                if(j >= vertices.count) j = 0;

                edge = vertices[j] - vertices[i];

                Vec2 normal = clockwiseWinding ? (Vec2){ edge[1], -edge[0] } : (Vec2){ -edge[1], edge[0] };
                normal = Vector2F::Normalize(normal);

                Float32 distance = Vector2F::DotProduct(normal, vertices[i]);
                if(distance >= minDistance) continue;

                minDistance = distance;
                minNormal = normal;
                minIndex = j;
            }

            const Vec2 support = a.center + minNormal * a.radius - Polygon::FurthestPoint(b, -minNormal);
            const Float32 distance = Vector2F::DotProduct(support, minNormal);

            if(abs(distance - minDistance) <= 0.001f)
            {
                manifold.normal = -minNormal;
                manifold.depth = distance + 0.01f;
                manifold = ContactPointsCirclePolygon(manifold, a, b);
                vertices.Deallocate();
                return manifold;
            }
            
            vertices.Insert(minIndex, support);
        }

        vertices.Deallocate();
        return manifold;
    }
 
    Bool PolygonPolygon(const Poly a, const Poly b)
    {
        return GJK(a, b).isCollision;
    }

    CollisionManifold2D PolygonPolygonManifold(const Poly a, const Poly b)
    {
        CollisionManifold2D manifold;
        manifold.isCollision = false;

        GJKManifold2D gjkManifold = GJK(a, b);
        if(!gjkManifold.isCollision) return manifold;
        
        return EPA(a, b, gjkManifold.simplex);
    }

    Bool CirclePolygon(const Circle a, const Poly b)
    {
        return GJKCircle(a, b).isCollision;
    }

    CollisionManifold2D CirclePolygonManifold(const Circle a, const Poly b)
    {
        CollisionManifold2D manifold;
        manifold.isCollision = false;

        GJKManifold2D gjkManifold = GJKCircle(a, b);
        if(!gjkManifold.isCollision) return manifold;

        return EPACircle(a, b, gjkManifold.simplex);
    }

    Bool CircleCircle(const Circle a, const Circle b)
    {
        const Vec2 heading = a.center - b.center;
        const Float32 distanceSqr = Vector2F::MagnitudeSquared(heading);
        const Float32 radiusSum = a.radius + b.radius;

        return distanceSqr < radiusSum * radiusSum;
    }

    CollisionManifold2D CircleCircleManifold(const Circle a, const Circle b)
    {
        CollisionManifold2D manifold;
        manifold.isCollision = false;
        
        const Vec2 heading = a.center - b.center;
        const Float32 distanceSqr = Vector2F::MagnitudeSquared(heading);
        const Float32 radiusSum = a.radius + b.radius;

        if(distanceSqr >= radiusSum * radiusSum)
            return manifold;

        manifold.normal = Vector2F::Normalize(heading);
        manifold.depth = radiusSum - powf(distanceSqr, 0.5);
        manifold.contactPoints = { b.center + Vector2F::Normalize(heading) * b.radius };
        manifold.isCollision = true;

        return manifold;
    }

    Bool RectRect(const Rect a, const Rect b)
    {
        Array<Vec2, 4> aVertices = Rectangle::Vertices(a);
        Array<Vec2, 4> bVertices = Rectangle::Vertices(b);
        return PolygonPolygon({aVertices.memory, 4}, {bVertices.memory, 4});
    }

    CollisionManifold2D RectRectManifold(const Rect a, const Rect b)
    {
        Array<Vec2, 4> aVertices = Rectangle::Vertices(a);
        Array<Vec2, 4> bVertices = Rectangle::Vertices(b);
        return PolygonPolygonManifold({ aVertices.memory, 4 }, { bVertices.memory, 4 });
    }

    Bool CircleRect(const Circle a, const Rect b)
    {
        Array<Vec2, 4> bVertices = Rectangle::Vertices(b);
        return CirclePolygon(a, { bVertices.memory, 4 });
    }

    CollisionManifold2D CircleRectManifold(const Circle a, const Rect b)
    {
        Array<Vec2, 4> bVertices = Rectangle::Vertices(b);
        return CirclePolygonManifold(a, { bVertices.memory, 4 });
    }



}
