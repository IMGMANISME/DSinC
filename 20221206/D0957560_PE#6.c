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
	FILE* enter = fopen("testcase.txt","r");
	FILE* output1 = fopen("SearchTable.txt","w");
	FILE* output2 = fopen("BuyTable.txt","w");
	FILE* output3 = fopen("SortTable.txt","w");
	FILE* output4 = fopen("LogTable.txt","w");
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
				break;
			case 2:
				scanf("%d",&input);
				printf("---------------------------\n");
				printf("\nAfter deleting %d\n", input);
				root = deleteNode(root, input);
				printf("Inorder traversal: ");
				inorder(root);
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
	fclose(enter);
	fclose(output1);
	fclose(output2);
	fclose(output3);
	fclose(output4);
}
