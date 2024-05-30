#include<stdio.h>
#include "lib/ds.h"

int main() {
    int arr[5] = {1, 2, 3, 4, 5};

    Node *head = list_create(arr, 5);
    list_print(head);

    list_free(head);
    return 0;
}
