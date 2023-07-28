#include "graphics/resource_manager.h"

#include <stdio.h>

static int load_shader_from_file(char* const line_buffer, const int line_size, char* const shader_buffer, const int shader_size, const char* const file_path);

int resource_manager_create(ResourceManager* const resource_manager, Allocator* const allocator, const int max_line_size, const int max_shader_size)
{   
    resource_manager->line_size = max_line_size;
    resource_manager->line_buffer = allocator_alloc(allocator, max_line_size);

    resource_manager->shader_size = max_shader_size;
    resource_manager->vertex_buffer = allocator_alloc(allocator, max_shader_size);
    resource_manager->fragment_buffer = allocator_alloc(allocator, max_shader_size);

    return 1;
}

int resource_manager_load_shader(ResourceManager* const resource_manager, const char* const vertex_file_path, const char* const fragment_file_path)
{
    if(!load_shader_from_file(resource_manager->line_buffer, resource_manager->line_size, resource_manager->vertex_buffer, resource_manager->shader_size, vertex_file_path))
        return 0;

    if(!load_shader_from_file(resource_manager->line_buffer, resource_manager->line_size, resource_manager->fragment_buffer, resource_manager->shader_size, fragment_file_path))
        return 0;

    return 1;
}

int resource_manager_load_texture(ResourceManager* const resource_manager, const char* const file_path)
{
    return 1;
}

static int load_shader_from_file(char* const line_buffer, const int line_size, char* const shader_buffer, const int shader_size, const char* const file_path)
{
    FILE* file_stream;
    file_stream = fopen(file_path, "r");

    if(file_stream == 0)
    {
        printf("[ERROR][BASE/GRAPHICS/RESOURCE_MANAGER/%d][File failed to open]\n", __LINE__);
        return 0;
    }

    int count = 0;
    while (fgets(line_buffer, line_size, file_stream))
    {
        int i = 0;
        while(1)
        {
            if (line_buffer[i] == '\0')
                break;

            shader_buffer[count] = line_buffer[i];
            i++;
            count++;
        }

        if (count == shader_size)
        {
            printf("[ERROR][BASE/GRAPHICS/RESOURCE_MANAGER/%d][Shader buffer capacity reached!]\n", __LINE__);
            return 0;
        }
    }

    shader_buffer[count] = '\0';

    //printf("%s\n", shader_buffer);

    fclose(file_stream);

    return 1;
}

