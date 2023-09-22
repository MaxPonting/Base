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
            events.Item((Int32)Event::KeyDown_Space) = true;
            break;
        case 0x41:
            events.Item((Int32)Event::KeyDown_A) = true;
            break;
        case 0x42:
            events.Item((Int32)Event::KeyDown_B) = true;
            break;
        case 0x43:
            events.Item((Int32)Event::KeyDown_C) = true;
            break; 
        case 0x44:
            events.Item((Int32)Event::KeyDown_D) = true;
            break;
        case 0x45:
            events.Item((Int32)Event::KeyDown_E) = true;
            break;
        case 0x46:
            events.Item((Int32)Event::KeyDown_F) = true;
            break; 
        case 0x47:
            events.Item((Int32)Event::KeyDown_G) = true;
            break;
        case 0x48:
            events.Item((Int32)Event::KeyDown_H) = true;
            break;
        case 0x49:
            events.Item((Int32)Event::KeyDown_I) = true;
            break;
        case 0x4A:
            events.Item((Int32)Event::KeyDown_J) = true;
            break;
        case 0x4B:
            events.Item((Int32)Event::KeyDown_K) = true;
            break;
        case 0x4C:
            events.Item((Int32)Event::KeyDown_L) = true;
            break;
        case 0x4D:
            events.Item((Int32)Event::KeyDown_M) = true;
            break;
        case 0x4E:
            events.Item((Int32)Event::KeyDown_N) = true;
            break;
        case 0x4F:
            events.Item((Int32)Event::KeyDown_O) = true;
            break;
        case 0x50:
            events.Item((Int32)Event::KeyDown_P) = true;
            break;
        case 0x51:
            events.Item((Int32)Event::KeyDown_Q) = true;
            break;
        case 0x52:
            events.Item((Int32)Event::KeyDown_R) = true;
            break;
        case 0x53:
            events.Item((Int32)Event::KeyDown_S) = true;
            break;
        case 0x54:
            events.Item((Int32)Event::KeyDown_T) = true;
            break;
        case 0x55:
            events.Item((Int32)Event::KeyDown_U) = true;
            break;
        case 0x56:
            events.Item((Int32)Event::KeyDown_V) = true;
            break;
        case 0x57:
            events.Item((Int32)Event::KeyDown_W) = true;
            break;
        case 0x58:
            events.Item((Int32)Event::KeyDown_X) = true;
            break;
        case 0x59:
            events.Item((Int32)Event::KeyDown_Y) = true;
            break;
        case 0x5A:
            events.Item((Int32)Event::KeyDown_Z) = true;
            break;
        }

        return 1;
    }

    Int32 ProcessKeyUp(WPARAM wParam)
    {
        switch(wParam)
        {
        case VK_SPACE:
            events.Item((Int32)Event::KeyUp_Space) = true;
            break;
        case 0x41:
            events.Item((Int32)Event::KeyUp_A) = true;
            break;
        case 0x42:
            events.Item((Int32)Event::KeyUp_B) = true;
            break;
        case 0x43:
            events.Item((Int32)Event::KeyUp_C) = true;
            break; 
        case 0x44:
            events.Item((Int32)Event::KeyUp_D) = true;
            break;
        case 0x45:
            events.Item((Int32)Event::KeyUp_E) = true;
            break;
        case 0x46:
            events.Item((Int32)Event::KeyUp_F) = true;
            break; 
        case 0x47:
            events.Item((Int32)Event::KeyUp_G) = true;
            break;
        case 0x48:
            events.Item((Int32)Event::KeyUp_H) = true;
            break;
        case 0x49:
            events.Item((Int32)Event::KeyUp_I) = true;
            break;
        case 0x4A:
            events.Item((Int32)Event::KeyUp_J) = true;
            break;
        case 0x4B:
            events.Item((Int32)Event::KeyUp_K) = true;
            break;
        case 0x4C:
            events.Item((Int32)Event::KeyUp_L) = true;
            break;
        case 0x4D:
            events.Item((Int32)Event::KeyUp_M) = true;
            break;
        case 0x4E:
            events.Item((Int32)Event::KeyUp_N) = true;
            break;
        case 0x4F:
            events.Item((Int32)Event::KeyUp_O) = true;
            break;
        case 0x50:
            events.Item((Int32)Event::KeyUp_P) = true;
            break;
        case 0x51:
            events.Item((Int32)Event::KeyUp_Q) = true;
            break;
        case 0x52:
            events.Item((Int32)Event::KeyUp_R) = true;
            break;
        case 0x53:
            events.Item((Int32)Event::KeyUp_S) = true;
            break;
        case 0x54:
            events.Item((Int32)Event::KeyUp_T) = true;
            break;
        case 0x55:
            events.Item((Int32)Event::KeyUp_U) = true;
            break;
        case 0x56:
            events.Item((Int32)Event::KeyUp_V) = true;
            break;
        case 0x57:
            events.Item((Int32)Event::KeyUp_W) = true;
            break;
        case 0x58:
            events.Item((Int32)Event::KeyUp_X) = true;
            break;
        case 0x59:
            events.Item((Int32)Event::KeyUp_Y) = true;
            break;
        case 0x5A:
            events.Item((Int32)Event::KeyUp_Z) = true;
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

        XStoreName(display, window, name);

        deleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", false);
        XSetWMProtocols(display, window, &deleteMessage, 1);

        events = Array<Int8>((Int32)Event::Count);

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

    Int32 ProcessKeyDown(XKeyEvent xkey)
    {
        KeySym keySym = XkbKeycodeToKeysym(display, xkey.keycode, 0, 1);

        switch(keySym)
        {
        case XK_space:
            events.Item((Int32)Event::KeyDown_Space) = true;
            break;
        case XK_A:
            events.Item((Int32)Event::KeyDown_A) = true;
            break;
        case XK_B:
            events.Item((Int32)Event::KeyDown_B) = true;
            break;
        case XK_C:
            events.Item((Int32)Event::KeyDown_C) = true;
            break; 
        case XK_D:
            events.Item((Int32)Event::KeyDown_D) = true;
            break;
        case XK_E:
            events.Item((Int32)Event::KeyDown_E) = true;
            break;
        case XK_F:
            events.Item((Int32)Event::KeyDown_F) = true;
            break; 
        case XK_G:
            events.Item((Int32)Event::KeyDown_G) = true;
            break;
        case XK_H:
            events.Item((Int32)Event::KeyDown_H) = true;
            break;
        case XK_I:
            events.Item((Int32)Event::KeyDown_I) = true;
            break;
        case XK_J:
            events.Item((Int32)Event::KeyDown_J) = true;
            break;
        case XK_K:
            events.Item((Int32)Event::KeyDown_K) = true;
            break;
        case XK_L:
            events.Item((Int32)Event::KeyDown_L) = true;
            break;
        case XK_M:
            events.Item((Int32)Event::KeyDown_M) = true;
            break;
        case XK_N:
            events.Item((Int32)Event::KeyDown_N) = true;
            break;
        case XK_O:
            events.Item((Int32)Event::KeyDown_O) = true;
            break;
        case XK_P:
            events.Item((Int32)Event::KeyDown_P) = true;
            break;
        case XK_Q:
            events.Item((Int32)Event::KeyDown_Q) = true;
            break;
        case XK_R:
            events.Item((Int32)Event::KeyDown_R) = true;
            break;
        case XK_S:
            events.Item((Int32)Event::KeyDown_S) = true;
            break;
        case XK_T:
            events.Item((Int32)Event::KeyDown_T) = true;
            break;
        case XK_U:
            events.Item((Int32)Event::KeyDown_U) = true;
            break;
        case XK_V:
            events.Item((Int32)Event::KeyDown_V) = true;
            break;
        case XK_W:
            events.Item((Int32)Event::KeyDown_W) = true;
            break;
        case XK_X:
            events.Item((Int32)Event::KeyDown_X) = true;
            break;
        case XK_Y:
            events.Item((Int32)Event::KeyDown_Y) = true;
            break;
        case XK_Z:
            events.Item((Int32)Event::KeyDown_Z) = true;
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
            events.Item((Int32)Event::KeyUp_Space) = true;
            break;
        case XK_A:
            events.Item((Int32)Event::KeyUp_A) = true;
            break;
        case XK_B:
            events.Item((Int32)Event::KeyUp_B) = true;
            break;
        case XK_C:
            events.Item((Int32)Event::KeyUp_C) = true;
            break; 
        case XK_D:
            events.Item((Int32)Event::KeyUp_D) = true;
            break;
        case XK_E:
            events.Item((Int32)Event::KeyUp_E) = true;
            break;
        case XK_F:
            events.Item((Int32)Event::KeyUp_F) = true;
            break; 
        case XK_G:
            events.Item((Int32)Event::KeyUp_G) = true;
            break;
        case XK_H:
            events.Item((Int32)Event::KeyUp_H) = true;
            break;
        case XK_I:
            events.Item((Int32)Event::KeyUp_I) = true;
            break;
        case XK_J:
            events.Item((Int32)Event::KeyUp_J) = true;
            break;
        case XK_K:
            events.Item((Int32)Event::KeyUp_K) = true;
            break;
        case XK_L:
            events.Item((Int32)Event::KeyUp_L) = true;
            break;
        case XK_M:
            events.Item((Int32)Event::KeyUp_M) = true;
            break;
        case XK_N:
            events.Item((Int32)Event::KeyUp_N) = true;
            break;
        case XK_O:
            events.Item((Int32)Event::KeyUp_O) = true;
            break;
        case XK_P:
            events.Item((Int32)Event::KeyUp_P) = true;
            break;
        case XK_Q:
            events.Item((Int32)Event::KeyUp_Q) = true;
            break;
        case XK_R:
            events.Item((Int32)Event::KeyUp_R) = true;
            break;
        case XK_S:
            events.Item((Int32)Event::KeyUp_S) = true;
            break;
        case XK_T:
            events.Item((Int32)Event::KeyUp_T) = true;
            break;
        case XK_U:
            events.Item((Int32)Event::KeyUp_U) = true;
            break;
        case XK_V:
            events.Item((Int32)Event::KeyUp_V) = true;
            break;
        case XK_W:
            events.Item((Int32)Event::KeyUp_W) = true;
            break;
        case XK_X:
            events.Item((Int32)Event::KeyUp_X) = true;
            break;
        case XK_Y:
            events.Item((Int32)Event::KeyUp_Y) = true;
            break;
        case XK_Z:
            events.Item((Int32)Event::KeyUp_Z) = true;
            break;
        }

        return 1;
    }

    Int32 PollEvents()
    {
        events.Clear();

        XEvent event;

        while(XPending(display) > 0)
        {
            XNextEvent(display, &event);

            switch(event.type)
            {
            case ClientMessage:
                if ((Atom)event.xclient.data.l[0] != deleteMessage)
                    break;
                events.Item((Int32)Event::Destroy) = true;
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

    Int32 SwapBuffer()
    {
        glXSwapBuffers(display, window);
        return 1;
    }


#elif PLATFORM == PLATFORM_MAC
#endif

}
