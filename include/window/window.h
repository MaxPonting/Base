#pragma once

#include "../platform/platform.h"
#include "../type/type.h"
#include "../log/log.h"
#include "../array/array.h"
#include "../opengl/opengl.h"

namespace Base::Window
{
    enum class Event
    {
        Destroy,
        Resize,
        SpaceKeyDown,
        SpaceKeyUp,
        Count
    };

    Array<Int8> events;

    Bool GetEvent(const Event event)
    {
        if (event == Event::Count)
            return false;

        return events.Item((Int32)event);
    }

#if PLATFORM == PLATFORM_WINDOWS

#include <windows.h>
#include <GL/wglext.h>

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
    
    HINSTANCE hInstance = NULL;
    HWND hWindow = NULL;
    HDC hDeviceContext = NULL;
    HGLRC hGLContext = NULL;

    RECT windowRect = {};

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
        case WM_SIZE:
            events.Item((Int32)Event::Resize) = true;
            GetClientRect(hWindow, &windowRect);
            break;
        case WM_PAINT:
            static PAINTSTRUCT paintStruct;
            BeginPaint(hWnd, &paintStruct);
            EndPaint(hWnd, &paintStruct);
            break;
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

        WNDCLASSEX windowClassEx; 

	    windowClassEx.cbClsExtra = 0;
	    windowClassEx.cbSize = sizeof(WNDCLASSEX);
	    windowClassEx.cbWndExtra = 0;
	    windowClassEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	    windowClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	    windowClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    	windowClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    	windowClassEx.hInstance = hInstance;
    	windowClassEx.lpfnWndProc = WindowProcedure;
    	windowClassEx.lpszClassName = "WindowClass";
    	windowClassEx.lpszMenuName = NULL;
    	windowClassEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;

