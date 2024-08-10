#include<stdio.h>
#include "lib/list.h"
#include "lib/stack.h"
#include "lib/btree.h"

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

BTree* create_sample_tree() {
    BTree *tree = btree_create(3);
    // TODO: refinement and optimizations
    BTreeNodeEntry *entry = _btree_node_entry_create(69, 1);
    BTreeNodeEntry *entry2 = _btree_node_entry_create(420, 2);
    BTreeNodeEntry *entry3 = _btree_node_entry_create(1337, 3);
    BTreeNodeEntry *entry4 = _btree_node_entry_create(455, 4);
    BTreeNodeEntry *entry5 = _btree_node_entry_create(980, 5);
    BTreeNodeEntry *entry6 = _btree_node_entry_create(123, 6);
    BTreeNodeEntry *entry7 = _btree_node_entry_create(845, 7);

    btree_insert(tree, entry);
    printf("--------------------------\n");
    printf("1 insert\n");
    print_tree(tree->root);
    printf("--------------------------\n");

    btree_insert(tree, entry2);
    printf("2 insert\n");
    print_tree(tree->root);
    printf("--------------------------\n");

    btree_insert(tree, entry3);
    printf("3 insert\n");
    print_tree(tree->root);
    printf("--------------------------\n");

    btree_insert(tree, entry4);
    printf("4 insert\n");
    print_tree(tree->root);
    printf("--------------------------\n");

    btree_insert(tree, entry5);
    printf("5 insert\n");
    print_tree(tree->root);
    printf("--------------------------\n");

    btree_insert(tree, entry6);
    printf("6 insert\n");
    print_tree(tree->root);
    printf("--------------------------\n");

    btree_insert(tree, entry7);
    printf("7 insert\n");
    print_tree(tree->root);
    printf("--------------------------\n");

    return tree;
}

void b_tree() {
    BTree *tree = create_sample_tree();
}

int main() {
    b_tree();

    return 0;
}
