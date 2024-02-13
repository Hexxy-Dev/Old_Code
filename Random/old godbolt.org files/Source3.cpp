#include <iostream>





const size_t width = 5;
const size_t height = 5;
uint8_t grid[height][width] = {
		{1,1,1,0,0},
		{1,1,0,0,1},
		{0,0,1,0,0},
		{1,0,1,0,1},
		{1,0,0,0,1}
};

void Populate()
{

}

void Display()
{
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++)
			printf("%d ", grid[i][j]);
		putchar('\n');
	}
}

uint8_t Clean(size_t i, size_t j)
{

}

int main()
{
	Populate();
	Display();
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++)
			Clean(i,j);
	Display();
}