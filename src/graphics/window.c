#include "graphics/window.h"
#include "log/log.h"
#include "vendor/glfw/glfw3.h"

static GLFWwindow* window;

int32 window_create(const uint32 width, const uint32 height, const char* const name)
{
    if(!glfwInit())
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "glfw failed to init", __LINE__);
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);   

    if (window != 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window has already been created", __LINE__);
        return 0;
    }

    window = glfwCreateWindow(width, height, name, 0, 0);

    if (window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window creation failed", __LINE__);
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    return 1;
};

int32 window_destroy()
{   
    if (window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window is null", __LINE__);
        return 0;
    }

    glfwTerminate();

    return 1;
};

int32 window_should_close()
{
    if (window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window is null", __LINE__);
        return 0;
    }

    return glfwWindowShouldClose(window);
}

int32 window_swap_buffer()
{
    if (window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window is null", __LINE__);
        return 0;
    }

    glfwSwapBuffers(window);

    return 1;
}

int32 window_poll_events()
{  
    if (window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window is null", __LINE__);
        return 0;
    }

    glfwPollEvents();

    return 1;
}

int32 window_get_size(int32* const width, int32* const height)
{
    if (window == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/GRAPHICS/WINDOW", "Window is null", __LINE__);
        return 0;
    }

    glfwGetWindowSize(window, width, height);

    return 1;
}