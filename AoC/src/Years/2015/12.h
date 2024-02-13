#pragma once

START

	void Part1(std::string& input)
	{
		int64_t result = 0;
		int64_t nr = 0;
		char sign = 1;
		for (size_t i = 0; i < input.size(); i++) {
			nr = 0;
			sign = 1;
			while (input[i] >= '0' && input[i] <= '9') {
				if (input[i - 1] == '-')
					sign = -1;
				nr *= 10;
				nr += input[i] - '0';
				i++;
			}
			result += nr * sign;
		}
		
		std::cout << result;
	}

	void Part2(std::string& input)
	{
		std::string pattern = "\"red\"";
		while (input.find(pattern) != std::string::npos) {
			size_t i = input.find(pattern);
			size_t left = 0;
			size_t right = 0;
			size_t lleft = 0;
			size_t rright = 0;

			size_t counter = 1;
			size_t counter2 = 1;
			for (size_t j = i; j > 0; j--) {
				if (input[j - 1] == '}')
					counter++;
				if (input[j - 1] == '{')
					counter--;
				if (input[j - 1] == '{' && counter == 0) {
					left = j - 1;
					break;
				}
				if (input[j - 1] == ']')
					counter2++;
				if (input[j - 1] == '[')
					counter2--;
				if (input[j - 1] == '[' && lleft == 0 && counter2 == 0)
					lleft = j;
			}
				
			counter = 1;
			counter2 = 1;
			for (size_t j = i; j < input.size(); j++) {
				if (input[j] == '{')
					counter++;
				if (input[j] == '}')
					counter--;
				if (input[j] == '}' && counter == 0) {
					right = j;
					break;
				}
				if (input[j] == '[')
					counter2++;
				if (input[j] == ']')
					counter2--;
				if (input[j] == ']' && rright == 0 && counter2 == 0)
					rright = j;
			}
			if (lleft > left && rright < right) {
				input.erase(input.begin() + i, input.begin() + i + pattern.size());
				continue;
			}
			input.erase(input.begin() + left, input.begin() + right + 1);
		}

		int64_t result = 0;
		int64_t nr = 0;
		char sign = 1;
		for (size_t i = 0; i < input.size(); i++) {
			nr = 0;
			sign = 1;
			while (input[i] >= '0' && input[i] <= '9') {
				if (input[i - 1] == '-')
					sign = -1;
				nr *= 10;
				nr += input[i] - '0';
				i++;
			}
			result += nr * sign;
		}

		std::cout << result;
	}

END