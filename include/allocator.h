#pragma once

#include <memory.h>
#include <malloc.h>

typedef struct
{
    unsigned char* memory;
    size_t offset;
    size_t capacity;
} Allocator;

int allocator_create(Allocator* const allocator, size_t capacity);
int allocator_destroy(Allocator* const allocator);
void* allocator_alloc(Allocator* const allocator, size_t capacity);
