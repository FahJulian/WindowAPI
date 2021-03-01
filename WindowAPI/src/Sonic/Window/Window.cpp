#include <iostream>
#include "Input/Mouse.h"
#include "Input/Keys.h"
#include "_WIN32Include.h"
#include "Window.h"

using namespace Sonic;

extern bool s_Running;


static HWND s_Win32Handle;
static uint64_t s_TimerOffset;
static uint64_t s_TimerFrequency;

static WindowInfo s_Info;


LRESULT CALLBACK Window::WindowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:  [[fallthrough]];
    case WM_QUIT:   [[fallthrough]];
    case WM_DESTROY:
        s_Running = false;
        return 0;

    case WM_LBUTTONDOWN:
        onMouseButtonPressed(MouseButtons::Left);
        return 0;

    case WM_LBUTTONUP:
        onMouseButtonReleased(MouseButtons::Left);
        return 0;

    case WM_RBUTTONDOWN:
        onMouseButtonPressed(MouseButtons::Right);
        return 0;

    case WM_RBUTTONUP:
        onMouseButtonReleased(MouseButtons::Right);
        return 0;

    case WM_MBUTTONDOWN:
        onMouseButtonPressed(MouseButtons::Middle);
        return 0;

    case WM_MBUTTONUP:
        onMouseButtonReleased(MouseButtons::Middle);
        return 0;

    case WM_XBUTTONDOWN:
        onMouseButtonPressed(GET_XBUTTON_WPARAM(wParam) == XBUTTON1 ? MouseButtons::MB_4 : MouseButtons::MB_5);
        return 0;

    case WM_XBUTTONUP:
        onMouseButtonReleased(GET_XBUTTON_WPARAM(wParam) == XBUTTON1 ? MouseButtons::MB_4 : MouseButtons::MB_5);
        return 0;
        
    case WM_MOUSEMOVE:
    {
        Mouse::s_X = (float)GET_X_LPARAM(lParam);
        Mouse::s_Y = (float)GET_Y_LPARAM(lParam);
        std::cout << "Mouse moved " << "(" << Mouse::s_X << ", " << Mouse::s_Y << ")" << std::endl;

        return 0;
    }

    case WM_MOUSEWHEEL:
        std::cout << "Mouse scrolled by " << GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA << " " << "(" << Mouse::s_X << ", " << Mouse::s_Y << ")" << std::endl;
        return 0;

    case WM_SYSKEYDOWN:
        std::cout << "System ";
        [[fallthrough]];
    case WM_KEYDOWN:
    {
        Key key = *((Key*)&wParam);

        if (key == Keys::Control) // Win32 does weird things
        {
            if (lParam & 1 << 24) // Extended key -> Right Control
            {
                key = Keys::RightControl;
            }
            else if (MSG next;  // When right alt is pressed, two messages are sent, the first one has to be ignored
                PeekMessage(&next, NULL, WM_KEYFIRST, WM_KEYLAST, PM_NOREMOVE))
            {
                if (Key nextKey = *((Key*)&next.wParam);
                    nextKey == Keys::Alt && next.lParam & 1 << 24)
                {
                    return 0;
                }
            }
        }
        else if (lParam & 1 << 24 && key == Keys::Alt)
        {
            key = Keys::RightAlt;
        }

        std::cout << "Key " << (int)key << " pressed" << std::endl;

        return 0;
    }

    case WM_SYSKEYUP:
        std::cout << "System ";
        [[fallthrough]];
    case WM_KEYUP:
    {
        Key key = *((Key*)&wParam);

        if (key == Keys::Control) // Win32 does weird things
        {
            if (lParam & 1 << 24) // Extended key -> Right Control
            {
                key = Keys::RightControl;
            }
            else if (MSG next;
                PeekMessage(&next, NULL, WM_KEYFIRST, WM_KEYLAST, PM_NOREMOVE))
            {
                if (Key nextKey = *((Key*)&next.wParam);
                    nextKey == Keys::Alt && next.lParam & 1 << 24)
                {
                    return 0;
                }
            }
        }
        else if (lParam & 1 << 24 && key == Keys::Alt)
        {
            key = Keys::RightAlt;
        }

        std::cout << "Key " << (int)key << " released" << std::endl;

        return 0;
    }

    case WM_SIZE:
        std::cout << "Window resized to " << "(" << LOWORD(lParam) << ", " << HIWORD(lParam) << ")" << std::endl;
        return 0;

    case WM_MOVE:
        std::cout << "Window moved to " << "(" << LOWORD(lParam) << ", " << HIWORD(lParam) << ")" << std::endl;
        return 0;
    }

    return DefWindowProc(handle, msg, wParam, lParam);
}

void Window::onMouseButtonPressed(MouseButton button)
{
    Mouse::s_Buttons[button] = true;
    std::cout << "Button " << (int)button << " pressed " << "(" << Mouse::s_X << ", " << Mouse::s_Y << ")" << std::endl;
}

void Window::onMouseButtonReleased(MouseButton button)
{
    Mouse::s_Buttons[button] = false;
    std::cout << "Button " << (int)button << " pressed " << "(" << Mouse::s_X << ", " << Mouse::s_Y << ")" << std::endl;
}

bool Window::init(const WindowInfo& info)
{
    s_Info = info;
    s_Info.currentWidth = s_Info.initialWidth;
    s_Info.currentHeight = s_Info.initialHeight;
    s_Info.currentMode = s_Info.initialMode;
    s_Info.currentName = s_Info.initialName;

    QueryPerformanceFrequency((LARGE_INTEGER*)&s_TimerFrequency);
    QueryPerformanceCounter((LARGE_INTEGER*)&s_TimerOffset);

    const wchar_t* className = L"Sample Window Class";
    HMODULE win32ModuleHandle = GetModuleHandle(0);

    WNDCLASS win32WindowClass = { };
    win32WindowClass.lpfnWndProc = Window::WindowProc;
    win32WindowClass.hInstance = win32ModuleHandle;
    win32WindowClass.lpszClassName = className;

    RegisterClass(&win32WindowClass);

    // Convert initial name to wide string
    WideString windowName;
    windowName.assign(s_Info.initialName.begin(), s_Info.initialName.end());

    s_Win32Handle = CreateWindowEx(
        0,                              // Optional window styles.
        className,                      // Window class
        windowName.c_str(),             // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, info.initialWidth, info.initialHeight,

        NULL,                           // Parent window    
        NULL,                           // Menu
        win32ModuleHandle,              // Instance handle
        NULL                            // Additional application data
    );

    if (s_Win32Handle == NULL)
    {
        DWORD error = GetLastError();
        // TODO: Print error
        return false;
    }

    ShowWindow(s_Win32Handle, 1);

    return true;
}

void Window::pollEvents()
{
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

double Window::getTime()
{
    uint64_t timer;
    QueryPerformanceCounter((LARGE_INTEGER*)&timer);
    return (double)(timer - s_TimerOffset) / s_TimerFrequency;
}
