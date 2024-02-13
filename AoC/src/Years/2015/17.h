#pragma once

START

	int64_t nextNumber(const std::string& str, size_t& i)
	{
		int64_t r = 0;
		while (str[i] < '0' || str[i] > '9' && i < str.size())
			i++;
		while (str[i] >= '0' && str[i] <= '9') {
			r = r * 10 + str[i] - '0';
			i++;
		}
		return r;
	}

	size_t combinations = 0;

	void Recursive(size_t max, std::vector<size_t>& values, size_t i = 0, size_t sum = 0)
	{
		for (; i < values.size(); i++) {
			Recursive(max, values, i + 1, sum + values[i]);
			if (sum > max)
				return;
		}
		if (sum == max)
			combinations++;
	}

	void Part1(std::string& input)
	{
		size_t max = 150;
		std::vector<size_t> values;
		for (size_t i = 0; i < input.size(); i++)
			values.push_back(nextNumber(input, i));

		std::sort(values.begin(), values.end());

		Recursive(max, values);

		size_t result = combinations;
		std::cout << result;
	}

	size_t min_I = -1;

	void Recursive21(size_t max, std::vector<size_t>& values, size_t i = 0, size_t sum = 0, std::string dbg = "")
	{
		for (; i < values.size(); i++) {
			Recursive21(max, values, i + 1, sum + values[i], (dbg + char('0' + i)));
			if (sum > max)
				return;
		}
		if (sum == max)
			min_I = std::min(dbg.size(), min_I);
	}
	void Recursive22(size_t max, std::vector<size_t>& values, size_t i = 0, size_t sum = 0, std::string dbg = "")
	{
		for (; i < values.size(); i++) {
			Recursive22(max, values, i + 1, sum + values[i], (dbg + char('0' + i)));
			if (sum > max)
				return;
		}
		if (sum == max && dbg.size() == min_I)
			combinations++;
	}

	void Part2(std::string& input)
	{
		combinations = 0;
		size_t max = 150;
		std::vector<size_t> values;
		for (size_t i = 0; i < input.size(); i++)
			values.push_back(nextNumber(input, i));

		std::sort(values.begin(), values.end(), std::greater());

		Recursive21(max, values);
		Recursive22(max, values);

		size_t result = combinations;
		std::cout << result;
	}

END