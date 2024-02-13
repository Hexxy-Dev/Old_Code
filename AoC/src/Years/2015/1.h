#pragma once

START

	void Part1(std::string& input)
	{
		int result = 0;
		for (size_t i = 0; i < input.size(); i++)
			result += (input[i] - '(') ? -1 : 1;
		std::cout << result;
	}

	void Part2(std::string& input)
	{
		int result = 0;
		size_t i;
		for (i = 0; i < input.size() && result >= 0; i++)
			result += (input[i] - '(') ? -1 : 1;
		std::cout << i;
	}

END