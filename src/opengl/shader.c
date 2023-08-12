#include "opengl/shader.h"
#include "log/log.h"
#include "vendor/glad/glad.h"

#include <malloc.h>

static uint32 compile(unsigned int type, const char* const source);

int32 shader_create(Shader* const shader, const char* const vertex_source, const char* const fragment_source)
{
    if(shader == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/SHADER", "Shader ptr is null", __LINE__);
        return 0; 
    }

    unsigned int program_id = glCreateProgram();

    unsigned int vertex_id = compile(GL_VERTEX_SHADER, vertex_source);
    if(vertex_id == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/SHADER", "Vertex shader failed to compile", __LINE__);        
        return 0;
    }

    unsigned int fragment_id = compile(GL_FRAGMENT_SHADER, fragment_source);
    if(vertex_id == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/SHADER", "fragment shader failed to compile", __LINE__);        
        return 0;
    }

    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glLinkProgram(program_id);
    glValidateProgram(program_id);

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    shader->program_id = program_id;     

    return 1;
}

int32 shader_destroy(Shader* const shader)
{
    if(shader == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/SHADER", "Shader ptr is null", __LINE__);
        return 0; 
    }

    if(shader->program_id == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/SHADER", "Shader is null", __LINE__);
        return 0; 
    }

    glDeleteProgram(shader->program_id);
        
    return 1;
}

int32 shader_use(const Shader shader)
{
    if(shader.program_id == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/RENDERER", "Shader is null", __LINE__);
        return 0;
    }

    glUseProgram(shader.program_id);

    return 1;
}

static uint32 compile(unsigned int type, const char* const source) 
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, 0);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/SHADER", message, __LINE__);
        glDeleteShader(id);
        return 0;
    }
 
    return id;
}