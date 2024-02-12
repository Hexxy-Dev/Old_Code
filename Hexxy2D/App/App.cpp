#include "Hexxy2D.h"

#include <iostream>

// THIS FILE IS A EXAMPLE OF WHAT YOU CAN DO WITH THIS LIBRARY

// THE "res" FOLDER AND THE DLL SHOULD ALSO BE IN: (main) Hexxy2D/x64/Release (or Debug)
// IF YOU WANT TO RUN IT FROM THE .exe FILE
// THUS IF YOU WANT TO SHARE JUST THE FINAL PRODUCT YOU WOULD SHARE THE ENTIRE /Release FOLDER

constexpr size_t GridHeight = 9;	// WARNING: Quad scaling happenes only on the Y axis rn
constexpr size_t GridWidht = 16;      
constexpr size_t NumberOfColors = 5;
// these numbers can be put directlly instead of creating variables
// they are here just to show what they represent

Hexxy::Display<GridHeight, GridWidht, NumberOfColors> display;

void SimultaneousSoundsTest()
{
	Audio::PlayMusic("orchestral.ogg");
	sf::sleep(sf::milliseconds(300));
	Audio::PlayMusic("ding.flac");
	sf::sleep(sf::milliseconds(300));
	Audio::PlaySoundWav("canary.wav");

	// WARNING IF YOU PLAY MORE THAN ONE SOUND AT ONCE YOU HAVE TO WAIT A BIT AFTER EACH
	// PlaySound() CALL. THE WAIT TIME SHOULD BE AROUND 300ms (or more depending on size)
}

void LeftClick()
{
	std::cout << Input::XMousePos << ", ";
	std::cout << Input::YMousePos << "\n";

	if (Input::XMousePos == 0 && Input::YMousePos == 0) // the button is the first square
														// of the display grid
	{
		std::cout << "You clicked on the button!!!!\n";
		Audio::PlaySoundWav("canary.wav");
	}// THE WARNING ABOVE APPLYES HERE TOO
}

void Scroll(double xoffset, double yoffset)
{
	std::cout << xoffset << ", " << yoffset << "\n";
}

int main()
{
	SimultaneousSoundsTest();

	Input::On("LEFT_MOUSE", "PRESS", LeftClick);
	Input::OnScroll(Scroll);

	// BY DEFAULT "ESCAPE" WILL CLOSE THE GAME WINDOW
	// 	   OR
	//	display.CloseWindow();
	// You can also close the window programatically with this function (this is the function
	// that is called by default when you press "ESCAPE")

	display.ColorPalette.set(1, 255, 0, 255, 1.0f);
	display.ColorPalette.set(2, 0, 255, 255, 1.0f);

	display.UpdateColors();

	uint8_t sprite[8][8] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0},
		{1, 0, 0, 1, 1, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 0, 1},
		{0, 1, 1, 0, 0, 1, 1, 0},
	};

	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 8; j++)
			display.Buffer[i][j] = sprite[i][j];

	// random "pixels"
	display.Buffer[7][15] = 2;
	display.Buffer[8][9] = 2;
	display.Buffer[8][12] = 2;
	display.Buffer[8][13] = 2;
	display.Buffer[8][14] = 2;
	display.Buffer[8][15] = 2;

	display.PrintColorPalette();
	display.PrintBuffer();

	// BY DEFAULT "ESCAPE" will also exit this while loop (because the window is closed)
	while (!glfwWindowShouldClose(window)) // this just draws until I "close" the window
										// also this should be the main game loop
	{
		if (Input::IsPressed("W"))
			std::cout << "W is pressed\n";
		if (Input::IsPressed("S"))
			std::cout << "S is pressed\n";

		display.Draw();
	}

	return 0;
}