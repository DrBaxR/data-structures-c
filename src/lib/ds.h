#ifndef __DS_H__
#define __DS_H__
// TODO: find out if there is any way you can make it so you have a single shared lib without having to have this huge file

#include <stdbool.h>
#include "list.h"
#include "stack.h"

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

// create a new empty stack
Stack* stack_create();

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
