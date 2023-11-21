#pragma once

#include <math.h>

#include "struct.h"

namespace Base::Math
{
    void Vec2Rotate2D(Vec2 vec, const Float32 rotation)
    {
        const Float32 cos = cosf(rotation);
        const Float32 sin = sinf(rotation);

        const Float32 x = vec[0];
        const Float32 y = vec[1];
    
        vec[0] = cos * x - sin * y;
        vec[1] = sin * x + cos * y;
    }
}