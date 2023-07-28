#include "graphics/renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void GLAPIENTRY debug_callback_gl(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

int renderer_create(Renderer* const renderer, Allocator* const allocator, const Window* const window, const int max_quads_per_draw)
{
    if(window->type == WINDOW_TYPE_GLFW)
    {   
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][Failed to initialize]\n", __LINE__);
            return 0;
        }
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(debug_callback_gl, 0);

        glViewport(0, 0, window->w, window->h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        glGenVertexArrays(1, &renderer->vertex_array_id);
        glBindVertexArray(renderer->vertex_array_id);

        glGenBuffers(1, &renderer->vertex_buffer_id);
        glBindBuffer(GL_ARRAY_BUFFER, renderer->vertex_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, max_quads_per_draw * sizeof(float) * sizeof(Vertex) * 4, 0, GL_DYNAMIC_DRAW);

        glEnableVertexArrayAttrib(renderer->vertex_array_id, 0);
        glVertexAttribPointer(0, 2, GL_FLOAT, 0, 6 * sizeof(float), (void*)0);
      
        glEnableVertexArrayAttrib(renderer->vertex_array_id, 1);
        glVertexAttribPointer(1, 4, GL_FLOAT, 0, 6 * sizeof(float), (void*)(2 * sizeof(float)));

        unsigned int* indices = allocator_alloc(allocator, sizeof(unsigned int) * max_quads_per_draw * 6);

        int count = 0;
        for (int i = 0; i < max_quads_per_draw * 6; i+=6)
        {
            indices[i + 0] = count + 0;
            indices[i + 1] = count + 1;
            indices[i + 2] = count + 2;
            indices[i + 3] = count + 2;
            indices[i + 4] = count + 3;
            indices[i + 5] = count + 0;

            count+=4;
        }
        
        glGenBuffers(1, &renderer->index_buffer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->index_buffer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * max_quads_per_draw * 6, indices, GL_DYNAMIC_DRAW);

        renderer->type = RENDERER_TYPE_OPENGL;
        renderer->max_quads_per_draw = max_quads_per_draw;
        renderer->vertices = allocator_alloc(allocator, max_quads_per_draw * sizeof(Vertex) * 4);
        if (!renderer->vertices)       
            return 0;        
    }
    else
    {
        printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][Window type not supported]\n", __LINE__);
        return 0;
    }

    return 1;
}

int renderer_destroy(Renderer* const renderer)
{
    renderer->type = RENDERER_TYPE_NULL;

    return 1;
}

int renderer_clear(Renderer* const renderer, Window* const window, Camera* const camera)
{
    if (renderer->type == RENDERER_TYPE_OPENGL)
    {   
        int width = 0;
        int height = 0;
        window->w = width;
        window->h = height;
        glfwGetFramebufferSize(window->ptr, &width, &height);
        glViewport(0, 0, width, height);
        glm_ortho(-width / 2, width / 2, -height / 2, height / 2, -1.0f, 1.0f, camera->projection);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else
    {
        printf("[WARNING][BASE/GRAPHICS/RENDERER/%d][Renderer type not supported]\n", __LINE__);
    }

    return 1;
}

int renderer_draw(Renderer* const renderer, Camera* const camera, Batch* const batch)
{
    camera_set_mvp(camera);

    int count = batch_count(batch);
    if (count > renderer->max_quads_per_draw)
    {
        count = renderer->max_quads_per_draw;
        printf("[WARNING][BASE/GRAPHICS/RENDERER/%d][Max quads count reached, drawing maxed]\n", __LINE__);
    }

    if (renderer->type == RENDERER_TYPE_OPENGL)
    {      
        for (int i = 0; i < count * 4; i+=4)
        {   
            Quad* quad = batch_get_quad(batch, i / 4);

            renderer->vertices[i + 0] = (Vertex){{ -0.5f, -0.5f }, { quad->color[0], quad->color[1], quad->color[2], quad->color[3] }};
            renderer->vertices[i + 1] = (Vertex){{  0.5f, -0.5f }, { quad->color[0], quad->color[1], quad->color[2], quad->color[3] }};
            renderer->vertices[i + 2] = (Vertex){{  0.5f,  0.5f }, { quad->color[0], quad->color[1], quad->color[2], quad->color[3] }};
            renderer->vertices[i + 3] = (Vertex){{ -0.5f,  0.5f }, { quad->color[0], quad->color[1], quad->color[2], quad->color[3] }};
        
            for (int j = 0; j < 4; j++)
            {   
                renderer->vertices[i + j].position[0] *= quad->size[0];
                renderer->vertices[i + j].position[1] *= quad->size[1];

                vec3 rotated_vertices;
                rotated_vertices[0] = renderer->vertices[i + j].position[0];
                rotated_vertices[1] = renderer->vertices[i + j].position[1];
                rotated_vertices[2] = 0;

                glm_vec3_rotate(
                    rotated_vertices, 
                    glm_rad(quad->rotation[0]), 
                    (vec3){1.0f, 0.0f, 0.0f}
                );

                glm_vec3_rotate(
                    rotated_vertices, 
                    glm_rad(quad->rotation[1]), 
                    (vec3){0.0f, 1.0f, 0.0f}
                );

                glm_vec3_rotate(
                    rotated_vertices, 
                    glm_rad(quad->rotation[2]), 
                    (vec3){0.0f, 0.0f, 1.0f}
                );

                renderer->vertices[i + j].position[0] = rotated_vertices[0];
                renderer->vertices[i + j].position[1] = rotated_vertices[1];

                renderer->vertices[i + j].position[0] += quad->position[0];
                renderer->vertices[i + j].position[1] += quad->position[1];         
            }         
        }

        glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * sizeof(Vertex) * 4, renderer->vertices);

        glUseProgram(batch->shader.program_id);

        int location = glGetUniformLocation(batch->shader.program_id, "model");
        if (location == -1)
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 model\" is not defined in vertex shader]", __LINE__);
            return 0;
        }
        glUniformMatrix4fv(location, 1, 0, (float*)camera->model);
        location = glGetUniformLocation(batch->shader.program_id, "view");
        if (location == -1)
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 view\" is not defined in vertex shader]", __LINE__);
            return 0;
        }
        glUniformMatrix4fv(location, 1, 0, (float*)camera->view);
        location = glGetUniformLocation(batch->shader.program_id, "projection");
        if (location == -1)
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 projection\" is not defined in vertex shader]", __LINE__);
            return 0;
        }
        glUniformMatrix4fv(location, 1, 0, (float*)camera->projection);

        glDrawElements(GL_TRIANGLES, count * 6, GL_UNSIGNED_INT, 0);
    }
    else
    {
        printf("[WARNING][BASE/GRAPHICS/RENDERER/%d][Renderer type not supported]\n", __LINE__);
        return 0;
    }

    return 1;
}

static void GLAPIENTRY debug_callback_gl(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) 
{
    printf("[ERROR][GRAPHICS/RENDERER/OPENGL][%d][%s]\n", type, message);
}

