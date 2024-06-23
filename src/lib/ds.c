#include "ds.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LIST
Node* list_create(int *arr, int size) {
  Node *head = node_create(arr[0]);
  for (int i = 1; i < size; i++) {
    node_add(head, arr[i]);
  }
  return head;
}

Node* node_create(int data) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
  node->next = NULL;
  return node;
}

Node* list_get(Node *head, int index) {
  Node *current = head;
  int i = 0;

  while (current != NULL) {
    if (i == index) {
      return current;
    }

    current = current->next;
    i++;
  }

  return NULL;
}

void node_free(Node *node) {
  free(node);
}

void node_add(Node *head, int data) {
  Node *new_node = node_create(data);
  Node *current = head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = new_node;
}

void list_print(Node *head) {
  Node *current = head;
  while (current != NULL) {
    printf(" |%d| ->", current->data);
    current = current->next;
  }
  printf(" NULL\n");
}

void list_to_string(char* buf, Node* head) {
  strcpy(buf, "[");

  Node* current = head;
  while (current != NULL) {
    char data_string[10];
    int_to_string(data_string, current->data);
    strcat(buf, data_string);
    strcat(buf, ", ");
    current = current->next;
  }

  buf[strlen(buf) - 2] = '\0';
  strcat(buf, "]");
}

void list_free(Node *head) {
  Node *current = head;
  while (current != NULL) {
    Node *next = current->next;
    node_free(current);
    current = next;
  }
}


// STACK
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