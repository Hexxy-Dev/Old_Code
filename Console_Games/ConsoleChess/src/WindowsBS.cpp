#define _CRT_SECURE_NO_WARNINGS

#include "WindowsBS.h"
#include <Windows.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>

void GetNiceConsole() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    cfi.dwFontSize.Y = 80;
    wcscpy(cfi.FaceName, L"Cascadia Mono");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void ClearScreen() {
    system("CLS");
}