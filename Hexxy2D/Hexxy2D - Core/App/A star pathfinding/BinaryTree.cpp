#include "BinaryTree.h"

#include <iostream>

BST::BST()
	: key(0), left(nullptr), right(nullptr)
{}
BST::BST(int value)
	: key(value), left(nullptr), right(nullptr)
{}

BST* BST::Insert(BST* root, int value)
{
	if (!root)
		return new BST(value);


	if (value > root->key)
		root->right = Insert(root->right, value);
	else
		root->left = Insert(root->left, value);

	return root;
}
void BST::Inorder(BST* root)
{
    if (!root) {
        return;
    }
    Inorder(root->left);
    std::cout << root->key << std::endl;
    Inorder(root->right);
}

////////////////////////////////////////////////////////////////////

void Inorder(BST* root)
{
	if (!root) {
		return;
	}
	Inorder(root->left);
	std::cout << root->key << std::endl;
	Inorder(root->right);
}

BST* insert(BST* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return new BST(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root */
BST* deleteNode(BST* root, int k)
{
    // Base case
    if (root == NULL)
        return root;

    // Recursive calls for ancestors of
    // node to be deleted
    if (root->key > k) {
        root->left = deleteNode(root->left, k);
        return root;
    }
    else if (root->key < k) {
        root->right = deleteNode(root->right, k);
        return root;
    }

    // We reach here when root is the node
    // to be deleted.

    // If one of the children is empty
    if (root->left == NULL) {
        BST* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        BST* temp = root->left;
        delete root;
        return temp;
    }

    // If both children exist
    else {

        BST* succParent = root;

        // Find successor
        BST* succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        // If there is no succ, then assign
        // succ->right to succParent->right
        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        // Copy Successor Data to root
        root->key = succ->key;

        // Delete Successor and return root
        delete succ;
        return root;
    }
}

/////////////////////////////////////////////////////////////////////

int BTfunc()
{
	/*create root*/
	struct Node* root = new Node(1);
	/* following is the tree after above statement

			 1
			/ \
		  NULL NULL
	*/
	root->left = new Node(2);
	root->right = new Node(3);
	/* 2 and 3 become left and right children of 1
					1
				  /    \
				 2       3
			   /  \     /  \
			NULL NULL  NULL NULL
	*/
	root->left->left = new Node(4);
	/* 4 becomes left child of 2
			   1
			/     \
		   2       3
		  / \     / \
		 4  NULL NULL NULL
		/ \
	 NULL NULL
	*/
	return 0;
}

int BSTfunc()
{
	BST b;
	BST* root = NULL;
	root = b.Insert(root, 50);
	b.Insert(root, 30);
	b.Insert(root, 20);
	b.Insert(root, 40);
	b.Insert(root, 70);
	b.Insert(root, 60);
	b.Insert(root, 80);

	b.Inorder(root);
	return 0;
}

int BSTfunc2()
{
    /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
    BST* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal of the given tree \n");
    Inorder(root);

    printf("\nDelete 20\n");
    root = deleteNode(root, 20);
    printf("Inorder traversal of the modified tree \n");
    Inorder(root);

    printf("\nDelete 30\n");
    root = deleteNode(root, 30);
    printf("Inorder traversal of the modified tree \n");
    Inorder(root);

    printf("\nDelete 50\n");
    root = deleteNode(root, 50);
    printf("Inorder traversal of the modified tree \n");
    Inorder(root);


    printf("\nDelete 70\n");
    root = deleteNode(root, 70);
    printf("Inorder traversal of the modified tree \n");
    Inorder(root);

    return 0;
}

int main()
{
	BTfunc();
	BSTfunc();
    BSTfunc2();
}