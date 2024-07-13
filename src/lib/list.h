#ifndef __DS_LIST_H
#define __DS_LIST_H

typedef struct Node {
  int data;
  struct Node *next;
} Node;

// create a new list from an array
Node* list_create(int *arr, int size);

// print the linked list
void list_print(Node *head);

// returns a string representation of the list
void list_to_string(char* buf, Node* head);

// get a node from the list
Node* list_get(Node *head, int index);

// free the memory allocated for the linked list
void list_free(Node *head);

// create a new node for the linked list
Node* node_create(int data);

// add a new node at the end of the linked list
void node_add(Node *head, int data);

// free the memory allocated for the node
void node_free(Node *node);

#endif