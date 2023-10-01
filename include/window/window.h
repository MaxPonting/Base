#pragma once

#include "../platform/platform.h"
#include "../type/type.h"
#include "../log/log.h"
#include "../array/array.h"
#include "../opengl/opengl.h"

#include <string.h>

namespace Base::Window
{
    enum class Event
    {
        Destroy,
        Resize,
        Move,
        MouseDown_Left,
        MouseDown_Middle,
        MouseDown_Right,
        MouseUp_Left,
        MouseUp_Middle,
        MouseUp_Right,
        KeyDown_Space,
        KeyDown_A,
        KeyDown_B,
        KeyDown_C,
        KeyDown_D,
        KeyDown_E,
        KeyDown_F,
        KeyDown_G,
        KeyDown_H,
        KeyDown_I,
        KeyDown_J,
        KeyDown_K,
        KeyDown_L,
        KeyDown_M,
        KeyDown_N,
        KeyDown_O,
        KeyDown_P,
        KeyDown_Q,
        KeyDown_R,
        KeyDown_S,
        KeyDown_T,
        KeyDown_U,
        KeyDown_V,
        KeyDown_W,
        KeyDown_X,
        KeyDown_Y,
        KeyDown_Z,
        KeyDown_Up,
        KeyDown_Down,
        KeyDown_Left,
        KeyDown_Right,
        KeyUp_Space,
        KeyUp_A,
        KeyUp_B,
        KeyUp_C,
        KeyUp_D,
        KeyUp_E,
        KeyUp_F,
        KeyUp_G,
        KeyUp_H,
        KeyUp_I,
        KeyUp_J,
        KeyUp_K,
        KeyUp_L,
        KeyUp_M,
        KeyUp_N,
        KeyUp_O,
        KeyUp_P,
        KeyUp_Q,
        KeyUp_R,
        KeyUp_S,
        KeyUp_T,
        KeyUp_U,
        KeyUp_V,
        KeyUp_W,
        KeyUp_X,
        KeyUp_Y,
        KeyUp_Z,
        KeyUp_Up,
        KeyUp_Down,
        KeyUp_Left,
        KeyUp_Right,
        Count
    };

    Array<Int8> windowEvents;

    Bool GetEvent(const Event event)
    {
        if (event == Event::Count)
            return false;

        return windowEvents.Item((Int32)event);
    }

    enum class OutputType
    {
        Windowed,
        Fullscreen,
        BorderlessFullscreen
    };

    OutputType windowOutputType;

    Int32 windowResolutionW = 0, windowResolutionH = 0;


#if PLATFORM == PLATFORM_WINDOWS


#include <windows.h>
#include <GL/wglext.h>

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
    
    HINSTANCE hInstance = NULL;
    HWND hWindow = NULL;
    HDC hDeviceContext = NULL;
    HGLRC hGLContext = NULL;

    RECT windowRect = {};
    Int32 windowX = 0, windowY = 0;
    WINDOWPLACEMENT windowPlacement = {};

