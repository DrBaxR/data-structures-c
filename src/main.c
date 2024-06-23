#include<stdio.h>
#include "lib/ds.h"

void list() {
    int arr[5] = {1, 2, 3, 4, 5};

    // maybe make this take a vararg
    Node *head = list_create(arr, 5);

    char str[256];
    list_to_string(str, head);
    printf("%s\n", str);

    list_free(head);
}

void stack() {
    Stack *stack = stack_create();

    stack_push(stack, 1);
    stack_push(stack, 2);
    stack_push(stack, 3);

    char stack_string[256];
    stack_to_string(stack_string, stack);
    printf("initial stack: %s\n", stack_string);

    printf("top element: %d\n", stack_peek(stack));

    printf("stack is empty: %d\n", stack_is_empty(stack));
    printf("stack size: %d\n", stack_size(stack));

    printf("stack pop: %d\n", stack_pop(stack));
    printf("stack pop: %d\n", stack_pop(stack));
    printf("stack pop: %d\n", stack_pop(stack));

    printf("stack is empty: %d\n", stack_is_empty(stack));

    stack_free(stack);
}

int main() {
    stack();

    return 0;
}
