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

// Insert a node
struct node *insert(struct node *node, int key) {
	// Return a new node if the tree is empty
	if (node == NULL) return newNode(key);

	// Traverse to the right place and insert the node
	if (key < node->key) {
		node->left = insert(node->left, key);
	} else {
		node->right = insert(node->right, key);
	}
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

struct node *root = NULL;
int record[500] = {0};
int cost_arr[500] = {0};
int total_cost = 0;
int i = 0;
int j = 0;


void inorder_cal(struct node *root) {

	if (root != NULL) {
		// Traverse left
		inorder_cal(root->left);

		// Traverse root
		printf("%d -> ", root->key);
		record[j] = root->key;
		j++;

		// Traverse right
		inorder_cal(root->right);
	}
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


// Driver code
int main() {
	int input;
	int total;
	int count;
	int check;
	while(1) {
		scanf("%d",&count);
		if(count == 0) {
			break;
		} else {
			check = count;
			for(i = check; i > 0; i--) {
				scanf("%d",&input);
				if(count != 0) {
					root = insert(root, input);
					printf("---------------------------\n");
					printf("Inorder traversal: ");
					inorder(root);
					printf("\n");
				}

			}

			printf("---------------------------\n");
			printf("Inorder traversal: ");
			printf("NULL\n");

			for(i = 0; i < count; i++) {
				printf("record[0] = %d\n",record[0]);
				printf("record[1] = %d\n",record[1]);
				cost_arr[i] = record[0] + record[1];
				root = insert(root, cost_arr[i]);
				root = deleteNode(root, record[0]);
				root = deleteNode(root, record[1]);
				printf("cost_arr[%d] = %d\n",i + 1,cost_arr[i]);
				inorder_cal(root);
				j = 0;
				printf("\n");
			}
			for(i = 0; i < count; i++) {
				total_cost += cost_arr[i];
			}
			printf("%d\n",total_cost);
		}
		
	}
}

