#include<stdio.h>
#include "lib/ds.h"

int main() {
    int arr[5] = {1, 2, 3, 4, 5};

    // maybe make this take a vararg
    Node *head = list_create(arr, 5);

    char str[256];
    list_to_string(str, head);
    printf("%s\n", str);

    list_free(head);
    return 0;
}
