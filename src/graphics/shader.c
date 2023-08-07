#include "graphics/shader.h"
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


int32 shader_uniform(Shader* const shader, const Uniform uniform)
{  
   if (shader == 0)
   {
      log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/SHADER", "Shader ptr is null", __LINE__);
      return 0;
   }

   if (uniform.value == 0)
   {
      log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/SHADER", "uniform.value ptr is null", __LINE__);
      return 0;
   }

   int32 location = glGetUniformLocation(shader->program_id, uniform.name);

   if (location == -1)
   {
      log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/SHADER", "Shader location was not found", __LINE__);
      return 0;
   }

   switch(uniform.type) 
   {
        case UNIFORM_FLOAT:
            glUniform1f(location, *(float*)uniform.value);
            break;
        case UNIFORM_FLOAT_2:
        {
            float* arr = (float*)uniform.value;   
            glUniform2f(location, arr[0], arr[1]);
            break;
        }
        case UNIFORM_FLOAT_3:
        {
            float* arr = (float*)uniform.value;
            glUniform3f(location, arr[0], arr[1], arr[2]);
            break;
        }
        case UNIFORM_FLOAT_4:
        {
            float* arr = (float*)uniform.value;
            glUniform4f(location, arr[0], arr[1], arr[2], arr[3]);
            break;
        }
        case UNIFORM_INT:
            glUniform1i(location, *(int*)uniform.value);
            break;
        case UNIFORM_INT_2:
        {
            int* arr = (int*)uniform.value;
            glUniform2i(location, arr[0], arr[1]);
            break;
        }
        case UNIFORM_INT_3:
        {
            int* arr = (int*)uniform.value;
            glUniform3i(location, arr[0], arr[1], arr[2]);
            break;
        }
        case UNIFORM_INT_4:
        {
            int* arr = (int*)uniform.value;
            glUniform4i(location, arr[0], arr[1], arr[2], arr[3]);
            break;
        }
        case UNIFORM_UNSIGNED_INT:
            glUniform1ui(location, *(unsigned int*)uniform.value);
            break;
        case UNIFORM_UNSIGNED_INT_2:
        {
            unsigned int* arr = (unsigned int*)uniform.value;
            glUniform2i(location, arr[0], arr[1]);
            break;
        }
        case UNIFORM_UNSIGNED_INT_3:
        {
            unsigned int* arr = (unsigned int*)uniform.value;
            glUniform3i(location, arr[0], arr[1], arr[2]);
            break;
        }
        case UNIFORM_UNSIGNED_INT_4:
        {
            unsigned int* arr = (unsigned int*)uniform.value;
            glUniform4i(location, arr[0], arr[1], arr[2], arr[3]);
            break;
        }
        case UNIFORM_FLOAT_ARRAY:
            glUniform1fv(location, uniform.count, (float*)uniform.value);
            break;
        case UNIFORM_FLOAT_2_ARRAY:
            glUniform2fv(location, uniform.count, (float*)uniform.value);
            break;
        case UNIFORM_FLOAT_3_ARRAY:
            glUniform3fv(location, uniform.count, (float*)uniform.value);
            break;
        case UNIFORM_FLOAT_4_ARRAY:
            glUniform4fv(location, uniform.count, (float*)uniform.value);
            break;
        case UNIFORM_INT_ARRAY:
            glUniform1iv(location, uniform.count, (int*)uniform.value);
            break;
        case UNIFORM_INT_2_ARRAY:
            glUniform2iv(location, uniform.count, (int*)uniform.value);
            break;
        case UNIFORM_INT_3_ARRAY:
            glUniform3iv(location, uniform.count, (int*)uniform.value);
            break;
        case UNIFORM_INT_4_ARRAY:
            glUniform4iv(location, uniform.count, (int*)uniform.value);
            break;
        case UNIFORM_UNSIGNED_INT_ARRAY:
            glUniform1uiv(location, uniform.count, (unsigned int*)uniform.value);
            break;
        case UNIFORM_UNSIGNED_INT_2_ARRAY:
            glUniform2uiv(location, uniform.count, (unsigned int*)uniform.value);
            break;
        case UNIFORM_UNSIGNED_INT_3_ARRAY:
            glUniform3uiv(location, uniform.count, (unsigned int*)uniform.value);
            break;
        case UNIFORM_UNSIGNED_INT_4_ARRAY:
            glUniform4uiv(location, uniform.count, (unsigned int*)uniform.value);
            break;
        case UNIFORM_MAT2_ARRAY:
            glUniformMatrix2fv(location, uniform.count, 0, (float*)uniform.value);
            break;
        case UNIFORM_MAT3_ARRAY:
            glUniformMatrix3fv(location, uniform.count, 0, (float*)uniform.value);
            break;
        case UNIFORM_MAT4_ARRAY:
            glUniformMatrix4fv(location, uniform.count, 0, (float*)uniform.value);
            break;
   }
      
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