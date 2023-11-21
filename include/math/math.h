#pragma once

namespace Base::Math
{
    const Float32 PI = 3.14159265359f;

    Float64 MinimumF64(const Float64 a, const Float64 b)
    {
        if(a <= b)
            return a;
        else
            return b;
    }

    Float64 MaximumF64(const Float64 a, const Float64 b)
    {
        if(a >= b)
            return a;
        else
            return b;    
    }

    Float32 MinimumF32(const Float32 a, const Float32 b)
    {
        if(a <= b)
            return a;
        else
            return b;
    }

    Float32 MaximumF32(const Float32 a, const Float32 b)
    {
        if(a >= b)
            return a;
        else
            return b;    
    }

    Int64 MinimumI64(const Int64 a, const Int64 b)
    {
        if(a <= b)
            return a;
        else
            return b;
    }

    Int64 MaximumI64(const Int64 a, const Int64 b)
    {
        if(a >= b)
            return a;
        else
            return b;    
    }

    Int32 MinimumI32(const Int32 a, const Int32 b)
    {
        if(a <= b)
            return a;
        else
            return b;
    }

    Int64 MaximumI32(const Int32 a, const Int32 b)
    {
        if(a >= b)
            return a;
        else
            return b;    
    }

    Float64 ClampF64(Float64 value, const Float64 min, const Float64 max)
    {
        return MaximumF64(MinimumF64(value, max), min);
    }

    Float32 ClampF32(Float32 value, const Float32 min, const Float32 max)
    {
        return MaximumF32(MinimumF32(value, max), min);
    }

    Int64 ClampI64(Int64 value, const Int64 min, const Int64 max)
    {
        return MaximumI64(MinimumI64(value, max), min);
    }

    Int32 ClampI32(Int32 value, const Int32 min, const Int32 max)
    {
        return MaximumI32(MinimumI32(value, max), min);
    }

    Float32 Radians(const Float32 rotation)
    {
        return rotation * (PI / 180.0f);
    }
}

