#pragma once

#include "../math/vector.h"

#include <stdio.h>

namespace Base::Game2D
{
    Vec2 MoveToPosition(Vec2 current, const Vec2 target, const Float32 speed)
    {
        const Vec2 direction = Math::Vector2F::Normalize(target - current);
        const Vec2 translation = direction * speed;

        current[0] += abs(translation[0]) < abs(target[0] - current[0]) ? translation[0] : target[0] - current[0];
        current[1] += abs(translation[1]) < abs(target[1] - current[1]) ? translation[1] : target[1] - current[1];

        return current;
    }
}