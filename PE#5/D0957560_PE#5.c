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
int cost_arr[500] = {0};
int total_cost = 0;
int i = 0;

void inorder(struct node* ,int );

int cal(int a) {
	if(i == 0) {
		cost_arr[i] = a;
	} else {
		cost_arr[i] = a + cost_arr[i - 1];
		//root = insert(root, cost_arr[i]);
	}
//	root = deleteNode(root, a);
//	root = insert(root, 0);
	i++;
}

// Inorder Traversal
void inorder(struct node *root,int a) {

	if (root != NULL) {
		// Traverse left
		inorder(root->left,a);

		// Traverse root
		printf("%d -> ", root->key);
		if(a == 0) {
			cal(root->key);
		}

		// Traverse right
		inorder(root->right,a);
	}
}


// Driver code
int main() {
	int input;
	int total;
	int count = 0;
	while(1) {
		scanf("%d",&input);
		if(input != 0) {
			root = insert(root, input);
			//root = deleteNode(root, input);
			printf("---------------------------\n");
			printf("Inorder traversal: ");
			inorder(root, input);
			printf("\n");
			count++;
		} else {
			printf("---------------------------\n");
			printf("Inorder traversal: ");
			inorder(root, input);
			printf("NULL\n");
			if(count < 3) {
				total_cost = 0;
			} else {
				for(i = 0; i < count; i++) {
					printf("cost_arr[%d] = %d\n", i + 1, cost_arr[i]);
					total_cost += cost_arr[i + 1];
				}
			}
			printf("Total Cost = %d\n",total_cost);
			break;
		}
	}
}
