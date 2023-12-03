#pragma once

#include "struct.h"

namespace Base::Math::Convert
{
    Rect RigidBody2DToRect(const RigidBody2D body, const Vec2 size)
    {
        return { body.position, size, body.rotation };
    }
}