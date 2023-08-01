#include "graphics/renderer.h"
#include "graphics/glad/glad.h"
#include "graphics/glfw/glfw3.h"

static void GLAPIENTRY debug_callback_gl(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

int renderer_create(Renderer* const renderer, Allocator* const allocator, const Window window)
{
    if(window.type == WINDOW_TYPE_GLFW)
    {   
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][Failed to initialize]\n", __LINE__);
            return 0;
        }
        
        glGenVertexArrays(1, &renderer->vertex_array_id);
        glBindVertexArray(renderer->vertex_array_id);

        float vertices[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
            -0.5f,  0.5f,
             0.5f,  0.5f
        };

        glGenBuffers(1, &renderer->vertex_buffer_id);
        glBindBuffer(GL_ARRAY_BUFFER, renderer->vertex_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, 0, 2 * sizeof(float), (void*)(0 * sizeof(float)));

        unsigned int indices[] = {
            0, 1, 2,
            1, 2, 3
        };

        glGenBuffers(1, &renderer->index_buffer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->index_buffer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        renderer->type = RENDERER_TYPE_OPENGL;
        renderer->last_shader_id = 0;
        renderer->quad_count = 0;
        renderer->shader_swap_count = 0;
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
        renderer->quad_count = 0;
        renderer->shader_swap_count = 0;
        renderer->last_shader_id = 0;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(debug_callback_gl, 0);

        int width = 0;
        int height = 0;
        window->w = width;
        window->h = height;
        glfwGetFramebufferSize(window->ptr, &width, &height);
        glViewport(0, 0, width, height);
        glm_ortho(-width / 2, width / 2, -height / 2, height / 2, -1.0f, 1.0f, camera->projection);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else
    {
        printf("[WARNING][BASE/GRAPHICS/RENDERER/%d][Renderer type not supported]\n", __LINE__);
    }

    return 1;
}

int renderer_draw(
    Renderer* const renderer, 
    Camera* const camera, 
    const vec2 position, 
    const vec2 size, 
    const float rotation,
    const vec4 color,
    const Shader shader
)
{
    if (renderer->type == RENDERER_TYPE_OPENGL)
    {      
        mat4 model;
        glm_mat4_identity(model);
        glm_translate(model, (vec4){position[0], position[1], 0, 0});
        glm_rotate(model, glm_rad(rotation), (vec4){0, 0, 1, 0});
        glm_scale(model, (vec4){size[0], size[1], 0, 0});
        
        camera_set_view(camera);

        if (renderer->last_shader_id == 0 || renderer->last_shader_id != shader.program_id)
        {
            glUseProgram(shader.program_id);

            if(!shader_set_mat4(shader, "u_View", camera->view))
            {
                printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 view\" is not defined in vertex shader]", __LINE__);
                return 0;
            }
            if(!shader_set_mat4(shader, "u_Projection", camera->projection))
            {
                printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 projection\" is not defined in vertex shader]", __LINE__);
                return 0;
            }
            
            renderer->last_shader_id = shader.program_id;
            renderer->shader_swap_count++;
        }

        if(!shader_set_mat4(shader, "u_Model", model))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 model\" is not defined in vertex shader]", __LINE__);
            return 0;
        }
        if(!shader_set_vec4(shader, "u_Color", color))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform vec3 color\" is not defined in vertex shader]", __LINE__);
            return 0;
        }

        glBindVertexArray(renderer->vertex_array_id);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    else
    {
        printf("[WARNING][BASE/GRAPHICS/RENDERER/%d][Renderer type not supported]\n", __LINE__);
        return 0;
    }

    renderer->quad_count++;

    return 1;
}

static void GLAPIENTRY debug_callback_gl(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) 
{
    printf("[ERROR][GRAPHICS/RENDERER/OPENGL][SOURCE:%d][TYPE:%d][ID:%d][SEVERITY:%d][%s]\n", source, type, id, severity, message);
}



