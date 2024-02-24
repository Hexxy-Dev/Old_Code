#include <iostream>
#include <vector>

std::vector<std::string> GeneratePermutations(size_t n)
{
	std::vector<std::string> permuations;



	return permuations;
}

size_t factorial(size_t n)
{
	if (!n)
		return 1;
	return factorial(n - 1) * n;
}

size_t GeneratePermutationsNumber(size_t n)
{
	return factorial(2 * n) / (factorial(n + 1) * factorial(n));//Catalan number
}

int main()
{
	size_t n;
	puts("Enter number of pairs:");
	//std::cin >> n;
	n = 3;
	printf("Permutations: %d\n", GeneratePermutationsNumber(n));
	std::vector<std::string> permutations = GeneratePermutations(n);
	for (const auto& permutation : permutations)
		puts(permutation.c_str());
}