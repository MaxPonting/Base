#include "graphics/quad.h"

int quad_create(Quad* const quad)
{
    quad->position[0] = 0; 
    quad->position[0] = 0;

    quad->size[0] = 10;
    quad->size[0] = 10;

    quad->rotation[0] = 0;
    quad->rotation[1] = 0;
    quad->rotation[2] = 0;

    quad->color[0] = 1;
    quad->color[1] = 1;
    quad->color[2] = 1;
    quad->color[3] = 1;

    return 1;
}