#include "Huffman.h"
#include "Utility.h"


void Decrypt()
{
	std::string input;
	std::ifstream fin;
	fin.open("OUT.txt", std::ios::binary);
	if (fin.fail()) {
		puts("Cannot open file");
		return;
	}
	input.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
	fin.close();


	std::vector<bool> binaryData;
	binaryData.reserve(input.size() * 8);

	for (char c : input)
		for (char i = 0; i < 8; i++)
			binaryData.emplace_back(c & (0b10000000 >> i));

	//{
	//	std::string s;
	//	for (auto b : binaryData)
	//		s += b + '0';
	//	puts(s.c_str());
	//}

	uint8_t PADDING = 0;
	for (int i = 0; i < 8; i++) {
		PADDING <<= 1;
		PADDING |= binaryData[i];
	}

	while (!binaryData[binaryData.size() - 1])
		binaryData.pop_back();
	binaryData.resize(binaryData.size() - PADDING);

	std::unordered_map<std::string, char> dictionary;

	std::vector<bool> entry;
	uint8_t paddingFound = 0;
	uint8_t terminators = 0;
	size_t i;
	for (i = 8; i < binaryData.size(); i++) {
		if (!binaryData[i]) {
			paddingFound = 0;
		}
		paddingFound += binaryData[i];

		if (paddingFound == PADDING - 1) {
			size_t k;
			for (k = entry.size() - 1; k >= 0; k--)
				if (entry[k] == 0)
					break;
			if (k == 0) {
				terminators++;
				entry.clear();
				continue;
			}

			k--;
			char c = 0;
			for (int j = 7; j >= 0; j--) {
				c <<= 1;
				c |= entry[k - j];
			}
			k -= 7;


			//{
			//	std::string code;
			//	for (int j = 0; j < k; j++)
			//		code += entry[j] + '0';
			//	std::cout << c << ' ' << code << '\n';
			//}

			std::string code;
			for (int j = 0; j < k; j++)
				code += entry[j];
			dictionary[code] = c;

			entry.clear();
			continue;
		}

		if (terminators == END_PADDING)
			break;

		entry.push_back(binaryData[i]);
	}

	std::string code = "";
	std::string output = "";

	for (; i < binaryData.size(); i++) {
		code += binaryData[i];

		if (dictionary.find(code) != dictionary.end()) {
			if (dictionary[code] != '\r')
				output += dictionary[code];
			code = "";
			entry.clear();
		}
	}
	//puts(output.c_str());
	std::ofstream fout;
	fout.open("OUTPUT.txt");
	fout << output;
	fout.close();
}

int main()
{
	Decrypt();
}