#include <iostream>
#include <bitset>

#define TYPE int

int main()
{
	TYPE x;
	puts("Enter number:");
	std::cin >> x;

	TYPE y = ~x + 1;
	std::cout << "Two's complement:\n\t" << std::bitset<sizeof(TYPE) * 8>(y)
		<< ' ' << y << '\n';
}