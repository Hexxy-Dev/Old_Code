#pragma once

struct Node {
	int data;
	struct Node* left;
	struct Node* right;

	Node(int val)
	{
		data = val;

		left = nullptr;
		right = nullptr;
	}
};

struct BST
{
	int key;
	BST* left, * right;

	BST();

	BST(int value);

	BST* Insert(BST* root, int value);

	void Inorder(BST* root);
};


/*
struct Node
{
	Node(int key, int value)
		: key(key), value(value)
	{}

	int key;
	int value;

	Node* parent;

	union
	{
		struct
		{
			Node* child[2];
		};
		struct
		{
			Node* left;
			Node* right;
		};
	};
};

namespace BinaryTree
{
	Node*& search_recursively(Node*& node, int key)
	{
		if (!node || key == node->key)
				return node;
		if (key < node->key)
			return search_recursively(node->left, key);
		else
			return search_recursively(node->right, key);
	}

	std::pair<char, Node*> search_duplicatesAllowed(Node*& node, int key)
	{
		Node* new_node = node;
		Node* current_node;
		char dir;
		while (new_node)
		{
			current_node = new_node;
			if (key < current_node->key)
				dir = 0;
			else
				dir = 1;
			new_node = current_node->child[dir];
		}
		return { dir, current_node };
	}
	
	void insert(Node*& root, int key, int value)
	{
		if (!root)
			root = new Node(key, value);
		else if (key == root->key)
			root->value = value;
		else if (key < root->key)
			insert(root->left, key, value);
		else  // key > root->key
			insert(root->right, key, value);
	}

	Node* find_min(Node*& root)
	{
		Node* current_node = root;
		while (current_node->left)
			current_node = current_node->left;
		return current_node;
	}

	void replace_node_in_parent(Node*& root, Node*& new_value)
	{
		if (root->parent)
			if (root == root->parent->left)
				root->parent->left = new_value;
			else
			{
				root->parent->right = new_value;
				if (new_value)
					new_value->parent = root->parent;
			}
	}

	void binary_tree_delete(Node*& root, int key)
	{
		if (key < root->key)
		{
			binary_tree_delete(root->left, key);
			return;
		}
		if (key > root->key)
		{
			binary_tree_delete(root->right, key);
			return;
		}

		if (root->left && root->right)
		{
			Node* successor = find_min(root->right);
			root->key = successor->key;
			binary_tree_delete(successor, successor->key);
		}
		else if (root->left)
			replace_node_in_parent(root, root->left);
		else if (root->right)
			replace_node_in_parent(root, root->right);
		else
		{
			Node* None;
			replace_node_in_parent(root, None);
		}
	}

	void inorder_traversal(Node* node) {
		if (node == NULL)
			return;

		inorder_traversal(node->left);
		printf("%i ,", node->value);
		inorder_traversal(node->right);
	}


	bool isBST(struct Node* node, int minKey, int maxKey) {
		if (node == NULL) return true;
		if (node->key < minKey || node->key > maxKey) return false;

		return isBST(node->left, minKey, node->key - 1) && isBST(node->right, node->key + 1, maxKey);
	}
};//*/