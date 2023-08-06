#include "string/string.h"
#include "allocator/allocator.h"
#include <stdio.h>

void string_create(String* const string, char* const c_string)
{   
    uint64 size = 0;
    while(1)
    {
        size++;
        if (c_string[size] == '\0') break;                   
    }

    string->ptr = (char*)allocator_alloc(sizeof(char) * (size + 1));
    string->size = size;
    memcpy(string->ptr, c_string, size);
    string->ptr[size] = '\0';
}

void string_set(String* const string, char* const ptr, const uint64 size)
{
    string->ptr = ptr;
    string->size = size;
}

char string_index(String* const string, const uint64 index)
{
    if (index >= string->size)
    {
        printf("String: Cannot get char at or above string size");
        return 0;
    }

    return string->ptr[index];
}

