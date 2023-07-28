#include "graphics/batch.h"

int batch_create(Batch* const batch, Allocator* const allocator, const size_t max_quads)
{
    if(!smart_array_create(&batch->quads, allocator, sizeof(Quad), max_quads))
        return 0;
    
    return 1;
}

int batch_push(Batch* const batch, Quad* const quad)
{
    if(!smart_array_push(&batch->quads, quad))
        return 0;

    return 1;
}

Quad* batch_get_quad(Batch* const batch, const int index)
{
    if(!smart_array_index(&batch->quads, index))
        return 0;
    
    return (Quad*)smart_array_index(&batch->quads, index);
}

int batch_clear(Batch* const batch)
{
    if(!smart_array_clear(&batch->quads))
        return 0;

    return 1;
}

int batch_count(Batch* const batch)
{   
    return batch->quads.size;
}