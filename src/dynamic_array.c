#include "../include/dynamic_array.h"

#include <memory.h>
#include <stdio.h>

int reallocate(DynamicArray* dynamic_array);

void dynamic_array_create(DynamicArray* const dynamic_array, size_t element_size, size_t capacity)
{
    dynamic_array->memory = malloc(capacity * element_size);
    dynamic_array->element_size = element_size;
    dynamic_array->capacity = capacity;
    dynamic_array->size = 0;
}

void* dynamic_array_index(DynamicArray* const dynamic_array, const size_t index)
{
    if (index >= dynamic_array->size)
    {
        printf("Dynamic Array: Cannot get data at or above array size\n");
        return 0;
    }

    return &(dynamic_array->memory)[index * dynamic_array->element_size];
}

void dynamic_array_push(DynamicArray* const dynamic_array, const void* const ptr)
{
    if (dynamic_array->size == dynamic_array->capacity)
    {   
        if(!reallocate(dynamic_array))
            return;
    }
  
    memcpy(dynamic_array->memory + dynamic_array->size * dynamic_array->element_size, ptr, dynamic_array->element_size);
    dynamic_array->size++;
}

void dynamic_array_insert(DynamicArray* const dynamic_array, const void* const ptr, const size_t index)
{
    if (dynamic_array->size == dynamic_array->capacity)
    {   
        if(!reallocate(dynamic_array))
            return;
    }

    if (index >= dynamic_array->size)
    {
        printf("Dynamic Array: Cannot insert data at or above array size, use push\n");
        return;
    }

    memcpy(dynamic_array->memory + (index + 1) * dynamic_array->element_size, dynamic_array->memory + index * dynamic_array->element_size, dynamic_array->element_size * (dynamic_array->size - index));
    memcpy(dynamic_array->memory + index * dynamic_array->element_size, ptr, dynamic_array->element_size);
    dynamic_array->size++;
}

void dynamic_array_delete(DynamicArray* const dynamic_array, const size_t index)
{
    if (dynamic_array->size == 0)
    {   
        printf("Dynamic Array: Capacity is 0, data was not deleted from array\n");
        return;
    }

    if (index >= dynamic_array->size)
    {
        printf("Dynamic Array: Cannot delete data at or above array size\n");
        return;
    }
  
    memcpy(dynamic_array->memory + index * dynamic_array->element_size, dynamic_array->memory + (index + 1) * dynamic_array->element_size, dynamic_array->element_size * (dynamic_array->size - index));
    dynamic_array->size--;
}

void dynamic_array_destroy(DynamicArray* const dynamic_array)
{
    free(dynamic_array->memory);
}

int reallocate(DynamicArray* dynamic_array)
{
    unsigned char* temp = realloc(dynamic_array->memory, dynamic_array->capacity * dynamic_array->element_size * 2);
    if (temp == 0)
    {
        printf("Dynamic Array: Reallocation has failed, data was not pushed");
        return 0;
    }
    dynamic_array->memory = temp;
    dynamic_array->capacity *= 2;

    return 1;
}

