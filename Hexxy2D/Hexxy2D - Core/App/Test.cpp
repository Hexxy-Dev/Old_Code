#include "Hexxy2D_pch.h"
//#include "Hexxy2D.h"

#include <iostream>

constexpr size_t GridHeight = 528;
constexpr size_t GridWidht = 477;
constexpr size_t NumberOfColors = 5;

int main()
{
    Hexxy::Display display(GridHeight, GridWidht, NumberOfColors);

    display.ColorPalette.SetClearColor(0, 255, 255);

    display.ColorPalette.set(0, 255, 255, 255);
    display.ColorPalette.set(1, 255, 0, 255, 0.5f);
    display.ColorPalette.set(2, 0, 255, 0);

    display.UpdateColors();

    for(int j = 0; j < GridHeight; j++)
        for(int i = 0; i < GridWidht - 100; i++)
            display.Buffer[j][i] = 1;

    display.PrintColorPalette();
    //display.PrintBuffer();

    while (!display.WindowShouldClose())
    {
        display.Draw();
    }

    return 0;
}