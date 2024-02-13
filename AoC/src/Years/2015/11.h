#pragma once

START

	bool IsValid(std::string pass)
	{
		for (size_t i = 0; i < pass.size(); i++)
			if (pass[i] == 'i' || pass[i] == 'o' || pass[i] == 'l')
				return false;

		char doubles = 0;
		for(size_t i = 0; i < pass.size() - 1; i++)
			if (pass[i] == pass[i + 1]) {
				doubles++;
				i++;
			}
		char consecutive = 0;
		for (size_t i = 0; i < pass.size() - 2; i++)
			if (pass[i] == (pass[i + 1] - 1) && pass[i] == (pass[i + 2] - 2)) {
				consecutive = 1;
				break;
			}
		return (consecutive && (doubles >= 2));
	}

	void IncrementString(std::string& pass)
	{
		pass[pass.size() - 1]++;
		if (pass[pass.size() - 1] > 'z') {
			pass.pop_back();
			IncrementString(pass);
		}
		if (pass.size() < 8) {
			pass += 'a' - 1;
			IncrementString(pass);
		}
	}

	void Part1(std::string& input)
	{
		std::string result = input;
		IncrementString(result);
		while (!IsValid(result))
			IncrementString(result);

		std::cout << result;
	}

	void Part2(std::string& input)
	{
		std::string result = input;
		IncrementString(result);
		while (!IsValid(result))
			IncrementString(result);

		IncrementString(result);
		while (!IsValid(result))
			IncrementString(result);

		std::cout << result;
	}

END