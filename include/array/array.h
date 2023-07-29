#pragma once

#include "../allocator/allocator.h"
#include <stdio.h>

typedef struct
{
    unsigned char* memory;
    size_t element_size;
    size_t capacity;
} Array;

int array_create(Array* const array, Allocator* const allocator, const size_t element_size, const size_t capacity);
void* array_index(Array* const array, const size_t index);
void array_clear(Array* const array);
