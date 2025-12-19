#ifndef BT_H
#define BT_H

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} treenode;

treenode* node_init(int value);
int height(treenode* root, int level);
void printtree(treenode* root);
int count_nodes(treenode* root);
void destroytree(treenode* root);

#endif
