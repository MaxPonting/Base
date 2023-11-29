#pragma once

#include "../platform/platform.h"
#include "../type/type.h"
#include "../log/log.h"
#include "../array/static_array.h"
#include "../math/struct.h"

#if PLATFORM == PLATFORM_WINDOWS
#include <windows.h>
#include <windowsx.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#elif PLATFORM == PLATFORM_LINUX
#include <GL/gl.h>
#include <GL/glext.h>
#endif

namespace Base::Window
{
    enum class Event
    { 
        Destroy, Resize, Move,
        Count
    };

    enum class OutputType
    {
        Windowed,
        Fullscreen,
        BorderlessFullscreen
    };

    enum class MouseButton
    {
        Left, Middle, Right, Count
    };

#if PLATFORM == PLATFORM_WINDOWS

    enum class Key
    {
        Backspace = 0x08, 
        Tab, Enter = 0x0D,  
        Escape = 0x1B, 
        Space = 0x20, 
        Left = 0x25,
        Up, Right, Down, Zero = 0x30, 
        One, Two, Three, Four, Five, Six, Seven, Eight, Nine, A = 0x41, 
        B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, LeftShift = 0xA0, 
        RightShift, LeftControl, RightControl, LeftAlt, RightAlt,

        Count
    };

#elif PLATFORM == PLATFORM_LINUX

    enum class Key
    {
        Space = 0x0020,
        One = 0x0030,
        Two, Three, Four, Five, Six, Seven, Eight, Nine, A = 0x0041,
        B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, // Group 1
        
        Backspace = 0x0068, 
        Tab, Enter = 0x006D,
        Escape = 0x007B, // Group 2

        Left = 0x0081,
        Up, Right, Down, // Group 3
        
        LeftShift = 0x0091,
        RightShift, LeftControl, RightControl, LeftAlt = 0x0099,
        RightAlt, // Group 4

        Count
    };

#endif

    StaticArray<Bool, (Int32)Event::Count> windowEvents;
    StaticArray<Bool, (Int32)Key::Count>windowKeyboardDown;
    StaticArray<Bool, (Int32)Key::Count> windowKeyboardUp;
    StaticArray<Bool, (Int32)Key::Count> windowKeyboard;
    StaticArray<Bool, (Int32)MouseButton::Count> windowMouseButtonDown;
    StaticArray<Bool, (Int32)MouseButton::Count> windowMouseButtonUp;
    StaticArray<Bool, (Int32)MouseButton::Count> windowMouseButton;
    Int32 windowMouseWheel = 0;
    IVec2 windowMousePosition = { 0, 0 };
    OutputType windowOutputType;

    Bool GetEvent(const Event event)
    {
        if (event == Event::Count)
            return false;

        return windowEvents[(Int32)event];
    }

    Bool GetKeyDown(const Key key)
    {
        if (key == Key::Count)
            return false;

        return windowKeyboardDown[(Int32)key];
    }

    Bool GetKeyUp(const Key key)
    {
        if (key == Key::Count)
            return false;

        return windowKeyboardUp[(Int32)key];       
    }

    Bool GetKey(const Key key)
    {
        if (key == Key::Count)
            return false;
        
        return windowKeyboard[(Int32)key];
    }

    Bool GetMouseButtonDown(const MouseButton button)
    {
        if (button == MouseButton::Count)
            return false;
        
        return windowMouseButtonDown[(Int32)button];
    }

    Bool GetMouseButtonUp(const MouseButton button)
    {
        if (button == MouseButton::Count)
            return false;
        
        return windowMouseButtonUp[(Int32)button];
    }

    Bool GetMouseButton(const MouseButton button)
    {
        if (button == MouseButton::Count)
            return false;
        
        return windowMouseButton[(Int32)button];
    }

    Int32 GetMouseWheel()
    {
        return windowMouseWheel;
    }

    IVec2 GetMousePosition()
    {
        return windowMousePosition;
    }


#if PLATFORM == PLATFORM_WINDOWS


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
        if(wParam >= (Int32)Key::Count)
            return 1;

        windowKeyboard[wParam] = true;
        windowKeyboardDown[wParam] = true;

