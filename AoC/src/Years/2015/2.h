#pragma once

START

	size_t NextNumber(std::string& input, size_t& i) {
		size_t nr = 0;
		if (input[i] == 'x' || input[i] == '\n')
			i++;
		while (input[i] != 'x' && input[i] != '\n' && i < input.size()) {
			nr = nr * 10 + input[i] - '0';
			i++;
		}
		return nr;
	}

	void Part1(std::string& input)
	{
		size_t result = 0;
		size_t i = 0;
		while (i < input.size())
		{
			size_t l, w, h;
			l = NextNumber(input, i);
			w = NextNumber(input, i);
			h = NextNumber(input, i);
			size_t total = 2 * l * w + 2 * w * h + 2 * h * l;
			size_t min = std::min(std::min(l * w, w * h), h * l);
			result += total + min;
		}
		std::cout << result;
	}

	void Part2(std::string& input)
	{
		size_t result = 0;
		size_t i = 0;
		while (i < input.size())
		{
			size_t l, w, h;
			l = NextNumber(input, i);
			w = NextNumber(input, i);
			h = NextNumber(input, i);
			size_t min1 = std::min(std::min(l, w), h);
			size_t min2;
			if (min1 == l)
				min2 = std::min(w, h);
			else if (min1 == w)
				min2 = std::min(l, h);
			else
				min2 = std::min(l, w);
			result += l * w * h + min1 * 2 + min2 * 2;
		}
		std::cout << result;
	}

END