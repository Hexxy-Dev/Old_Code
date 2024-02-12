#include "Hexxy2D_pch.h"
#include "ChromeProfiler.h"

#include <iostream>

constexpr uint16_t displayWidth = 160;
constexpr uint16_t displayHeight = 90;
constexpr size_t ColorBlock = 10;

uint8_t currentColor = 0;
uint8_t BrushSize = 0;

Hexxy::Display* display;

void Paint(uint8_t color)
{
#if PROFILING == 1 || PROFILING == 2
	PROFILE_FUNCTION();
#endif
	for (int i = Input::YMousePos; i <= Input::YMousePos + BrushSize; i++)
	{
		for (int j = Input::XMousePos; j <= Input::XMousePos + BrushSize; j++)
		{
			if (i - BrushSize / 2 > ColorBlock)
				if (i - BrushSize / 2 < displayHeight - 1)
					if (j - BrushSize / 2 > 0)
						if (j - BrushSize / 2 < displayWidth - 1)
							display->Buffer[i - BrushSize / 2][j - BrushSize / 2] = color;
		}
	}
}

void LeftClick()
{
	if (Input::YMousePos < ColorBlock)
	{
		currentColor = display->Buffer[Input::YMousePos][Input::XMousePos];
		return;
	}
	Paint(currentColor);
}

void Erase()
{
	Paint(0);
}

void Scroll(double xoffset, double yoffset)
{
	if (yoffset > 0)
	{
		if(BrushSize < ColorBlock)
			BrushSize += 2;
	}
	else if (yoffset < 0)
	{
		if(BrushSize > 0)
			BrushSize -= 2;
	}
}

int main()
{
	Hexxy::Display display(displayHeight, displayWidth, 17);
	::display = &display;

	Audio::PlayMusic("ding.flac");

	Input::On("LEFT_MOUSE", "PRESS", LeftClick);
	Input::On("E", "PRESS", Erase);
	Input::OnScroll(Scroll);

	display.ColorPalette.set(1,  255, 255, 255);
	display.ColorPalette.set(2,  178, 31, 53);
	display.ColorPalette.set(3,  216, 39, 53);
	display.ColorPalette.set(4,  255, 116, 53);
	display.ColorPalette.set(5,  255, 161, 53);
	display.ColorPalette.set(6,  255, 203, 53);
	display.ColorPalette.set(7,  255, 240, 53);
	display.ColorPalette.set(8,  0, 117, 58);
	display.ColorPalette.set(9,  0, 158, 71);
	display.ColorPalette.set(10, 22, 221, 53);
	display.ColorPalette.set(11, 0, 82, 165);
	display.ColorPalette.set(12, 0, 121, 231);
	display.ColorPalette.set(13, 0, 169, 252);
	display.ColorPalette.set(14, 104, 60, 126);
	display.ColorPalette.set(15, 125, 60, 180);
	display.ColorPalette.set(16, 189, 122, 246);

	display.UpdateColors();

	size_t color = 1;
	for (size_t offset = 0; offset < displayWidth; offset += ColorBlock)
	{
		for (size_t i = 0; i < ColorBlock; i++)
			for (size_t j = 0; j < ColorBlock; j++)
				display.Buffer[i][j + offset] = color;
		color++;
	}


	while (!display.WindowShouldClose())
	{
		if (Input::IsPressed("LEFT_MOUSE"))
			LeftClick();

		if (Input::IsPressed("E"))
			Erase();

		display.Draw();
	}

	return 0;
}