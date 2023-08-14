#include "nuklear/nuklear.h"
#include "window/window.h"
#include "log/log.h"

#include <stdio.h>

static struct nk_glfw glfw = {0};

int32 nuklear_create()
{
    void* window = 0;
    if(!window_get_ptr(&window))
        return 0;

    nuklear_ctx = nk_glfw3_init(&glfw, window, NK_GLFW3_INSTALL_CALLBACKS);
    
    if(!nuklear_ctx)
    {
        log_print(LOG_TYPE_ERROR, "BASE/NUKLEAR/NUKLEAR", "Context failed to create", __LINE__);
        return 0;
    }

    {
        struct nk_font_atlas *atlas;
        nk_glfw3_font_stash_begin(&glfw, &atlas);
        nk_glfw3_font_stash_end(&glfw);
    }

    return 1;
}

int32 nuklear_destroy()
{
    if (nuklear_ctx == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/NUKLEAR/NUKLEAR", "Nuklear in null", __LINE__);
        return 0;
    }

    nk_glfw3_shutdown(&glfw);
    
    return 1;
}

int32 nuklear_new_frame()
{
    if (nuklear_ctx == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/NUKLEAR/NUKLEAR", "Nuklear in null", __LINE__);
        return 0;
    }

    nk_glfw3_new_frame(&glfw);

    return 1;
}

int32 nuklear_render()
{
    if (nuklear_ctx == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/NUKLEAR/NUKLEAR", "Nuklear in null", __LINE__);
        return 0;
    }

    nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

    return 1;
}