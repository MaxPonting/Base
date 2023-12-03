#pragma once

#include "../type/type.h"
#include "../math/struct.h"

namespace Base
{
    struct RGB
    {
        UInt8 data[3];
        UInt8& operator[](const Int32 index) { return data[index]; }
        UInt8 operator[](const Int32 index) const { return data[index]; }
    };

    struct RGBA
    {
        UInt8 data[4];
        UInt8& operator[](const Int32 index) { return data[index]; }
        UInt8 operator[](const Int32 index) const { return data[index]; }
    };

    struct SubTexture
    {
        Vec2 bottom;
        Vec2 top;
    };

    struct Sprite 
    {
        Vec2 position;
        Vec2 size;
        Float32 rotation;
        RGBA colour;
        SubTexture subTexture;
    };

    enum class CoordinateSpace
    {
        Window, Screen, World
    };

}