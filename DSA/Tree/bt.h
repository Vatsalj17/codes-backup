#ifndef BT_H
#define BT_H

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} treenode;

treenode* tree_node_init(int val);
int height(treenode* root, int level);
void printtree(treenode* root);
int count_nodes(treenode* root);
void destroy_tree(treenode* root);

#endif
