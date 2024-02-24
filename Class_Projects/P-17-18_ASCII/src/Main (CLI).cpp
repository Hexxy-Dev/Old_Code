#include <iostream>
#include <fstream>
#include <string>

void Encrypt(std::string text)
{
	for (size_t i = 0; i < text.size(); i++)
		printf("%d ", (int)text[i]);
	printf("\n\0");
}

void Decrypt(std::string text)
{
	char c;
	for (size_t i = 0; i < text.size(); i++) {
		c = 0;
		while (text[i] != ' ' && i < text.size()) {
			c *= 10;
			c += text[i] - '0';
			i++;
		}
		printf("%c", c);
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		puts("Usage:"
				"\n\tReq: action       -e  -> encrypt"
				"\n\t                  -d  -> decrypt"
				"\n\tReq: input type   -c  -> stdin"
				"\n\t                  -f  -> file"
				"\n\tReq: filename     when using -f");
		return -1;
	}

	std::string input = "";

	switch (argv[2][1]) {
		case 'c': {
					std::getline(std::cin, input);
				} break;
		case 'f': {
					std::fstream fin;
					fin.open(argv[3]);
					if (fin.fail()) {
						puts("Cannot open file");
						return -4;
					}
					input.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
					fin.close();
				} break;
		default: puts("Invalid input type"); return -3;
	}

	switch (argv[1][1]) {
		case 'e': Encrypt(input); break;
		case 'd': Decrypt(input); break;
		default: puts("Invalid action"); return -2;
	}
}