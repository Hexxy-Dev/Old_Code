#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
	if (argc < 2) {
		puts("Usage:"
			"\n\tReq: input type   -c  -> stdin"
			"\n\t                  -f  -> file"
			"\n\tReq: filename     when using -f");
		return -1;
	}

	std::string input = "";
	std::unordered_map<std::string, size_t> words;

	switch (argv[1][1]) {
		case 'c': {
			std::getline(std::cin, input);
			std::string delimiter = " ";
			size_t pos = 0;
			while ((pos = input.find(delimiter)) != std::string::npos) {
				words[input.substr(0, pos)]++;
				input.erase(0, pos + delimiter.length());
			}
		} break;
		case 'f': {
			std::fstream fin;
			fin.open(argv[2]);
			if (fin.fail()) {
				puts("Cannot open file");
				return -2;
			}
			std::string word;
			while (fin >> word) words[word]++;
			fin.close();
		} break;
		default: puts("Invalid input type"); return -3;
	}

	
	std::vector<std::pair<std::string, size_t>> words_common(words.begin(), words.end());
	std::sort(words_common.begin(), words_common.end(),
		[](const std::pair<std::string, size_t>& l,
		const std::pair<std::string, size_t>& r)
		{ return l.second > r.second; });

	puts("Enter X:");
	size_t x;
	std::cin >> x;
	if (x > words_common.size()) {
		puts("Index does not exist!");
		return -4;
	}
	printf("X most common word: %s (%d)", words_common[x - 1].first.c_str(), words_common[x - 1].second);

}