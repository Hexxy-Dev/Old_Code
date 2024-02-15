#include "Window.h"

#include <iostream>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd, &ps);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

PIXELFORMATDESCRIPTOR pfd =
{
    sizeof(PIXELFORMATDESCRIPTOR),
    1,                    //nVersion
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
    PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
    32,                   // Colordepth of the framebuffer.
    0, 0, 0, 0, 0, 0,     //cRedBits cRedShift cGreenBits cGreenShift cBlueBits cBlueShift
    0,                    //cAlphaBits
    0,                    //cAlphaShift
    0,                    //cAccumBits
    0, 0, 0, 0,           //cAccumRedBits cAccumGreenBits cAccumBlueBits cAccumAlphaBits
    24,                   // Number of bits for the depthbuffer
    8,                    // Number of bits for the stencilbuffer
    0,                    // Number of Aux buffers in the framebuffer.
    PFD_MAIN_PLANE,       //iLayerType
    0,                    //bReserved
    0, 0, 0               //dwLayerMask dwVisibleMask dwDamageMask
}; 


namespace Hexxy { namespace Platforms { namespace Windows {

        Window::Window()
            : wc(), hInstance(GetModuleHandle(0)), CLASS_NAME(L"Hexxy Window Class"), nCmdShow(0), msg()
        {}
        Window::Window(const wchar_t* WindowName) : Window()
        {
            CreateBaseWindow(WindowName);
            Show(1);
        }

        void Window::Show(bool show)
        {
            nCmdShow = show;
            ShowWindow(hwnd, nCmdShow);
        }

        void Window::ProcessMessage()
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        bool Window::WindowIsActive()
        {
            return GetMessage(&msg, NULL, 0, 0);
        }

        void Window::CreateWindowClass()
        {
            wc.lpfnWndProc = WindowProc;
            wc.hInstance = hInstance;
            wc.lpszClassName = CLASS_NAME;
            RegisterClass(&wc);
        }

        void Window::CreateWindowHandle(const wchar_t* WindowName)
        {
            hwnd = CreateWindowEx(
                0,                              // Optional window styles.
                CLASS_NAME,                     // Window class
                WindowName,                     // Window text
                CS_OWNDC,                       // Window style
                // Size and position
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                NULL,       // Parent window    
                NULL,       // Menu
                hInstance,  // Instance handle
                NULL        // Additional application data
            );

            if (hwnd == NULL)
                puts("FAILED TO CREATE WINDOW!!!");
        }


        void Window::CreateBaseWindow(const wchar_t* WindowName)
        {
            CreateWindowClass();
            CreateWindowHandle(WindowName);
        }



        OpenGLWindow::OpenGLWindow(const wchar_t* WindowName)
        {
            CreateBaseWindow(WindowName);
            SetPixelFormatDescriptor();
            SetOpenGLContext();
            Show(1);
        }

        OpenGLWindow::~OpenGLWindow()
        {
            wglMakeCurrent(DC, NULL);
            wglDeleteContext(OpenGLhwnd);
        }

        void OpenGLWindow::SetPixelFormatDescriptor()
        {
            DC = GetDC(hwnd);

            int pixelFormatNumber = ChoosePixelFormat(DC, &pfd);

            SetPixelFormat(DC, pixelFormatNumber, &pfd);
        }

        void OpenGLWindow::SetOpenGLContext()
        {
            OpenGLhwnd = wglCreateContext(DC);

            wglMakeCurrent(DC, OpenGLhwnd);

            puts("CREATED OPENGL CONTEXT");

            printf("%d\n", wglGetCurrentContext());
            printf("%d\n", wglGetCurrentDC());
        }
        

} } }