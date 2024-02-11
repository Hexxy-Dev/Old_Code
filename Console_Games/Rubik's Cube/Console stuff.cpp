#include "Console stuff.h"

#include <cwchar>
#include <Windows.h>


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

SHORT cols = 100, rows = 300;

// set console font size (on Y)
void set_console_font_size(int size)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 30;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    //wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(console, FALSE, &cfi);
}

// set the console's number of columns and rows to be displayed
void set_console_window_size(SHORT cols, SHORT rows)
{
    CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx;
    sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(console, &sbInfoEx);
    sbInfoEx.dwSize.X = cols;
    sbInfoEx.dwSize.Y = rows;
    sbInfoEx.srWindow = { 0, 0, cols, rows };
    sbInfoEx.dwMaximumWindowSize = { cols, rows };
    SetConsoleScreenBufferInfoEx(console, &sbInfoEx);

    DWORD mode;
    GetConsoleMode(console, &mode);
    mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
    SetConsoleMode(console, mode);
}

// make the console fullscreen
void make_console_fullscreen()
{
    SetConsoleDisplayMode(console, CONSOLE_FULLSCREEN_MODE, 0);
}

#include <iostream>
using std::cerr;

// remove the console's scrollbar
void remove_scrollbar()
{
    try {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        GetConsoleScreenBufferInfo(console, &csbi);
        COORD scrollbar = {
            csbi.srWindow.Right - csbi.srWindow.Left + 1,
            csbi.srWindow.Bottom - csbi.srWindow.Top + 1
        };

        if (console == 0) {
            throw 0;
        }
        else {
            SetConsoleScreenBufferSize(console, scrollbar);
        }
    }
    catch (...) {
        cerr << "Error removing scrollbar";
    }
}

// set the cursor pozition
void set_cursor_poz(short i, short j) {
    SetConsoleCursorPosition(console, { j, i });
}

// [temporary] pause the program for n ms
void temp_sleep(int n) 
{
    Sleep(n);
}

// initial setup for the console
void console_setup() 
{
    SetConsoleTitle(L"Console Rubik's Cube");
    
    set_console_window_size(cols, rows);
    set_console_font_size(5);
    make_console_fullscreen();

    remove_scrollbar();                    // IDK why this conflicts with the set window size
                                           // but it messes everything up so this is the only
    make_console_fullscreen();             // way I can make it work
    set_console_window_size(cols, rows);   // TODO: Try to fix this

    set_cursor_poz(0, 0);
}