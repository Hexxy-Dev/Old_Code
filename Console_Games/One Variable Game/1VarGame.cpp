#include <iostream>
#include <bitset>
#include <future>
#include <Windows.h>

uint64_t GAME = 0b0001000000000000000000000000000000000000000000000000000000000000;

void Stop()
{
	std::cin.get();
	GAME |= 0b0100000000000000000000000000000000000000000000000000000000000000;
}

bool PrintAndLogic()
{
	std::cout << ".\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t     Win\n\t\t\t\t\t\t\t\t\t\t\t---------------------------|     |---------------------------\n\t\t\t\t\t\t\t\t\t\t\t";
	std::cout << std::bitset<8 * 8 - 3>(GAME) << "\n\t\t\t\t\t\t\t\t\t\t\t---------------------------|     |---------------------------\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	if (GAME & 0b1110000000000000000000000000000000000000000000000000000000000000)
		return 1;

	Sleep(1);
	return 0;
}

int main()
{
	auto fi = std::async(std::launch::async, Stop);

	while (true)
	{
		for (; GAME ^ 0b0000000000000000000000000000000000000000000000000000000000000001; GAME >>= 1)
			if (PrintAndLogic())
				goto END;
		for (; GAME ^ 0b0001000000000000000000000000000000000000000000000000000000000000; GAME <<= 1)
			if (PrintAndLogic())
				goto END;
	}
END://              ---------------------------|     |---------------------------
	if (GAME & 0b0001000000000000000000000000000111110000000000000000000000000000)
		std::cout << ".\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t     YOU WIN!!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	else
		std::cout << ".\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t     YOU LOST\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	std::cin.get();
}