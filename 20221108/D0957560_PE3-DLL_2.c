#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef Node;
typedef struct Node {
	Node* next;
	int data;
	Node* prev;
} node1;

void push(struct Node** head_ref, int new_data) {
	/* 1. allocate node */
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	/* 2. put in the data  */
	new_node->data = new_data;
	/* 3. Make next of new node as head and previous as NULL*/
	new_node->next = (*head_ref);
	new_node->prev = NULL;
	/* 4. change prev of head node to new node */
	if ((*head_ref) != NULL)
		(*head_ref)->prev = new_node;
	/* 5. move the head to point to the new node */
	(*head_ref) = new_node;
}

void append(struct Node** head_ref, int new_data) {
	/* 1. allocate node */
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	struct Node* last = *head_ref; /* used in step 5*/
	/* 2. put in the data  */
	new_node->data = new_data;
	/* 3. This new node is going to be the last node, so make next of it as NULL*/
	new_node->next = NULL;
	/* 4. If the Linked List is empty, then make the new node as head */
	if (*head_ref == NULL) {
		new_node->prev = NULL;
		*head_ref = new_node;
		return;
	}
	/* 5. Else traverse till the last node */
	while (last->next != NULL) {
		last = last->next;
	}
	/* 6. Change the next of last node */
	last->next = new_node;
	/* 7. Make last node as previous of new node */
	new_node->prev = last;
	return;
}

void printList(struct Node* node) {
	struct Node* last;
	printf("\nTraversal in forward direction \n");
	while (node != NULL) {
		printf(" %d -> ", node->data);
		last = node;
		node = node->next;
	}

	printf("\nTraversal in reverse direction \n");
	while (last != NULL) {
		printf(" %d -> ", last->data);
		last = last->prev;
	}
}


int main() {
	FILE* input = fopen("input.txt","r");
	FILE* output = fopen("output.txt","w");
	char temp[5000] = {'\0'};
	struct Node* head = NULL;


	fgets(temp, 5000, input);
	temp[strlen(temp)] = '\n';
	int i, num1, check1;
	int tmp = 0;
	char ch;
	int check = 0;
	int finish = 0;
	Node no;

	for(i = 0; i< strlen(temp); i++) {
		ch = temp[i];
		while(ch != '\n') {
			if(ch == ' ') {
				break;
			} else if(ch == 'B' || ch == 'E' || ch == 'R') {
				if(ch == 'B') {
					check = 1;
				} else if(ch == 'E') {
					check = 2;
				} else {
					check = 3;
				}
				break;
			} else {
				char* chnum = &ch;
				int num = atoi(chnum);
				tmp = 10 * tmp;
				tmp += num;
				if(temp[i + 1] == ' ' || temp[i + 1] == '\n') {
					num1 = tmp;
					tmp = 0;
					finish = 1;
				}
				break;
			}
		}
		while(check == 3 || finish != 0) {
			switch(check) {
				case 1:
					push(&head,num1);
					break;
				case 2:
					append(&head,num1);
					break;
				case 3:
					deleteNode(&head, head);
					deleteNode(&head, head->next);
					break;

			}
			printf("check = %d, num1 = %d\n",check,num1);
			printf("finished\n");
			check = 0;
			num1 = 0;
			finish = 0;
			break;
		}

	}
	printf("Created DLL is: ");
	printList(head);
	printf("NULL");

	getchar();
	return 0;

	fclose(input);
	fclose(output);


}
