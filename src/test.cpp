#define BASE_DEBUG

#include <math/vector.h>
#include <array/array.h>
#include <vector>

#include <stdio.h>

Base::Array<Int32, 16> arr;
std::vector<Int32> vec;

void Print()
{
    printf("Array:  ");
    for(Int32 i = 0; i < arr.GetSize(); i++)
    {
        printf("[%d]", arr[i]);
    }
    printf("\nVector: ");
    for(UInt32 i = 0; i < vec.size(); i++)
    {
        printf("[%d]", vec[i]);
    }
    printf("\n");
}

int main()
{
    using namespace Base;

    Allocator::Create(1024 * 1024);

    printf("Start:\n");
    Print();
    printf("\n");

    for(Int32 i = 0; i < 1; i++)
    {
        arr.Clear();
        vec = std::vector<Int32>(8);
        for(Int32 j = 0; j < 8; j++)
        {
            const Int32 index = rand() % 8;
            const Int32 value = rand() % 99;

            printf("Index %d Value %d\n", index, value);

            arr.Insert(index, value);
            vec.insert(vec.begin() + index, value);

            Print();
            printf("\n");
        }
    }

    printf("\n\nEnd:\n");
    Print();

    Allocator::Destroy();

    return 0;
}