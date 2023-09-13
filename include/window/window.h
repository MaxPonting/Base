#include "../platform/platform.h"
#include "../type/type.h"
#include "../log/log.h"

#if PLATFORM == PLATFORM_TYPE_WINDOWS

#include <windows.h>

namespace Base::Window
{
    HINSTANCE hInstance = NULL;
    HWND hWindow = NULL;

    LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    Int32 Create(const char* name, const Int32 width, const Int32 height)
    {
        hInstance = GetModuleHandle(NULL);        

        if(!hInstance)
        {
            Log::Print("hInstance not received", Log::TYPE_ERROR, __LINE__, __FILE__);
            return 0;
        }

        WNDCLASS windowClass = {};

        windowClass.lpfnWndProc     = WindowProcedure;
        windowClass.hInstance       = hInstance;
        windowClass.lpszClassName   = "WindowClass";

        RegisterClass(&windowClass);

        hWindow = CreateWindowEx(
            0,
            "WindowClass",
            name,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            width,
            height,
            NULL,
            NULL,
            hInstance,
            NULL
        );

        if(!hWindow)
        {
            Log::Print("Window creation failed", Log::TYPE_ERROR, __LINE__, __FILE__);
            return 0;
        }
        
        
    }

    Int32 Destroy()
    {

    }

    Int32 PollEvents()
    {

    }

    Int32 SwapBuffer()
    {

    }

}

#elif PLATFORM == PLATFORM_TYPE_LINUX

namespace Base::Window
{

}

#endif

