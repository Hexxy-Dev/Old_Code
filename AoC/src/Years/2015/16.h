#pragma once

START

	std::string nextWord(const std::string& str, size_t& i)
	{
		std::string r = "";
		while (str[i] == ' ' || str[i] == '\n' || str[i] == '\0'
			|| str[i] == '.' || str[i] == ',' || str[i] == ':')
			i++;
		while ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
			r += str[i];
			i++;
		}
		return r;
	}

	int64_t nextNumber(const std::string& str, size_t& i)
	{
		int64_t r = 0;
		char sign = 1;
		while (str[i] < '0' || str[i] > '9' && i < str.size())
			i++;
		if (str[i - 1] == '-')
			sign = -1;
		while (str[i] >= '0' && str[i] <= '9') {
			r = r * 10 + str[i] - '0';
			i++;
		}
		return r * sign;
	}

	bool IsTheOne(std::vector<std::pair<std::string, size_t>> belongings) {
		std::vector<std::pair<std::string, size_t>> values = {
			std::make_pair("children", 3),
			std::make_pair("cats", 7),
			std::make_pair("samoyeds", 2),
			std::make_pair("pomeranians", 3),
			std::make_pair("akitas", 0),
			std::make_pair("vizslas", 0),
			std::make_pair("goldfish", 5),
			std::make_pair("trees", 3),
			std::make_pair("cars", 2),
			std::make_pair("perfumes", 1)
		};

		for (size_t i = 0; i < belongings.size(); i++)
			for (size_t j = 0; j < values.size(); j++)
				if (belongings[i].first == values[j].first)
					if (belongings[i].second != values[j].second)
						return false;
		return true;
	}

	void Part1(std::string& input)
	{
		std::vector<std::vector<std::pair<std::string, size_t>>> be;
		for (size_t i = 0; i < input.size(); i++) {
			nextWord(input, i);
			nextNumber(input, i);
			std::string s1 = nextWord(input, i);
			size_t v1 = nextNumber(input, i);
			std::string s2 = nextWord(input, i);
			size_t v2 = nextNumber(input, i);
			std::string s3 = nextWord(input, i);
			size_t v3 = nextNumber(input, i);
			std::vector<std::pair<std::string, size_t>> values;
			values.push_back(std::make_pair(s1, v1));
			values.push_back(std::make_pair(s2, v2));
			values.push_back(std::make_pair(s3, v3));
			be.push_back(values);
		}

		size_t result = 0;
		for (; result < be.size(); result++)
			if (IsTheOne(be[result]))
				break;
		std::cout << result + 1;
	}

	bool IsTheOnePart2(std::vector<std::pair<std::string, size_t>> belongings) {
		std::vector<std::pair<std::string, size_t>> values = {
			std::make_pair("children", 3),
			std::make_pair("samoyeds", 2),
			std::make_pair("akitas", 0),
			std::make_pair("vizslas", 0),
			std::make_pair("cars", 2),
			std::make_pair("perfumes", 1)
		};

		for (size_t i = 0; i < belongings.size(); i++) {
			for (size_t j = 0; j < values.size(); j++)
				if (belongings[i].first == values[j].first)
					if (belongings[i].second != values[j].second)
						return false;
			if (belongings[i].first == "cats")
				if (belongings[i].second <= 7)
					return false;
			if (belongings[i].first == "trees")
				if (belongings[i].second <= 3)
					return false;
			if (belongings[i].first == "pomeranians")
				if (belongings[i].second >= 3)
					return false;
			if (belongings[i].first == "goldfish")
				if (belongings[i].second >= 5)
					return false;
		}
			
		return true;
	}

	void Part2(std::string& input)
	{
		std::vector<std::vector<std::pair<std::string, size_t>>> be;
		for (size_t i = 0; i < input.size(); i++) {
			nextWord(input, i);
			nextNumber(input, i);
			std::string s1 = nextWord(input, i);
			size_t v1 = nextNumber(input, i);
			std::string s2 = nextWord(input, i);
			size_t v2 = nextNumber(input, i);
			std::string s3 = nextWord(input, i);
			size_t v3 = nextNumber(input, i);
			std::vector<std::pair<std::string, size_t>> values;
			values.push_back(std::make_pair(s1, v1));
			values.push_back(std::make_pair(s2, v2));
			values.push_back(std::make_pair(s3, v3));
			be.push_back(values);
		}

		size_t result = 0;
		for (; result < be.size(); result++)
			if (IsTheOnePart2(be[result]))
				break;
		std::cout << result + 1;
	}

END