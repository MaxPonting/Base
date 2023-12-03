#pragma once

#include "struct.h"
#include "../math/struct.h"

namespace Base::Graphics::Convert
{
    Rect SpriteToRect(const Sprite sprite)
    {
        return { sprite.position, sprite.size, sprite.rotation };
    }
}
