#pragma once

START

	void Part1(std::string& input)
	{
		size_t count = 0;
		for (size_t i = 0; i < input.size(); i++) {
			//\x32a
			char tmp = input[i];
			if (tmp == '\\') {
				char tmp2 = input[++i];
				if (tmp2 == 'x')
					i += 2;
			}
			if (tmp == '"')
				continue;
			count++;
		}

		size_t result = 0;
		result = input.size() - count;
		std::cout << result;
	}

	void Part2(std::string& input)
	{
		size_t count = 0;
		int escaped = 0;
		long long count2 = 0;
		for (size_t i = 0; i < input.size(); i++) {
			if (input[i] == '\\') {
				count++;
				escaped = 2;
			}
			if (input[i] == '\"') {
				if (escaped > 0) {
					escaped = 0;
					count2--;
				}
				count++;
				count2++;
			}
			count++;
			escaped--;
			//" \" "
			//" \" \\ " \" "
		}
		size_t result = 0;
		result = (count + count2) - input.size(); //should be 2046 but I get 2039
		std::cout << result;
	}

END