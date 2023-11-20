#define BASE_DEBUG

#include <stdio.h>
#include <array/static_array.h>

int main()
{
    Base::StaticArray<int, 10> arr;

    arr.Push(4);
    arr.Push(7);
    arr.Clear();

    for(int i = 0; i < arr.GetSize(); i++)
    {
        printf("%d\n", arr.Item(i));
    } 

    return 0;

}