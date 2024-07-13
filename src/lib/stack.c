#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "util.h"

Stack* stack_create() {
  Stack* stack = (Stack*) malloc(sizeof(Stack));

  stack->data = (int*) malloc(sizeof(int) * STACK_CHUNK_SIZE);
  stack->size = STACK_CHUNK_SIZE;
  stack->head = 0;

  return stack;
}

Stack* stack_enlarge(Stack *stack) {
  stack->data = (int*) realloc(stack->data, sizeof(int) * (stack->size + STACK_CHUNK_SIZE));
  stack->size += STACK_CHUNK_SIZE;

  return stack;
}

void stack_free(Stack *stack) {
  free(stack->data);
  free(stack);
}

void stack_push(Stack *stack, int el) {
  stack->data[stack->head] = el;
  stack->head++;
}

int stack_pop(Stack *stack) {
  int el = stack->data[stack->head - 1];
  stack->head--;

  return el;
}

void stack_to_string(char *buf, Stack *stack) {
  strcpy(buf, "[");

  for (int i = stack->head - 1; i >= 0; i--) {
    char el_string[10];
    int_to_string(el_string, stack->data[i]);
    strcat(buf, el_string);
    strcat(buf, ", ");
  }

  buf[strlen(buf) - 2] = '\0';
  strcat(buf, "]");
}

int stack_peek(Stack *stack) {
  return stack->data[stack->head - 1];
}

bool stack_is_empty(Stack *stack) {
  return stack->head == 0;
}

int stack_size(Stack* stack) {
  return stack->head;
}