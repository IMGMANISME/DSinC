// Binary Search Tree operations in C

#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	struct node *left, *right;
};

// Create a node
struct node *newNode(int item) {
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

// Inorder Traversal
void inorder(struct node *root) {
	if (root != NULL) {
		// Traverse left
		inorder(root->left);

		// Traverse root
		printf("%d -> ", root->key);

		// Traverse right
		inorder(root->right);
	}
}

// Preorder traversal
void preorder(struct node* root) {
	if (root == NULL) return;
	printf("%d ->", root->key);
	preorder(root->left);
	preorder(root->right);
}

// Postorder traversal
void postorder(struct node* root) {
	if (root == NULL) return;
	postorder(root->left);
	postorder(root->right);
	printf("%d ->", root->key);
}

// Insert a node
struct node *insert(struct node *node, int key) {
	// Return a new node if the tree is empty
	if (node == NULL) return newNode(key);

	// Traverse to the right place and insert the node
	if (key < node->key)
		node->left = insert(node->left, key);
	else
		node->right = insert(node->right, key);

	return node;
}

// Find the inorder successor
struct node *minValueNode(struct node *node) {
	struct node *current = node;

	// Find the leftmost leaf
	while (current && current->left != NULL)
		current = current->left;

	return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
	// Return if the tree is empty
	if (root == NULL) return root;

	// Find the node to be deleted
	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	else {
		// If the node is with only one child or no child
		if (root->left == NULL) {
			struct node *temp = root->right;
			free(root);
			return temp;
		} else if (root->right == NULL) {
			struct node *temp = root->left;
			free(root);
			return temp;
		}

		// If the node has two children
		struct node *temp = minValueNode(root->right);

		// Place the inorder successor in position of the node to be deleted
		root->key = temp->key;

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->key);
	}
	return root;
}

// Driver code
int main() {
	struct node *root = NULL;
	int sel, input;
	do {
		printf("---------------------------\nPlease enter your selection\nInsert : 1\nDelete : 2\nExit : 0\n---------------------------\n");
		scanf("%d",&sel);
		switch(sel) {
			case 0:
				break;
			case 1:
				scanf("%d",&input);
				root = insert(root, input);
				printf("---------------------------\n");
				printf("Inorder traversal: ");
				inorder(root);
				printf("\n");
				printf("Preorder traversal: ");
				preorder(root);
				printf("\n");
				printf("Postorder traversal: ");
				postorder(root);
				printf("\n");
				break;
			case 2:
				scanf("%d",&input);
				printf("---------------------------\n");
				printf("\nAfter deleting %d\n", input);
				root = deleteNode(root, input);
				printf("Inorder traversal: ");
				inorder(root);
				printf("\n");
				printf("Preorder traversal: ");
				preorder(root);
				printf("\n");
				printf("Postorder traversal: ");
				postorder(root);
				printf("\n");
				break;
			default:
				printf("---------------------------\n");
				printf("Inalid, please enter again\n");
		}
	} while(sel != 0);

	printf("---------------------------\n");
	printf("Inorder traversal: ");
	inorder(root);
	printf("NULL\n");
	printf("Preorder traversal: ");
	preorder(root);
	printf("NULL\n");
	printf("Postorder traversal: ");
	postorder(root);
	printf("NULL\n");
}
