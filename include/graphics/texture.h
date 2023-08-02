#pragma once

typedef struct 
{
    unsigned int id;
    int width, height, bits_per_pixel;
    int cell_width, cell_height;
} Texture;

typedef struct Renderer Renderer;

int texture_create(Texture* const texture, const Renderer renderer, const char* const file_path, const int cell_width, const int cell_height);
int texture_destroy(Texture* const texture, const Renderer renderer);