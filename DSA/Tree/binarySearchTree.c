#include <stdlib.h>

#include "bst.h"

static bool bst_insert_rec(treenode** rootptr, int val) {
	treenode* root = *rootptr;
	if (root == NULL) {
		*rootptr = tree_node_init(val);
		return true;
	}
	if (val == root->val) {
		return false;
	} else if (val < root->val) {
		return bst_insert_rec(&(root->left), val);
	} else {
		return bst_insert_rec(&(root->right), val);
	}
}

bool bst_insert_node(treenode** rootptr, int val) {
	while (*rootptr) {
		if (val == (*rootptr)->val) {
			return false;
		} else if (val < (*rootptr)->val) {
			rootptr = &(*rootptr)->left;
		} else {
			rootptr = &(*rootptr)->right;
		}
	}
	*rootptr = tree_node_init(val);
	return true;
}

bool in_bst(treenode* root, int val) {
	if (root == NULL) return false;
	if (val == root->val)
		return true;
	else if (val < root->val)
		return in_bst(root->left, val);
	else
		return in_bst(root->right, val);
}

treenode* bst_find(treenode* root, int val) {
	while (root != NULL && root->val != val) {
		root = (val < root->val) ? root->left : root->right;
	}
	return root;
}

static treenode* last_right(treenode* root) {
    if (root->right == NULL) return root;
    return last_right(root->right);
}

// attaching the right subtree to extreme right of left subtree
static treenode* helper_of_delete(treenode* root) {
    treenode* temp = root;
    if (temp->left == NULL) {
        treenode* new = temp->right;
        free(temp);
        return new;
    }
    if (temp->right == NULL) {
        treenode* new = temp->left;
        free(temp);
        return new;
    }
    treenode* rightleaf = temp->right;
    treenode* last_right_of_left = last_right(temp->left);
    last_right_of_left->right = rightleaf;
    treenode* new = temp->left;
    free(temp);
    return new;
}

bool bst_delete_node(treenode** rootptr, int val) {
	treenode* root = *rootptr;
	if (root == NULL) return false;
    if (root->val == val) {
        root = helper_of_delete(root);
        *rootptr = root;
        return true;
    }
    while (root != NULL) {
        if (root->val > val) {
            if (root->left != NULL && root->left->val == val) {
                root->left = helper_of_delete(root->left);
                return true;
            } else {
                root = root->left;
            }
        } else {
            if (root->right != NULL && root->right->val == val) {
                root->right = helper_of_delete(root->right);
                return true;
            } else {
                root = root->right;
            }
        }
    }
	return false;
}
