#pragma once

#include "../type/type.h"

struct Vec2
{
    Float32 data[2];
    Float32& operator[](const Int32 index) { return data[index]; }
    Float32 operator[](const Int32 index) const { return data[index]; }
};

struct Vec3
{
    Float32 data[3];
    Float32& operator[](const Int32 index) { return data[index]; }
    Float32 operator[](const Int32 index) const { return data[index]; }
};

struct Vec4
{
    Float32 data[4];
    Float32& operator[](const Int32 index) { return data[index]; }
    Float32 operator[](const Int32 index) const { return data[index]; }
};

struct IVec2
{
    Int32 data[2];
    Int32& operator[](const Int32 index) { return data[index]; }
    Int32 operator[](const Int32 index) const { return data[index]; }
};

struct IVec3
{
    Int32 data[3];
    Int32& operator[](const Int32 index) { return data[index]; }
    Int32 operator[](const Int32 index) const { return data[index]; }
};

struct IVec4
{
    Int32 data[4];
    Int32& operator[](const Int32 index) { return data[index]; }
    Int32 operator[](const Int32 index) const { return data[index]; }
};

struct Mat2
{
    Vec2 data[2];
    Vec2& operator[](const Int32 index) { return data[index]; } 
    Vec2 operator[](const Int32 index) const { return data[index]; } 
};

struct Mat3
{
    Vec3 data[3];
    Vec3& operator[](const Int32 index) { return data[index]; } 
    Vec3 operator[](const Int32 index) const { return data[index]; } 
};

struct Mat4
{
    Vec4 data[4];
    Vec4& operator[](const Int32 index) { return data[index]; } 
    Vec4 operator[](const Int32 index) const { return data[index]; } 
};

struct Rect
{
    Vec2 position;
    Vec2 size;
    Float32 rotation;
};