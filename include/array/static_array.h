#pragma once

#include "../type/type.h"
#include "../log/log.h"
#include "../allocator/allocator.h"

#include <stdlib.h>
#include <stdio.h>

namespace Base
{
    template <typename T, Int32 size>
    struct StaticArray
    {
        T memory[size];
        Int32 count;
        
        StaticArray()
        {
            count = 0;
            memset(memory, 0, size * sizeof(T));
        };
  
        T& Item(const Int32 index)
        {
            if (index >= size || index < 0)
            {
                Log::Print("Array index out of bounds", Log::Type::Error, __LINE__, __FILE__);
                exit(0);
            }
            
            return memory[index];
        }

        Int32 Push(const T value)
        {
            if(count == size)
            {
                Log::Print("Array size reached, value was not pushed", Log::Type::Warning, __LINE__, __FILE__);
                return 0;
            }
            
            memory[count] = value;
            count++;

            return 1;
        }

        Int32 Sort(Int32(&compare)(const void*, const void*))
        {
            if(count < 2)
            {
                Log::Print("Array not sorted count is less than 2", Log::Type::Message, __LINE__, __FILE__);
                return 1;
            }

            qsort(memory, count, sizeof(T), compare);

            return 1;
        }

        Int32 Clear()
        {
            memset(memory, 0, size * sizeof(T));
            count = 0;

            return 1;
        }

        Int32 GetSize()
        {
            return size;
        }
    };
}