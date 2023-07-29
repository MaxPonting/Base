#pragma once

#include "../allocator/allocator.h"

#include <stdio.h>

typedef struct 
{
    char* ptr;
    size_t size;
} String;

void string_create(String* const string, Allocator* const allocator, char* const c_string);
void string_set(String* const string, char* const ptr, const size_t size);
char string_index(String* const string, const size_t index);
