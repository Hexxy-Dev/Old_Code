#include <iostream>
#include <conio.h>
#include <random>


uint8_t P_score = 0;
uint8_t C_score = 0;

uint8_t flags = 0b00000001;

#define difficulty (flags & 0b00000011)
#define P_move ((flags & 0b00001100) >> 2)

constexpr char* moves[] = { "Rock","Paper","Scissors" };

void SelectPlayerMove()
{
	puts("Select Move:"
		"\n\t1)Rock"
		"\n\t2)Paper"
		"\n\t3)Scissors");
	while (true) {
		switch (getch()) {
			case '1': flags &= 0b00000011; return;
			case '2': flags |= 0b00000100; return;
			case '3': flags |= 0b00001000; return;
		}
		puts("invalid move");
	}
}

int Win_Check(uint8_t RNG)
{
	switch (difficulty) {
		case 0: {	uint8_t RNG_Bias[] = { 1,1,1,1,1,1,1,2,2,0,0,0,0,0,0,0,0,0,0,0 }; // 35% W 10% D
					return RNG_Bias[RNG];}

		case 1: {	uint8_t RNG_Bias[] = { 1,1,1,1,1,1,1,1,1,2,2,2,0,0,0,0,0,0,0,0 }; // 45% W 15% D
					return RNG_Bias[RNG]; }

		case 2: {	uint8_t RNG_Bias[] = { 1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,0,0,0 }; // 55% W 30% D
					return RNG_Bias[RNG];}

		case 3: return 1; // 100% W
	}
}

int main()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<> uniform_distribution(0, 19);

	puts("Select \"Difficulty\": (def = 1)"
		"\n\t0)Easy"
		"\n\t1)Normal"
		"\n\t2)Hard"
		"\n\t3)Impossible");
	{
		char c = getch();
		if (c >= '0' && c <= '3')
			flags = c - '0';
	}
	system("CLS");

	while (true) {
		printf("Score: P1 %d - %d CPU\n", P_score, C_score);

		SelectPlayerMove();

		system("CLS");

		printf("P1 chose: %s\n", moves[P_move]);

		switch (Win_Check(uniform_distribution(generator))) {
			case 1:
				printf("CPU chose: %s\n\tCPU WINS\n", moves[(P_move + 1) % 3]);
				C_score++;
				break;
			case 2:
				printf("CPU chose: %s\n\tDRAW\n", moves[P_move]);
				break;
			default:
				printf("CPU chose: %s\n\tP1 WINS\n", moves[(P_move + 2) % 3]);
				P_score++;
		}

		puts("Try Again? (*/n)");
		if (getch() == 'n')
			return 0;

		system("CLS");
		if (P_score == 100 || C_score == 100) {
			if (P_score == 100)
				puts("\tP1 WINS");
			else
				puts("\tCPU WINS");
			return 0;
		}
		
		flags &= 0b00000011;
	}
}