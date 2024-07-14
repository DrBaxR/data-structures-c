#include "btree.h"
#include <stdlib.h>

BTree* btree_create(int order) {
    BTree *tree = (BTree*) malloc(sizeof(BTree));

    tree->order = order;
    tree->root = (BTreeNode*) malloc(sizeof(BTreeNode));

    tree->root->left_child = NULL;
    tree->root->len = 0;
    tree->root->data = (BTreeNodeEntry**) malloc(order * sizeof(BTreeNodeEntry*));

    return tree;
}

BTreeNodeEntry* btree_search(BTreeNode *tree_root, int key) {
    if (tree_root == NULL) {
        return NULL;
    }

    // check if in current node
    BTreeNodeEntry *found = _btree_node_search(tree_root, key);
    if (found != NULL) {
        return found;
    }

    // find elements range in which key is part of -> i-1 and i are bounding entries
    int i = 0;
    while (i < tree_root->len && tree_root->data[i]->key > key) {
        i++;
    }

    // recursively call function for respective tree
    if (i == 0) {
        return btree_search(tree_root->left_child, key);
    } else {
        return btree_search(tree_root->data[i - 1]->right_child, key);
    }
}

// returns NULL if not found
BTreeNodeEntry* _btree_node_search(BTreeNode *node, int key) {
    // TODO: change to binary search and try to merge with other while used in btree_search
    for (int i = 0; i < node->len; i++) {
        BTreeNodeEntry *current = (node->data)[i];

        if (current->key == key) {
            return current;
        }
    }

    return NULL;
}

void btree_free(BTree *tree) {
    // TODO
}