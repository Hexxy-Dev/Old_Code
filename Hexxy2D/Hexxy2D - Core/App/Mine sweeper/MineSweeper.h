#pragma once
#include <iostream>
#include <random>
#include <time.h>

#include <Windows.h>

const uint8_t mineFieldWidth = 24 + 2;
const uint8_t mineFieldHeight = 30 + 2;
const uint8_t mineNumber = 80;

uint8_t mineField[mineFieldHeight][mineFieldWidth];
uint8_t mineField_Revealed[mineFieldHeight][mineFieldWidth] = { false };


void init()
{
	for (uint8_t i = 0; i < mineFieldHeight; i++)
		for (uint8_t j = 0; j < mineFieldWidth; j++)
			if (!i || !j || i == mineFieldHeight - 1 || j == mineFieldWidth - 1) {
				mineField[i][j] = '#';
				mineField_Revealed[i][j] = true;
			}
			else
				mineField[i][j] = ' ';
}

void PlaceMines()
{
	uint8_t placed_mines = 0;
	while (placed_mines != mineNumber) {
		while (true) {
			uint8_t i = rand() / (mineFieldHeight - 3) + 1;
			uint8_t j = rand() / (mineFieldWidth - 3) + 1;
			if (mineField[i][j] == ' ') {
				int8_t c = 0;
				for (int8_t i = -1; i < 2; i++)
					for (int8_t j = -1; j < 2; j++)
						if (mineField[i][j] == '*')
							c++;
				if (c != 8)
				{
					placed_mines++;
					mineField[i][j] = '*';
					break;
				}
			}
		}
	}
}

void PlaceNumbers()
{
	for (uint8_t i = 1; i < mineFieldHeight - 1; i++) {
		for (uint8_t j = 1; j < mineFieldWidth - 1; j++) {
			if (mineField[i][j] == '*')
				continue;
			uint8_t mines = 0;
			for (int8_t k = -1; k < 2; k++)
				for (int8_t y = -1; y < 2; y++)
					mines += (mineField[i + k][j + y] == '*');
			if (mines)
				mineField[i][j] = mines + '0';
		}
	}
}

char input_i;
char input_j;
char flag;

void Reveal_recursive(int i, int j)
{
	if (mineField_Revealed[i][j] || mineField[i][j] == '*')
		return;
	mineField_Revealed[i][j] = true;
	if (mineField[i][j] != ' ')
		return;
	for (int8_t k = -1; k < 2; k++)
		for (int8_t y = -1; y < 2; y++)
			Reveal_recursive(i + k, j + y);
}

uint8_t BOOM = false;

void Click(int i, int j)
{
	if (flag == 'f') {
		if (mineField_Revealed[i][j] == true)
			return;
		if (mineField_Revealed[i][j] == 2)
			mineField_Revealed[i][j] = false;
		else
			mineField_Revealed[i][j] = 2;
		return;
	}
	if (mineField_Revealed[i][j] == 2)
		return;
	if (mineField[i][j] == '*')
		BOOM = true;
	mineField_Revealed[i][j] = true;
}

void Reveal()
{
	if(!mineField_Revealed[input_i][input_j] && flag != 'f')
	for (int8_t i = -1; i < 2; i++)
		for (int8_t j = -1; j < 2; j++)
			Reveal_recursive(input_i + i, input_j + j);

	if (mineField_Revealed[input_i][input_j] && flag != 'f') {
		uint8_t c = 0;
		for (int8_t i = -1; i < 2; i++)
			for (int8_t j = -1; j < 2; j++)
				if (mineField_Revealed[input_i + i][input_j + j] == 2)
					c++;
		if (c == mineField[input_i][input_j] - '0')
			for (int8_t i = -1; i < 2; i++)
				for (int8_t j = -1; j < 2; j++)
					Click(input_i + i, input_j + j);
	}
	Click(input_i, input_j);
}

bool CheckWin()
{
	for (uint8_t i = 0; i < mineFieldHeight; i++) {
		for (uint8_t j = 0; j < mineFieldWidth; j++)
			if (!mineField_Revealed[i][j] || (mineField[i][j] == '*' && mineField_Revealed[i][j] != 2) || (mineField[i][j] != '*' && mineField_Revealed[i][j] == 2))
				return false;
	}
	return true;
}

void RevealAll()
{
	for (uint8_t i = 0; i < mineFieldHeight; i++)
		for (uint8_t j = 0; j < mineFieldWidth; j++)
			mineField_Revealed[i][j] = true;
}