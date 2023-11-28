#pragma once

#include "../log/log.h"
#include "../type/type.h"
#include "../platform/platform.h"

#include <memory.h>
#include <malloc.h>
#include <stdio.h>

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
            Log::Print("Memory allocation failed", Log::Type::Error, __LINE__, __FILE__);
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
            Log::Print("Linear allocator has no allocation", Log::Type::Warning, __LINE__, __FILE__);
            return 0;
        }

        free(memory);

        return 1;
    }

    void* Allocate(const UInt64 _size)
    {
        if (memory == 0)
        {
            Log::Print("Linear allocator has not been created", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
        
        if (offset + _size > size)
        {
            char log[256];
#if PLATFORM == PLATFORM_WINDOWS
            sprintf(log, "Linear allocator is full, Size:%I64u, Offset:%I64u, New Offset:%I64u", size, offset, offset + _size);
#elif PLATFORM == PLATFORM_LINUX || PLATFORM_MAC
            sprintf(log, "Linear allocator is full, Size:%llu, Offset:%llu, New Offset:%llu", size, offset, offset + _size);
#endif
            Log::Print(log, Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        void* ptr = &memory[offset];
        offset += _size;
        memset(ptr, 0, _size);

        return ptr;
    }

    Int32 Deallocate(const UInt64 _size)
    {
        if (memory == 0)
        {
            Log::Print("Linear allocator has not been created", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        if (offset == 0)
        {
            Log::Print("Linear allocator is empty", Log::Type::Warning, __LINE__, __FILE__);
            return 0;
        }

        if((Int64)offset - (Int64)_size < 0)
            offset = 0;
        else 
            offset -= _size;

        return 1;
    }
}