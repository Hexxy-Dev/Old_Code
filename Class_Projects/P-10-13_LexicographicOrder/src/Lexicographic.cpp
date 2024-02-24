#include <iostream>
#include <string>

void PrintLexicographicOrder(std::string str, size_t n, size_t k, size_t prev = 1)
{
	if (k == 0) {
		puts(str.c_str());
		return;
	}

	for (size_t i = prev; i <= n; i++) {
		std::string next = str;
		next += std::to_string(i);
		next += ' ';
		PrintLexicographicOrder(next, n, k - 1, i + 1);
	}
}

int main()
{
	size_t n, k;
	puts("N =");
	std::cin >> n;
	puts("K =");
	std::cin >> k;
	PrintLexicographicOrder("", n, k);
}