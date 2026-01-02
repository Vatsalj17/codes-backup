#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bt.h"

treenode* tree_node_init(int val) {
    treenode* new = malloc(sizeof(treenode));
    if (new == NULL) return NULL;
    new->left = NULL;
    new->right = NULL;
    new->val = val;
    return new;
}

int count_nodes(treenode* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

int height(treenode* root, int level) {
    if (root == NULL) return level;
    int left = height(root->left, level + 1);
    int right = height(root->right, level + 1);
    return (left > right)? left: right;
}

int balanced(treenode* root, int level, bool *state) {
    if (root == NULL) return level;
    int left = balanced(root->left, level + 1, state);
    int right = balanced(root->right, level + 1, state);
    int diff = left - right;
    if (diff < -1 || diff > 1) *state = false;
    return (left > right)? left: right;
}

int diameter(treenode* root, int* max) {
    if (root == NULL) return 0;
    int left = diameter(root->left, max);
    int right = diameter(root->right, max);
    int sum = left + right;
    if (sum >= *max) *max = sum;
    return 1 + ((left > right)? left: right);
}

void printtabs(int numtabs) {
    for (int i = 0; i < numtabs; i++) {
        printf("\t");
    }
}

void printtree_rec(treenode* root, int level) {
    if (root == NULL) {
        printtabs(level);
        printf("{<end>}\n");
        return;
    }
    printtabs(level);
    printf("val = %d\n", root->val);
    printtabs(level);

    printf("left -> \n");
    printtree_rec(root->left, level + 1);
    printtabs(level);

    printf("right -> \n");
    printtree_rec(root->right, level + 1);
    printtabs(level);

    printf("done\n");
}

void printtree(treenode* root) {
    printtree_rec(root, 0);
}

void destroy_tree(treenode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// int main() {
//     treenode* n1 = node_init(10);
//     treenode* n2 = node_init(20);
//     treenode* n3 = node_init(30);
//     treenode* n4 = node_init(40);
//     treenode* n5 = node_init(50);
//     treenode* n6 = node_init(60);
//     treenode* n7 = node_init(60);
//     n1->left = n2;
//     n1->right = n3;
//     n3->left = n4;
//     n3->right = n5;
//     n2->left = n6;
//     printtree(n1);
//     printf("height: %d\n", height(n1, 0));
//     free(n6);
//     free(n5);
//     free(n4);
//     free(n3);
//     free(n2);
//     free(n1);
//     return 0;
// }
