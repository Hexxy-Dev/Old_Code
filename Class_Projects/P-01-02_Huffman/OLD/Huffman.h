#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <bitset>


const uint8_t END_PADDING = 2;


struct Node {
	Node(size_t weight, Node* left, Node* right)
		: c('\0'), weight(weight), left(left), right(right)
	{}
	Node(std::pair<char, size_t> pair)
		: c(pair.first), weight(pair.second), left(nullptr), right(nullptr)
	{}
	char c;
	size_t weight;

	Node* left;
	Node* right;

	bool operator>(const Node& other) const { return (weight > other.weight); }
	bool operator<(const Node& other) const { return (weight < other.weight); }
};

class PointerCompare {
public:
	template<typename T>
	bool operator()(T a, T b) { return (*a) > (*b); }
};


Node* GetMaxPriority(std::priority_queue<Node*, std::vector<Node*>, PointerCompare>& primaryQueue,
	std::priority_queue<Node*, std::vector<Node*>, PointerCompare>& secondaryQueue)
{
	Node* ptr;
	if (primaryQueue.size()) {
		if (secondaryQueue.size()) {
			if (*primaryQueue.top() < *secondaryQueue.top()) {
				ptr = primaryQueue.top();
				primaryQueue.pop();
			}
			else {
				ptr = secondaryQueue.top();
				secondaryQueue.pop();
			}
		}
		else {
			ptr = primaryQueue.top();
			primaryQueue.pop();
		}
	}
	else {
		ptr = secondaryQueue.top();
		secondaryQueue.pop();
	}

	return ptr;
}

Node* GenerateTree(std::priority_queue<Node*, std::vector<Node*>, PointerCompare>& primaryQueue)
{
	std::priority_queue<Node*, std::vector<Node*>, PointerCompare> secondaryQueue;

	Node* left;
	Node* right;

	while (primaryQueue.size() || secondaryQueue.size() > 1) {

		left = GetMaxPriority(primaryQueue, secondaryQueue);
		right = GetMaxPriority(primaryQueue, secondaryQueue);

		secondaryQueue.push(new Node(left->weight + right->weight, left, right));
	}

	return secondaryQueue.top();
}

void CreateLetterMaps(std::unordered_map<char, std::string>& letterMap, Node* root, std::string code = "")
{
	if (!root)
		return;
	if (root->left == nullptr && root->right == nullptr)
		letterMap[root->c] = code;

	CreateLetterMaps(letterMap, root->left, code + '\0');
	CreateLetterMaps(letterMap, root->right, code + '\1');
}

inline void AddBit(std::string& stringOutput, char& o, char& bits, char val)
{
	o <<= 1;
	o |= val;
	bits++;
	if (bits == 8) {
		bits = 0;
		stringOutput += o;
	}
}

void WRITE_DATA_TO_FILE(std::vector<bool>& dictionary, std::vector<bool>& binaryData)
{
	std::string stringOutput;
	char o = 0;
	char bits = 0;
	for (size_t i = 1; i <= dictionary.size(); i++)// {
		AddBit(stringOutput, o, bits, dictionary[i - 1]);
	//	o <<= 1;
	//	o |= dictionary[i - 1];
	//	bits++;
	//	if (bits == 8) {
	//		bits = 0;
	//		stringOutput += o;
	//	}
	//}

	for (size_t i = 1; i <= binaryData.size(); i++)// {
		AddBit(stringOutput, o, bits, binaryData[i - 1]);
	//	o <<= 1;
	//	o |= binaryData[i - 1];
	//	bits++;
	//	if (bits == 8) {
	//		bits = 0;
	//		stringOutput += o;
	//	}
	//}

	while (bits != 0)// {
		AddBit(stringOutput, o, bits, 0);
	//	o <<= 1;
	//	bits++;
	//	if (bits == 8) {
	//		bits = 0;
	//		stringOutput += o;
	//	}
	//}

	std::ofstream fout("OUT.txt", std::ios::binary);
	fout << stringOutput;
	fout.close();
}