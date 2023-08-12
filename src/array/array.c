#include "array/array.h"
#include "allocator/allocator.h"
#include "log/log.h"

int array_create(Array* const array, const uint64 element_size, const uint64 capacity)
{
    array->memory = allocator_alloc(capacity * element_size);
    if (array->memory == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/ARRAY/ARRAY", "Array allocation failed", __LINE__);
        return 0;
    }

    array->element_size = element_size;
    array->capacity = capacity;

    return 1;
}

void* array_index(Array* const array, const uint64 index)
{
    if (index >= array->capacity)
    {
        log_print(LOG_TYPE_ERROR, "BASE/ARRAY/ARRAY", "Index is larger than capacity", __LINE__);
        return 0;
    }

    return &(array->memory)[index * array->element_size];
}

int32 array_clear(Array* const array)
{
    if (array->memory == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/ARRAY/ARRAY", "Array has not been allocated", __LINE__);
        return 0;
    }

    memset(array->memory, 0, array->capacity);

    return 1;
}
