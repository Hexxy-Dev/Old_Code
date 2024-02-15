#include "WindowsAbstraction.h"

#include <Windows.h>

HANDLE hConsole;

void InitWindowsAbstractionLayer()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

int SetTextColor(const char foreground, const char background)
{
	int k = foreground + background * 16;
	SetConsoleTextAttribute(hConsole, k);
	return k;
}

int SetTextColor(const int color)
{
	SetConsoleTextAttribute(hConsole, color);
	return color;
}