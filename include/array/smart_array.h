#pragma once

#include "../allocator/allocator.h"

typedef struct
{
    unsigned char* memory;
    size_t element_size;
    size_t size;
    size_t capacity;
} SmartArray;

void smart_array_create(SmartArray* const smart_array, Allocator* const allocator, size_t element_size, size_t capacity);
void* smart_array_index(SmartArray* const smart_array, const size_t index);
void smart_array_push(SmartArray* const smart_array, const void* const ptr);
void smart_array_insert(SmartArray* const smart_array, const void* const ptr, const size_t index);
void smart_array_delete(SmartArray* const smart_array, const size_t index);
