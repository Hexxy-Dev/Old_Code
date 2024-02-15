#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include <vector>
#include <set>

#include <algorithm>
#include <string>

#include <unordered_map>

#include <stdio.h>
#include <stdlib.h>

const std::string CommonCodePath = "./src/";

std::string ReadFile(const std::string& FilePath)
{
	FILE* f = fopen(FilePath.c_str(), "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* string = (char*)malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);
	string[fsize] = '\0';
	return string;
}

std::vector<std::string> SyntaxSeparator(std::string& RawText)
{
	const std::string const delims{ " ;+-=*/%(){}[]\"'" };
	const std::string const ignoredDelims{ " ;\"" };

	std::vector<std::string> words;

	RawText.erase(std::unique(RawText.begin(), RawText.end(), [](char lhs, char rhs)
		{ return (lhs == rhs) && (lhs == ' '); }), RawText.end());
	RawText.erase(std::remove(RawText.begin(), RawText.end(), '\t'), RawText.end());
	RawText.erase(std::remove(RawText.begin(), RawText.end(), '\r'), RawText.end());
	RawText.erase(std::remove(RawText.begin(), RawText.end(), '\n'), RawText.end());

	size_t prev = 0, pos = 0;
	while ((pos = RawText.find_first_of(delims, prev)) != std::string::npos)
	{
		if (pos > prev)
			words.push_back(RawText.substr(prev, pos - prev));
		if(ignoredDelims.find(RawText[pos]) == std::string::npos)
			words.push_back(RawText.substr(pos, 1));
		prev = pos + 1;
	}
	if (prev < RawText.length())
		words.push_back(RawText.substr(prev, std::string::npos));

	return words;
}

void Preprocessor(std::vector<std::string>& Words)
{
	for (size_t i = 0; i < Words.size(); i++) {
		if (Words[i] == "#include") {
			std::string NewFile = ReadFile(CommonCodePath + Words[i + 1]);
			std::vector<std::string> words = SyntaxSeparator(NewFile);
			Words.erase(Words.begin() + i, Words.begin() + i + 2);
			Words.reserve(words.size());
			Words.insert(Words.begin() + i, words.begin(), words.end());
			i--;
		}
	}
}

struct Token
{
	int type;
};

struct NameToken : public Token
{
	std::string name;
};

std::unordered_map<std::string, int> keywords{
	std::make_pair("int", 1),
};

void Tokenizer(std::vector<std::string>& Words)
{

}

int main()
{
	std::string RawText = ReadFile(CommonCodePath + "main");
	std::vector<std::string> words = SyntaxSeparator(RawText);
	Preprocessor(words);
	Tokenizer(words);
	for (auto& word : words)
		std::cout << word << '\n';
}