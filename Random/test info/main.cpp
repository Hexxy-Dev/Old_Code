#include <iostream>

using namespace std;

void nr1ex1() {
	cout << "Nr1 Ex1:\n";
/*
1 2 3 4 5
2 2 3 4 5
3 3 3 4 5
*/
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			cout << ((i >= j) ? i : j);
			cout << " ";
		}
		cout << endl;
	}
}

void nr1ex2() {
	cout << "Nr1 Ex2:\n";
/*
1 6 11 16
2 7 12 17
3 8 13 18
4 9 14 19
*/
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << i + j * 5 + 1;
			cout << " ";
		}
		cout << endl;
	}
}

void nr1ex3() {
	cout << "Nr1 Ex3:\n";
/*
sa se construiasca o matrice cu n linii si m coloane
-prima coloana contine nr de la 1 la n in ordine crescatoare
-prima linie contine nr de la 1 la m in ordine crescatoare
-restul elementelor se vor initializa ca suma elementelor vecine situate in stanga si deasupra elementului

1 2 3 4 5
2 4 7 11 16
3 7 14 25 41
*/
	int arr[404][404], n, m;

	//cin >> n >> m;
	n = 3;
	m = 5;

	for (int i = 0; i < n; i++)
		arr[i][0] = i + 1;

	for (int j = 1; j < m; j++)
		arr[0][j] = j + 1;

	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++)
			arr[i][j] = arr[i - 1][j] + arr[i][j - 1];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << arr[i][j];
			cout << " ";
		}
		cout << endl;
	}
}

void nr2ex1() {
	cout << "Nr2 Ex1:\n";
/*
5 3 5 3 5
3 5 3 5 3
5 3 5 3 5
*/
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			cout << (((i + j) % 2) ? 3 : 5);
			cout << " ";
		}
		cout << endl;
	}
}

void nr2ex2() {
	cout << "Nr2 Ex2:\n";
/*
1 2 3 4 5
5 6 7 8 9
9 10 11 12 13
13 14 15 16 17
*/
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << i * 4 + j + 1;
			cout << " ";
		}
		cout << endl;
	}
}

void nr2ex3() {
	cout << "Nr2 Ex3:\n";
/*
sa se construiasca o matrice cu n linii si m coloane
care contine sirul primelor n * m patrate perfecte pare ca in exemplul:

196 144 100 64
36 16 4 0
*/
	int arr[404][404], n, m, rppp = 0;

	//cin >> n >> m;
	n = 2;
	m = 4;

	for (int i = n - 1; i >= 0; i--)
		for (int j = m - 1; j >= 0; j--)
		{
			arr[i][j] = rppp * rppp;
			rppp += 2;
		}
			

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << arr[i][j];
			cout << " ";
		}
		cout << endl;
	}
}

int main()
{
	nr1ex1();
	cout << endl << endl;
	nr1ex2();
	cout << endl << endl;
	nr1ex3();
	cout << endl << endl;
	cout << endl << endl;
	nr2ex1();
	cout << endl << endl;
	nr2ex2();
	cout << endl << endl;
	nr2ex3();
	cout << endl << endl;
}

//completion time: 6/4/2021 5:58 PM