#include "btree.h"
#include <stdlib.h>

BTree* btree_create(int order) {
    BTree *tree = (BTree*) malloc(sizeof(BTree));

    tree->order = order;
    tree->root = _btree_node_create(order);

    return tree;
}

BTreeNode* _btree_node_create(int order) {
    BTreeNode *node = (BTreeNode*) malloc(sizeof(BTreeNode));

    node->left_child = NULL;
    node->len = 0;
    node->data = (BTreeNodeEntry**) malloc(order * sizeof(BTreeNodeEntry*));

    return node;
}

BTreeNodeEntry* _btree_node_entry_create(int record, int key) {
    BTreeNodeEntry *entry = (BTreeNodeEntry*) malloc(sizeof(BTreeNodeEntry));

    entry->record = record;
    entry->key = key;
    entry->right_child = NULL;

    return entry;
}

void btree_free(BTree *tree) {
    // TODO
}

void _btree_node_free(BTreeNode *node) {
    // TODO
}

void _btree_node_entry_free(BTreeNodeEntry *entry) {
    // TODO
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

void btree_insert(BTree *tree, BTreeNodeEntry *entry) {
    // search for the leaf node where new element belongs into
    BTreeNode *node_to_insert_into = _btree_find_insertion_leaf(tree->root, entry);

    // TODO
    // insert new element into the node
    //      1. node.elements < max => insert element in the node, keeping order
    //      2. node is full => split node in two nodes:
    //          1. pick median element
    //          2. values less than the median put in left node, greater into right
    //          3. median element inserted into parent, which may cause it to be split and so on. if node has no parent, create a new root above node
}

BTreeNode* _btree_find_insertion_leaf(BTreeNode *tree_root, BTreeNodeEntry *entry) {
    if (_btree_node_is_leaf(tree_root) == 1) {
        return tree_root;
    }

    int greater_index = _btree_node_get_greater_index(tree_root, entry->key);
    if (greater_index == -1) {
        // root is empty => should insert in it
        return tree_root;
    }

    BTreeNode *insertion_child = tree_root->left_child;
    if (greater_index > 0) {
        // insert in child between lesser element and greater element
        return _btree_find_insertion_leaf(tree_root->data[greater_index - 1]->right_child, entry);
    }

    return _btree_find_insertion_leaf(insertion_child, entry);
}

int _btree_node_get_greater_index(BTreeNode *node, int key) {
    if (node->len == 0) {
        return -1;
    }

    int greater_index = 0;

    while (greater_index < node->len && node->data[greater_index]->key <= key) {
        greater_index++;
    }

    return greater_index;
}

int _btree_node_is_leaf(BTreeNode *node) {
    for (int i = 0; i < node->len; i++) {
        if (node->data[i] != NULL) {
            return 0;
        }
    }

    // all children are NULL
    return 1;
}
