#pragma once

#include <malloc.h>

typedef struct
{
    unsigned char* memory;
    size_t element_size;
    size_t size;
    size_t capacity;
} DynamicArray;

int dynamic_array_create(DynamicArray* const dynamic_array, size_t element_size, size_t capacity);
void* dynamic_array_index(DynamicArray* const dynamic_array, const size_t index);
void dynamic_array_push(DynamicArray* const dynamic_array, const void* const ptr);
void dynamic_array_insert(DynamicArray* const dynamic_array, const void* const ptr, const size_t index);
void dynamic_array_clear(DynamicArray* const dynamic_array);
void dynamic_array_delete(DynamicArray* const dynamic_array, const size_t index);
void dynamic_array_destroy(DynamicArray* const dynamic_array);