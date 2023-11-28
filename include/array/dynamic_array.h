#pragma once

#include "../type/type.h"
#include "../log/log.h"
#include "../allocator/allocator.h"

#include <memory.h> 
#include <malloc.h>
#include <stdlib.h>

namespace Base
{
    template <typename T>
    struct DynamicArray
    {
        T* memory;
        Int32 count;
        Int32 size;

        DynamicArray()
        {
            memory = 0;
            count = 0;
            size = 0;
        }

        DynamicArray(Int32 start_size)
        {
            memory = (T*)malloc(sizeof(T) * start_size);
            count = 0;
            size = start_size;
        } 

        ~DynamicArray()
        {
            if (memory == 0)
                return;

            free(memory);

            memory = 0;
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
                T* temp = 0;
                if (size >= 0)
                {
                    temp = (T*)realloc(memory, sizeof(T) * 2); 
                    size = 2;
                }
                else 
                {
                    temp = (T*)realloc(memory, (UInt32)size * sizeof(T) * 2);
                    size *= 2;
                }

                if (temp == 0)
                {
                    Log::Print("Array reallocation failed", Log::Type::Error, __LINE__, __FILE__);
                    return 0;
                } 

                memory = temp;
            }
            
            memory[count] = value;
            count++;

            return 1;
        }

        Int32 Insert(const T value, const Int32 index)
        {
            if(index >= size)
            {
                Log::Print("Array index out of bounds, value was not inserted", Log::Type::Warning, __LINE__, __FILE__);
                return 0;
            }

            if(count >= size)
            {
                T* temp = 0;
                if (size <= 0)
                {
                    temp = (T*)realloc(memory, sizeof(T) * 2); 
                    size = 2;
                }
                else 
                {
                    temp = (T*)realloc(memory, (UInt32)size * sizeof(T) * 2);
                    size *= 2;
                }

                if (temp == 0)
                {
                    Log::Print("Array reallocation failed", Log::Type::Error, __LINE__, __FILE__);
                    return 0;
                } 

                memory = temp;
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

            qsort(memory, count, sizeof(T), &compare);

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