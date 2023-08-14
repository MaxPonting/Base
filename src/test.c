#include "allocator/allocator.h"
#include "window/window.h"
#include "file/file.h"
#include "opengl/opengl.h"
#include "opengl/shader.h"
#include "math/math.h"
#include "log/log.h"

#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_IMPLEMENTATION
#include "nuklear/nuklear.h"

static const uint64 ALLOCATOR_SIZE = 1000000; // 1 MB

int main()
{   
    if(!allocator_create(ALLOCATOR_SIZE))
        return 1;

    if(!window_create(1280, 720, "Window", WINDOW_VERSION_MAJOR_4, WINDOW_VERSION_MINOR_3))
        return 1;

    if(!opengl_create())
        return 1;

    opengl_enable_debug();

    if(!nuklear_create())
        return 1;

    Shader shader;
    {
        char vertex_source[1000];
        char fragment_source[1000];

        file_read("../../res/shader/colour.vert", vertex_source, 1000);
        file_read("../../res/shader/colour.frag", fragment_source, 1000);

        if(!shader_create(&shader, vertex_source, fragment_source))
            return 1;
    }

    mat4 view;
    mat4 projection;

    math_mat4_identity(view);
    math_mat4_transform_2d(view, (vec2){200, 0}, (vec2){100, 100}, math_radians(45));
    math_mat4_identity(projection);
    math_orthographic(projection, -640, 640, -360, 360, -1, 1);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    float32 vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f
    };

    uint32 indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    uint32 vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    uint32 vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, 4 * sizeof(float32), (void*)(0 * sizeof(float)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, 4 * sizeof(float32), (void*)(2 * sizeof(float)));

    uint32 index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    uint32 uniform_buffer;
    glGenBuffers(1, &uniform_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(mat4) * 2, 0, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniform_buffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), view);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), projection);

    while(!window_should_close())
    {
        window_poll_events();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader.program_id);   
        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        nuklear_new_frame();
        if (nk_begin(nuklear_ctx, "Debug", nk_rect(50, 50, 230, 250),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {

        }
        nk_end(nuklear_ctx);
        nuklear_render();
        
        window_swap_buffer();
    }

    nuklear_destroy();
    window_destroy();
    allocator_destroy();
}