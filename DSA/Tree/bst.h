#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include "bt.h"

bool bst_insert_node(treenode** rootptr, int val);
bool in_bst(treenode* root, int val);
treenode* bst_find(treenode* root, int val);
bool bst_delete_node(treenode** rootptr, int val);

#endif
