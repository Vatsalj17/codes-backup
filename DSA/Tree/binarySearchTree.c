#include <stdbool.h>
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

bool insertNumber(treenode** rootptr, int value) {
	treenode* root = *rootptr;
	if (root == NULL) {
		*rootptr = createNode(value);
		return true;
	}
	if (value == root->value) {
		return false;
	} else if (value < root->value) {
		return insertNumber(&(root->left), value);
	} else {
		return insertNumber(&(root->right), value);
	}
}

bool findNumber(treenode* root, int value) {
	if (root == NULL) return false;
	if (value == root->value)
		return true;
	else if (value < root->value)
		return findNumber(root->left, value);
	else
		return findNumber(root->right, value);
}

int main() {
	treenode* root = NULL;
	int n, val;
	printf("Enter the number of values you want to insert: ");
	scanf("%d", &n);
	printf("Enter the values to insert in tree: ");
	for (int i = 0; i < n; i++) {
		scanf("%d", &val);
		if (!insertNumber(&root, val)) break;
	}
	printtree(root);
	printf("Enter the number you want to find: ");
	scanf("%d", &val);
	if (findNumber(root, val))
		printf("Found\n");
	else
		printf("Not Found\n");
	return 0;
}
