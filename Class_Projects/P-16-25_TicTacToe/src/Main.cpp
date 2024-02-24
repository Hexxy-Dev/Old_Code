#include <iostream>
#include <limits>
#include <cmath>

bool piece = 0; //0 to start with O   1 to start with X

char board[3][3];

void initializeBoard(){
	for (uint8_t i = 0; i < 3; i++)
		for (uint8_t j = 0; j < 3; j++)
			board[i][j] = '#';
}

bool gameOver(){
	for (uint8_t i = 0; i < 3; i++)
		for (uint8_t j = 0; j < 3; j++)
			if (board[i][j] == '#') return false;
	std::cout << "tie\n";
	return true;
}

bool checkWin(){
	char win='n';
	
	for (uint8_t i = 0; i < 3; i++) {
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != '#')
			if (board[i][0] == 'x') win = 'x'; else win = 'o';
	}

	for (uint8_t j = 0; j < 3; j++) {
		if (board[0][j] == board[1][j] && board[0][j] == board[2][j] && board[0][j] != '#')
			if (board[0][j] == 'x') win = 'x'; else win = 'o';
	}

	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != '#')
		if (board[0][0] == 'x') win = 'x'; else win = 'o';
	if (board[2][0] == board[1][1] && board[2][0] == board[0][2] && board[2][0] != '#')
		if (board[2][0] == 'x') win = 'x'; else win = 'o';

	if (win == 'x') {
		std::cout << "x wins\n";
		return true;
	}
	if (win == 'o') {
		std::cout << "o wins\n";
		return true;
	}

	return false;
}

void printBoard(){
	system("CLS");
	for (uint8_t i = 0; i < 3; i++) {
		for (uint8_t j = 0; j < 3; j++)
			std::cout << board[i][j] << " ";
		std::cout << '\n';
	}
	std::cout << '\n';
}

void printError(std::string err){
	printBoard();
	std::cout << err << '\n';
}

bool placePiece(uint8_t x, uint8_t y){
	if (board[x][y] == '#')
		if (piece)
			board[x][y] = 'o';
		else
			board[x][y] = 'x';
	else {
		printError("Piece already in place");
		return false;
	}
	return true;
}

void nextTurn(bool next){
	if (next)
		if (piece)
			piece = 0;
		else
			piece = 1;
	if (piece)
		std::cout << "o's turn-";
	else
		std::cout << "x's turn-";
}

uint8_t convertInput(uint8_t UnconvertedInput){
	uint8_t finalInput;
	
	switch(UnconvertedInput){
		case(1): finalInput = 11; break;
		case(2): finalInput = 12; break;
		case(3): finalInput = 13; break;
		case(4): finalInput = 21; break;
		case(5): finalInput = 22; break;
		case(6): finalInput = 23; break;
		case(7): finalInput = 31; break;
		case(8): finalInput = 32; break;
		case(9): finalInput = 33; break;
		default: finalInput = UnconvertedInput; break;
	}
	return finalInput;
}

int main(){

	initializeBoard();

	short input = 11;

	while(true){

		printBoard();

		if (checkWin() || gameOver()) break;

		nextTurn(1);

		while (true) {

			std::cin >> input;

			input = convertInput(input);

			if (input % 10 <= 3 && input / 10 <= 3 && input > 10) {
				if (placePiece(input / 10 - 1, input % 10 - 1))
					break;
				else {
					nextTurn(0);
					continue;
				}
			} else {
				printError("Incorrect value (should be: RowColumn OR 1 to 9)");
				nextTurn(0);
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}