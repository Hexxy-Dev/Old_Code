#include "OpenGL.h"

#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <iostream>

namespace Hexxy { namespace Platforms { namespace Windows { namespace OpenGL {

    void* GetGLFuncAddress(const char* name)
    {
        void* p = (void*)wglGetProcAddress(name);
        if (p == 0 ||
            (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
            (p == (void*)-1))
        {
            HMODULE module = LoadLibraryA("opengl32.dll");
            p = (void*)GetProcAddress(module, name);
        }

        return p;
    }

    void init()
    {
        puts("LOADING OPENGL FUNCTIONS!!");
         glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)GetGLFuncAddress("glGenVertexArrays");
         glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)GetGLFuncAddress("glBindVertexArray");
         glGenBuffers = (PFNGLGENBUFFERSPROC)GetGLFuncAddress("glGenBuffers");
         glBindBuffer = (PFNGLBINDBUFFERPROC)GetGLFuncAddress("glBindBuffer");
         glBufferData = (PFNGLBUFFERDATAPROC)GetGLFuncAddress("glBufferData");
         glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)GetGLFuncAddress("glVertexAttribPointer");
         glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)GetGLFuncAddress("glEnableVertexAttribArray");
         glCreateShader = (PFNGLCREATESHADERPROC)GetGLFuncAddress("glCreateShader");
         glShaderSource = (PFNGLSHADERSOURCEPROC)GetGLFuncAddress("glShaderSource");
         glCompileShader = (PFNGLCOMPILESHADERPROC)GetGLFuncAddress("glCompileShader");
         glGetShaderiv = (PFNGLGETSHADERIVPROC)GetGLFuncAddress("glGetShaderiv");
         glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)GetGLFuncAddress("glGetShaderInfoLog");
         glCreateProgram = (PFNGLCREATEPROGRAMPROC)GetGLFuncAddress("glCreateProgram");
         glAttachShader = (PFNGLATTACHSHADERPROC)GetGLFuncAddress("glAttachShader");
         glLinkProgram = (PFNGLLINKPROGRAMPROC)GetGLFuncAddress("glLinkProgram");
         glUseProgram = (PFNGLUSEPROGRAMPROC)GetGLFuncAddress("glUseProgram");
         glDeleteShader = (PFNGLDELETESHADERPROC)GetGLFuncAddress("glDeleteShader");
         glClearColor = (PFNGLCLEARCOLORPROC)GetGLFuncAddress("glClearColor");
         glClear = (PFNGLCLEARPROC)GetGLFuncAddress("glClear");
         glDrawElements = (PFNGLDRAWELEMENTSPROC)GetGLFuncAddress("glDrawElements");


          glBegin = (PFNGLBEGINPROC)GetGLFuncAddress("glBegin");
          glColor4f = (PFNGLCOLOR4FPROC)GetGLFuncAddress("glColor4f");
          glVertex2f = (PFNGLVERTEX2FPROC)GetGLFuncAddress("glVertex2f");
          glEnd = (PFNGLENDPROC)GetGLFuncAddress("glEnd");

          glGetString = (PFNGLGETSTRINGPROC)GetGLFuncAddress("glGetString");
    }

} } } }