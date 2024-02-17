#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#include<set>

std::vector<char*> sortText(char text[]) {
	std::vector<char*> words;
	char* word = strtok(text, " ");
	words.push_back(word);
	while (word = strtok(NULL, " "))
		words.push_back(word);
	std::sort(words.begin(), words.end(), [](const char* a, const char* b)
		{ return (strcmp(a, b) == -1) ? 1 : 0; });
	return words;
}

int main()
{
	char text[251] = "";// REDACTED

	std::vector<char*> words = sortText(text);
	
	for (auto& word : words)
		std::cout << word << ' ';

	return 0;
}
