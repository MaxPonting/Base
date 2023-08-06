#pragma once

#include "../type/type.h"

typedef struct 
{
    char* ptr;
    uint64 size;
} String;

void string_create(String* const string, char* const c_string);
void string_set(String* const string, char* const ptr, const uint64 size);
char string_index(String* const string, const uint64 index);