        if(!RegisterClassEx(&windowClassEx))
        {
            Log::Print("Failed to register window class", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        hWindow = CreateWindowEx(
            WS_EX_APPWINDOW,
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

    Int32 LoadWGLProcerdures()
    {
        WNDCLASSEX windowClassEx; 

	    windowClassEx.cbClsExtra = 0;
	    windowClassEx.cbSize = sizeof(WNDCLASSEX);
	    windowClassEx.cbWndExtra = 0;
	    windowClassEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	    windowClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	    windowClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    	windowClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    	windowClassEx.hInstance = hInstance;
    	windowClassEx.lpfnWndProc = WindowProcedure;
    	windowClassEx.lpszClassName = TEXT("DummyWindowClass");
    	windowClassEx.lpszMenuName = NULL;
    	windowClassEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

        RegisterClassEx(&windowClassEx);

        HWND hDummyWindow = CreateWindowEx(
            WS_EX_APPWINDOW,
            "DummyWindowClass",
            "Dummy",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,
            NULL,
            hInstance,
            NULL
        );

        if(!hDummyWindow)
        {
            Log::Print("Dummy window creation failed", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        HDC hDummyDeviceContext = GetDC(hDummyWindow);

        PIXELFORMATDESCRIPTOR desiredPixelFormat = {};
        desiredPixelFormat.nSize = sizeof(desiredPixelFormat);
        desiredPixelFormat.nVersion = 1;
        desiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
        desiredPixelFormat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
        desiredPixelFormat.cColorBits = 32;
        desiredPixelFormat.cAlphaBits = 8;
        desiredPixelFormat.cDepthBits = 24;
        desiredPixelFormat.iLayerType = PFD_MAIN_PLANE;

        Int32 pixelFormatIndex = ChoosePixelFormat(hDummyDeviceContext, &desiredPixelFormat);
        PIXELFORMATDESCRIPTOR pixelFormat;
        DescribePixelFormat(hDummyDeviceContext, pixelFormatIndex, sizeof(pixelFormat), &pixelFormat);
        SetPixelFormat(hDummyDeviceContext, pixelFormatIndex, &pixelFormat);

        HGLRC hDummyGLContext = wglCreateContext(hDummyDeviceContext);

        if (!hDummyGLContext)
        {
            Log::Print("Failed to create dummy context", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        wglMakeCurrent(hDummyDeviceContext, hDummyGLContext);

        wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)GetGLProcAddress("wglChoosePixelFormatARB");
        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)GetGLProcAddress("wglCreateContextAttribsARB");

        wglDeleteContext(hDummyGLContext);
        ReleaseDC(hDummyWindow, hDummyDeviceContext);
        DestroyWindow(hDummyWindow);

        return 1;
    }

    Int64 GetGLProcAddress(const char* name)
    {
        return (Int64)wglGetProcAddress(name);
    }

    Int32 SetGLContext(const Int32 majorVersion, const Int32 minorVersion)
    {
        if(!LoadWGLProcerdures())
        {
            Log::Print("Loading wgl procedures failed", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        Int32 pixelFormatAttribs[] = {
            WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
            WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
            WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB,         32,
            WGL_DEPTH_BITS_ARB,         24,
            WGL_STENCIL_BITS_ARB,       8,
            WGL_SAMPLE_BUFFERS_ARB,     GL_TRUE,
            WGL_SAMPLES_ARB,            4,
            0
        };

        Int32 pixelFormatIndex;
        UInt32 numFormats;
        if(!wglChoosePixelFormatARB(hDeviceContext, pixelFormatAttribs, 0, 1, &pixelFormatIndex, &numFormats))
        {
            Log::Print("Failed to set pixel format", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        PIXELFORMATDESCRIPTOR pixelFormat;
        DescribePixelFormat(hDeviceContext, pixelFormatIndex, sizeof(pixelFormat), &pixelFormat);

        if(!SetPixelFormat(hDeviceContext, pixelFormatIndex, &pixelFormat))
        {
            Log::Print("Failed to set pixel format", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        Int32 glAttribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, majorVersion,
            WGL_CONTEXT_MINOR_VERSION_ARB, minorVersion,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        hGLContext = wglCreateContextAttribsARB(hDeviceContext, 0, glAttribs);
        if(!hGLContext)
        {
            Log::Print("Failed to create OpenGL context", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        if(!wglMakeCurrent(hDeviceContext, hGLContext))
        {
            Log::Print("Failed to create OpenGL context", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
 
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

    Int32 GetWidth()
    {
        return windowRect.right - windowRect.left;
    }

    Int32 GetHeight()
    {
        return windowRect.bottom - windowRect.top;
    }


#elif PLATFORM == PLATFORM_LINUX

#include <X11/Xlib.h>

    Display* display;
    Window window;
    Screen* screen;
    Int32 screenID;

    Int32 Create(const char* name, const Int32 width, const Int32 height)
    {
        display = XOpenDisplay(NULL);
        if (!display)
        {
            Log::Print("Could not open display", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        screen = DefaultScreenOfDisplay(display);
        screenID = DefaultScreen(display);
        window = XCreateSimpleWindow(display, RootWindowOfScreen(screen), 0, 0, width, height, 1, BlackPixel(display, screenID), WhitePixel(display, screenID));

        events = Array<Int8>((Int32)Event::Count);

        return 1;
    }

    Int32 Destroy()
    {
        XDestroyWindow(display, window);
        XFree(screen);
        XCloseDisplay(display);

        return 1;
    }

    Int32 Show()
    {
        XClearWindow(display, window);
        XMapRaised(display, window);

        return 1;
    }

    Int32 PollEvents()
    {
        events.Clear();

        XEvent event;

        while(XPending(display) > 0)
        {
            printf("Check event\n");
            XNextEvent(display, &event);
            if (event.type == DestroyNotify)
            {
                events.Item((Int32)Event::Destroy) = true;
                break;
            }
        }

        return 1;
    }

    Int32 SwapBuffer()
    {
        return 1;
    }


#elif PLATFORM == PLATFORM_MAC
#endif

}
