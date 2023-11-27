#pragma once

#include <math.h>

#include "struct.h"
#include <stdio.h>

namespace Base::Math::Vector2F
{
    Vec2 Division(const Vec2 vec, const Float32 div)
    {
        return { vec[0] / div, vec[1] / div };
    }

    Vec2 Multiplication(const Vec2 vec, const Float32 mul)
    {
        return { vec[0] * mul, vec[1] * mul };
    }

    Vec2 Translation(const Vec2 a, const Vec2 b)
    {
        return { a[0] + b[0], a[1] + b[1] };
    }

    Float32 DotProduct(Vec2 a, Vec2 b)
    {
        return a[0] * b[0] + a[1] * b[1];
    }

    Float32 Magnitude(const Vec2 vec)
    {
        return powf(vec[0] * vec[0] + vec[1] * vec[1], 0.5f);
    }

    Vec2 Normalize(const Vec2 vec)
    {
        return Division(vec, Magnitude(vec));
    }

    Vec2 Normal(const Vec2 vector)
    {
        return {-vector[1], -vector[0]};
    }

    Vec2 Rotate(const Vec2 a, const Float32 rotation)
    {
        Float32 sin = sinf(rotation);
        Float32 cos = cosf(rotation);

        return { a[0] * cos - a[1] * sin, a[0] * sin + a[1] * cos };
    }

    Vec2 RotateCache(const Vec2 a, const Float32 sin, const Float32 cos)
    {
        return { a[0] * cos - a[1] * sin, a[0] * sin + a[1] * cos };
    }

    Vec2 RotateAroundPoint(Vec2 a, const Vec2 p, const Float32 rotation)
    {
        a[0] -= p[0];
        a[1] -= p[1];

        const Vec2 aNew = Rotate(a, rotation);

        return { aNew[0] + p[0], aNew[1] + p[1] };
    }

    Vec2 RotateAroundPointCache(Vec2 a, const Vec2 p, const Float32 sin, const Float32 cos)
    {
        a[0] -= p[0];
        a[1] -= p[1];

        const Vec2 aNew = RotateCache(a, sin, cos);

        return { aNew[0] + p[0], aNew[1] + p[1] };
    }

    Vec2 LineSegment(const Vec2 a, const Vec2 b)
    {
        return { b[0] - a[0], b[1] - a[1] };
    }

    Float32 ProjectPointOnLineScalar(const Vec2 x, const Vec2 a, const Vec2 b)
    {
        const Vec2 ab = LineSegment(a, b);
        return DotProduct(ab, LineSegment(a, x)) / Magnitude(ab);
    }

    Vec2 ProjectPointOnLine(const Vec2 x, const Vec2 a, const Vec2 b)
    {
        const Vec2 unitAB = Normalize(LineSegment(a, b));
        return Translation(a, Multiplication(unitAB, DotProduct(LineSegment(a, x), unitAB)));
    }
}