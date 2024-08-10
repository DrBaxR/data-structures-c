#ifndef __DS_B_TREE_H
#define __DS_B_TREE_H

#include <stdio.h>

#define B_TREE_PARENT_NOT_FOUND -1

typedef struct BTree {
    int order;                      // max entries in node, i.e. order 5 means <=4 entries
    struct BTreeNode *root;
} BTree;

typedef struct BTreeNode {
    struct BTreeNode *left_child;
    struct BTreeNodeEntry **data;   // array of entries
    int len;                        // current length of data in node
} BTreeNode;

typedef struct BTreeNodeEntry {
    struct BTreeNode *right_child;
    int record;                     // actual data stored in the entry
    int key;                        // unique identifier used to search for entry
} BTreeNodeEntry;

typedef struct BTreeInsertionSplit {
    struct BTreeNode *left;         // left node resulted of a split
    struct BTreeNode *right;        // right node resulted of a split
    struct BTreeNodeEntry *median;  // median element that has left to the left and right to the right
    struct BTreeNode *split_node;   // node that was split into left and right and median
} BTreeInsertionSplit;

BTree* btree_create(int order);

BTreeNode* _btree_node_create(int order);

BTreeNodeEntry* _btree_node_entry_create(int record, int key);
    
void btree_free(BTree *tree);

void _btree_node_free(BTreeNode *node);

void _btree_node_entry_free(BTreeNodeEntry *entry);

BTreeNodeEntry* btree_search(BTreeNode *tree_root, int key);

// search for entry within node, not within children
// returns NULL if not found
BTreeNodeEntry* _btree_node_search(BTreeNode *node, int key);

void btree_insert(BTree *tree, BTreeNodeEntry *entry);

// returns a pointer to the parent node of the node passed as parameter
BTreeNode* _btree_get_node_parent(BTreeNode *root, BTreeNode *parent, BTreeNode *node);

// insert entry into node that is part of tree
// also mutates tree if the root changes
void _btree_node_insert_with_rebalance(BTree *tree, BTreeNode *node, BTreeNodeEntry *entry, int order);

// TODO: move descriptions here
BTreeInsertionSplit* insert_in_parent_with_potential_split(BTree *tree, BTreeNode* original_node, BTreeNodeEntry *entry_to_insert, BTreeNode *entry_left, BTreeNode *entry_right);

BTreeInsertionSplit* insert_with_potential_split(BTreeNode *node, BTreeNodeEntry *entry, int order);

BTreeInsertionSplit* split_node(BTreeNode *node, int order);

BTreeInsertionSplit* _btree_insertion_split_create(BTreeNode *left, BTreeNode *right, BTreeNodeEntry *median, BTreeNode *split_node);

void _btree_insertion_split_free(BTreeInsertionSplit *is);

// insert entry into the array of data in a node, without rebalancing
// does NOT check if node is FULL before inserting
// return index where entry is placed inside node->data
int _btree_node_insert_sorted(BTreeNode *node, BTreeNodeEntry *entry, int order);

// remove median entry of the node and return it (median entry returned is newly allocated, not the actual one)
// also frees memory for the entry that was removed
// should only be used when node data elements has an odd number of entries
BTreeNodeEntry* _btree_node_remove_median_entry(BTreeNode *node);

// find leaf in which entry should be inserted into
BTreeNode* _btree_find_insertion_leaf(BTreeNode *tree_root, BTreeNodeEntry *entry);

// return index of first element in node data that is greater than key
// return -1 if node is empty
int _btree_node_get_greater_index(BTreeNode *node, int key);

// 1 = node is leaf; 0 = node is NOT leaf
int _btree_node_is_leaf(BTreeNode *node);

void print_tree(BTreeNode *root);

#endif
