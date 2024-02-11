#include <iostream>
#include <string>

#define clear() puts("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

#include <unistd.h>
void sleep_ms(size_t milliseconds)
{
	struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}


#include "./presets.hpp"

unsigned int generation = 0;
int board[board_size_i + 2][board_size_j + 2] = { 0 };

void print_board() {
	clear();

	std::string output = "";

	for (int i = 1; i < board_size_i + 1; i++) {
		for (int j = 1; j < board_size_j + 1; j++) {
			if (board[i][j] == 0) {
				output += "\033[107m ";
				continue;
			}
			output += "\033[40m ";
		}
		output += '\n';
	}
	puts(output.c_str());

	gotoxy(0,0);
}

int nr_of_neighbours(int x, int y) {
	int s = 0;
	for (int i = x + 1; i > x - 2; i--) {
		for (int j = y - 1; j < y + 2; j++) {
			if(board[i][j] == 1 || board[i][j] == 2 || board[i][j] == 3)
				s++;
		}
	}
	return s - board[x][y];
}

void tick() {
	for (int i = 1; i < board_size_i + 1; i++) {
		for (int j = 1; j < board_size_j + 1; j++) {
			if (board[i][j] == 0) {
				if (nr_of_neighbours(i, j) == 3)
					board[i][j] = 4;
				continue;
			}

			switch (nr_of_neighbours(i, j)) {
				case(0):
				case(1):
					board[i][j] = 2;
					break;
				case(2):
				case(3):
					board[i][j] = 3;
					break;

				default:
					board[i][j] = 2;
					break;
			}
		}
	}

	for (int i = 1; i < board_size_i + 1; i++) {
		for (int j = 1; j < board_size_j + 1; j++) {
			if (board[i][j] == 0)
				continue;

			board[i][j] -= 2;
			if (board[i][j] == 2)
				board[i][j]--;
		}
	}

	generation++;
}

void init_board() {
	for (int i = offset; i < init_board_size_i+offset; i++) {
		for (int j = 0; j < init_board_size_j; j++) {
			board[i + 1][j + 1] = new_board[i-offset][j];
		}
	}
}

int main() {
	puts("\033[107m");

	init_board();
	print_board();

	int z = 0;
	while (true) {
		tick();
		sleep_ms(sleep_duration);
		if (z == step) {
			print_board();
			z = 0;
		}
		z++;
	}
}