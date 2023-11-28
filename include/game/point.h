#pragma once

#include "../math/struct.h"
#include "../math/vector.h"

namespace Base::Game2D
{
    Vec2 ScreenToWorldPoint(Vec2 point, const Rect camera)
    {
        point = Math::Vector2F::Translation(point, camera.position);
        point = Math::Vector2F::Rotate(point, camera.rotation);
        point = Math::Vector2F::Scale(point, camera.size);

        return point;
    }
}