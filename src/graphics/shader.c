#include "graphics/shader.h"
#include "graphics/renderer.h"

#include <glad/glad.h>

static int compile_shader_gl(unsigned int* const id, unsigned int type, const char* const source);

int shader_create(Shader* const shader, const Renderer* const renderer, const char* const vertex_source, const char* const fragment_source)
{
    if (renderer->type == RENDERER_TYPE_OPENGL)
    {
        shader->program_id = glCreateProgram();
        if(!compile_shader_gl(&shader->vertex_id, GL_VERTEX_SHADER, vertex_source))
            return 0;
        if(!compile_shader_gl(&shader->fragment_id, GL_FRAGMENT_SHADER, fragment_source))
            return 0;

        glAttachShader(shader->program_id, shader->vertex_id);
        glAttachShader(shader->program_id, shader->fragment_id);
        glLinkProgram(shader->program_id);
        glValidateProgram(shader->program_id);

        glDeleteShader(shader->vertex_id);
        glDeleteShader(shader->fragment_id);
    }
    else 
    {
        printf("[ERROR][BASE/GRAPHICS/SHADER/%d][Renderer type not supported]\n", __LINE__);
        return 0;
    }

    return 1;
}

int shader_destroy(Shader* const shader, const Renderer* const renderer)
{
    if (shader->program_id == 0)
    {
        printf("[ERROR][BASE/GRAPHICS/SHADER/%d][Cannot destroy null shader]\n", __LINE__);
        return 0;
    }

    if (renderer->type == RENDERER_TYPE_OPENGL)
    {
        glDeleteProgram(shader->program_id);
    }
    else 
    {
        printf("[ERROR][BASE/GRAPHICS/SHADER/%d][Renderer type not supported]\n", __LINE__);
    }

    return 1;
}

static int compile_shader_gl(unsigned int* const id, unsigned int type, const char* const source)
{
    *id = glCreateShader(type);
    glShaderSource(*id, 1, &source, 0);
    glCompileShader(*id);

    int result;
    glGetShaderiv(*id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(*id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(*id, length, &length, message);
        printf("[ERROR][BASE/GRAPHICS/SHADER/%d][Shader compiliation failed][%s]\n", __LINE__, message);
        glDeleteShader(*id);
        return 0;
    }
 
    return 1;
}