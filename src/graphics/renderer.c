#include "graphics/renderer.h"
#include "vendor/glad/glad.h"
#include "vendor/glfw/glfw3.h"
#include "log/log.h"

static uint32 vertex_array_id;
static uint32 vertex_buffer_id;
static uint32 index_buffer_id;

int32 renderer_create()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/RENDERER", "Failed to initialize glad", __LINE__);
        return 0;
    } 

    

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    return 1;
}

int32 renderer_destroy()
{
    return 1;
}

int32 renderer_start()
{
    glClear(GL_COLOR_BUFFER_BIT);

    return 1;
}

int32 renderer_draw_quad()
{
    return 1; 
}

int32 renderer_end()
{
    return 1;
}