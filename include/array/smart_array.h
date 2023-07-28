#pragma once

#include "allocator/allocator.h"

typedef struct
{
    unsigned char* memory;
    size_t element_size;
    size_t size;
    size_t capacity;
} SmartArray;

int smart_array_create(SmartArray* const smart_array, Allocator* const allocator, size_t element_size, size_t capacity);
void* smart_array_index(SmartArray* const smart_array, const size_t index);
int smart_array_push(SmartArray* const smart_array, const void* const ptr);
int smart_array_insert(SmartArray* const smart_array, const void* const ptr, const size_t index);
int smart_array_clear(SmartArray* const smart_array);
int smart_array_delete(SmartArray* const smart_array, const size_t index);
