#pragma once

#include "struct.h"
#include <math.h>

namespace Base::Math::F64
{
    const Float64 PI = 3.14159265359;

    Float64 Radians(const Float64 rotation)
    {
        return rotation * (PI / 180.0);
    }

    Float64 Degrees(const Float64 rotation)
    {
        return rotation * (180 / PI);
    }

    Float64 Minimum(const Float64 a, const Float64 b)
    {
        if(a <= b)
            return a;
        else
            return b;
    }

    Float64 Maximum(const Float64 a, const Float64 b)
    {
        if(a >= b)
            return a;
        else
            return b;    
    }

    Float64 Clamp(Float64 value, const Float64 min, const Float64 max)
    {
        return Maximum(Minimum(value, max), min);
    }
}

namespace Base::Math::F32
{
    const Float32 PI = 3.14159265359f;

    Float32 Radians(const Float32 rotation)
    {
        return rotation * (PI / 180.0f);
    }

    Float32 Degrees(const Float32 rotation)
    {
        return rotation * (180 / PI);
    }

    Float32 Minimum(const Float32 a, const Float32 b)
    {
        if(a <= b)
            return a;
        else
            return b;
    }

    Float32 Maximum(const Float32 a, const Float32 b)
    {
        if(a >= b)
            return a;
        else
            return b;    
    }

    Float32 Clamp(Float32 value, const Float32 min, const Float32 max)
    {
        return Maximum(Minimum(value, max), min);
    }
}

namespace Base::Math::I64
{
    Int64 Minimum(const Int64 a, const Int64 b)
    {
        if(a <= b)
            return a;
        else
            return b;
    }

    Int64 Maximum(const Int64 a, const Int64 b)
    {
        if(a >= b)
            return a;
        else
            return b;    
    }

    Int64 ClampI64(Int64 value, const Int64 min, const Int64 max)
    {
        return Maximum(Minimum(value, max), min);
    }
}

namespace Base::Math::I32
{
    Int32 Minimum(const Int32 a, const Int32 b)
    {
        if(a <= b)
            return a;
        else
            return b;
    }

    Int64 Maximum(const Int32 a, const Int32 b)
    {
        if(a >= b)
            return a;
        else
            return b;    
    }

    Int32 Clamp(Int32 value, const Int32 min, const Int32 max)
    {
        return Maximum(Minimum(value, max), min);
    }
}