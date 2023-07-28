#include "array/array.h"

int array_create(Array* const array, Allocator* const allocator, const size_t element_size, const size_t capacity)
{
    array->memory = allocator_alloc(allocator, capacity * element_size);
    if (array->memory == 0)
    {
        return 1;
    }

    array->element_size = element_size;
    array->capacity = capacity;

    return 0;
}

void* array_index(Array* const array, const size_t index)
{
    if (index >= array->capacity)
    {
        printf("Array: Cannot access index that is equal to or larger than capacity\n");
        return 0;
    }

    return &(array->memory)[index * array->element_size];
}

void array_clear(Array* const array)
{
    memset(array->memory, 0, array->capacity);
}
