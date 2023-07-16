#include "../../include/allocator/allocator.h"

int allocator_create(Allocator* const allocator, size_t capacity)
{   
    allocator->memory = (unsigned char*)malloc(capacity);

    if (allocator->memory == 0)
        return 1;

    allocator->offset = 0;
    allocator->capacity = capacity; 
    
    return 0;
}

int allocator_destroy(Allocator* const allocator)
{
    if (allocator->memory == 0)
        return 1;

    free(allocator->memory);

    return 0;
}

void* allocator_alloc(Allocator* const allocator, size_t capacity)
{
    if (allocator->offset + capacity > allocator->capacity)
        return 0;

    void* ptr = &allocator->memory[allocator->offset];
    allocator->offset += capacity;

    memset(ptr, 0, capacity);
    return ptr;
}