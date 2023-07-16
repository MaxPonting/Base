#include "../include/array.h"

void array_create(Array* const array, Allocator* const allocator, const size_t element_size, const size_t capacity)
{
    array->memory = allocator_alloc(allocator, capacity * element_size);
    array->element_size = element_size;
    array->capacity = capacity;
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
