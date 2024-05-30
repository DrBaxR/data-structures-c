#include "ds.h"
#include <stdio.h>
#include <stdlib.h>

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

void list_free(Node *head) {
  Node *current = head;
  while (current != NULL) {
    Node *next = current->next;
    node_free(current);
    current = next;
  }
}
