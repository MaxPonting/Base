#include "allocator/allocator.h"

#include <stdio.h>

static uint8* memory;
static uint64 offset;
static uint64 capacity;

int allocator_create(const uint64 c)
{   
    memory = (unsigned char*)malloc(c);

    if (memory == 0)
    {   
        printf("[ERROR][BASE/ALLOCATOR/11][Allocation failed]\n");
        return 0;
    }
        
    offset = 0;
    capacity = c; 
    
    return 1;
}

int allocator_destroy()
{
    if (memory == 0)
        return 0;

    free(memory);

    return 1;
}

void* allocator_alloc(const uint64 c)
{
    if (offset + c > capacity)
    {
        printf("[ERROR][BASE/ALLOCATOR/35][Capacity reached]\n");
        return 0;
    }
        
    void* ptr = &memory[offset];
    offset += c;

    memset(ptr, 0, c);
    return ptr;
}