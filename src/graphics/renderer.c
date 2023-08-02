#include "graphics/renderer.h"
#include "graphics/glad/glad.h"
#include "graphics/glfw/glfw3.h"

static void GLAPIENTRY debug_callback_gl(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

static const char* shader_vertex_color_source;
static const char* shader_fragment_color_source;
static const char* shader_vertex_texture_source;
static const char* shader_fragment_texture_source;

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
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 1.0f,
             0.5f,  0.5f, 1.0f, 1.0f
        };

        glGenBuffers(1, &renderer->vertex_buffer_id);
        glBindBuffer(GL_ARRAY_BUFFER, renderer->vertex_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, 0, 4 * sizeof(float), (void*)(0 * sizeof(float)));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, 0, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        unsigned int indices[] = {
            0, 1, 2,
            1, 2, 3
        };

        glGenBuffers(1, &renderer->index_buffer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->index_buffer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        renderer->type = RENDERER_TYPE_OPENGL;
        renderer->last_shader_id = 0;
        renderer->render_time_s = 0;
        renderer->quad_count = 0;
        renderer->shader_swap_count = 0;

        if(!shader_create(&renderer->shader_color, *renderer, shader_vertex_color_source, shader_fragment_color_source))
            return 0;
        if(!shader_create(&renderer->shader_texture, *renderer, shader_vertex_texture_source, shader_fragment_texture_source)) 
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
    if (renderer->type = RENDERER_TYPE_OPENGL)
    {   
        glDeleteProgram(renderer->shader_color.program_id);
        glDeleteProgram(renderer->shader_texture.program_id);
        glDeleteBuffers(1, &renderer->vertex_buffer_id);
        glDeleteBuffers(1, &renderer->index_buffer_id);
        glDeleteVertexArrays(1, &renderer->vertex_array_id);
    }
    else 
    {
        printf("[WARNING][BASE/GRAPHICS/RENDERER/%d][Renderer type not supported]\n", __LINE__);
        return 0;
    }

    renderer->type = RENDERER_TYPE_NULL;

    return 1;
}

int renderer_clear(Renderer* const renderer, Window* const window, Camera* const camera)
{
    if (renderer->type == RENDERER_TYPE_OPENGL)
    {   
        static uint64_t last_time_value;
        uint64_t time_value = glfwGetTimerValue();
        renderer->render_time_s = (double)(time_value - last_time_value) / (double)glfwGetTimerFrequency();
        last_time_value = time_value;

        renderer->quad_count = 0;
        renderer->shader_swap_count = 0;
        renderer->last_shader_id = 0;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(debug_callback_gl, 0);

        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(window->ptr, &width, &height);
        window->w = width;
        window->h = height;
        glViewport(0, 0, width, height);
        glm_ortho(-width / 2, width / 2, -height / 2, height / 2, -1.0f, 1.0f, camera->projection);

        camera_set_view(camera, (vec2){width, height});

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else
    {
        printf("[WARNING][BASE/GRAPHICS/RENDERER/%d][Renderer type not supported]\n", __LINE__);
        return 0;
    }

    return 1;
}

int renderer_draw_color(
    Renderer* const renderer, 
    Camera* const camera, 
    const vec2 position, 
    const vec2 size, 
    const float rotation,
    const vec4 color
)
{
    if (renderer->type == RENDERER_TYPE_OPENGL)
    {      
        mat4 model;
        glm_mat4_identity(model);
        glm_translate(model, (vec4){position[0], position[1], 0, 0});
        glm_rotate(model, glm_rad(rotation), (vec4){0, 0, 1, 0});
        glm_scale(model, (vec4){size[0], size[1], 0, 0});
             
        if (renderer->last_shader_id == 0 || renderer->last_shader_id != renderer->shader_color.program_id)
        {
            glUseProgram(renderer->shader_color.program_id);

            if(!shader_set_mat4(renderer->shader_color, "u_View", camera->view))
            {
                printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 u_View\" is not defined in vertex shader]", __LINE__);
                return 0;
            }
            if(!shader_set_mat4(renderer->shader_color, "u_Projection", camera->projection))
            {
                printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 u_Projection\" is not defined in vertex shader]", __LINE__);
                return 0;
            }
            
            renderer->last_shader_id = renderer->shader_color.program_id;
            renderer->shader_swap_count++;
        }

        if(!shader_set_mat4(renderer->shader_color, "u_Model", model))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 u_Model\" is not defined in vertex shader]", __LINE__);
            return 0;
        }
        if(!shader_set_4f(renderer->shader_color, "u_Color", color))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform vec3 u_Color\" is not defined in fragment shader]", __LINE__);
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

