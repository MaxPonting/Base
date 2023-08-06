#pragma once

#include "../type/type.h"

typedef struct
{
    uint8* memory;
    uint64 element_size;
    uint64 capacity;
} Array;

int32 array_create(Array* const array, const uint64 element_size, const uint64 capacity);
void* array_index(Array* const array, const uint64 index);
int32 array_clear(Array* const array);
