#pragma once

#include "../type/type.h"

namespace Base::Allocator
{
    Int32 Create(const UInt64 size);
    Int32 Destroy();
    Int32 Allocate(const UInt64 size, void** ptr);
}