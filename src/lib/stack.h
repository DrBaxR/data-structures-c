#ifndef __DS_STACK_H
#define __DS_STACK_H

#include <stdbool.h>

// stack data allocated memory grows in chunks, this is the chunk size
#define STACK_CHUNK_SIZE 256

typedef struct Stack {
  int *data;
  int size;
  int head; // next position to add element
} Stack;

// create a new empty stack
Stack* s_stack_create();

// expand memory allocated for data by STACK_CHUNK
Stack* s_stack_enlarge(Stack *stack);

// free memory of a stack
void s_stack_free(Stack *stack);

// push element to the stack
void s_stack_push(Stack *stack, int el);

// pop element from the stack
int s_stack_pop(Stack *stack);

// transform stack to string in the character buffer passed as param
void s_stack_to_string(char *buf, Stack *stack);

// peek at the top element of the stack
int s_stack_peek(Stack *stack);

// true if is empty, false otherwise
bool s_stack_is_empty(Stack *stack);

// number of elements in the stack
int s_stack_size(Stack* stack);

#endif