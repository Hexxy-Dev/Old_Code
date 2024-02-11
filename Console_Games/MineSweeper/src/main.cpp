#include <iostream>
#include <random>
#include <time.h>

void clear() { puts("\033[H\033[J"); }

const uint8_t mineFieldWidth = 9 + 2;
const uint8_t mineFieldHeight = 9 + 2;
const uint8_t mineNumber = 30;

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

void Display()
{
	clear();
	std::cout << "-1 ";
	for (uint8_t i = 0; i < mineFieldHeight; i++)
		std::cout << (int)i << ((i > 9) ? " " : "  ");
	std::cout << '\n';
	for (uint8_t i = 0; i < mineFieldHeight; i++) {
		std::cout << (int)i << ((i+1 > 10)? " " : "  ");
		for (uint8_t j = 0; j < mineFieldWidth; j++)
			if (mineField_Revealed[i][j])
				if (mineField_Revealed[i][j] == 2)
					std::cout << "F  ";
				else
					std::cout << mineField[i][j] << "  ";
			else
				std::cout << "#  ";
		std::cout << '\n';
	}
}

char input_i;
char input_j;
char flag;

void input()
{
	std::cin >> input_i;
	std::cin >> input_j;
	flag = std::cin.get();
	std::cin.clear();
	input_i -= '0';
	input_j -= '0';
}

void Reveal_recursive(int i, int j)
{
	if (mineField_Revealed[i][j] || mineField[i][j] == '*')
		return;
	mineField_Revealed[i][j] = true;
	if (mineField[i][j] != ' ')
		return;
	Reveal_recursive(i - 1, j);
	Reveal_recursive(i, j - 1);
	Reveal_recursive(i, j + 1);
	Reveal_recursive(i + 1, j);
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
	if (mineField_Revealed[input_i][input_j] && flag != 'f') {
		uint8_t c = 0;
		for (int8_t i = -1; i < 2; i++)
			for (int8_t j = -1; j < 2; j++)
				if (mineField_Revealed[input_i + i][input_j + j])
					c++;
		if(c == mineField[input_i][input_j] - '0')
		for(int8_t i = -1; i < 2; i++)
			for(int8_t j = -1; j < 2; j++)
				Click(input_i + i, input_j + j);
	}
	Click(input_i, input_j);
	if (flag == 'f')
		return;
	Reveal_recursive(input_i - 1, input_j);
	Reveal_recursive(input_i, input_j - 1);
	Reveal_recursive(input_i, input_j + 1);
	Reveal_recursive(input_i + 1, input_j);
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

int main()
{
	srand(time(NULL));
	init();
	PlaceMines();
	PlaceNumbers();

	while (!BOOM && !CheckWin()) {
		Display();
		input();
		Reveal();
	}
	RevealAll();
	Display();
	if (CheckWin())
		std::cout << "YOU WON!";
	else
		std::cout << "GAME OVER";
	std::cin.get();
}