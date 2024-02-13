#include <iostream>

bool Valid(int n, int k)
{
	while (n) {
		if (n % 10 == k)
			return true;
		n /= 10;
	}
	return false;
}

void Test(bool a, bool b, bool c, bool d)
{
	printf("ACTUAL: %d\n", (a && b) || (c && d));
	printf("%d ", !((a || b) && (c || d)));
	printf("%d ", !((!a && !b) || (!c && !d)));
	printf("%d ", !((!a || !b) && (!c || !d)));
	//!(!a || !b)
	//a 1 1 0 0
	//b 1 0 1 0
	//a'0 0 1 1
	//b'0 1 0 1
	//()'0 1 1 1
	//R 1 0 0 0
	//(a && b)
	printf("%d ", !(!(a && b) || !(c && d)));
	printf("%d ", !(!(a || b) && !(c || d)));
	//!(a || b)
	//a 1 1 0 0
	//b 1 0 1 0
	//R 0 0 0 1
	printf("%d\n", (!a || !b) && (!c || !d));
}

int main()
{
	size_t c = 0;
	for (size_t i = 1; i < 1000; i++)
		if (Valid(i, 9)) {
			printf("%u ", i);
			c++;
		}
	printf("\n\n%u", c);

	int hmm = -12;
	printf("\n\n%d %d\n\n\n", hmm / 10, hmm % 10);


	size_t mat[20][21];
	for (size_t i = 0; i < 20; i++)
		for (size_t j = 0; j < 21; j++)
			mat[i][j] = std::min(i + 1, j + 1);
	for (size_t i = 0; i < 20; i++)
		mat[i][i] = (i + 1) * (i + 1);

	size_t sum = 0;
	for (size_t i = 0; i < 20; i++)
		for (size_t j = 0; j < 21; j++)
			sum += mat[i][j];
	for (size_t i = 0; i < 20; i++) {
		for (size_t j = 0; j < 21; j++)
			printf("%u%s", mat[i][j],
				(mat[i][j] > 9 ? (mat[i][j] > 99 ? " " : "  ") : "   "));
		puts("");
	}
	printf("\n\n%u", sum);

	Test(0, 0, 0, 0);
	Test(1, 0, 0, 0);
	Test(0, 1, 0, 0);
	Test(0, 0, 1, 0);
	Test(0, 0, 0, 1);
	Test(1, 1, 0, 0);
	Test(1, 0, 1, 0);
	Test(1, 0, 0, 1);
	Test(0, 1, 1, 0);
	Test(0, 1, 0, 1);
	Test(0, 0, 1, 1);
	Test(1, 1, 1, 0);
	Test(1, 1, 0, 1);
	Test(0, 1, 1, 1);
	Test(1, 1, 1, 1);


}