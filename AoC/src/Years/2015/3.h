#pragma once

START

	struct hash_pair {
		template <class T1, class T2>
		size_t operator()(const std::pair<T1, T2>& p) const
		{
			auto hash1 = std::hash<T1>{}(p.first);
			auto hash2 = std::hash<T2>{}(p.second);
			return hash1 ^ hash2;
		}
	};

	void Part1(std::string& input)
	{
		size_t result = 0;
		long long x = 0;
		long long y = 0;
		std::unordered_map<std::pair<long long, long long>,size_t, hash_pair> visited;
		for (size_t i = 0; i < input.size(); i++) {
			visited[std::make_pair(x,y)]++;
			switch (input[i])
			{
			case '>':
				x++;
				break;
			case '<':
				x--;
				break;
			case '^':
				y++;
				break;
			case 'v':
				y--;
				break;
			}
		}
		result = visited.size();
		std::cout << result;
	}

	void Part2(std::string& input)
	{
		size_t result = 0;
		long long x1 = 0;
		long long y1 = 0;
		long long x2 = 0;
		long long y2 = 0;
		std::unordered_map<std::pair<long long, long long>, size_t, hash_pair> visited;
		for (size_t i = 0; i < input.size(); i++) {
			visited[std::make_pair(x1, y1)]++;
			visited[std::make_pair(x2, y2)]++;
			switch (input[i])
			{
			case '>':
				x1++;
				break;
			case '<':
				x1--;
				break;
			case '^':
				y1++;
				break;
			case 'v':
				y1--;
				break;
			}
			switch (input[++i])
			{
			case '>':
				x2++;
				break;
			case '<':
				x2--;
				break;
			case '^':
				y2++;
				break;
			case 'v':
				y2--;
				break;
			}
		}
		visited[std::make_pair(x1, y1)]++;
		visited[std::make_pair(x2, y2)]++;
		result = visited.size();
		std::cout << result;
	}

END