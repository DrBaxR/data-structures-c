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

    BTreeNode *node_to_insert_into_parent = _btree_get_node_parent(tree->root, NULL, node_to_insert_into);
    _btree_node_insert_with_rebalance(tree, node_to_insert_into, entry, tree->order);
}

BTreeNode* _btree_get_node_parent(BTreeNode *root, BTreeNode *parent, BTreeNode *node) {
    if (root == node) {
        return parent;
    }

    if (root == NULL) {
        return (BTreeNode*) B_TREE_PARENT_NOT_FOUND;
    }


    BTreeNode *potential_parent = _btree_get_node_parent(root->left_child, root, node);
    if (potential_parent != (BTreeNode*) B_TREE_PARENT_NOT_FOUND) {
        return potential_parent;
    }

    for (int i = 0; i < root->len; i++) {
        potential_parent = _btree_get_node_parent(root->data[i]->right_child, root, node);
        if (potential_parent != (BTreeNode*) B_TREE_PARENT_NOT_FOUND) {
            return potential_parent;
        }
    }

    return (BTreeNode*) B_TREE_PARENT_NOT_FOUND;
}

void _btree_node_insert_with_rebalance(BTree *tree, BTreeNode *node, BTreeNodeEntry *entry, int order) {
    BTreeInsertionSplit *is = _btree_node_insert_with_potential_split(node, entry, order);

    // no split for node
    if (is == NULL) {
        return;
    }

    // median element inserted into parent, which may cause it to be split and so on. if node has no parent, create a new root above node
    while (is->split_node != tree->root) {
        // if not root, call insert in parent with potential split
        BTreeInsertionSplit *new_is = _btree_node_insert_in_parent_with_potential_split(tree, is->split_node, is->median, is->left, is->right);
        // _btree_insertion_split_free(is);
        is = new_is;

        if (is == NULL) {
            // parent was not split, we are done; otherwise continue
            return;
        }
    }

    // if root, allocate new node and insert median in there (we only get here if `is->split_node` contains the root of the tree)
    BTreeNode *new_root = _btree_node_create(tree->order);
    is->median->right_child = is->right;
    new_root->left_child = is->left;
    _btree_node_insert_sorted(new_root, is->median, tree->order);

    // TODO: check why this is invalid pointer in case of 7 inserts (root split)
    // _btree_insertion_split_free(is);

    tree->root = new_root;
}

BTreeInsertionSplit* _btree_node_insert_in_parent_with_potential_split(BTree *tree, BTreeNode* original_node, BTreeNodeEntry *entry_to_insert, BTreeNode *entry_left, BTreeNode *entry_right) {
    // find parent of original_node
    BTreeNode *parent = _btree_get_node_parent(tree->root, NULL, original_node);

    // insert entry_to_insert into parent =>
    int median_index = _btree_node_insert_sorted(parent, entry_to_insert, tree->order);

    // arrange child pointers where median was inserted
    entry_to_insert->right_child = entry_right;
    if (median_index == 0) {
        parent->left_child = entry_left;
    } else {
        parent->data[median_index - 1]->right_child = entry_left;
    }

    //      1. node had enough space in it (return nothing)
    if (parent->len < tree->order) {
        return NULL;
    }

    //      2. node did not have enough space, so it split (return left, right, new_entry_to_insert)
    return _btree_node_split(parent, tree->order);
}

BTreeInsertionSplit* _btree_node_insert_with_potential_split(BTreeNode *node, BTreeNodeEntry *entry, int order) {
    _btree_node_insert_sorted(node, entry, order);

    if (node->len < order) {
        return NULL;
    }

    return _btree_node_split(node, order);
}

BTreeInsertionSplit* _btree_node_split(BTreeNode *node, int order) {
    BTreeNodeEntry *median = _btree_node_remove_median_entry(node);

    BTreeNode *right = _btree_node_create(order);
    for (int i = node->len / 2; i < node->len; i++) {
        right->data[i - node->len / 2] = node->data[i];
        right->len++;
    }

    node->len = node->len / 2;
    BTreeNode *left = node;

    BTreeInsertionSplit *is = _btree_insertion_split_create(left, right, median, node);
    return is;
}

BTreeInsertionSplit* _btree_insertion_split_create(BTreeNode *left, BTreeNode *right, BTreeNodeEntry *median, BTreeNode *split_node) {
    BTreeInsertionSplit *is = (BTreeInsertionSplit*) malloc(sizeof(BTreeInsertionSplit));

    is->left = left;
    is->right = right;
    is->median = median;
    is->split_node = split_node;

    return is;
}

void _btree_insertion_split_free(BTreeInsertionSplit *is) {
    free(is);
}

int _btree_node_insert_sorted(BTreeNode *node, BTreeNodeEntry *entry, int order) {
    int greater_index = _btree_node_get_greater_index(node, entry->key);

    if (greater_index == -1) {
        node->data[0] = entry;
        node->len = 1;

        return 0;
    }

    for (int i = greater_index + 1; i <= order; i++) {
        node->data[i] = node->data[i - 1];
    }

    node->len++;
    node->data[greater_index] = entry;

    return greater_index;
    return 0;
}

BTreeNodeEntry* _btree_node_remove_median_entry(BTreeNode *node) {
    BTreeNodeEntry *median_element = node->data[node->len / 2];

    for (int i = node->len / 2; i < node->len - 1; i++) {
        node->data[i] = node->data[i + 1];
    }
    node->len--;

    BTreeNodeEntry *median_clone = _btree_node_entry_create(median_element->record, median_element->key);
    _btree_node_entry_free(median_element);

    return median_clone;
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
    if (insertion_child == NULL) {
        return tree_root;
    }

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
    if (node->left_child != NULL) {
        return 0;
    }

    for (int i = 0; i < node->len; i++) {
        if (node->data[i] != NULL) {
            return 0;
        }
    }

    // all children are NULL
    return 1;
}

void print_tree(BTreeNode *root) {
    if (root == NULL) {
        return;
    }

    printf("%p\n", root);
    printf("%p <- |", root->left_child);
    for (int i = 0; i < root->len; i++) {
        printf(" [%d] (%d) -> '%p' |", root->data[i]->key, root->data[i]->record, root->data[i]->right_child);
    }
    printf("\n\n");

    print_tree(root->left_child);
    for (int i = 0; i < root->len; i++) {
        print_tree(root->data[i]->right_child);
    }

    printf("\n");
}
