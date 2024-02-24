#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

void MeasureAverageExecutionTime(size_t func(size_t), size_t func_argument, size_t runs)
{
	size_t accumulator = 0;
	for (size_t i = 0; i < runs; i++) {
		auto start = std::chrono::high_resolution_clock::now();
		size_t result = func(func_argument);
		auto end = std::chrono::high_resolution_clock::now();
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		printf("Run %u: Function Took: %u ms\tResult: %u\n", i, ms.count(), result);
		accumulator += ms.count();
	}
	printf("Average Execution Time: %u ms\n", accumulator / runs);
}

size_t GetPrimesCount_UnOptimised(size_t n)
{
	std::vector<bool> primes(n);
	primes[0] = primes[1] = true;
	for (size_t i = 2; i < n; i++)
		if (!primes[i])
			for (size_t j = i + i; j < n; j += i)
				primes[j] = true;
	return std::count(primes.begin(), primes.end(), false);
}

size_t GetPrimesCount_O1(size_t n) // till sqrt
{
	std::vector<bool> primes(n);
	primes[0] = primes[1] = true;
	for (size_t i = 2; i * i < n; i++)
		if (!primes[i])
			for (size_t j = i * i; j < n; j += i)
				primes[j] = true;
	return std::count(primes.begin(), primes.end(), false);
}

size_t GetPrimesCount_O2(size_t n) // only odd
{
	size_t sqrt_n = sqrt(n) + 1;
	size_t size = n / 2;
	std::vector<bool> primes(size);
	for (size_t i = 3; i < sqrt_n; i += 2)
		if (!primes[i / 2])
			for (size_t j = (i * i) / 2; j < size; j += i)
				primes[j] = true;
	return std::count(primes.begin(), primes.end(), false);
}

// further optimisations: segmented sieve, multithreaded sieve

int main()
{
	puts("Un optimised Sieve: 100 M");
	MeasureAverageExecutionTime(GetPrimesCount_UnOptimised, 100000000, 3);
	puts("O1 Sieve:  100 M");
	MeasureAverageExecutionTime(GetPrimesCount_O1, 100000000, 3);
	puts("O2 Sieve:  100 M");
	MeasureAverageExecutionTime(GetPrimesCount_O2, 100000000, 3);
	puts("O2 Sieve:  1 B");
	MeasureAverageExecutionTime(GetPrimesCount_O2, 1000000000, 3);
}