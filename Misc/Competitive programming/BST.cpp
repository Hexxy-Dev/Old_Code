
#include <iostream>

struct Node
{
	Node()
		: key(0), value(0), left(nullptr), right(nullptr)
	{}
	Node(int key, int value = 0)
		: key(key), value(value), left(nullptr), right(nullptr)
	{}

	int key, value;
	Node* left;
	Node* right;
};

void Insert(Node*& root, int key, int value)
{
	if (!root)
		root = new Node(key, value);
	else if (root->key == key)
		root->value = value;
	else if (key < root->key)
		Insert(root->left, key, value);
	else
		Insert(root->right, key, value);
}

void inorder_traversal(Node*& root)
{
	if (!root)
		return;
	inorder_traversal(root->left);
	std::cout << root->value << std::endl;
	inorder_traversal(root->right);
}

///*
int tree_depth(Node*& root, const int& depth)
{
	int current_depth = depth;
	if (root)
	{
		current_depth++;
		return int(std::max(current_depth, std::max(tree_depth(root->left, current_depth), tree_depth(root->right, current_depth))));
	}
	return 0;
}//*/

int main()
{
	Node* root = new Node();

	Insert(root, 2, 2);
	Insert(root, 5, 5);
	Insert(root, 1, 1);
	Insert(root, 3, 3);
	
	Insert(root, 4, 4);
	Insert(root, -2, -2);
	Insert(root, -4, -4);
	Insert(root, -1, -1);
	Insert(root, -3, -3);
	
	
	inorder_traversal(root);
	std::cout << "\nDepth: " << tree_depth(root, 0);
}
