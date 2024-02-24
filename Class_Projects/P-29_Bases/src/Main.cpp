#include <iostream>
#include <string>
#include <bitset>

int main()
{
	int64_t hmm = 0;
	std::string input = "017";

	std::cin >> input;

	if (input[0] == '0') {
		if (input[1] == 'b') {
			for (size_t i = 2; i < input.size(); i++) {
				hmm *= 2;
				hmm += input[i] - '0';
			}
		} else 
			if (input[1] == 'x') {
				for (size_t i = 2; i < input.size(); i++) {
					char c = input[i];
					if (c >= 'A' && c <= 'Z')
						c -= 'Z' - 'z';
					hmm *= 16;
					hmm += c - (c >= 'a' ? 'a' - 10 : '0');
				}
			} else {
				for (size_t i = 1; i < input.size(); i++) {
					hmm *= 8;
					hmm += input[i] - '0';
				}
			}
	}
	else
		for (size_t i = 0; i < input.size(); i++) {
			hmm *= 10;
			hmm += input[i] - '0';
		}


	std::cout << "Bin: 0b" << std::bitset<sizeof(hmm) * 8>(hmm) << '\n';
	std::cout << "Oct: 0" << std::oct << hmm << std::oct << '\n';
	std::cout << "Dec: " << std::dec << hmm << std::dec << '\n';
	std::cout << "Hex: 0x" << std::hex << hmm << std::hex << '\n';
}