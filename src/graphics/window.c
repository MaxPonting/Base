#include "graphics./window.h"
#include "graphics/glfw/glfw3.h"

int window_create(Window* const window, Allocator* const allocator, char* const name, const int w, const int h)
{
    if (PLATFORM == PLATFORM_TYPE_WINDOWS)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window->ptr = glfwCreateWindow(w, h, name, 0, 0);
        if (window->ptr == 0)
        {
            printf("[ERROR][BASE/GRAPHICS/WINDOW/%d][Failed to create window]\n", __LINE__);
            glfwTerminate();
            return 0;
        }

        glfwMakeContextCurrent(window->ptr);
        glfwSwapInterval(1);

        window->w = w;
        window->h = h;
        window->type = WINDOW_TYPE_GLFW;
        string_create(&window->name, allocator, name);
    }
    else 
    {
        printf("[ERROR][BASE/GRAPHICS/WINDOW/%d][Platform is not supported]\n", __LINE__);
        return 0;
    }

    return 1;
}

int window_destroy()
{
    glfwTerminate();

    return 1;
}

int window_swap_buffers(Window* const window)
{
    if (window->type == WINDOW_TYPE_GLFW)
        glfwSwapBuffers(window->ptr);
    else 
        return 0;

    return 1;
}

int window_poll_events(Window* const window)
{
    if (window->type == WINDOW_TYPE_GLFW)
        glfwPollEvents();
    else 
        return 0;

    return 1;
}

int window_should_close(Window* const window)
{
    if (window->type == WINDOW_TYPE_GLFW)
        return glfwWindowShouldClose(window->ptr);
    else 
        return 0;
}

int window_get_key(Window* const window, const int key)
{   
    if (window->type == WINDOW_TYPE_GLFW)
        return glfwGetKey(window->ptr, key) + 1;
    else
        return 0;
}