    Int32 ProcessKeyDown(WPARAM wParam)
    {
        switch(wParam)
        {
        case VK_SPACE:
            windowEvents.Item((Int32)Event::KeyDown_Space) = true;
            break;
        case 0x41:
            windowEvents.Item((Int32)Event::KeyDown_A) = true;
            break;
        case 0x42:
            windowEvents.Item((Int32)Event::KeyDown_B) = true;
            break;
        case 0x43:
            windowEvents.Item((Int32)Event::KeyDown_C) = true;
            break; 
        case 0x44:
            windowEvents.Item((Int32)Event::KeyDown_D) = true;
            break;
        case 0x45:
            windowEvents.Item((Int32)Event::KeyDown_E) = true;
            break;
        case 0x46:
            windowEvents.Item((Int32)Event::KeyDown_F) = true;
            break; 
        case 0x47:
            windowEvents.Item((Int32)Event::KeyDown_G) = true;
            break;
        case 0x48:
            windowEvents.Item((Int32)Event::KeyDown_H) = true;
            break;
        case 0x49:
            windowEvents.Item((Int32)Event::KeyDown_I) = true;
            break;
        case 0x4A:
            windowEvents.Item((Int32)Event::KeyDown_J) = true;
            break;
        case 0x4B:
            windowEvents.Item((Int32)Event::KeyDown_K) = true;
            break;
        case 0x4C:
            windowEvents.Item((Int32)Event::KeyDown_L) = true;
            break;
        case 0x4D:
            windowEvents.Item((Int32)Event::KeyDown_M) = true;
            break;
        case 0x4E:
            windowEvents.Item((Int32)Event::KeyDown_N) = true;
            break;
        case 0x4F:
            windowEvents.Item((Int32)Event::KeyDown_O) = true;
            break;
        case 0x50:
            windowEvents.Item((Int32)Event::KeyDown_P) = true;
            break;
        case 0x51:
            windowEvents.Item((Int32)Event::KeyDown_Q) = true;
            break;
        case 0x52:
            windowEvents.Item((Int32)Event::KeyDown_R) = true;
            break;
        case 0x53:
            windowEvents.Item((Int32)Event::KeyDown_S) = true;
            break;
        case 0x54:
            windowEvents.Item((Int32)Event::KeyDown_T) = true;
            break;
        case 0x55:
            windowEvents.Item((Int32)Event::KeyDown_U) = true;
            break;
        case 0x56:
            windowEvents.Item((Int32)Event::KeyDown_V) = true;
            break;
        case 0x57:
            windowEvents.Item((Int32)Event::KeyDown_W) = true;
            break;
        case 0x58:
            windowEvents.Item((Int32)Event::KeyDown_X) = true;
            break;
        case 0x59:
            windowEvents.Item((Int32)Event::KeyDown_Y) = true;
            break;
        case 0x5A:
            windowEvents.Item((Int32)Event::KeyDown_Z) = true;
            break;
        }

        return 1;
    }

    Int32 ProcessKeyUp(WPARAM wParam)
    {
        switch(wParam)
        {
        case VK_SPACE:
            windowEvents.Item((Int32)Event::KeyUp_Space) = true;
            break;
        case 0x41:
            windowEvents.Item((Int32)Event::KeyUp_A) = true;
            break;
        case 0x42:
            windowEvents.Item((Int32)Event::KeyUp_B) = true;
            break;
        case 0x43:
            windowEvents.Item((Int32)Event::KeyUp_C) = true;
            break; 
        case 0x44:
            windowEvents.Item((Int32)Event::KeyUp_D) = true;
            break;
        case 0x45:
            windowEvents.Item((Int32)Event::KeyUp_E) = true;
            break;
        case 0x46:
            windowEvents.Item((Int32)Event::KeyUp_F) = true;
            break; 
        case 0x47:
            windowEvents.Item((Int32)Event::KeyUp_G) = true;
            break;
        case 0x48:
            windowEvents.Item((Int32)Event::KeyUp_H) = true;
            break;
        case 0x49:
            windowEvents.Item((Int32)Event::KeyUp_I) = true;
            break;
        case 0x4A:
            windowEvents.Item((Int32)Event::KeyUp_J) = true;
            break;
        case 0x4B:
            windowEvents.Item((Int32)Event::KeyUp_K) = true;
            break;
        case 0x4C:
            windowEvents.Item((Int32)Event::KeyUp_L) = true;
            break;
        case 0x4D:
            windowEvents.Item((Int32)Event::KeyUp_M) = true;
            break;
        case 0x4E:
            windowEvents.Item((Int32)Event::KeyUp_N) = true;
            break;
        case 0x4F:
            windowEvents.Item((Int32)Event::KeyUp_O) = true;
            break;
        case 0x50:
            windowEvents.Item((Int32)Event::KeyUp_P) = true;
            break;
        case 0x51:
            windowEvents.Item((Int32)Event::KeyUp_Q) = true;
            break;
        case 0x52:
            windowEvents.Item((Int32)Event::KeyUp_R) = true;
            break;
        case 0x53:
            windowEvents.Item((Int32)Event::KeyUp_S) = true;
            break;
        case 0x54:
            windowEvents.Item((Int32)Event::KeyUp_T) = true;
            break;
        case 0x55:
            windowEvents.Item((Int32)Event::KeyUp_U) = true;
            break;
        case 0x56:
            windowEvents.Item((Int32)Event::KeyUp_V) = true;
            break;
        case 0x57:
            windowEvents.Item((Int32)Event::KeyUp_W) = true;
            break;
        case 0x58:
            windowEvents.Item((Int32)Event::KeyUp_X) = true;
            break;
        case 0x59:
            windowEvents.Item((Int32)Event::KeyUp_Y) = true;
            break;
        case 0x5A:
            windowEvents.Item((Int32)Event::KeyUp_Z) = true;
            break;
        }

        return 1;
    }

    LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            windowEvents.Item((Int32)Event::Destroy) = true;
            PostQuitMessage(0);
            return 0;
        case WM_SIZE:
            windowEvents.Item((Int32)Event::Resize) = true;
            GetClientRect(hWindow, &windowRect);
            break;
        case WM_MOVE:
            windowEvents.Item((Int32)Event::Move) = true;
            windowX = LOWORD(lParam);
            windowY = HIWORD(lParam);
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

    Int32 Create(const char* name, const OutputType outputType, const Int32 width, const Int32 height)
    {
        windowEvents = Array<Int8>((Int32)Event::Count);

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

        windowOutputType = outputType;

        if(outputType == OutputType::Windowed)
        {
            RECT clientRect = {0, 0, width, height};
            AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, false);
        
            hWindow = CreateWindowEx(
                WS_EX_APPWINDOW,
                "WindowClass",
                name,
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                clientRect.right - clientRect.left,
                clientRect.bottom - clientRect.top,
                NULL,
                NULL,
                hInstance,
                NULL
           );
        }
        else if(outputType == OutputType::Fullscreen)
        {
            DEVMODE devMode;
            EnumDisplaySettings(NULL, 0, &devMode);
            devMode.dmPelsWidth = width;
            devMode.dmPelsHeight = height;
            devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

            ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);

