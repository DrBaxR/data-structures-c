#ifndef __DS_B_TREE_H
#define __DS_B_TREE_H

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

// insert entry into node that has parent in a tree of order
void _btree_node_insert_with_rebalance(BTreeNode *parent, BTreeNode *node, BTreeNodeEntry *entry, int order);

// insert entry into the array of data in a node, without rebalancing
// does NOT check if node is FULL before inserting
void _btree_node_insert_sorted(BTreeNode *node, BTreeNodeEntry *entry, int order);

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

#endif
