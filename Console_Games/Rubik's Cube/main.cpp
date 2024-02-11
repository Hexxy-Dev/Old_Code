#include <iostream>
#include <fstream>

#include "Console stuff.h"

using std::cout;

//0 is empty      0
//1 is white      down
//2 is blue       front
//3 is yellow     up
//4 is magenta    left
//5 is red        right
//6 is green      back

const int cube_size = 3;

const std::string colors[7] = {
	"   ",
	//"\33[40m   ",						// black
	"\33[107m  \33[40m ",               // white
	"\33[104m  \33[40m ",               // blue
	"\33[103m  \33[40m ",               // yellow
	"\33[105m  \33[40m ",               // magenta
	"\33[101m  \33[40m ",               // red
	"\33[102m  \33[40m "                // green
};

char cube[(cube_size * 3)][(cube_size * 4)];

char preset[3][4] = {
	{0,3,0,0},
	{4,2,5,6},
	{0,1,0,0}
};

void Populate_cube()
{
	for (int i = 0; i < cube_size * 3; i++)
	{
		for (int j = 0; j < cube_size * 4; j++)
		{
			cube[i][j] = preset[i / cube_size][j / cube_size];
		}
	}
}
void Display_unfolded_cube()
{
	system("CLS");

	std::string output = ".\n";

	for (int i = 0; i < cube_size * 3; i++)
	{
		for (int j = 0; j < cube_size * 4; j++)
		{
			output += colors[cube[i][j]];
		}
		output += "\n\n";
	}

	std::cout << output;
}

void Rotate_arr_right(int i_offset = cube_size - 1, int j_offset = cube_size - 1, int size_offset = 2)
{
	char* new_face = new char[(cube_size + size_offset) * (cube_size + size_offset)];

	for (int i = 0; i < cube_size + size_offset; i++)
		for (int j = 0; j < cube_size + size_offset; j++)
			new_face[(cube_size + size_offset) * j + i] = cube[cube_size + size_offset - 1 - i + i_offset][j + j_offset];

	for (int i = 0; i < cube_size + size_offset; i++)
		for (int j = 0; j < cube_size + size_offset; j++)
			cube[i + i_offset][j + j_offset] = new_face[(cube_size + size_offset) * i + j];

	delete[] new_face;
}
void Rotate_arr_left(int i_offset = cube_size - 1, int j_offset = cube_size - 1, int size_offset = 2)
{
	char * new_face = new char [(cube_size + size_offset) * (cube_size + size_offset)];

	for (int i = 0; i < cube_size + size_offset; i++)
		for (int j = 0; j < cube_size + size_offset; j++)
			new_face[(cube_size + size_offset) * j + i] = cube[i + i_offset][cube_size + size_offset - 1 - j + j_offset];

	for (int i = 0; i < cube_size + size_offset; i++)
		for (int j = 0; j < cube_size + size_offset; j++)
			cube[i + i_offset][j + j_offset] = new_face[(cube_size + size_offset) * i + j];

	delete[] new_face;
}

