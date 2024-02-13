#pragma once

START

	std::string LookAndSay(std::string input)
	{
		std::string result;
		char count = 0;
		char last = input[0];
		for (size_t i = 0; i < input.size(); i++) {
			if (input[i] == last)
				count++;
			if (input[i] != last) {
				result += std::to_string(count);
				result += last;
				count = 1;
			}
			last = input[i];
		}
		result += count + '0';
		result += last;
		return result;
	}
	
	void Part1(std::string& input)
	{
		std::string result = input;
		//result = "d"; // neat thing is that d will always be the last digit
		for (size_t i = 0; i < 40; i++)
			result = LookAndSay(result);
		std::cout << result.length();
	}

	void Part2(std::string& input)
	{
		std::string result = input;
		for (size_t i = 0; i < 50; i++)
			result = LookAndSay(result);
		std::cout << result.length();
	}

END