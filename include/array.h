#pragma once

#include "allocator.h"
#include <stdio.h>

typedef struct
{
    unsigned char* memory;
    size_t element_size;
    size_t capacity;
} Array;

void array_create(Array* const array, Allocator* const allocator, const size_t element_size, const size_t capacity);
void* array_index(Array* const array, const size_t index);
