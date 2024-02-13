#pragma once

START

	struct Node {
		Node(std::string name)
			: name(name)
		{}
		std::string name;
		std::vector<std::pair<Node*, size_t>> connections;
	};

	std::vector<Node*> references;

	void AddNode(std::string s, std::string s2, size_t d)
	{
		Node* first = nullptr;
		Node* second = nullptr;
		for (Node* i : references) {
			if (i->name == s)
				first = i;
			if (i->name == s2)
				second = i;
		}
		if (!first) {
			first = new Node(s);
			references.push_back(first);
		}
		if (!second) {
			second = new Node(s2);
			references.push_back(second);
		}
		first->connections.push_back(std::make_pair(second, d));
		second->connections.push_back(std::make_pair(first, d));
	}

	std::vector<size_t> values;

	void CalculateDistance(Node* n, size_t sum = 0, std::vector<Node*> visited = {})
	{
		visited.push_back(n);
		for (auto& pair : n->connections) {
			for (Node* p : visited)
				if (p == pair.first)
					goto HMM;
			CalculateDistance(pair.first, sum + pair.second, visited);
			HMM:;
		}
		if (visited.size() == references.size())
			values.push_back(sum);
	}

	void CreateGraph(std::string& input)
	{
		std::string name;
		std::string name2;
		size_t distance = 0;

		for (size_t i = 0; i < input.size(); i++) {
			if (input[i] == ' ') {
				if (input[i + 1] == 't') {
					name2 = name;
					name = "";
					i += 3;
					continue;
				}
				if (input[i + 1] == '=') {
					distance = 0;
					i += 3;
					while (input[i] >= '0' && input[i] <= '9') {
						distance *= 10;
						distance += input[i] - '0';
						i++;
					}
					i += 1;
					AddNode(name2, name, distance);
					name = "";
				}
			}
			name += input[i];
		}
	}

	void Part1(std::string& input)
	{
		CreateGraph(input);

		for (Node* p : references)
			CalculateDistance(p); //basically computing all valid routes

		size_t min = -1;
		for (size_t v : values)
			min = std::min(min, v);

		size_t result = min;
		std::cout << result;
	}

	void Part2(std::string& input)
	{
		//no need to recreate graph or calculate distances
		size_t max = 0;
		for (size_t v : values)
			max = std::max(max, v);

		size_t result = max;
		std::cout << result;
	}

END