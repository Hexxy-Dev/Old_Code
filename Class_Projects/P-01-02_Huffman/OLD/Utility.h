#pragma once
#include "Huffman.h"


void Traverse(Node* root, std::string code = "")
{
	if (!root)
		return;
	if (root->left == nullptr && root->right == nullptr) {
		std::string chr = (root->c == '\n') ? std::string("\\n") : (std::string("") + root->c);
		printf("%s - %s - %d\n", code.c_str(), chr.c_str(), root->weight);
	}
	else
		printf("%s - %d\n", code.c_str(), root->weight);

	Traverse(root->left, code + "0");
	Traverse(root->right, code + "1");
}
void print(const std::string& prefix, const Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "+--" : "L--");

		std::cout << node->weight << "  " << ((node->c == '\n') ? std::string("\\n") : (std::string("") + node->c)) << std::endl;

		print(prefix + (isLeft ? "|   " : "    "), node->left, true);
		print(prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}
void print(const Node* node)
{
	print("", node, false);
}
void PrintQueue(std::priority_queue<Node*, std::vector<Node*>, PointerCompare> queue)
{
	while (queue.size()) {
		printf("%d %c\n", queue.top()->weight, queue.top()->c);
		queue.pop();
	}
}