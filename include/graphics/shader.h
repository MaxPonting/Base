#pragma once

#include "cglm/struct.h"

typedef struct
{
    unsigned int program_id;
    unsigned int vertex_id;
    unsigned int fragment_id;
} Shader;

typedef struct Renderer Renderer;

int shader_create(Shader* const shader, const Renderer renderer, const char* const vertex_source, const char* const fragment_source);
int shader_destroy(Shader* const shader, const Renderer renderer);

int shader_set_1i(const Shader shader, const char* const name, const int value);
int shader_set_1iv(const Shader shader, const char* const name, const int* values, const int count);
int shader_set_2f(const Shader shader, const char* const name, const vec2 value);
int shader_set_4f(const Shader shader, const char* const name, const vec4 value);
int shader_set_mat4(const Shader shader, const char* const name, const mat4 value);