#pragma once

START

	std::string nextWord(const std::string& str, size_t& i)
	{
		std::string r = "";
		while (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) && i < str.size())
			i++;
		while ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') && i < str.size()) {
			r += str[i];
			i++;
		}
		return r;
	}



	void Part1(std::string& input)
	{
		input =
			"H = > HO\n"
			"H = > OH\n"
			"O = > HH\n"
			"\n"
			"HOH";

		
		std::string formula;
		std::vector<std::pair<std::string, std::string>> conversions;
		for (size_t i = 0; i < input.size(); i++) {
			std::string e1 = nextWord(input, i);
			std::string e2 = nextWord(input, i);
			conversions.push_back(std::make_pair(e1, e2));
			if (input[i] == '\n' && input[i + 1] == '\n') {
				formula = nextWord(input, i);
				break;
			}
		}

		std::unordered_map<std::string, size_t> outputs;

		for(auto p : conversions)
			std::cout << p.first << ' ' << p.second << '\n';

		size_t result = 0;
		std::cout << result;
	}

	void Part2(std::string& input)
	{
		size_t result = 0;
		std::cout << result;
	}

END