        return 1;
    }

    Int32 ProcessKeyUp(WPARAM wParam)
    {
        if(wParam >= (Int32)Key::Count)
            return 1;

        windowKeyboard[wParam] = false;
        windowKeyboardUp[wParam] = true;

        return 1;
    }

    LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            windowEvents[(Int32)Event::Destroy] = true;
            PostQuitMessage(0);
            return 0;
        case WM_SIZE:
            windowEvents[(Int32)Event::Resize] = true;
            GetClientRect(hWindow, &windowRect);
            break;
        case WM_MOVE:
            windowEvents[(Int32)Event::Move] = true;
            windowX = LOWORD(lParam);
            windowY = HIWORD(lParam);
            break;
        case WM_PAINT:
            static PAINTSTRUCT paintStruct;
            BeginPaint(hWnd, &paintStruct);
            EndPaint(hWnd, &paintStruct);
            break;
        case WM_KEYDOWN:
            if(lParam & (1<<30))
                break;
            ProcessKeyDown(wParam);
            break;
        case WM_KEYUP:
            ProcessKeyUp(wParam);
            break;
        case WM_MOUSEWHEEL:
            windowMouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            break;
        case WM_MOUSEMOVE:
            windowMousePosition[0] = GET_X_LPARAM(lParam) - (windowRect.right - windowRect.left) / 2;
            windowMousePosition[1] = -(GET_Y_LPARAM(lParam) - (windowRect.bottom - windowRect.top) / 2);
            break;
        case WM_LBUTTONDOWN:
            windowMouseButtonDown[(Int32)MouseButton::Left] = true;
            windowMouseButton[(Int32)MouseButton::Left] = true;
            break;
        case WM_LBUTTONUP:
            windowMouseButtonUp[(Int32)MouseButton::Left] = true;
            windowMouseButton[(Int32)MouseButton::Left] = false;
            break;
        case WM_MBUTTONDOWN:
            windowMouseButtonDown[(Int32)MouseButton::Middle] = true;
            windowMouseButton[(Int32)MouseButton::Middle] = true;
            break;
        case WM_MBUTTONUP:
            windowMouseButtonUp[(Int32)MouseButton::Middle] = true;
            windowMouseButton[(Int32)MouseButton::Middle] = false;
            break;
        case WM_RBUTTONDOWN:
            windowMouseButtonDown[(Int32)MouseButton::Right] = true;
            windowMouseButton[(Int32)MouseButton::Right] = true;
            break;
        case WM_RBUTTONUP:
            windowMouseButtonUp[(Int32)MouseButton::Right] = true;
            windowMouseButton[(Int32)MouseButton::Right] = false;
            break;
        }

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    Int32 Create(const char* name, const OutputType outputType, const Int32 width, const Int32 height)
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
                200,
                200,
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

        GetClientRect(hWindow, &windowRect);

        GetWindowPlacement(hWindow, &windowPlacement);

        if(windowOutputType == OutputType::Fullscreen)
        {
            RECT rect = {200, 200, width + 200, height + 200};
            AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
            windowPlacement.rcNormalPosition = rect;
        }

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
        windowKeyboardDown.Clear();
        windowKeyboardUp.Clear();
        windowMouseButtonDown.Clear();
        windowMouseButtonUp.Clear();
        windowMouseWheel = 0;

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

    Int32 SetVSync(Bool value)
    {
        wglSwapIntervalEXT(value);

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
    
    Int32 SetSize(const Int32 width, const Int32 height)
    {
        if(windowOutputType == OutputType::BorderlessFullscreen)
        {
            Log::Print("Cannot change size when output type is 'Borderless Fullscreen'", Log::Type::Warning, __LINE__, __FILE__);
            return 1;
        }
        
        RECT rect = {windowX, windowY, width, height};
        AdjustWindowRect(&rect, windowOutputType == OutputType::Windowed ? WS_OVERLAPPEDWINDOW : WS_POPUP | WS_VISIBLE, false);
       
        SetWindowPos(hWindow, windowOutputType == OutputType::Windowed ? NULL : HWND_TOP,
            rect.left,
            rect.top,
            rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_NOOWNERZORDER | SWP_FRAMECHANGED 
        );

        if(windowOutputType == OutputType::Fullscreen)
        {
            DEVMODE devMode;
            EnumDisplaySettings(NULL, 0, &devMode);
            devMode.dmPelsWidth = rect.right - rect.left;
            devMode.dmPelsHeight = rect.bottom - rect.top;
            devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

            ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);

            RECT rect = {200, 200, width + 200, height + 200};
            AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
            windowPlacement.rcNormalPosition = rect;
        }

        return 1;
    }

    Int32 SetPosition(const Int32 x, const Int32 y)
    {
        if(windowOutputType != OutputType::Windowed)
        {
            Log::Print("Cannot change position when output type is not 'Windowed'", Log::Type::Warning, __LINE__, __FILE__);
            return 1;
        }

        RECT rect = {x, y, (windowRect.right - windowRect.left) + x, (windowRect.bottom - windowRect.top) + y};
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

        SetWindowPos(hWindow, NULL, 
            rect.left,
            rect.top,
            rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_NOOWNERZORDER | SWP_FRAMECHANGED 
        );

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

    IVec2 GetSize()
    {
        return { GetWidth(), GetHeight() };
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
    typedef void (*glXSwapIntervalEXTProc)(Display*, GLXDrawable, int);

    glXSwapIntervalEXTProc glXSwapIntervalEXT;

    Display* display = NULL;
    Window window = {};
    Screen* screen = NULL;
    Int32 screenID = 0;
    Atom deleteMessage = 0;
    XVisualInfo* visualInfo = NULL;
    GLXContext context = {};
    GLXFBConfig frameBuffer = {};
    Int32 windowX = 0, windowY = 0, windowWidth = 0, windowHeight = 0;

    Int32 FilterKeySym(KeySym keySym)
    {
        if(keySym >= XK_BackSpace && keySym <= XK_Escape)  
        {
            keySym -= 0xFF00;
            keySym += 0x0060;
        } 
        else if(keySym >= XK_Left && keySym <= XK_Down)
        {
            keySym -= 0xFF00;
            keySym += 0x0030;
        }
        else if(keySym >= XK_Shift_L && keySym <= XK_Alt_R)
        {
            keySym -= 0xFF00;
            keySym -= 0x0050;
        }

        return (Int32)keySym;
    }

    Int32 ProcessKeyDown(XKeyEvent xkey)
    {
        const Int32 index = FilterKeySym(XkbKeycodeToKeysym(display, xkey.keycode, 0, 1));

        if(index >= (Int32)Key::Count)
            return 1;

        windowKeyboard[index] = true;
        windowKeyboardDown[index] = true;
        
        return 1;
    }

    Int32 ProcessKeyUp(XKeyEvent xkey)
    {
        const Int32 index = FilterKeySym(XkbKeycodeToKeysym(display, xkey.keycode, 0, 1));

        if(index >= (Int32)Key::Count)
            return 1;

        windowKeyboard[index] = false;
        windowKeyboardUp[index] = true;

        return 1;
    }


    Int32 PollEvents()
    {
        windowEvents.Clear();
        windowKeyboardDown.Clear();
        windowKeyboardUp.Clear();
        windowMouseButtonDown.Clear();
        windowMouseButtonUp.Clear();
        windowMouseWheel = 0;

        XEvent event;

        while(XPending(display) > 0)
        {
            XNextEvent(display, &event);

            switch(event.type)
            {
            case ClientMessage:
                if ((Atom)event.xclient.data.l[0] != deleteMessage)
                    break;
                windowEvents[(Int32)Event::Destroy] = true;
                break;
            case ConfigureNotify:
                if(windowX != event.xconfigure.x || windowY != event.xconfigure.y)
                {
                    windowX = event.xconfigure.x;
                    windowY = event.xconfigure.y;
                    windowEvents[(Int32)Event::Move] = true;
                }
                if(windowWidth != event.xconfigure.width || windowHeight != event.xconfigure.height)
                {
                    windowWidth = event.xconfigure.width;
                    windowHeight = event.xconfigure.height;
                    windowEvents[(Int32)Event::Resize] = true;
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
                    {
                        XNextEvent(display, &event);
                        break;
                    }
                }
                ProcessKeyUp(event.xkey);
                break;
            case ButtonPress:
                switch(event.xbutton.button)
                {
                case 1:
                    windowMouseButtonDown[(Int32)MouseButton::Left] = true;
                    windowMouseButton[(Int32)MouseButton::Left] = true;
                    break;
                case 2:
                    windowMouseButtonDown[(Int32)MouseButton::Middle] = true;
                    windowMouseButton[(Int32)MouseButton::Middle] = true;
                    break;
                case 3:
                    windowMouseButtonDown[(Int32)MouseButton::Right] = true;
                    windowMouseButton[(Int32)MouseButton::Right] = true;
                    break;
                case 4:
                    windowMouseWheel += 1;
                    break;
                case 5:
                    windowMouseWheel -= 1;
                    break;
                }
                break;
            case ButtonRelease:
                switch(event.xbutton.button)
                {
                case 1:
                    windowMouseButtonUp[(Int32)MouseButton::Left] = true;
                    windowMouseButton[(Int32)MouseButton::Left] = false;
                    break;
                case 2:
                    windowMouseButtonUp[(Int32)MouseButton::Middle] = true;
                    windowMouseButton[(Int32)MouseButton::Middle] = false;
                    break;
                case 3:
                    windowMouseButtonUp[(Int32)MouseButton::Right] = true;
                    windowMouseButton[(Int32)MouseButton::Right] = false;
                    break;
                }
                break;
            case MotionNotify:
                windowMousePosition[0] = event.xmotion.x - windowWidth / 2;
                windowMousePosition[1] = -(event.xmotion.y - windowHeight / 2);
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
        windowAttributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | KeymapStateMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask;
        window = XCreateWindow(display, RootWindow(display, screenID), 0, 0, width, height, 0, visualInfo->depth, InputOutput, visualInfo->visual, CWBackPixel | CWBorderPixel | CWColormap| CWEventMask, &windowAttributes);
        XFree(visualInfo);

        if(outputType == OutputType::Fullscreen || outputType == OutputType::BorderlessFullscreen)
        {
            Atom wmState   = XInternAtom (display, "_NET_WM_STATE", true );
            Atom wmFullscreen = XInternAtom (display, "_NET_WM_STATE_FULLSCREEN", true );

            XChangeProperty(display, window, wmState, 1, 32, PropModeReplace, (unsigned char *)&wmFullscreen, 1);

            XMapWindow(display, window);

            windowOutputType = OutputType::BorderlessFullscreen;
        }
        else if(outputType == OutputType::Windowed)
        {
            windowOutputType = OutputType::Windowed;
        }

        XStoreName(display, window, name);

        deleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", false);
        XSetWMProtocols(display, window, &deleteMessage, 1);

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
        glXSwapIntervalEXT = (glXSwapIntervalEXTProc)glXGetProcAddressARB((const UInt8*)"glXSwapIntervalEXT");

        glXSwapIntervalEXT(display, glXGetCurrentDrawable(), 1);

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

    Int32 SetVSync(Bool value)
    {
        glXSwapIntervalEXT(glXGetCurrentDisplay(), glXGetCurrentDrawable(), value);

        return 1;
    }

    Int32 SetOutputType(const OutputType outputType)
    {
        if(outputType == windowOutputType)
            return 1;
        
        Atom wmState   = XInternAtom (display, "_NET_WM_STATE", true );
        Atom wmFullscreen = XInternAtom (display, "_NET_WM_STATE_FULLSCREEN", true );

        XEvent xev;
        xev.type = ClientMessage;
        xev.xclient.window = window;
        xev.xclient.message_type = wmState;
        xev.xclient.format = 32;
        xev.xclient.data.l[0] = (outputType == OutputType::Windowed) ? 0 : 1;
        xev.xclient.data.l[1] = wmFullscreen;
        xev.xclient.data.l[2] = 0;

        XSendEvent(display, DefaultRootWindow(display), False, SubstructureNotifyMask, &xev); 

        windowOutputType = outputType;

        return 1;
    }

    Int32 SetSize(const Int32 width, const Int32 height)
    {
        if(windowOutputType != OutputType::Windowed)
        {
            Log::Print("Cannot change size of window when output type is not 'Windowed'", Log::Type::Warning, __LINE__, __FILE__);
            return 1;
        }

        XResizeWindow(display, window, width, height);

        return 1;
    }

    Int32 SetPosition(const Int32 x, const Int32 y)
    {
        if(windowOutputType != OutputType::Windowed)
        {
            Log::Print("Cannot change size of window when output type is not 'Windowed'", Log::Type::Warning, __LINE__, __FILE__);
            return 1;
        }

        XMoveWindow(display, window, x, y);

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

    IVec2 GetSize()
    {
        return { GetWidth(), GetHeight() };
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