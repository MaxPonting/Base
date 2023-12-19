#pragma once

#include "../type/type.h"
#include "../log/log.h"
#include "../allocator/allocator.h"

#include <memory.h> 
#include <stdlib.h>

namespace Base
{
    template <typename T>
    struct HeapArray
    {
        T* memory;
        Int32 count;
        Int32 size;
        
        HeapArray()
        {
            memory = 0;
            count = 0;
            size = 0;
        };
  
        HeapArray(Int32 _size)
        {
            memory = (T*)Allocator::Allocate(_size * sizeof(T));

            if(memory == 0)
            {
                Log::Print("Allocator has not been created, exiting application", Log::Type::Error, __LINE__, __FILE__);
                exit(0);
            }

            count = 0;
            size = _size;
        };

        Int32 Deallocate()
        {
            if(memory == 0 || size == 0)
            {
                return 0; 
            }

            Allocator::Deallocate(size * sizeof(T));

            return 1;
        }

        T& operator[](const Int32 index) 
        { 
            if (index >= size || index < 0)
            {
                Log::Print("Array index out of bounds", Log::Type::Error, __LINE__, __FILE__);
                exit(0);
            }

            return memory[index]; 
        } 

        T operator[](const Int32 index) const 
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

        Int32 Insert(const Int32 index, const T value)
        {
            if(index >= size || index < 0)
            {
                Log::Print("Array index out of bounds", Log::Type::Error, __LINE__, __FILE__);
                return 0;
            }

            if(count == size)
            {
                memory[index] = value;
                return 1;
            }

            if(index >= count)
            {
                memory[index] = value;
                count = index + 1;
                return 1;
            }

            const UInt64 moveSize = (count - index) * sizeof(T);

            T* temp = (T*)Allocator::Allocate(moveSize);

            memcpy(temp, memory + index, moveSize);
            memcpy(memory + index + 1, temp, moveSize);

            memory[index] = value;
            count++;

            Allocator::Deallocate(moveSize);

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