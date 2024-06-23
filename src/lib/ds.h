#ifndef __DS_H__
#define __DS_H__

#include <stdbool.h>

// stack data allocated memory grows in chunks, this is the chunk size
#define STACK_CHUNK_SIZE 256

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
static Node* node_create(int data);

// add a new node at the end of the linked list
static void node_add(Node *head, int data);

// free the memory allocated for the node
static void node_free(Node *node);

typedef struct Stack {
  int *data;
  int size;
  int head; // next position to add element
} Stack;

// create a new empty stack
Stack* stack_create();

// expand memory allocated for data by STACK_CHUNK
static Stack* stack_enlarge(Stack *stack);

// free memory of a stack
void stack_free(Stack *stack);

// push element to the stack
void stack_push(Stack *stack, int el);

// pop element from the stack
int stack_pop(Stack *stack);

// transform stack to string in the character buffer passed as param
void stack_to_string(char *buf, Stack *stack);

// peek at the top element of the stack
int stack_peek(Stack *stack);

// true if is empty, false otherwise
bool stack_is_empty(Stack *stack);

// number of elements in the stack
int stack_size(Stack* stack);

#endif
