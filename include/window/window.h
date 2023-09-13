#include "../platform/platform.h"
#include "../type/type.h"
#include "../log/log.h"
#include "../array/array.h"

namespace Base::Window
{
    enum class Event
    {
        Destroy,
        SpaceKeyDown,
        SpaceKeyUp,
        Count
    };

    Array<Int8> events;

#if PLATFORM == PLATFORM_TYPE_WINDOWS

#include <windows.h>

    HINSTANCE hInstance = NULL;
    HWND hWindow = NULL;
    HDC hDeviceContext = NULL;
    HGLRC hGLContext = NULL;

    Int32 ProcessKeyDown(WPARAM wParam)
    {
        switch(wParam)
        {
        case VK_SPACE:
            events.Item((Int32)Event::SpaceKeyDown) = true;
            break;
        }

        return 1;
    }

    Int32 ProcessKeyUp(WPARAM wParam)
    {
        switch(wParam)
        {
        case VK_SPACE:
            events.Item((Int32)Event::SpaceKeyUp) = true;
            break;
        }

        return 1;
    }

    LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            events.Item((Int32)Event::Destroy) = true;
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            ProcessKeyDown(wParam);
            break;
        case WM_KEYUP:
            ProcessKeyUp(wParam);
            break;
        }

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    Int32 Create(const char* name, const Int32 width, const Int32 height)
    {
        hInstance = GetModuleHandle(NULL);        

        if(!hInstance)
        {
            Log::Print("hInstance not received", Log::Type::Error, __LINE__, __FILE__);
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
            Log::Print("Window creation failed", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        hDeviceContext = GetDC(hWindow);

        if(!hDeviceContext)
        {
            Log::Print("hDeviceContext not received", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        events = Array<Int8>((Int32)Event::Count);

        return 1;
    }

    Int32 Destroy()
    {
        if (hGLContext)
        {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hGLContext);
        }

        if (hDeviceContext)
        {
            ReleaseDC(hWindow, hDeviceContext);
        }

        if (hWindow)
        {
            DestroyWindow(hWindow);
        }

        return 1;
    }

    Int32 SetGLContext()
    {
        PIXELFORMATDESCRIPTOR desiredPixelFormat = {};
        desiredPixelFormat.nSize = sizeof(desiredPixelFormat);
        desiredPixelFormat.nVersion = 1;
        desiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
        desiredPixelFormat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
        desiredPixelFormat.cColorBits = 32;
        desiredPixelFormat.cAlphaBits = 8;
        desiredPixelFormat.cDepthBits = 24;
        desiredPixelFormat.iLayerType = PFD_MAIN_PLANE;

        Int32 pixelFormatIndex = ChoosePixelFormat(hDeviceContext, &desiredPixelFormat);
        PIXELFORMATDESCRIPTOR pixelFormat;
        DescribePixelFormat(hDeviceContext, pixelFormatIndex, sizeof(pixelFormat), &pixelFormat);
        SetPixelFormat(hDeviceContext, pixelFormatIndex, &pixelFormat);

        hGLContext = wglCreateContext(hDeviceContext);
        wglMakeCurrent(hDeviceContext, hGLContext);

        return 1;
    }

    Int32 Show()
    {
        if(!hWindow)
        {
            Log::Print("Window has not been created", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        ShowWindow(hWindow, SW_NORMAL);

        return 1;
    }

    Int32 PollEvents()
    {
        if (!hWindow)
        {
            Log::Print("Window has not been created", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        events.Clear();

        MSG msg = {};
        while (PeekMessage(&msg, hWindow, 0, 0, PM_REMOVE) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return 1;
    }

    Int32 SwapBuffer()
    {
        if (!hDeviceContext)
        {
            Log::Print("Window has not been created", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        SwapBuffers(hDeviceContext);

        return 1;
    }

    Bool GetEvent(const Event event)
    {
        if (event == Event::Count)
            return false;

        return events.Item((Int32)event);
    }


#elif PLATFORM == PLATFORM_TYPE_LINUX



#endif

}
