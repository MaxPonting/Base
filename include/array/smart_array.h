#pragma once

#include "../type/type.h"

typedef struct
{
    uint8* memory;
    uint64 element_size;
    uint64 size;
    uint64 capacity;
} SmartArray;

int32 smart_array_create(SmartArray* const smart_array, uint64 element_size, uint64 capacity);
void* smart_array_index(SmartArray* const smart_array, const uint64 index);
int32 smart_array_push(SmartArray* const smart_array, const void* const ptr);
int32 smart_array_insert(SmartArray* const smart_array, const void* const ptr, const uint64 index);
int32 smart_array_sort(SmartArray* const smart_array, int(*compar)(const void*, const void*), const uint64 start_index, const uint64 end_index);
int32 smart_array_clear(SmartArray* const smart_array);
int32 smart_array_delete(SmartArray* const smart_array, const uint64 index);
