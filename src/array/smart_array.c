#include "array/smart_array.h"

#include <stdio.h>

int smart_array_create(SmartArray* const smart_array, Allocator* const allocator, size_t element_size, size_t capacity)
{
    smart_array->memory = allocator_alloc(allocator, capacity * element_size);
    if (smart_array->memory == 0)
    {
        return 0;
    }
    smart_array->element_size = element_size;
    smart_array->capacity = capacity;
    smart_array->size = 0;

    return 1;
}

void* smart_array_index(SmartArray* const smart_array, const size_t index)
{
    if (index >= smart_array->size)
    {
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Cannot get data at or above array size]\n", __LINE__);
        return 0;
    }

    return &(smart_array->memory)[index * smart_array->element_size];
}

int smart_array_push(SmartArray* const smart_array, const void* const ptr)
{
    if (smart_array->size == smart_array->capacity)
    {   
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Capacity reached, data was not pushed]\n", __LINE__);
        return 0;
    }
  
    memcpy(smart_array->memory + smart_array->size * smart_array->element_size, ptr, smart_array->element_size);
    smart_array->size++;

    return 1;
}

int smart_array_insert(SmartArray* const smart_array, const void* const ptr, const size_t index)
{
    if (smart_array->size == smart_array->capacity)
    {   
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Capacity reached, data was not inserted]\n", __LINE__);
        return 0;
    }

    if (index >= smart_array->size)
    {
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Cannot insert data at or above array size]\n", __LINE__);
        return 0;
    }
    
    memcpy(smart_array->memory + (index + 1) * smart_array->element_size, smart_array->memory + index * smart_array->element_size, smart_array->element_size * (smart_array->size - index));
    memcpy(smart_array->memory + index * smart_array->element_size, ptr, smart_array->element_size);
    smart_array->size++;

    return 1;
}
int smart_array_clear(SmartArray* const smart_array)
{
    memset(smart_array->memory, 0, smart_array->size);

    smart_array->size = 0;

    return 1;
}

int smart_array_delete(SmartArray* const smart_array, const size_t index)
{
    if (smart_array->size == 0)
    {   
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Capacity is 0, index was not deleted]\n", __LINE__);
        return 0;
    }

    if (index >= smart_array->size)
    {
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Cannot delete data at or above array size]\n", __LINE__);
        return 0;
    }
  
    memcpy(smart_array->memory + index * smart_array->element_size, smart_array->memory + (index + 1) * smart_array->element_size, smart_array->element_size * (smart_array->size - index));
    smart_array->size--;

    return 1;
}

