#include "ds.h"
#include "util.h"
#include "list.h"

// LIST
Node* list_create(int *arr, int size) {
  return l_list_create(arr, size);
}

Node* node_create(int data) {
  return l_node_create(data);
}

Node* list_get(Node *head, int index) {
  return l_list_get(head, index);
}

void node_free(Node *node) {
  l_node_free(node);
}

void node_add(Node *head, int data) {
  l_node_add(head, data);
}

void list_print(Node *head) {
  l_list_print(head);
}

void list_to_string(char* buf, Node* head) {
  l_list_to_string(buf, head);
}

void list_free(Node *head) {
  l_list_free(head);
}


// STACK
Stack* stack_create() {
  return s_stack_create();
}

Stack* stack_enlarge(Stack *stack) {
  return s_stack_enlarge(stack);
}

void stack_free(Stack *stack) {
  s_stack_free(stack);
}

void stack_push(Stack *stack, int el) {
  s_stack_push(stack, el);
}

int stack_pop(Stack *stack) {
  return s_stack_pop(stack);
}

void stack_to_string(char *buf, Stack *stack) {
  s_stack_to_string(buf, stack);
}

int stack_peek(Stack *stack) {
  return s_stack_peek(stack);
}

bool stack_is_empty(Stack *stack) {
  return s_stack_is_empty(stack);
}

int stack_size(Stack* stack) {
  return s_stack_size(stack);
}