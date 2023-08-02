#pragma once

#include "../allocator/allocator.h"

typedef struct 
{
    int line_size, shader_size;
    char *line_buffer, *vertex_buffer, *fragment_buffer;
} ResourceManager;

int resource_manager_create(ResourceManager* const resource_manager, Allocator* const allocator, const int max_line_size, const int max_shader_size);
int resource_manager_load_shader(ResourceManager* const resource_manager, const char* const vertex_file_path, const char* const fragment_file_path);
