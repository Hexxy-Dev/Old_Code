#include <iostream>

#include "ChromeProfiler.h"

// 1 2 3      7 4 1
// 4 5 6   -> 8 5 2
// 7 8 9      9 6 3
//
// k = n - 1 - j
// y = n - 1 - i
// ij ki yk jy
// 00 20 22 02
// 01 10 21 12
// 11 11 11 11

inline void rotateR90(int*& arr, const int& n)
{
	for (int i = 0; i < (n >> 1); i++)
	{
		for (int j = i; j < n - 1 - i; j++)
		{
			int temp = arr[i * n + j];
			arr[i * n + j] = arr[(n - 1 - j) * n + i];
			arr[(n - 1 - j) * n + i] = arr[(n - 1 - i) * n + n - 1 - j];
			arr[(n - 1 - i) * n + n - 1 - j] = arr[j * n + n - 1 - i];
			arr[j * n + n - 1 - i] = temp;
		}
	}
}

int main()
{
	Instrumentor::Instance().beginSession("Profile");

	const int iterations = 100000;
	const int n = 100;
	/*
	int arr[n][n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arr[i][j] = i * n + j;
		}
	}

	for (int i = 0; i < (n >> 1); i++)
	{
		for (int j = i; j < n - 1 - i; j++)
		{
			int k = n - 1 - j;
			int y = n - 1 - i;
			int temp = arr[i][j];
			arr[i][j] = arr[k][i];
			arr[k][i] = arr[y][k];
			arr[y][k] = arr[j][y];
			arr[j][y] = temp;
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << arr[i][j] << ((arr[i][j] < 10)?"  ":" ");
		}
		std::cout << '\n';
	}//*/

	int* arr = new int[n * n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arr[i * n + j] = i * n + j;
		}
	}

	/*
	for (int i = 0; i < (n >> 1); i++)
	{
		for (int j = i; j < n - 1 - i; j++)
		{
			int k = n - 1 - j;
			int y = n - 1 - i;
			int temp = arr[i * n + j];
			arr[i * n + j] = arr[k * n + i];
			arr[k * n + i] = arr[y * n + k];
			arr[y * n + k] = arr[j * n + y];
			arr[j * n + y] = temp;
		}
	}//*/

	{
		PROFILE_SCOPE("V1");
		for (int z = 0; z < iterations; z++)
		{
			for (int i = 0; i < (n >> 1); i++)
			{
				for (int j = i; j < n - 1 - i; j++)
				{
					int temp = arr[i * n + j];
					arr[i * n + j] = arr[(n - 1 - j) * n + i];
					arr[(n - 1 - j) * n + i] = arr[(n - 1 - i) * n + n - 1 - j];
					arr[(n - 1 - i) * n + n - 1 - j] = arr[j * n + n - 1 - i];
					arr[j * n + n - 1 - i] = temp;
				}
			}
		}
	}
	
	{
		PROFILE_SCOPE("V2");
		for (int z = 0; z < iterations; z++)
		{
			rotateR90(arr, n);
		}
	}

	Instrumentor::Instance().endSession();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << arr[i * n + j] << ((arr[i * n + j] < 10) ? "  " : " ");
		}
		std::cout << '\n';
	}

	delete arr;
}