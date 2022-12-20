#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
  struct node *prev;
} Node;

void add_node(Node **start, int value, char state);
void print_list(Node *node);
void inverse_print_list(Node *node);
void free_list(Node *node);

int main(int argc, char *argv[]) {
  FILE *ptr;
  Node *head = NULL;
  char inputChar, temp;
  int inputNumber;

  ptr = fopen("input.txt", "r");
  while (!feof(ptr)) {
    fscanf(ptr, "%c%c", &temp, &inputChar);
    if (inputChar != 'R') {
      fscanf(ptr, "%c%d", &temp, &inputNumber);
    }
    // printf("%c %d\n", inputChar, inputNumber);

    // create first node "head"

    if (inputChar == 'R') {
      head = head->next;
      Node *last = head;
      while (last->next->next != NULL) {
        last = last->next;
      }
      last->next = NULL;
    } else {
      if (inputChar == 'B') {
        add_node(&head, inputNumber, 'B');
      } else if (inputChar == 'E') {
        add_node(&head, inputNumber, 'E');
      }
    }
  }

  print_list(head);

  Node *last = head;
  while (last->next != NULL) {
    last = last->next;
  }

  inverse_print_list(last);

  return 0;
}

void add_node(Node **start, int value, char state) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = value;
  new_node->next = NULL;
  new_node->prev = NULL;

  if (state == 'E') {
    if (*start == NULL) {
      *start = new_node;
      return;
    } else {
      Node *current;
      current = *start;
      while (current->next != NULL) {
        current = current->next;
      }
      current->next = new_node;
      new_node->prev = current;
      return;
    }
  } else {
    if (*start == NULL) {
      *start = new_node;
      return;
    } else {
      new_node->next = *start;
      (*start)->prev = new_node;
      *start = new_node;
      return;
    }
  }
}

void print_list(Node *node) {
  while (node != NULL) {
    printf("%d->", node->data);
    node = node->next;
  }
  printf("NULL\n");
}

void inverse_print_list(Node *node) {
  while (node != NULL) {
    printf("%d->", node->data);
    node = node->prev;
  }
  printf("NULL\n");
}
