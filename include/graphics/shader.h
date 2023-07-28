#pragma once

typedef struct
{
    unsigned int program_id;
    unsigned int vertex_id;
    unsigned int fragment_id;
} Shader;

typedef struct Renderer Renderer;

int shader_create(Shader* const shader, const Renderer* const renderer, const char* const vertex_source, const char* const fragment_source);
int shader_destroy(Shader* const shader, const Renderer* const renderer);