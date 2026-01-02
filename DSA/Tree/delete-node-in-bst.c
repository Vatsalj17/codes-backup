#include "bst.h"

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    bst_delete_node(&root, key);
    return root;
}
