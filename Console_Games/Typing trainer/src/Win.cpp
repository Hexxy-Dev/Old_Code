#include "Win.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cwchar>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


void AdjustConsole()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 60;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void FullScreen()
{
	//system("mode con COLS=700");
	//::ShowWindow(::GetConsoleWindow(), SW_MAXIMIZE);
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}

void ConsoleClear() {
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

void pos(short C, short R)
{
    COORD xy;
    xy.X = C;
    xy.Y = R;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), xy);
}
void cls()
{
    pos(0, 0);
    for (int j = 0; j < 100; j++)
        std::cout << std::string(100, ' ');
    pos(0, 0);
}

//void clear() { // for *NIX
//    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
//    std::cout << "\x1B[2J\x1B[H";
//}
