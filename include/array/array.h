#pragma once

#include "../type/type.h"
#include "../log/log.h"
#include "../allocator/allocator.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h> 

namespace Base
{
    template <typename T>
    struct Array
    {
        T* memory;
        Int32 count;
        Int32 size;
        
        Array()
        {
            memory = 0;
            count = 0;
            size = 0;
        };
  
        Array(Int32 _size)
        {
            memory = 0;
            Allocator::Allocate(_size, (void**)&memory);

            if(memory == 0)
            {
                Log::Print("Allocator has not been created, exiting application", Log::Type::Error, __LINE__, __FILE__);
                exit(0);
            }

            count = 0;
            size = _size;
        };

        T& Item(const Int32 index)
        {
            if (index >= size)
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

        Int32 Insert(const T value, const Int32 index)
        {
            if(count == size || count == size - 1)
            {
                Log::Print("Array size reached, value was not inserted", Log::Type::Warning, __LINE__, __FILE__);
                return 0;
            }
            
            if(index >= size)
            {
                Log::Print("Array index out of bounds, value was not inserted", Log::Type::Warning, __LINE__, __FILE__);
                return 0;
            }

            memcpy((UInt8*)memory + (index + 1) * sizeof(T), (UInt8*)memory + index * sizeof(T), sizeof(T) * (count - index));
            memory[index] = value;
            count++;

            return 1;
        }

        Int32 Delete(const Int32 index)
        {
            if(count == 0)
            {
                Log::Print("Array count is 0, value was not deleted", Log::Type::Warning, __LINE__, __FILE__);
                return 0;
            }

            if(index >= size)
            {
                Log::Print("Array index out of bounds", Log::Type::Warning, __LINE__, __FILE__);
                return 0;
            }

            if(index >= count)
            {
                Log::Print("Array index is larger than array count", Log::Type::Warning, __LINE__, __FILE__);
                return 0;
            }

            memcpy((UInt8*)memory + index * sizeof(T), (UInt8*)memory + (index + 1) * sizeof(T), sizeof(T) * (count - index));
            count--;

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


    };
}