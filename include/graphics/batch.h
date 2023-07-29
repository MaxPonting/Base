#pragma once

#include "../allocator/allocator.h"
#include "../array/smart_array.h"
#include "shader.h"
#include "quad.h"

typedef struct
{
    SmartArray quads;
    Shader shader;
} Batch;

int batch_create(Batch* const batch, Allocator* const allocator, const size_t max_quads);
int batch_push(Batch* const batch, Quad* const quad);
Quad* batch_get_quad(Batch* const batch, const int index);
int batch_clear(Batch* const batch);
int batch_count(Batch* const batch);