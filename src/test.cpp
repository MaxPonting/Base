#define BASE_DEBUG

#include <math/vector.h>
#include <array/array.h>
#include <math/collision2D.h>

#include <stdio.h>

int main()
{
    using namespace Base;

    Allocator::Create(1024 * 1024);

    /*
    Vec2 referenceVertex = { 1, 0 };
    Vec2 referenceNormal = { referenceVertex[1], -referenceVertex[0] };
    printf("%f, %f\n", referenceNormal[0], referenceNormal[1]);
    return 0;
    */

    CollisionManifold2D manifold;
    manifold.depth = 1;
    manifold.normal = { 0, -1 };

    const int example = 2;

    if(example == 1)
    {
        Rect a = {{11, 6}, { 6, 4 }, 0};
        Rect b = {{8, 3.5f}, { 8, 3 }, 0};
        manifold = Math::Collision2D::RectRectManifold(a, b);
    }
    else if(example == 2)
    {
        Vec2 vertices1[] = {{6, 4}, {9, 7}, {5, 11}, {2, 8}};
        Vec2 vertices2[] = {{12, 5}, {4, 5}, {4, 2}, {12, 2}};
        manifold = Base::Math::Collision2D::PolygonPolygonManifold({vertices1, 4}, {vertices2, 4});
    }

    for(Int32 i = 0; i < manifold.contactPoints.count; i++)
    {
        printf("%f, %f\n", manifold.contactPoints[i][0], manifold.contactPoints[i][1]);
    }

    Allocator::Destroy();

    return 0;
}