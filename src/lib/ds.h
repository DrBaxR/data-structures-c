#ifndef __DS_H__
#define __DS_H__

typedef struct Node {
  int data;
  struct Node *next;
} Node;

// create a new list from an array
Node* list_create(int *arr, int size);

// print the linked list
void list_print(Node *head);

// get a node from the list
Node* list_get(Node *head, int index);

// free the memory allocated for the linked list
void list_free(Node *head);

// create a new node for the linked list
static Node* node_create(int data);

// add a new node at the end of the linked list
static void node_add(Node *head, int data);

// free the memory allocated for the node
static void node_free(Node *node);

#endif
