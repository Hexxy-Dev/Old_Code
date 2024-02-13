#include <iostream>

struct Node {
	int data;
	Node* left = nullptr;
	Node* right = nullptr;
};

void Inorder(Node* root)
{
	if (!root)
		return;
	
	Inorder(root->left);
	printf("%d ", root->data);
	Inorder(root->right);
}

int main()
{
	Node* root = new Node;
	Node** nodes = new Node*[8];
	for (size_t i = 0; i < 8; i++)
		nodes[i] = new Node;

	root->data = 2;
	root->left = nodes[0];
	nodes[0]->data = 7;
	root->right = nodes[1];
	nodes[1]->data = 5;

	nodes[0]->left = nodes[2];
	nodes[2]->data = 2;
	nodes[0]->right = nodes[3];
	nodes[3]->data = 6;

	nodes[1]->right = nodes[4];
	nodes[4]->data = 9;

	nodes[3]->left = nodes[5];
	nodes[5]->data = 5;
	nodes[3]->right = nodes[6];
	nodes[6]->data = 11;

	nodes[4]->left = nodes[7];
	nodes[7]->data = 4;

	Inorder(root);

	for (size_t i = 0; i < 8; i++)
		delete nodes[i];
	delete[] nodes;
}