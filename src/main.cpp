#define DEBUG

#include <allocator/allocator.h>
#include <array/array.h>
#include <array/dynamic_array.h>
#include <log/log.h>
#include <math/math.h>

#include <stdio.h>

const UInt64 ALLOCATION_SIZE = 1024 * 1024; // MB

Int32 main()
{
    Base::Allocator::Create(ALLOCATION_SIZE);

    Base::Mat4 matrix;
    Base::Math::Mat4Identity(matrix);

    Base::Allocator::Destroy();

    return 0;
}
