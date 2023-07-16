#include "../include/smart_array.h"

#include <stdio.h>

void smart_array_create(SmartArray* const smart_array, Allocator* const allocator, size_t element_size, size_t capacity)
{
    smart_array->memory = allocator_alloc(allocator, capacity * element_size);
    smart_array->element_size = element_size;
    smart_array->capacity = capacity;
    smart_array->size = 0;
}

void* smart_array_index(SmartArray* const smart_array, const size_t index)
{
    if (index >= smart_array->size)
    {
        printf("Smart Array: Cannot get data at or above array size\n");
        return 0;
    }

    return &(smart_array->memory)[index * smart_array->element_size];
}

void smart_array_push(SmartArray* const smart_array, const void* const ptr)
{
    if (smart_array->size == smart_array->capacity)
    {   
        printf("Smart Array: Capacity reached, data was not pushed to array\n");
        return;
    }
  
    memcpy(smart_array->memory + smart_array->size * smart_array->element_size, ptr, smart_array->element_size);
    smart_array->size++;
}

void smart_array_insert(SmartArray* const smart_array, const void* const ptr, const size_t index)
{
    if (smart_array->size == smart_array->capacity)
    {   
        printf("Smart Array: Capacity reached, data was not inserted into array\n");
        return;
    }

    if (index >= smart_array->size)
    {
        printf("Smart Array: Cannot insert data at or above array size, use push\n");
        return;
    }
    
    memcpy(smart_array->memory + (index + 1) * smart_array->element_size, smart_array->memory + index * smart_array->element_size, smart_array->element_size * (smart_array->size - index));
    memcpy(smart_array->memory + index * smart_array->element_size, ptr, smart_array->element_size);
    smart_array->size++;
}

void smart_array_delete(SmartArray* const smart_array, const size_t index)
{
    if (smart_array->size == 0)
    {   
        printf("Smart Array: Capacity is 0, data was not deleted from array\n");
        return;
    }

    if (index >= smart_array->size)
    {
        printf("Smart Array: Cannot delete data at or above array size\n");
        return;
    }
  
    memcpy(smart_array->memory + index * smart_array->element_size, smart_array->memory + (index + 1) * smart_array->element_size, smart_array->element_size * (smart_array->size - index));
    smart_array->size--;
}

