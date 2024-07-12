#ifndef __DS_LIST_H
#define __DS_LIST_H

typedef struct Node {
  int data;
  struct Node *next;
} Node;

// create a new list from an array
Node* l_list_create(int *arr, int size);

// print the linked list
void l_list_print(Node *head);

// returns a string representation of the list
void l_list_to_string(char* buf, Node* head);

// get a node from the list
Node* l_list_get(Node *head, int index);

// free the memory allocated for the linked list
void l_list_free(Node *head);

// create a new node for the linked list
Node* l_node_create(int data);

// add a new node at the end of the linked list
void l_node_add(Node *head, int data);

// free the memory allocated for the node
void l_node_free(Node *node);

#endif