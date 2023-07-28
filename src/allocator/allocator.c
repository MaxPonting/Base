#include "allocator/allocator.h"

#include <stdio.h>

int allocator_create(Allocator* const allocator, size_t capacity)
{   
    allocator->memory = (unsigned char*)malloc(capacity);

    if (allocator->memory == 0)
    {   
        printf("[ERROR][BASE/ALLOCATOR/11][Creation failed]\n");
        return 0;
    }
        
    allocator->offset = 0;
    allocator->capacity = capacity; 
    
    return 1;
}

int allocator_destroy(Allocator* const allocator)
{
    if (allocator->memory == 0)
        return 0;

    free(allocator->memory);

    return 1;
}

void* allocator_alloc(Allocator* const allocator, size_t capacity)
{
    if (allocator->offset + capacity > allocator->capacity)
    {
        printf("[ERROR][BASE/ALLOCATOR/35][Capacity reached]\n");
        return 0;
    }
        
    void* ptr = &allocator->memory[allocator->offset];
    allocator->offset += capacity;

    memset(ptr, 0, capacity);
    return ptr;
}