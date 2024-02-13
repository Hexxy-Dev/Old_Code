#pragma once

START

	const unsigned int board_size_i = 100;
	const unsigned int board_size_j = 100;

	int board[board_size_i + 2][board_size_j + 2] = {0};
	unsigned int generation = 0;

	int nr_of_neighbours(int x, int y) {
		int s = 0;
		for (int i = x + 1; i > x - 2; i--) {
			for (int j = y - 1; j < y + 2; j++) {
				if (board[i][j] == 1 || board[i][j] == 2 || board[i][j] == 3)
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

	void Part1(std::string& input)
	{
		std::string tmp;
		for (size_t i = 0; i < input.size(); i++)
			if(input[i] != '\n')
				tmp += input[i];
		
		for (size_t i = 0; i < tmp.size(); i++)
			board[i/ board_size_i + 1][i% board_size_j + 1] = (tmp[i] == '#');
		
		while (generation < 100)
			tick();
		
		size_t result = 0;
		for (int i = 1; i < board_size_i + 1; i++)
			for (int j = 1; j < board_size_j + 1; j++)
				result += board[i][j];
		std::cout << result;
	}

	void Part2(std::string& input)
	{
		generation = 0;
		std::string tmp;
		for (size_t i = 0; i < input.size(); i++)
			if (input[i] != '\n')
				tmp += input[i];

		for (size_t i = 0; i < tmp.size(); i++)
			board[i / board_size_i + 1][i % board_size_j + 1] = (tmp[i] == '#');

		while (generation < 100) {
			board[1][1] = 1;
			board[1][board_size_j] = 1;
			board[board_size_i][1] = 1;
			board[board_size_i][board_size_j] = 1;
			tick();
		}

		board[1][1] = 1;
		board[1][board_size_j] = 1;
		board[board_size_i][1] = 1;
		board[board_size_i][board_size_j] = 1;

		size_t result = 0;
		for (int i = 1; i < board_size_i + 1; i++)
			for (int j = 1; j < board_size_j + 1; j++)
				result += board[i][j];
		std::cout << result;
	}

END