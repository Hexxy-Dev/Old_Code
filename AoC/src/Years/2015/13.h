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

	struct Node {
		Node(std::string name)
			: name(name)
		{}
		std::string name;
		std::vector<std::pair<Node*, int64_t>> connections;
	};

	std::vector<Node*> references;

	void AddNodeConnection(std::string& s, std::string& s2, int64_t v)
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
		first->connections.push_back(std::make_pair(second, v));
	}

	std::vector<int64_t> values;

#include <algorithm>

	int64_t FindConnection(Node* f, Node* p)
	{
		for (auto& v : p->connections)
			if (v.first == f)
				return v.second;
		throw "HMM";
	}

	void CalculateValues()
	{
		do {
			int64_t sum = 0;
			sum += FindConnection(references[0], references[references.size() - 1]);
			sum += FindConnection(references[references.size() - 1], references[0]);
			for (size_t i = 0; i < references.size() - 1; i++) {
				sum += FindConnection(references[i], references[i + 1]);
				sum += FindConnection(references[i + 1], references[i]);
			}
			values.push_back(sum);
		} while (std::next_permutation(references.begin(), references.end()));
	}

	void Part1(std::string& input)
	{
		for (size_t i = 0; i < input.size(); i++) {
			std::string name1 = nextWord(input, i);
			i += 6;
			std::string action = nextWord(input, i);
			char sign = 1;
			if (action == "lose")
				sign = -1;
			int64_t nr = nextNumber(input, i);
			i += 35;
			std::string name2 = nextWord(input, i);

			AddNodeConnection(name1, name2, nr * sign);
		}

		CalculateValues();

		int64_t result = 0;
		for (int64_t v : values)
			result = std::max(result, v);

		std::cout << result;
	}

	void Part2(std::string& input)
	{
		values.clear(); // clear previous values
		// no need to parse and recompute all connections
		Node* me = new Node("Me");

		for (Node* p : references) {
			p->connections.push_back(std::make_pair(me, 0));
			me->connections.push_back(std::make_pair(p, 0));
		}
		references.push_back(me);

		CalculateValues();

		int64_t result = 0;
		for (int64_t v : values)
			result = std::max(result, v);

		std::cout << result;
	}

END