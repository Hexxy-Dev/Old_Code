//#include "Hexxy2D.h"

#include "Hexxy2D_pch.h"
//#include "../wrappers/Utility.h"

#include <iostream>

// THIS FILE IS A EXAMPLE OF WHAT YOU CAN DO WITH THIS LIBRARY

// IF YOU WANT TO RUN THE APP FROM THE .exe FILE THE RES FOLDER ALSO NEEDS TO BE ADDED
// IN THE SAME FOLDER AS THE .exe ALONG WITH THE .dll

constexpr size_t GridHeight = 9;
constexpr size_t GridWidht = 30;
constexpr size_t NumberOfColors = 5;

Hexxy::Display* display;

void SimultaneousSoundsTest()
{
	Audio::PlayMusic("orchestral.ogg");
	Hexxy::Sleep_For_Milliseconds(300);
	Audio::PlayMusic("ding.flac");
	Hexxy::Sleep_For_Milliseconds(300);
	Audio::PlaySoundWav("canary.wav");

	// WARNING IF YOU PLAY MORE THAN ONE SOUND AT ONCE YOU HAVE TO WAIT A BIT AFTER EACH
	// PlaySound() CALL. THE WAIT TIME SHOULD BE AROUND 300ms (or more depending on size)
}

void LeftClick()
{
	std::cout << Input::XMousePos << ", "; // these coords are grid coords but if you move the buffer
	std::cout << Input::YMousePos << "\n"; // using the offsets it will NOT move
										   // they are "grid coords" but are relative to the screen

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

void Use_Display_Object_Globally()
{
	display->PrintBuffer();
	// OR
	(*display).PrintBuffer();
}


int Really_Unsafe_Var;
float Offset = 0;

void On_FixedUpdate()// this func will be called once every X ms
{
	if (Input::IsPressed("H"))
	{
		Hexxy::Fixed_Update_OK = false; // when you add to the buffer in fixed update you should do this
										// to avoid screen thare
		if (display->Buffer[3][3] == 1)
			display->Buffer[3][3] = 2;
		else
			display->Buffer[3][3] = 1;
		Hexxy::Fixed_Update_OK = true;// after you finish editing the buffer or color pallette make sure
									// to set it back to true
									// this var is also set to true when this function ends
	}

	std::cout << "Fixed Update!\n";
	Really_Unsafe_Var++;




	Offset++;
	display->SetOffsets(0, -Offset);
}


int main()
{
	Hexxy::Display display(GridHeight, GridWidht, NumberOfColors);
	// WARNING: MULTIPLE DISPLAYS ARE NOT SUPPORTED!!!
	::display = &display; // ah yes, pointer fuckery
	// this fuckery is because the display object needs to be declared in main() :(

	Hexxy::Set_Fixed_Update_Function(On_FixedUpdate);

	Use_Display_Object_Globally();
	
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

	// WARNING: NO INDEX ADDRESSABLE VARIABLES HAVE INDEX SIZE GUARDS!! YOU CAN VERY EASALY GET A INDEX OUT OF THE ARRAY 

	// random "pixels"
	display.Buffer[7][15] = 2;
	display.Buffer[8][9] = 2;
	display.Buffer[8][12] = 2;
	display.Buffer[8][13] = 2;
	display.Buffer[8][14] = 2;
	display.Buffer[8][15] = 2;

	display.Buffer[8][16] = 2;
	display.Buffer[8][17] = 2;
	display.Buffer[8][18] = 1;
	display.Buffer[8][19] = 2;
	display.Buffer[8][20] = 1;
	display.Buffer[8][21] = 2;
	display.Buffer[8][22] = 1;
	display.Buffer[8][23] = 2;
	display.Buffer[8][24] = 1;
	display.Buffer[7][25] = 2;
	display.Buffer[8][29] = 2;

	display.PrintColorPalette();
	display.PrintBuffer();

	// BY DEFAULT "ESCAPE" will also exit this while loop (because the window is closed)
	while (!display.WindowShouldClose()) // this just draws until I "close" the window
										// also this should be the main game loop
	{
		Hexxy::Wait_Fixed_Update();

		if (Input::IsPressed("W"))
			std::cout << "W is pressed\n";
		if (Input::IsPressed("S"))
			std::cout << "S is pressed\n";

		std::cout << "Main thread: Unsafe var:" << Really_Unsafe_Var << '\n';

		display.Draw();
	}

	return 0;
}