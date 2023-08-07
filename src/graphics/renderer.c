#include "graphics/renderer.h"
#include "graphics/window.h"
#include "vendor/glad/glad.h"
#include "vendor/glfw/glfw3.h"
#include "log/log.h"
#include "vendor/cglm/cglm.h"

typedef struct 
{
    vec2 position;    
    vec2 texture_coordinate;
} Vertex;

static Vertex vertices_default[4] = 
{
    {{-0.5f, -0.5f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f}, {0.0f, 1.0f}},
    {{ 0.5f,  0.5f}, {1.0f, 1.0f}}
};

static uint32 indices_default[6] = {
    0, 1, 2,
    1, 2, 3
};

static const char* vertex_source;
static const char* fragment_source;

static uint32 vertex_array_id;
static uint32 vertex_buffer_id;
static uint32 index_buffer_id;

static Shader shader;

static mat4 view;
static mat4 projection;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam); 
 
int32 renderer_create()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/RENDERER", "Failed to initialize glad", __LINE__);
        return 0;
    } 

    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    glGenBuffers(1, &vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_default), vertices_default, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(Vertex), (void*)(0 * sizeof(float)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(Vertex), (void*)(2 * sizeof(float)));

    glGenBuffers(1, &index_buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_default), indices_default, GL_DYNAMIC_DRAW);

    if(!shader_create(&shader, vertex_source, fragment_source))
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/RENDERER", "Default shader failed to compile", __LINE__);
        return 0;
    }

    return 1;
}

int32 renderer_destroy()
{
    return 1;
}

int32 renderer_start(const Camera camera)
{
    if(vertex_array_id == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/RENDERER", "Renderer is null", __LINE__);
        return 0;
    }

    int width, height;
    if(!window_get_size(&width, &height))
        return 0;
    
    glm_mat4_identity(projection);
    glm_ortho(-width / 2, width / 2, -height / 2, height / 2, -1.0f, 1.0f, projection);

    glm_mat4_identity(view);
    glm_translate(view, (vec3){-camera.position[0], -camera.position[1]});
    glm_rotate(view, -camera.rotation, (vec3){0, 0, 1}); 
    if (camera.scale[0] == 0 || camera.scale[1] == 0)
        glm_scale(view, (vec3){1, 1});
    else
        glm_scale(view, (vec3){1 / camera.scale[0], 1 / camera.scale[1]});

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
    glViewport(0, 0, width, height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    return 1;
}

int32 renderer_draw_quad(vec2 position, vec2 size, float rotation, vec4 colour)
{
    if(vertex_array_id == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/RENDERER", "Renderer is null", __LINE__);
        return 0;
    }

    Vertex vertices[4];

    const float32 cos = cosf(glm_rad(rotation));
    const float32 sin = sinf(glm_rad(rotation));

    for (uint32 i = 0; i < 4; i++)
    {
        vertices[i].position[0] = vertices_default[i].position[0] * size[0];
        vertices[i].position[1] = vertices_default[i].position[1] * size[1];
        
        const float32 x = vertices[i].position[0];
        const float32 y = vertices[i].position[1];

        vertices[i].position[0] = x * cos - y * sin;
        vertices[i].position[1] = y * cos + x * sin;

        vertices[i].position[0] += position[0];
        vertices[i].position[1] += position[1];

        vertices[i].texture_coordinate[0] = vertices_default[i].texture_coordinate[0];
        vertices[i].texture_coordinate[1] = vertices_default[i].texture_coordinate[1];
    } 

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    if(!shader_use(shader))
        return 0;

    if(!shader_uniform(&shader, (Uniform){UNIFORM_MAT4_ARRAY, "u_View", view, 1}))
    {
        log_print(LOG_TYPE_WARNING, "BASE/GRAPHICS/RENDERER", "mat4 u_View is not defined in vertex shader", __LINE__);
        return 0;
    } 

    if(!shader_uniform(&shader, (Uniform){UNIFORM_MAT4_ARRAY, "u_Projection", projection, 1}))
    {
        log_print(LOG_TYPE_WARNING, "BASE/GRAPHICS/RENDERER", "mat4 u_Projection is not defined in vertex shader", __LINE__);
        return 0;
    }

    if(!shader_uniform(&shader, (Uniform){UNIFORM_FLOAT_4, "u_Colour", colour, 1}))
    {
        log_print(LOG_TYPE_WARNING, "BASE/GRAPHICS/RENDERER", "vec4 u_Colour is not defined in fragment shader", __LINE__);
        return 0;
    }
    
    glBindVertexArray(vertex_array_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return 1; 
}

int32 renderer_end()
{
    return 1;
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    printf("[ERROR][OPENGL][%s]\n", message);
}

static const char* vertex_source = "#version 330 core\n\nlayout(location = 0) in vec4 a_Position;layout(location = 1) in vec2 a_TextureCoordinates;uniform mat4 u_View;uniform mat4 u_Projection;void main(){gl_Position = u_Projection * u_View * a_Position;}";
static const char* fragment_source = "#version 330 core\n\nuniform vec4 u_Colour;out vec4 o_Colour;void main(){o_Colour = u_Colour;}";