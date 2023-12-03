#pragma once

#include "../type/type.h"
#include "../log/log.h"
#include "../allocator/allocator.h"

#include <stdlib.h>
#include <initializer_list>

namespace Base
{
    template <typename T, Int32 size>
    struct Array
    {
        T memory[size];
        Int32 count;
        
        Array()
        {
            count = 0;
            memset(memory, 0, size * sizeof(T));
        };

        Array(std::initializer_list<T> elements)
        {
            if(elements.size() > size)
                exit(0);

            memcpy(memory, elements.begin(), elements.size() * sizeof(T));
            memset(memory + elements.size(), 0, (size - elements.size()) * sizeof(T));
            count = elements.size();
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
                Log::Print("Array size reached, value was not inserted", Log::Type::Warning, __LINE__, __FILE__);
                return 0;
            }

            if(index >= count)
            {
                memory[count] = value;
                count++;
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

        Int32 GetSize() const
        {
            return size;
        }
    };
}