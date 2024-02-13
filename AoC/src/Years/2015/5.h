#pragma once

START
	
	bool isVowel(char c)
	{
		const char vowels[] = "aeiou";
		for (char i = 0; i < sizeof(vowels); i++)
			if (c == vowels[i])
				return true;
		return false;
	}

	bool isDissalowed(char a, char b)
	{
		const char dissalowed[4][2] = { {'a','b'},{'c','d'},{'p','q'},{'x','y'} };
		for (char i = 0; i < sizeof(dissalowed); i++)
			if (a == dissalowed[i][0] && b == dissalowed[i][1])
				return true;
		return false;
	}

	bool isNice(const std::string& str)
	{
		char last = str[0];
		uint8_t vc = isVowel(last);
		uint8_t twice = false;
		for (size_t i = 1; i < str.size(); i++) {
			vc += isVowel(str[i]);
			if (isDissalowed(last, str[i]))
				return false;
			if(last == str[i])
				twice = true;
			last = str[i];
		}
		if (twice && vc >= 3)
			return true;
		return false;
	}

	std::string Next(const std::string& str, size_t& index)
	{
		std::string next = "";
		if (str[index] == '\n')
			index++;
		while (str[index] != '\n' && str[index] != '\0') {
			next += str[index];
			index++;
		}
		return next;
	}

	void Part1(std::string& input)
	{
		size_t result = 0;
		for (size_t i = 0; i < input.size(); i++)
			result += isNice(Next(input, i));
		std::cout << result;
	}



	bool isNiceP2(const std::string& str)
	{
		//uint8_t flags = 0b00;
		//for (size_t k = 2; k < str.size(); k++)
		//	if (str[0] == str[k] && str[1] == str[k + 1])
		//		flags |= 0b10;
		//for (size_t i = 2; i < str.size(); i++) {
		//	if (str[i - 2] == str[i])
		//		flags |= 0b01;
		//	for (size_t k = i + 2; k < str.size() && (flags & 0b10) != 0b10; k++)
		//		if (str[i - 1] == str[k] && str[i] == str[k + 1])
		//			flags |= 0b10;
		//	if (flags == 0b11)
		//		return true;
		//}
		//return false; // ^^^ THIS HAS SOME BUG

		std::regex regex("(?=.*(.).\\1)(?=.*(..)(.*)\\2)");
		return std::regex_search(str, regex);
	}

	void Part2(std::string& input)
	{
		size_t result = 0;
		for (size_t i = 0; i < input.size(); i++)
			result += isNiceP2(Next(input, i));
		std::cout << result;
	}

END