void Rotate_cube_faces_clockwise()
{
	char buffer[cube_size][cube_size];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			buffer[i][j] = cube[cube_size + i][j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + i][j] = cube[cube_size + i][cube_size + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + i][cube_size + j] = cube[cube_size + i][cube_size * 2 + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + i][cube_size * 2 + j] = cube[cube_size + i][cube_size * 3 + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + i][cube_size * 3 + j] = buffer[i][j];
}
void Rotate_cube_faces_counter_clockwise()
{
	char buffer[cube_size][cube_size];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			buffer[i][j] = cube[cube_size + i][cube_size * 3 + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + i][cube_size * 3 + j] = cube[cube_size + i][cube_size * 2 + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + i][cube_size * 2 + j] = cube[cube_size + i][cube_size + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + i][cube_size + j] = cube[cube_size + i][j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + i][j] = buffer[i][j];
}
void Rotate_cube_faces_forward()
{
	char buffer[cube_size][cube_size];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			buffer[i][j] = cube[cube_size + cube_size - 1 - i][cube_size * 3 + cube_size - 1 - j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + cube_size - 1 - i][cube_size * 3 + cube_size - 1 - j] = cube[cube_size * 2 + i][cube_size + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size * 2 + i][cube_size + j] = cube[cube_size + i][cube_size + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + i][cube_size + j] = cube[i][cube_size + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[i][cube_size + j] = buffer[i][j];
}
void Rotate_cube_faces_back()
{
	char buffer[cube_size][cube_size];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			buffer[i][j] = cube[i][cube_size + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[i][cube_size + j] = cube[cube_size + i][cube_size + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + i][cube_size + j] = cube[cube_size * 2 + i][cube_size + j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size * 2 + i][cube_size + j] = cube[cube_size + cube_size - 1 - i][cube_size * 3 + cube_size - 1 - j];

	for (int i = 0; i < cube_size; i++)
		for (int j = 0; j < cube_size; j++)
			cube[cube_size + cube_size - 1 - i][cube_size * 3 + cube_size - 1 - j] = buffer[i][j];
}

void Rotate_cube_clockwise()
{
	Rotate_arr_right(0, cube_size, 0);
	Rotate_arr_left(cube_size * 2, cube_size, 0);
	Rotate_cube_faces_clockwise();
}
void Rotate_cube_counter_clockwise()
{
	Rotate_arr_right(cube_size * 2, cube_size, 0);
	Rotate_arr_left(0, cube_size, 0);
	Rotate_cube_faces_counter_clockwise();
}
void Rotate_cube_forward()
{
	Rotate_arr_right(cube_size, 0, 0);
	Rotate_arr_left(cube_size, cube_size * 2, 0);
	Rotate_cube_faces_forward();
}
void Rotate_cube_back()
{
	Rotate_arr_right(cube_size, cube_size * 2, 0);
	Rotate_arr_left(cube_size, 0, 0);
	Rotate_cube_faces_back();
}

void R_move(int rows = 1)
{
	Rotate_cube_clockwise();
	Rotate_arr_right(cube_size - rows, cube_size - rows, rows * 2);
	Rotate_cube_counter_clockwise();
}
void Ri_move(int rows = 1)
{
	Rotate_cube_clockwise();
	Rotate_arr_left(cube_size - rows, cube_size - rows, rows * 2);
	Rotate_cube_counter_clockwise();
}

void L_move(int rows = 1)
{
	Rotate_cube_counter_clockwise();
	Rotate_arr_right(cube_size - rows, cube_size - rows, rows * 2);
	Rotate_cube_clockwise();
}
void Li_move(int rows = 1)
{
	Rotate_cube_counter_clockwise();
	Rotate_arr_left(cube_size - rows, cube_size - rows, rows * 2);
	Rotate_cube_clockwise();
}

void B_move(int rows = 1)
{
	Rotate_cube_forward();
	Rotate_cube_forward();
	Rotate_arr_right(cube_size - rows, cube_size - rows, rows * 2);
	Rotate_cube_back();
	Rotate_cube_back();
}
void Bi_move(int rows = 1)
{
	Rotate_cube_forward();
	Rotate_cube_forward();
	Rotate_arr_left(cube_size - rows, cube_size - rows, rows * 2);
	Rotate_cube_back();
	Rotate_cube_back();
}

void D_move(int rows = 1)
{
	Rotate_cube_back();
	Rotate_arr_right(cube_size - rows, cube_size - rows, rows * 2);
	Rotate_cube_forward();
}
void Di_move(int rows = 1)
{
	Rotate_cube_back();
	Rotate_arr_left(cube_size - rows, cube_size - rows, rows * 2);
	Rotate_cube_forward();
}

void F_move(int rows = 1)
{
	Rotate_arr_right(cube_size - rows, cube_size - rows, rows * 2);
}
void Fi_move(int rows = 1)
{
	Rotate_arr_left(cube_size - rows, cube_size - rows, rows * 2);
}

void U_move(int rows = 1)
{
	Rotate_cube_forward();
	Rotate_arr_right(cube_size - rows, cube_size - rows, rows * 2);
	Rotate_cube_back();
}
void Ui_move(int rows = 1)
{
	Rotate_cube_forward();
	Rotate_arr_left(cube_size - rows, cube_size - rows, rows * 2);
	Rotate_cube_back();
}

void Display_from_file()
{
	std::ifstream fin("Input.in");

	bool i = false;
	char char_array[3];
	std::string move;
	int times;

	while (fin >> move)
	{
		times = 1;
		i = false;

		char_array[0] = move[0];
		char_array[1] = move[1];

		if (char_array[1] == '\'' || char_array[1] == 'i' || char_array[1] == 'p')
			i = true;

		if (isdigit(char_array[1]))
			times = char_array[1] - '0';

		while (times > 0)
		{
			switch (char_array[0])
			{
			case 'R':
				if (!i)
					R_move();
				else
					Ri_move();
				break;
			case 'L':
				if (!i)
					L_move();
				else
					Li_move();
				break;
			case 'B':
				if (!i)
					B_move();
				else
					Bi_move();
				break;
			case 'D':
				if (!i)
					D_move();
				else
					Di_move();
				break;
			case 'F':
				if (!i)
					F_move();
				else
					Fi_move();
				break;
			case 'U':
				if (!i)
					U_move();
				else
					Ui_move();
				break;
			default:
				cout << "unknown move : " << char_array[0] << char_array[1];
				break;
			}
			Display_unfolded_cube();
			temp_sleep(200);

			times--;
		}
	}
}

int main()
{
	console_setup();
	Populate_cube();
	Display_unfolded_cube();

	Display_from_file();
}