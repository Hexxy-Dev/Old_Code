#pragma once

START

	std::string nextWord(const std::string& str, size_t& i)
	{
		std::string r = "";
		while (str[i] == ' ' || str[i] == '\n')
			i++;
		while (str[i] != ' ' && str[i] != '\0') {
			r += str[i];
			i++;
		}
		return r;
	}

	uint16_t nextNumber(const std::string& str, size_t& i)
	{
		uint16_t r = 0;
		while (str[i] < '0' || str[i] > '9' && i < str.size())
			i++;
		while (str[i] >= '0' && str[i] <= '9') {
			r = r * 10 + str[i] - '0';
			i++;
		}
		return r;
	}

	void Part1(std::string& input)
	{
		std::bitset<1000 * 1000>* lights = new std::bitset<1000 * 1000>();
		size_t i = 0;
		while (i < input.size())
		{
			std::string instruction = nextWord(input, i);
			if (instruction == "turn")
				instruction = nextWord(input, i);
			uint16_t x_start = nextNumber(input, i);
			uint16_t y_start = nextNumber(input, i);
			uint16_t x_end = nextNumber(input, i);
			uint16_t y_end = nextNumber(input, i);

			if (instruction == "toggle") {
				for (uint16_t x = x_start; x <= x_end; x++)
					for (uint16_t y = y_start; y <= y_end; y++)
						(*lights)[x * 1000 + y] = !(*lights)[x * 1000 + y];
			}
			else if (instruction == "on") {
				for (uint16_t x = x_start; x <= x_end; x++)
					for (uint16_t y = y_start; y <= y_end; y++)
						(*lights)[x * 1000 + y] = 1;
			} else {
				for (uint16_t x = x_start; x <= x_end; x++)
					for (uint16_t y = y_start; y <= y_end; y++)
						(*lights)[x * 1000 + y] = 0;
			}
		}

		size_t result = 0;
		result = lights->count();
		delete lights;
		std::cout << result;
	}

	void Part2(std::string& input)
	{
		uint64_t* lights = new uint64_t[1000 * 1000];
		for (size_t i = 0; i < 1000 * 1000; i++)
			lights[i] = 0;
		size_t i = 0;
		while (i < input.size())
		{
			std::string instruction = nextWord(input, i);
			if (instruction == "turn")
				instruction = nextWord(input, i);
			uint16_t x_start = nextNumber(input, i);
			uint16_t y_start = nextNumber(input, i);
			uint16_t x_end = nextNumber(input, i);
			uint16_t y_end = nextNumber(input, i);

			if (instruction == "toggle") {
				for (uint16_t x = x_start; x <= x_end; x++)
					for (uint16_t y = y_start; y <= y_end; y++)
						lights[x * 1000 + y] += 2;
			}
			else if (instruction == "on") {
				for (uint16_t x = x_start; x <= x_end; x++)
					for (uint16_t y = y_start; y <= y_end; y++)
						lights[x * 1000 + y] += 1;
			}
			else {
				for (uint16_t x = x_start; x <= x_end; x++)
					for (uint16_t y = y_start; y <= y_end; y++)
						lights[x * 1000 + y] += (lights[x * 1000 + y]>0)?-1:0;
			}
		}

		uint64_t result = 0;
		for (size_t i = 0; i < 1000 * 1000; i++)
			result += lights[i];
		std::cout << result;
	}

END