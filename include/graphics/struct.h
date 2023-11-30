#pragma once

#include "../type/type.h"

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