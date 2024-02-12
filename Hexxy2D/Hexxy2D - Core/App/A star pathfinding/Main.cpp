//#include "Hexxy2D.h"

#include "Hexxy2D_pch.h"

#include <iostream>

constexpr size_t GridHeight = 9;
constexpr size_t GridWidht = 30;
constexpr size_t NumberOfColors = 5;

Hexxy::Display* display;

void LeftClick()
{
	std::cout << Input::XMousePos << ", ";
	std::cout << Input::YMousePos << "\n";

	if (Input::XMousePos == 0 && Input::YMousePos == 0)
	{
		std::cout << "You clicked on the button!!!!\n";
	}
}

int main()
{
	Hexxy::Display display(GridHeight, GridWidht, NumberOfColors);

	Input::On("LEFT_MOUSE", "PRESS", LeftClick);
	
	display.ColorPalette.set(1, 255, 0, 255, 1.0f);
	display.ColorPalette.set(2, 0, 255, 255, 1.0f);

	display.UpdateColors();

	while (!display.WindowShouldClose())
	{
		display.Draw();
	}

	return 0;
}