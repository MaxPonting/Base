#pragma once

#include "../type/type.h"
#include "../vendor/glad/glad.h"

typedef struct
{
   uint32 program_id; 
} Shader;

int32 shader_create(Shader* const shader, const char* const vertex_source, const char* const fragment_source);
int32 shader_destroy(Shader* const shader);

int32 shader_use(const Shader shader);