int renderer_draw_texture(
    Renderer* const renderer, 
    Camera* const camera, 
    const vec2 position, 
    const vec2 size, 
    const float rotation,
    const vec4 color,
    const SubTexture sub_texture
)
{
    if (renderer->type == RENDERER_TYPE_OPENGL)
    {      
        mat4 model;
        glm_mat4_identity(model);
        glm_translate(model, (vec4){position[0], position[1], 0, 0});
        glm_rotate(model, glm_rad(rotation), (vec4){0, 0, 1, 0});
        glm_scale(model, (vec4){size[0], size[1], 0, 0});
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sub_texture.texture->id);
        
        if (renderer->last_shader_id == 0 || renderer->last_shader_id != renderer->shader_texture.program_id)
        {
            glUseProgram(renderer->shader_texture.program_id);

            if(!shader_set_mat4(renderer->shader_texture, "u_View", camera->view))
            {
                printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 u_View\" is not defined in vertex shader]", __LINE__);
                return 0;
            }
            if(!shader_set_mat4(renderer->shader_texture, "u_Projection", camera->projection))
            {
                printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 u_Projection\" is not defined in vertex shader]", __LINE__);
                return 0;
            }
            
            renderer->last_shader_id = renderer->shader_texture.program_id;
            renderer->shader_swap_count++;
        }

        if(!shader_set_mat4(renderer->shader_texture, "u_Model", model))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform mat4 u_Model\" is not defined in vertex shader]", __LINE__);
            return 0;
        }
        if(!shader_set_2f(renderer->shader_texture, "u_TextureSize", (float[]){ sub_texture.texture->width, sub_texture.texture->height }))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform vec2 u_TextureSize\" is not defined in vertex shader]", __LINE__);
            return 0;
        }
        if(!shader_set_2f(renderer->shader_texture, "u_SubTextureIndex", sub_texture.index))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform vec2 u_SubTextureIndex\" is not defined in vertex shader]", __LINE__);
            return 0;
        }
        if(!shader_set_2f(renderer->shader_texture, "u_SubTextureSize", sub_texture.sprite_size))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform vec2 u_SubTextureSize\" is not defined in vertex shader]", __LINE__);
            return 0;
        }

        if(!shader_set_4f(renderer->shader_texture, "u_Color", color))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform vec3 u_Color\" is not defined in fragment shader]", __LINE__);
            return 0;
        }
        if(!shader_set_1iv(renderer->shader_texture, "u_Textures", (int[]){ 0, 1, 2, 3 }, 4))
        {
            printf("[ERROR][BASE/GRAPHICS/RENDERER/%d][\"uniform sampler2D u_Textures\" is not defined in fragment shader]", __LINE__);
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

int renderer_set_native_resolution(Renderer* const renderer, const vec2 resolution)
{
    return 1;
}

static void GLAPIENTRY debug_callback_gl(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) 
{
    printf("[ERROR][GRAPHICS/RENDERER/OPENGL][SOURCE:%d][TYPE:%d][ID:%d][SEVERITY:%d][%s]\n", source, type, id, severity, message);
}

static const char* shader_vertex_color_source = "#version 330 core\n\nlayout(location = 0) in vec4 a_Position;layout(location = 1) in vec2 a_TextureCoordinates;uniform mat4 u_Model;uniform mat4 u_View;uniform mat4 u_Projection;void main(){gl_Position = u_Projection * u_View * u_Model * a_Position;}";
static const char* shader_fragment_color_source = "#version 330 core\n\nuniform vec4 u_Color;out vec4 o_Color;void main(){o_Color = u_Color;}";

static const char* shader_vertex_texture_source = "#version 330 core\n\nlayout(location = 0) in vec4 a_Position;layout(location = 1) in vec2 a_TextureCoordinates;uniform mat4 u_Model;uniform mat4 u_View;uniform mat4 u_Projection;uniform vec2 u_TextureSize;uniform vec2 u_SubTextureIndex;uniform vec2 u_SubTextureSize;out vec2 v_TextureCoordinates;void main(){gl_Position = u_Projection * u_View * u_Model * a_Position;v_TextureCoordinates = ((u_SubTextureIndex + a_TextureCoordinates) * u_SubTextureSize) / u_TextureSize;}";
static const char* shader_fragment_texture_source = "#version 330 core\n\nin vec2 v_TextureCoordinates;uniform vec4 u_Color;uniform sampler2D u_Textures[4];out vec4 o_Color;void main(){o_Color = texture2D(u_Textures[0], v_TextureCoordinates) * u_Color;}";