#include "array/smart_array.h"
#include "allocator/allocator.h"

#include <stdio.h>
#include <stdlib.h>

int32 smart_array_create(SmartArray* const smart_array, uint64 element_size, uint64 capacity)
{
    smart_array->memory = allocator_alloc(capacity * element_size);

    if (smart_array->memory == 0)
    {
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Creation failed]\n", __LINE__);
        return 0;
    }

    smart_array->element_size = element_size;
    smart_array->capacity = capacity;
    smart_array->size = 0;

    return 1;
}

void* smart_array_index(SmartArray* const smart_array, const uint64 index)
{
    if (index >= smart_array->size)
    {
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Cannot get data at or above array size]\n", __LINE__);
        return 0;
    }

    return &(smart_array->memory)[index * smart_array->element_size];
}

int32 smart_array_push(SmartArray* const smart_array, const void* const ptr)
{
    if (smart_array->size == smart_array->capacity)
    {   
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Capacity reached, data was not pushed][Capacity: %I64d, Size: %I64d]\n", __LINE__, smart_array->capacity, smart_array->size);
        return 0;
    }
  
    memcpy(smart_array->memory + smart_array->size * smart_array->element_size, ptr, smart_array->element_size);
    smart_array->size++;

    return 1;
}

int32 smart_array_insert(SmartArray* const smart_array, const void* const ptr, const uint64 index)
{
    if (smart_array->size == smart_array->capacity)
    {   
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Capacity reached, data was not inserted]\n", __LINE__);
        return 0;
    }

    if (index >= smart_array->size)
    {
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Cannot insert data at or above array size]\n", __LINE__);
        return 0;
    }
    
    memcpy(smart_array->memory + (index + 1) * smart_array->element_size, smart_array->memory + index * smart_array->element_size, smart_array->element_size * (smart_array->size - index));
    memcpy(smart_array->memory + index * smart_array->element_size, ptr, smart_array->element_size);
    smart_array->size++;

    return 1;
}

int32 smart_array_sort(SmartArray* const smart_array, int(*compar)(const void*, const void*), const uint64 start_index, const uint64 end_index)
{   
    if (smart_array->size < 2)    
    {   
        printf("[MESSAGE][BASE/ARRAY/SMART_ARRAY/%d][Array not sorted, size is less 2]\n", __LINE__);
        return 0;
    }
        
    if (start_index >= smart_array->size)
    {   
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Array not sorted, start_index is larger than array size]\n", __LINE__);
        return 0;
    }

    if (end_index >= smart_array->size)
    {   
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Array not sorted, end_index is larger than array size]\n", __LINE__);
        return 0;
    }

    if (start_index > end_index)
    {   
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Array not sorted, start_index is larger than end_index]\n", __LINE__);
        return 0;
    }
       
    const uint64 count = (end_index - start_index) + 1;

    if (count < 2)
    {
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Array not sorted, count is less than 2]\n", __LINE__);
        return 0;
    }

    qsort(smart_array->memory + start_index * smart_array->element_size, count, smart_array->element_size, compar);
        
    return 1;
}

int32 smart_array_clear(SmartArray* const smart_array)
{
    smart_array->size = 0;

    return 1;
}

int32 smart_array_delete(SmartArray* const smart_array, const uint64 index)
{
    if (smart_array->size == 0)
    {   
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Capacity is 0, index was not deleted]\n", __LINE__);
        return 0;
    }

    if (index >= smart_array->size)
    {
        printf("[WARNING][BASE/ARRAY/SMART_ARRAY/%d][Cannot delete data at or above array size]\n", __LINE__);
        return 0;
    }
  
    memcpy(smart_array->memory + index * smart_array->element_size, smart_array->memory + (index + 1) * smart_array->element_size, smart_array->element_size * (smart_array->size - index));
    smart_array->size--;

    return 1;
}

