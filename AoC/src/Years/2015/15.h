#pragma once

START

	std::string nextWord(const std::string& str, size_t& i)
	{
		std::string r = "";
		while (str[i] == ' ' || str[i] == '\n' || str[i] == '\0' || str[i] == '.')
			i++;
		while (str[i] != ' ' && str[i] != '\0' && str[i] != '.') {
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


	struct Ingredient {
		std::string name;
		int64_t capacity;
		int64_t durability;
		int64_t flavor;
		int64_t texture;
		int64_t calories;
	};

	std::vector<int64_t> values;
	std::vector<int64_t> values_calories;

	void CalculateRecursive(std::vector<Ingredient*>& ingredients, size_t i = 0, size_t d = 0,
		int64_t capacity = 0, int64_t durability = 0, int64_t flavor = 0, int64_t texture = 0,
		int64_t calories = 0)
	{
		for (; i < 100; i++) {
			if (d < ingredients.size() - 1)
				CalculateRecursive(ingredients, i, d + 1, capacity, durability, flavor, texture, calories);
			capacity += ingredients[d]->capacity;
			durability += ingredients[d]->durability;
			flavor += ingredients[d]->flavor;
			texture += ingredients[d]->texture;
			calories += ingredients[d]->calories;
		}
		capacity = capacity > 0 ? capacity : 0;
		durability = durability > 0 ? durability : 0;
		flavor = flavor > 0 ? flavor : 0;
		texture = texture > 0 ? texture : 0;
		calories = calories > 0 ? calories : 0;
		values.push_back(capacity * durability * flavor * texture);
		values_calories.push_back(calories);
	}

	void Part1(std::string& input)
	{
		std::vector<Ingredient*> ingredients;
		for (size_t i = 0; i < input.size(); i++) {
			Ingredient* ing = new Ingredient;
			ing->name = nextWord(input, i);
			ing->capacity = nextNumber(input, i);
			ing->durability = nextNumber(input, i);
			ing->flavor = nextNumber(input, i);
			ing->texture = nextNumber(input, i);
			ing->calories = nextNumber(input, i);
			ingredients.push_back(ing);
		}

		CalculateRecursive(ingredients);

		int64_t result = 0;
		for (int64_t v : values)
			result = std::max(result, v);

		std::cout << result;
	}

	void Part2(std::string& input)
	{
		int64_t result = 0;
		for (size_t i = 0; i < values.size(); i++)
			if(values_calories[i] == 500)
				result = std::max(result, values[i]);
		std::cout << result;
	}

END