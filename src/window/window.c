#include "window/window.h"
#include "log/log.h"
#include "vendor/glfw/glfw3.h"

static GLFWwindow* s_window;

int32 window_create(const uint32 width, const uint32 height, const char* const name, const WindowVersionMajor version_major, const WindowVersionMinor version_minor)
{
    if(!glfwInit())
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "glfw failed to init", __LINE__);
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    if (s_window != 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window has already been created", __LINE__);
        return 0;
    }

    s_window = glfwCreateWindow(width, height, name, 0, 0);

    if (s_window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window creation failed", __LINE__);
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(s_window);
    glfwSwapInterval(1);

    return 1;
};

int32 window_destroy()
{   
    if (s_window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window is null", __LINE__);
        return 0;
    }

    s_window = 0;
    glfwTerminate();

    return 1;
};

int32 window_swap_buffer()
{
    if (s_window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window is null", __LINE__);
        return 0;
    }

    glfwSwapBuffers(s_window);

    return 1;
}

int32 window_poll_events()
{  
    if (s_window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window is null", __LINE__);
        return 0;
    }

    glfwPollEvents();

    return 1;
}


int32 window_should_close()
{
    if (s_window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window is null", __LINE__);
        return 0;
    }

    return glfwWindowShouldClose(s_window);
}

int32 window_is_active()
{
    if(s_window == 0)
        return 0;
    
    return 1;
}

int32 window_get_size(int32* const width, int32* const height)
{
    if (s_window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window is null", __LINE__);
        return 0;
    }

    glfwGetWindowSize(s_window, width, height);

    return 1;
}
