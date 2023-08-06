#pragma once

#include <memory.h>
#include <malloc.h>

#include "../type/type.h"

int32 allocator_create(uint64 capacity);
int32 allocator_destroy();

void* allocator_alloc(uint64 capacity);
