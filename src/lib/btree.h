#ifndef __DS_B_TREE_H
#define __DS_B_TREE_H

typedef struct BTree {
    int order;                      // max entries in node, i.e. order 5 means <=4 entries
    struct BTreeNode *root;
} BTree;

typedef struct BTreeNode {
    struct BTreeNode *left_child;
    struct BTreeNodeEntry *data;    // array of entries
    int len;                        // current length of data in node
} BTreeNode;

typedef struct BTreeNodeEntry {
    struct BTreeNode *right_child;
    int record;                     // actual data stored in the entry
    int key;                        // unique identifier used to search for entry
} BTreeNodeEntry;

#endif