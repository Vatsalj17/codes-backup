#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} treenode;

treenode* createNode(int value) {
    treenode* new = malloc(sizeof(treenode));
    if (new == NULL) return NULL;
    new->left = NULL;
    new->right = NULL;
    new->value = value;
    return new;
}

int height(treenode* root, int level) {
    if (root == NULL) return level;
    int left = height(root->left, level + 1);
    int right = height(root->right, level + 1);
    return (left > right)? left: right;
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
    printf("value = %d\n", root->value);
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

int main() {
    treenode* n1 = createNode(10);
    treenode* n2 = createNode(20);
    treenode* n3 = createNode(30);
    treenode* n4 = createNode(40);
    treenode* n5 = createNode(50);
    treenode* n6 = createNode(60);
    treenode* n7 = createNode(60);
    n1->left = n2;
    n1->right = n3;
    n3->left = n4;
    n3->right = n5;
    n2->left = n6;
    printtree(n1);
    printf("height: %d\n", height(n1, 0));
    free(n6);
    free(n5);
    free(n4);
    free(n3);
    free(n2);
    free(n1);
    return 0;
}