            hWindow = CreateWindowEx(
                WS_EX_APPWINDOW,
                "WindowClass",
                name,
                WS_POPUP | WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                width,
                height,
                NULL,
                NULL,
                hInstance,
                NULL
           );
        }
        else if(outputType == OutputType::BorderlessFullscreen)
        {
            HMONITOR hMonitor = MonitorFromWindow(hWindow, MONITOR_DEFAULTTOPRIMARY);
            MONITORINFO monitorInfo = { sizeof(monitorInfo) };
            GetMonitorInfo(hMonitor, &monitorInfo);

            hWindow = CreateWindowEx(
                WS_EX_APPWINDOW,
                "WindowClass",
                name,
                WS_POPUP | WS_VISIBLE,
                monitorInfo.rcMonitor.left,
                monitorInfo.rcMonitor.top,
                monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
                monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
                NULL,
                NULL,
                hInstance,
                NULL
           );
        }

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

        GetWindowPlacement(hWindow, &windowPlacement);

        printf("Created Window\n");

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

        PIXELFORMATDESCRIPTOR desiredPixelFormat;
        desiredPixelFormat.nSize = sizeof(desiredPixelFormat);
        desiredPixelFormat.nVersion = 1;
        desiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
        desiredPixelFormat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
        desiredPixelFormat.cColorBits = 32;
        desiredPixelFormat.cRedBits = 0;
        desiredPixelFormat.cRedShift = 0;
        desiredPixelFormat.cGreenBits = 0;
        desiredPixelFormat.cGreenShift = 0;
        desiredPixelFormat.cBlueBits = 0;
        desiredPixelFormat.cBlueShift = 0;
        desiredPixelFormat.cAlphaBits = 0;
        desiredPixelFormat.cAlphaShift = 0;
        desiredPixelFormat.cAccumBits = 0;
        desiredPixelFormat.cAccumRedBits = 0;
        desiredPixelFormat.cAccumGreenBits = 0;
        desiredPixelFormat.cAccumBlueBits = 0;
        desiredPixelFormat.cAccumAlphaBits = 0;
        desiredPixelFormat.cStencilBits = 8;
        desiredPixelFormat.cAuxBuffers = 0;
        desiredPixelFormat.bReserved = 0;
        desiredPixelFormat.cDepthBits = 24;
        desiredPixelFormat.dwLayerMask = 0;
        desiredPixelFormat.dwVisibleMask = 0;
        desiredPixelFormat.dwVisibleMask = 0;
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
        wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)GetGLProcAddress("wglSwapIntervalEXT");

        wglDeleteContext(hDummyGLContext);
        ReleaseDC(hDummyWindow, hDummyDeviceContext);
        DestroyWindow(hDummyWindow);

        return 1;
    }

    Int64 GetGLProcAddress(const char* name)
    {
        PROC proc = wglGetProcAddress(name);

        if(proc == NULL)
        {
            char buffer[50] = "Failed to retrieve procedure: ";
            strncat_s(buffer, 50, name, strlen(name));
            Log::Print(buffer, Log::Type::Warning, __LINE__, __FILE__);
            return 0;
        }

        return (Int64)proc;
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
            WGL_SAMPLE_BUFFERS_ARB,     GL_FALSE,
            WGL_SAMPLES_ARB,            0,
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

        wglSwapIntervalEXT(1);
 
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

        windowEvents.Clear();

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

    Int32 SetOutputType(const OutputType outputType)
    {
        if(windowOutputType == outputType)
            return 1;

        if(outputType == OutputType::Windowed)
        {
            SetWindowLong(hWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW);
            SetWindowPlacement(hWindow, &windowPlacement);
            SetWindowPos(hWindow, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
            ChangeDisplaySettings(NULL, CDS_RESET);
            windowOutputType = OutputType::Windowed;
        }
        else if(outputType == OutputType::Fullscreen)
        {
            if(windowOutputType == OutputType::Windowed)
                GetWindowPlacement(hWindow, &windowPlacement);

            DEVMODE devMode;
            EnumDisplaySettings(NULL, 0, &devMode);
            devMode.dmPelsWidth = windowRect.right - windowRect.left;
            devMode.dmPelsHeight = windowRect.bottom - windowRect.top;
            devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

            DWORD dWordStyle = GetWindowLong(hWindow, GWL_STYLE);
            SetWindowLong(hWindow, GWL_STYLE, dWordStyle & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos(hWindow, HWND_TOP,
                   0, 
                   0,
                   devMode.dmPelsWidth,
                   devMode.dmPelsHeight,
                   SWP_NOOWNERZORDER | SWP_FRAMECHANGED
            );
            ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
            windowOutputType = OutputType::Fullscreen;
        }
        else if(outputType == OutputType::BorderlessFullscreen)
        {
            if(windowOutputType == OutputType::Windowed)
                GetWindowPlacement(hWindow, &windowPlacement);

            DWORD dWordStyle = GetWindowLong(hWindow, GWL_STYLE);
            HMONITOR hMonitor = MonitorFromWindow(hWindow, MONITOR_DEFAULTTOPRIMARY);
            if(!hMonitor)
            {
                Log::Print("Failed to retrieve monitor", Log::Type::Error, __LINE__, __FILE__);
                return 0;
            }
            MONITORINFO monitorInfo = { sizeof(monitorInfo) };
            if(!GetMonitorInfo(hMonitor, &monitorInfo))
            {
                Log::Print("Failed to retrieve monitor info", Log::Type::Error, __LINE__, __FILE__);
                return 0;
            }
            SetWindowLong(hWindow, GWL_STYLE, dWordStyle & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos(hWindow, HWND_TOP,
                   monitorInfo.rcMonitor.left, 
                   monitorInfo.rcMonitor.top,
                   monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
                   monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
                   SWP_NOOWNERZORDER | SWP_FRAMECHANGED
            );
            ChangeDisplaySettings(NULL, CDS_RESET);
            windowOutputType = OutputType::BorderlessFullscreen;
        }

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

    Int32 GetX()
    {
        return windowX;
    }

    Int32 GetY()
    {
        return windowY;
    }


#elif PLATFORM == PLATFORM_LINUX


#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <GL/glx.h>

    typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

    Display* display = NULL;
    Window window = {};
    Screen* screen = NULL;
    Int32 screenID = 0;
    Atom deleteMessage = 0;
    XVisualInfo* visualInfo = NULL;
    GLXContext context = {};
    GLXFBConfig frameBuffer = {};

    Int32 windowX = 0, windowY = 0, windowWidth = 0, windowHeight = 0;

    Int32 ProcessKeyDown(XKeyEvent xkey)
    {
        KeySym keySym = XkbKeycodeToKeysym(display, xkey.keycode, 0, 1);

        switch(keySym)
        {
        case XK_space:
            windowEvents.Item((Int32)Event::KeyDown_Space) = true;
            break;
        case XK_A:
            windowEvents.Item((Int32)Event::KeyDown_A) = true;
            break;
        case XK_B:
            windowEvents.Item((Int32)Event::KeyDown_B) = true;
            break;
        case XK_C:
            windowEvents.Item((Int32)Event::KeyDown_C) = true;
            break; 
        case XK_D:
            windowEvents.Item((Int32)Event::KeyDown_D) = true;
            break;
        case XK_E:
            windowEvents.Item((Int32)Event::KeyDown_E) = true;
            break;
        case XK_F:
            windowEvents.Item((Int32)Event::KeyDown_F) = true;
            break; 
        case XK_G:
            windowEvents.Item((Int32)Event::KeyDown_G) = true;
            break;
        case XK_H:
            windowEvents.Item((Int32)Event::KeyDown_H) = true;
            break;
        case XK_I:
            windowEvents.Item((Int32)Event::KeyDown_I) = true;
            break;
        case XK_J:
            windowEvents.Item((Int32)Event::KeyDown_J) = true;
            break;
        case XK_K:
            windowEvents.Item((Int32)Event::KeyDown_K) = true;
            break;
        case XK_L:
            windowEvents.Item((Int32)Event::KeyDown_L) = true;
            break;
        case XK_M:
            windowEvents.Item((Int32)Event::KeyDown_M) = true;
            break;
        case XK_N:
            windowEvents.Item((Int32)Event::KeyDown_N) = true;
            break;
        case XK_O:
            windowEvents.Item((Int32)Event::KeyDown_O) = true;
            break;
        case XK_P:
            windowEvents.Item((Int32)Event::KeyDown_P) = true;
            break;
        case XK_Q:
            windowEvents.Item((Int32)Event::KeyDown_Q) = true;
            break;
        case XK_R:
            windowEvents.Item((Int32)Event::KeyDown_R) = true;
            break;
        case XK_S:
            windowEvents.Item((Int32)Event::KeyDown_S) = true;
            break;
        case XK_T:
            windowEvents.Item((Int32)Event::KeyDown_T) = true;
            break;
        case XK_U:
            windowEvents.Item((Int32)Event::KeyDown_U) = true;
            break;
        case XK_V:
            windowEvents.Item((Int32)Event::KeyDown_V) = true;
            break;
        case XK_W:
            windowEvents.Item((Int32)Event::KeyDown_W) = true;
            break;
        case XK_X:
            windowEvents.Item((Int32)Event::KeyDown_X) = true;
            break;
        case XK_Y:
            windowEvents.Item((Int32)Event::KeyDown_Y) = true;
            break;
        case XK_Z:
            windowEvents.Item((Int32)Event::KeyDown_Z) = true;
            break;
        }


        return 1;
    }

    Int32 ProcessKeyUp(XKeyEvent xkey)
    {
        KeySym keySym = XkbKeycodeToKeysym(display, xkey.keycode, 0, xkey.state & ShiftMask ? 1 : 0);

        switch(keySym)
        {
        case XK_space:
            windowEvents.Item((Int32)Event::KeyUp_Space) = true;
            break;
        case XK_A:
            windowEvents.Item((Int32)Event::KeyUp_A) = true;
            break;
        case XK_B:
            windowEvents.Item((Int32)Event::KeyUp_B) = true;
            break;
        case XK_C:
            windowEvents.Item((Int32)Event::KeyUp_C) = true;
            break; 
        case XK_D:
            windowEvents.Item((Int32)Event::KeyUp_D) = true;
            break;
        case XK_E:
            windowEvents.Item((Int32)Event::KeyUp_E) = true;
            break;
        case XK_F:
            windowEvents.Item((Int32)Event::KeyUp_F) = true;
            break; 
        case XK_G:
            windowEvents.Item((Int32)Event::KeyUp_G) = true;
            break;
        case XK_H:
            windowEvents.Item((Int32)Event::KeyUp_H) = true;
            break;
        case XK_I:
            windowEvents.Item((Int32)Event::KeyUp_I) = true;
            break;
        case XK_J:
            windowEvents.Item((Int32)Event::KeyUp_J) = true;
            break;
        case XK_K:
            windowEvents.Item((Int32)Event::KeyUp_K) = true;
            break;
        case XK_L:
            windowEvents.Item((Int32)Event::KeyUp_L) = true;
            break;
        case XK_M:
            windowEvents.Item((Int32)Event::KeyUp_M) = true;
            break;
        case XK_N:
            windowEvents.Item((Int32)Event::KeyUp_N) = true;
            break;
        case XK_O:
            windowEvents.Item((Int32)Event::KeyUp_O) = true;
            break;
        case XK_P:
            windowEvents.Item((Int32)Event::KeyUp_P) = true;
            break;
        case XK_Q:
            windowEvents.Item((Int32)Event::KeyUp_Q) = true;
            break;
        case XK_R:
            windowEvents.Item((Int32)Event::KeyUp_R) = true;
            break;
        case XK_S:
            windowEvents.Item((Int32)Event::KeyUp_S) = true;
            break;
        case XK_T:
            windowEvents.Item((Int32)Event::KeyUp_T) = true;
            break;
        case XK_U:
            windowEvents.Item((Int32)Event::KeyUp_U) = true;
            break;
        case XK_V:
            windowEvents.Item((Int32)Event::KeyUp_V) = true;
            break;
        case XK_W:
            windowEvents.Item((Int32)Event::KeyUp_W) = true;
            break;
        case XK_X:
            windowEvents.Item((Int32)Event::KeyUp_X) = true;
            break;
        case XK_Y:
            windowEvents.Item((Int32)Event::KeyUp_Y) = true;
            break;
        case XK_Z:
            windowEvents.Item((Int32)Event::KeyUp_Z) = true;
            break;
        }

        return 1;
    }


    Int32 PollEvents()
    {
        windowEvents.Clear();

        XEvent event;

        while(XPending(display) > 0)
        {
            XNextEvent(display, &event);

            switch(event.type)
            {
            case ClientMessage:
                if ((Atom)event.xclient.data.l[0] != deleteMessage)
                    break;
                windowEvents.Item((Int32)Event::Destroy) = true;
                break;
            case ConfigureNotify:
                if(windowX != event.xconfigure.x || windowY != event.xconfigure.y)
                {
                    windowX = event.xconfigure.x;
                    windowY = event.xconfigure.y;
                    windowEvents.Item((Int32)Event::Move) = true;
                }
                if(windowWidth != event.xconfigure.width || windowHeight != event.xconfigure.height)
                {
                    windowWidth = event.xconfigure.width;
                    windowHeight = event.xconfigure.height;
                    windowEvents.Item((Int32)Event::Resize) = true;
                }
                break;
            case KeymapNotify:
                XRefreshKeyboardMapping(&event.xmapping);
                break;
            case KeyPress:
                ProcessKeyDown(event.xkey);               
                break;
            case KeyRelease:
                if (XEventsQueued(display, QueuedAfterReading))
                {
                    XEvent nextEvent;
                    XPeekEvent(display, &nextEvent);
                    if (nextEvent.type == KeyPress && nextEvent.xkey.time == event.xkey.time && nextEvent.xkey.keycode == event.xkey.keycode)
                        break;
                }
                ProcessKeyUp(event.xkey);
                break;
            }
        }

        return 1;
    }

    Int32 Create(const char* name, const OutputType outputType, const Int32 width, const Int32 height)
    {
        display = XOpenDisplay(NULL);
        if (!display)
        {
            Log::Print("Could not open display", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        screen = DefaultScreenOfDisplay(display);
        screenID = DefaultScreen(display);

        if(!glXQueryExtension(display, 0, 0))
        {
            Log::Print("X server doesn't support GLX extension", Log::Type::Error, __LINE__, __FILE__);
            return 1;
        }

        Int32 majorGLX, minorGLX;
        glXQueryVersion(display, &majorGLX, &minorGLX);
        if (majorGLX <= 1 && minorGLX < 2)
        {
            Log::Print("GLX 1.2 or greater is required", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        Int32 glxAttributes[] = {
            GLX_X_RENDERABLE,   true,
            GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
            GLX_RENDER_TYPE,    GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE,  GLX_TRUE_COLOR, 
            GLX_DEPTH_SIZE,     24,
            GLX_STENCIL_SIZE,   8,
            GLX_RED_SIZE,       8,
            GLX_GREEN_SIZE,     8,
            GLX_BLUE_SIZE,      8,
            GLX_ALPHA_SIZE,     8,
            GLX_DOUBLEBUFFER,   true,
            None
        };

        Int32 frameBufferCount;
        GLXFBConfig* frameBufferConfig = glXChooseFBConfig(display, DefaultScreen(display), glxAttributes, &frameBufferCount);
        if (!frameBufferConfig)
        {
            Log::Print("Failed to retrieve framebuffer", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }
        frameBuffer = frameBufferConfig[0];
        XFree(frameBufferConfig);

        visualInfo = glXGetVisualFromFBConfig(display, frameBuffer);
        if (!visualInfo)
        {
            Log::Print("Failed to created visual info", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        XSetWindowAttributes windowAttributes;
        windowAttributes.border_pixel = BlackPixel(display, screenID);
        windowAttributes.background_pixel = WhitePixel(display, screenID);
        windowAttributes.override_redirect = true;
        windowAttributes.colormap = XCreateColormap(display, RootWindow(display, screenID), visualInfo->visual, AllocNone);
        windowAttributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | KeymapStateMask;
        window = XCreateWindow(display, RootWindow(display, screenID), 0, 0, width, height, 0, visualInfo->depth, InputOutput, visualInfo->visual, CWBackPixel | CWBorderPixel | CWColormap| CWEventMask, &windowAttributes);
        XFree(visualInfo);

        if(outputType == OutputType::Fullscreen || outputType == OutputType::BorderlessFullscreen)
        {
            Atom wmState = XInternAtom(display, "_NET_WM_STATE", false);
            Atom wmFullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", false);
            XEvent event;
            memset(&event, 0, sizeof(event));
            event.type = ClientMessage;
            event.xclient.window = window;
            event.xclient.message_type = wmState;
            event.xclient.format = 32;
            event.xclient.data.l[0] = 1;
            event.xclient.data.l[1] = wmFullscreen;
            event.xclient.data.l[2] = 0;
            XSendEvent(display, DefaultRootWindow(display), false, SubstructureRedirectMask | SubstructureNotifyMask, &event);

            Atom wmFullscreenMonitors = XInternAtom(display, "_NET_WM_FULLSCREEN_MONITORS", false);
            memset(&event, 0, sizeof(event));
            event.type = ClientMessage;
            event.xclient.window = window;
            event.xclient.message_type = wmFullscreenMonitors;
            event.xclient.format = 32;
            event.xclient.data.l[0] = 0; /* your topmost monitor number */
            event.xclient.data.l[1] = 0; /* bottommost */
            event.xclient.data.l[2] = 0; /* leftmost */
            event.xclient.data.l[3] = 1; /* rightmost */
            event.xclient.data.l[4] = 0; /* source indication */
            XSendEvent(display, DefaultRootWindow(display), false, SubstructureRedirectMask | SubstructureNotifyMask, &event);

            XMapWindow(display, window);
        }

        XStoreName(display, window, name);

        deleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", false);
        XSetWMProtocols(display, window, &deleteMessage, 1);

        windowEvents = Array<Int8>((Int32)Event::Count);

        XWindowAttributes attributes; 
        XGetWindowAttributes(display, window, &attributes);

        windowX = attributes.x;
        windowY = attributes.y;
        windowWidth = attributes.width;
        windowHeight = attributes.height;

        return 1;
    }

    Int64 GetGLProcAddress(const char* name)
    {
        Int64 proc = (Int64)glXGetProcAddressARB((const UInt8*)name);

        if(proc == 0)
        {
            char buffer[50] = "Failed to retrieve procedure: ";
            Log::Print(buffer, Log::Type::Warning, __LINE__, __FILE__);
            return 0;           
        }

        return (Int64)proc;
    }

    Int32 SetGLContext(const Int32 majorVersion, const Int32 minorVersion)
    {
        glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
        glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const UInt8*)"glXCreateContextAttribsARB");

        if(!glXCreateContextAttribsARB)
        {
            Log::Print("'glXCreateContextAttribsARB()' was not found", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        Int32 contextAttributes[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB,      majorVersion,
            GLX_CONTEXT_MINOR_VERSION_ARB,      minorVersion,
            GLX_CONTEXT_PROFILE_MASK_ARB,   GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
            None 
        };

        context = glXCreateContextAttribsARB(display, frameBuffer, 0, true, contextAttributes);
        glXMakeCurrent(display, window, context);

        XSync(display, false);

        return 1;
    }

    Int32 Destroy()
    {
        if(context)
            glXDestroyContext(display, context);

        if (display)
            XCloseDisplay(display);

        return 1;
    }

    Int32 Show()
    {
        XClearWindow(display, window);
        XMapRaised(display, window);

        return 1;
    }

    Int32 SwapBuffer()
    {
        glXSwapBuffers(display, window);
        return 1;
    }

    Int32 SetFullScreen()
    {
        return 1;
    }

    Int32 GetWidth()
    {
        return windowWidth;
    }

    Int32 GetHeight()
    {
        return windowHeight;
    }
        
    Int32 GetX()
    {
        return windowX;
    }

    Int32 GetY()
    {
        return windowY;
    }

#elif PLATFORM == PLATFORM_MAC
#endif

}
