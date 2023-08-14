#include "opengl/opengl.h"
#include "window/window.h"
#include "vendor/glfw/glfw3.h"
#include "log/log.h"

static void GLAPIENTRY debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

int32 opengl_create()
{
    if (!window_is_active())
    {
        log_print(LOG_TYPE_ERROR, "BASE/OPENGL/OPENGL", "Window is not active", __LINE__);
        return 0;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log_print(LOG_TYPE_ERROR, "BASE/OPENGL/OPENGL", "Glad failed to initialize", __LINE__);
        return 0;
    }

    return 1;
}

int32 opengl_enable_debug()
{
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debug_message_callback, 0);

    return 1;
}

static void GLAPIENTRY debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    log_print(LOG_TYPE_ERROR, "BASE/OPENGL/OPENGL", message, __LINE__);
}
