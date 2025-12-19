#include <stdio.h>
#include <stdlib.h>
#include "bt.h"
// #include "../Stack/stack.h"

typedef void (*traversal) (treenode*, int*, int*);

void preorder(treenode* root, int* pre, int *i) {
    if (root == NULL) {
        return;
    }
    pre[(*i)++] = root->value;
    preorder(root->left, pre, i);
    preorder(root->right, pre, i);
}

void postorder(treenode* root, int* post, int* i) {
    if (root == NULL) {
        return;
    }
    postorder(root->left, post, i);
    postorder(root->right, post, i);
    post[(*i)++] = root->value;
}

void inorder(treenode* root, int* in, int* i) {
    if (root == NULL) {
        return;
    }
    inorder(root->left, in, i);
    in[(*i)++] = root->value;
    inorder(root->right, in, i);
}

int* dfs_traverse(treenode* root, int* return_size, traversal fun) {
    int* result = malloc(1024 * sizeof(int));
    int i = 0;
    fun(root, result, &i);
    *return_size = i;
    return result;
}

void bfs_itr(treenode* root, int* return_size, char* approach) {
    treenode* temp = root;
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->right;
        temp = temp->left;
    }
}

int main(void) {
    treenode* n1 = node_init(1);
    treenode* n2 = node_init(2);
    treenode* n3 = node_init(3);
    treenode* n4 = node_init(4);
    treenode* n5 = node_init(5);
    treenode* n6 = node_init(6);
    treenode* n7 = node_init(7);
    treenode* n8 = node_init(8);
    treenode* n9 = node_init(9);
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;
    n3->right = n6;
    n4->left = n7;
    n6->right = n8;
    n7->right = n9;

    int n;
    int* arr = dfs_traverse(n1, &n, preorder);
    printf("Preorder: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    free(arr);
    arr = dfs_traverse(n1, &n, inorder);
    printf("\nInorder: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    free(arr);
    arr = dfs_traverse(n1, &n, postorder);
    printf("\nPostorder: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    free(arr);
    destroytree(n1);
}
