#pragma once

#include "../log/log.h"
#include "../type/type.h"

#include <memory.h>
#include <malloc.h>

namespace Base::Allocator
{
    UInt8* memory;
    UInt64 offset;
    UInt64 size;

    Int32 Create(const UInt64 _size)
    {
        memory = (unsigned char*)malloc(_size);

        if (memory == 0)
        {
            Log::Print("Memory allocation failed", Log::TYPE_ERROR, __LINE__, __FILE__);
            return 0;
        }

        offset = 0;
        size = _size;

        return 1;
    }

    Int32 Destroy()
    {
        if (memory == 0)
        {
            Log::Print("Linear allocator has no allocation", Log::TYPE_WARNING, __LINE__, __FILE__);
            return 0;
        }

        free(memory);

        return 1;
    }

    Int32 Allocate(const UInt64 _size, void** _ptr)
    {
        if (memory == 0)
        {
            Log::Print("Linear allocator has not been created", Log::TYPE_ERROR, __LINE__, __FILE__);
            return 0;
        }
        
        if (offset + _size > size)
        {
            Log::Print("Linear allocator is full", Log::TYPE_ERROR, __LINE__, __FILE__);
            return 0;
        }

        *_ptr = &memory[offset];
        offset += _size;
        memset(*_ptr, 0, _size);
        return 1;
    }
}