#define BASE_DEBUG

#include <math/vector.h>
#include <array/array.h>

#include <stdio.h>

int main()
{
    using namespace Base;

    Allocator::Create(256);

    Array<Int32, 5> arr = { 2, 4, 5 };
    arr.Insert(2, 7);

    for(Int32 i = 0; i < arr.count; i++)
    {
        printf("[%d]", arr[i]);
    }

    Allocator::Destroy();

    return 0;
}