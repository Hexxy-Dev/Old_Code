#include <iostream>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

void CreateArrayBorder(const uint8_t& n, uint32_t* arr)
{
	for (uint8_t i = 0; i < n; i++)
		arr[i * n] = i + 2;

	for (uint8_t i = 0; i < n; i++)
		arr[i * n + n - 1] = i + 1 + n;

	for (uint8_t j = 1; j < n - 1; j++)
		arr[j] = j + 2;

	for (uint8_t j = 1; j < n - 1; j++)
		arr[(n - 1) * n + j] = j + 1 + n;
}

void FillArray(const uint8_t& n, uint32_t* arr)
{
	// fill using the given rule:
	// |  y=...+a+b |  a     |
	// |  x=a+b+c   |  b     |
	// |  z=b+c+... |  c     |
	for (uint8_t j = n - 2; j != 0; j--)
		for (uint8_t i = 1; i < n - 1; i++)
			arr[i * n + j] = arr[(i - 1) * n + j + 1] + arr[i * n + j + 1] + arr[(i + 1) * n + j + 1];
}

void DisplayArray(const uint8_t& n, const uint32_t* arr)
{
	uint64_t max = arr[(n / 2 + n % 2) * n + 1], copy;
	uint8_t spaces = 1, lenght;

	for (uint8_t i = 0; i < n; i++)
	{
		for (uint8_t j = 0; j < n; j++)
		{
			copy = arr[i * n + j];
			lenght = 0;

			spaces = 1;

			max = arr[(n / 2 + (j ? n % 2 : n / 2 - 1) + (j == n - 2) * (n / 2 - 2)) * n + j]; // approximate max len value
			for (; max; max /= 10, spaces++) {}

			std::cout << copy;
			
			for (; copy; copy /= 10, lenght++) {}

			for (uint8_t k = 0; k < spaces - lenght; k++)
				std::cout << " ";
		}

		std::cout << std::endl;
	}
}

int main()
{
	uint8_t n;
	n = 20;

	uint32_t* arr = new uint32_t[n * n];

	CreateArrayBorder(n, arr);

	FillArray(n, arr);

	DisplayArray(n, arr);

	delete[] arr;
}