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
		size_t max_time = 2503;
		std::vector<size_t> values;
		for (size_t i = 0; i < input.size(); i++) {
			std::string name = nextWord(input, i);
			size_t speed = nextNumber(input, i);
			size_t time = nextNumber(input, i);
			size_t rest = nextNumber(input, i);
			i += 8;
			size_t total_time = 0;
			size_t distance = 0;
			while (total_time < max_time) {
				size_t current = 0;
				while (total_time < max_time && current < time) {
					distance += speed;
					current++;
					total_time++;
				}
				total_time += rest;
			}
			values.push_back(distance);
		}

		size_t result = 0;
		for (auto v : values)
			result = std::max(result, v);

		std::cout << result;
	}

	struct Candidate {
		std::string name;
		size_t speed;
		size_t time;
		size_t rest;
		size_t distance;
		size_t current;
		size_t score;
		void Increment()
		{
			current++;
			if (current <= time)
				distance += speed;
			if (current == time + rest)
				current = 0;
		}
	};

	void Part2(std::string& input)
	{
		size_t max_time = 2503;
		std::vector<Candidate*> candidates;
		for (size_t i = 0; i < input.size(); i++) {
			std::string name = nextWord(input, i);
			size_t speed = nextNumber(input, i);
			size_t time = nextNumber(input, i);
			size_t rest = nextNumber(input, i);
			i += 8;
			candidates.push_back(new Candidate{ name,speed,time,rest,0,0,0 });
		}

		for (size_t current_Time = 0; current_Time < max_time; current_Time++) {
			for (Candidate* c : candidates)
				c->Increment();
			size_t max_distance = 0;
			for (Candidate* c : candidates)
				max_distance = std::max(c->distance, max_distance);
			for (Candidate* c : candidates)
				if (c->distance == max_distance)
					c->score++;
		}

		size_t result = 0;
		for (Candidate* c : candidates)
			result = std::max(result, c->score);

		std::cout << result;
	}

END