#pragma once

//#include "../OpenGL/Hexxy_OpenGL.h"

#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

namespace Hexxy { namespace Platforms { namespace Windows {

	struct Window {
        Window();
        Window(const wchar_t* WindowName);
        void Show(bool show);
        void ProcessMessage();
        bool WindowIsActive();
    private:
        void CreateWindowClass();
        void CreateWindowHandle(const wchar_t* WindowName);
    private:
        WNDCLASS wc;
        const wchar_t* CLASS_NAME;
        int nCmdShow;
        HINSTANCE hInstance;
        MSG msg;
    protected:
        void CreateBaseWindow(const wchar_t* WindowName);
    protected:
        HWND hwnd;
	};

    struct OpenGLWindow : public Window {
        OpenGLWindow(const wchar_t* WindowName);
        ~OpenGLWindow();
    private:
        void SetPixelFormatDescriptor();
        void SetOpenGLContext();
    private:
        HDC DC;
        HGLRC OpenGLhwnd;
    };

} } }