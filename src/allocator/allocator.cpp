#include "allocator/allocator.h"
#include "log/log.h"

#include <memory.h>
#include <malloc.h>

namespace Base::Allocator
{
    static UInt8* s_memory;
    static UInt64 s_offset;
    static UInt64 s_size;

    Int32 Create(const UInt64 size)
    {
        s_memory = (unsigned char*)malloc(size);

        if (s_memory == 0)
        {
            Log::Print("Memory allocation failed", Log::TYPE_ERROR, __LINE__, __FILE__);
            return 0;
        }

        s_offset = 0;
        s_size = size;

        return 1;
    }

    Int32 Destroy()
    {
        if (s_memory == 0)
        {
            Log::Print("Linear allocator has no allocation", Log::TYPE_WARNING, __LINE__, __FILE__);
            return 0;
        }

        free(s_memory);

        return 1;
    }

    Int32 Allocate(const UInt64 size, void** ptr)
    {
        if (s_memory == 0)
        {
            Log::Print("Linear allocator has not been created", Log::TYPE_ERROR, __LINE__, __FILE__);
            return 0;
        }
        
        if (s_offset + size > s_size)
        {
            Log::Print("Linear allocator is full", Log::TYPE_ERROR, __LINE__, __FILE__);
            return 0;
        }

        *ptr = &s_memory[s_offset];
        s_offset += size;
        memset(*ptr, 0, size);

        return 1;
    }
}