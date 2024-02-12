#include "Hexxy2D_pch.h"
//#include "ChromeProfiler.h"

#include "../wrappers/3x3Font.h"
#include "../wrappers/5x5Font.h"

#include <iostream>

#include "MineSweeper.h"

constexpr uint8_t sprite_size = 5;

constexpr uint16_t displayWidth = mineFieldWidth * (sprite_size + 1);
constexpr uint16_t displayHeight = mineFieldHeight * (sprite_size + 1);
constexpr size_t NumberOfColors = 20;

Hexxy::Display* display;

char press = false;

void LeftClick()
{
	std::cout << Input::XMousePos / sprite_size << ", ";
	std::cout << Input::YMousePos / sprite_size << "\n";
	input_i = Input::YMousePos / (sprite_size + 1);
	input_j = Input::XMousePos / (sprite_size + 1);
	flag = ' ';

	press = true;
}

void RightClick()
{
	std::cout << Input::XMousePos / sprite_size << ", ";
	std::cout << Input::YMousePos / sprite_size << "\n";
	input_i = Input::YMousePos / (sprite_size + 1);
	input_j = Input::XMousePos / (sprite_size + 1);
	flag = 'f';

	press = true;
}

Hexxy::Fonts::Font5x5 font;

void Display()
{
	Hexxy::Fixed_Update_OK = false;

	for (uint8_t i = 0; i < mineFieldHeight; i++)
		for (uint8_t j = 0; j < mineFieldWidth; j++)
			for (uint8_t k = 0; k < sprite_size; k++)
				for (uint8_t y = 0; y < sprite_size; y++) {
					char displayd_char = (mineField_Revealed[i][j]) ? ((mineField_Revealed[i][j] == 2)? 'F' : mineField[i][j]) : 'o';
					display->Buffer[i * sprite_size + k + i][j * sprite_size + y + j] = font[displayd_char][k][y];
				}

	Hexxy::Fixed_Update_OK = true;
}

void On_FixedUpdate()
{
}


int main()
{
	Hexxy::Display display(displayHeight, displayWidth, NumberOfColors);
	::display = &display;
	
	Hexxy::Set_Fixed_Update_Function(On_FixedUpdate);
	
	Input::On("LEFT_MOUSE", "PRESS", LeftClick);
	Input::On("RIGHT_MOUSE", "PRESS", RightClick);

	display.ColorPalette.SetClearColor(0, 0, 255);
	display.ColorPalette.set(0, 30, 30, 30);
	display.ColorPalette.set(1, 0, 255, 255);
	display.ColorPalette.set(2, 0, 255, 0);
	display.ColorPalette.set(3, 255, 0, 0);
	display.ColorPalette.set(4, 0, 0, 255);
	display.ColorPalette.set(5, 140, 0, 0);
	display.ColorPalette.set(6, 0, 255, 150);
	display.ColorPalette.set(7, 0, 0, 0);
	display.ColorPalette.set(8, 50, 50, 50);
	display.ColorPalette.set(9, 255, 255, 0);
	display.ColorPalette.set(10, 0, 0, 0);
	display.ColorPalette.set(11, 255, 0, 255);

	display.UpdateColors();

	srand(time(NULL));
	init();
	PlaceMines();
	PlaceNumbers();

	for (char i = 'A'; i < 'Z'; i++)
		for (uint8_t k = 0; k < sprite_size; k++)
			for (uint8_t y = 0; y < sprite_size; y++)
				font[i].letter[k * 5 + y] = (font[i][k][y]) ? 11 : 0;

	for (int i = 0; i < 8; i++)
		for (uint8_t k = 0; k < sprite_size; k++)
			for (uint8_t y = 0; y < sprite_size; y++)
				font['0' + i].letter[k * 5 + y] = (font['0' + i][k][y])? i : 0;

	for (uint8_t k = 0; k < sprite_size; k++)
		for (uint8_t y = 0; y < sprite_size; y++)
			font['F'].letter[k * 5 + y] = (font['F'][k][y]) ? 9 : 0;

	for (uint8_t k = 0; k < sprite_size; k++)
		for (uint8_t y = 0; y < sprite_size; y++)
			font['#'].letter[k * 5 + y] = (font['#'][k][y]) ? 8 : 0;

	for (uint8_t k = 0; k < sprite_size; k++)
		for (uint8_t y = 0; y < sprite_size; y++)
			font['o'].letter[k * 5 + y] = (font['o'][k][y]) ? 8 : 0;

	for (uint8_t k = 0; k < sprite_size; k++)
		for (uint8_t y = 0; y < sprite_size; y++)
			font['*'].letter[k * 5 + y] = (font['*'][k][y]) ? 10 : 0;

	char revealed = false;
	while (!display.WindowShouldClose())
	{
		Hexxy::Wait_Fixed_Update();

		Display();
		if(!BOOM && !CheckWin()) {
			if(press) {
				Reveal();
				flag = ' ';
				press = false;
			}
		}

		if (!(!BOOM && !CheckWin()))
			if (CheckWin()) {
				std::string message = "YOU WON!";
				for (uint8_t j = 0; j < message.size(); j++)
					for (uint8_t k = 0; k < sprite_size; k++)
						for (uint8_t y = 0; y < sprite_size; y++)
							display.Buffer[k][(j + 10) * sprite_size + y + j] = font[message[j]][k][y];
			}
			else {
				if (!revealed) {
					RevealAll();
					revealed = true;
				}
				std::string message = "GAME OVER";
				for (uint8_t j = 0; j < message.size(); j++)
					for (uint8_t k = 0; k < sprite_size; k++)
						for (uint8_t y = 0; y < sprite_size; y++)
							display.Buffer[k][(j + 10) * sprite_size + y + j] = font[message[j]][k][y];
			}

		display.Draw();
	}

	return 0;
}