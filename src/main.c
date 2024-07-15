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
    BTreeNodeEntry *entry = _btree_node_entry_create(69, 12);
    BTreeNodeEntry *entry2 = _btree_node_entry_create(420, 8);

    // only using this until insertion algorithm is fully implemented
    _btree_node_insert_sorted(tree->root, entry, tree->order);
    _btree_node_insert_sorted(tree->root, entry2, tree->order);

    return tree;
}

void b_tree() {
    BTree *tree = create_sample_tree();

    printf("Search: %d\n", btree_search(tree->root, 12)->record);
    printf("%d\n", _btree_node_get_greater_index(tree->root, 10));
    printf("Insert: TODO\n");
    printf("Delete: TODO\n");
}

int main() {
    b_tree();

    return 0;
}
