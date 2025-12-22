#include <stdio.h>
#include <stdlib.h>

#include "../library/src/queue.h"
#include "../library/src/stack.h"
#include "bt.h"

typedef void (*traversal)(treenode*, int*, int*);

void preorder(treenode* root, int* pre, int* i) {
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

void preorder_itr(treenode* root, int* pre, int* i) {
	if (root == NULL) {
		return;
	}
	stack_t* s = stack_init(10, sizeof(treenode*));
	push(s, &root);
	while (!stack_empty(s)) {
		root = *(treenode**)stack_top(s);
		pop(s);
		pre[(*i)++] = root->value;
		if (root->right != NULL) push(s, &root->right);
		if (root->left != NULL) push(s, &root->left);
	}
	stack_destroy(s);
}

void inorder_itr(treenode* root, int* pre, int* i) {
    if (root == NULL) {
        return;
    }
    printf("got here");
    stack_t* s = stack_init(10, sizeof(treenode*));
    push(s, &root);
    while (!stack_empty(s)) {
        root = *(treenode**)stack_top(s);
        if (root->left != NULL)
            push(s, &root->left);
        else {
            push(s, &root->right);
            root = *(treenode**)stack_top(s);
            pop(s);
            pre[(*i)++] = root->value;
        }
    }
    stack_destroy(s);
}

int* dfs_traverse(treenode* root, int* return_size, traversal fun) {
	int* result = malloc(1024 * sizeof(int));
	int i = 0;
	fun(root, result, &i);
	*return_size = i;
	return result;
}

#define MAX 2000

int** bfs(treenode* root, int* return_size, int** returnCols_size) {
	int** result = malloc(MAX * sizeof(int*));
	if (result == NULL) {
		perror("malloc");
		return NULL;
	}
	*return_size = 0;
	int* cols = calloc(MAX, sizeof(int));

	if (root == NULL) {
		*returnCols_size = cols;
		return result;
	}

	int lvl = 0;
	queue_t* q = queue_init(MAX, sizeof(treenode*));
	enqueue(q, &root);
	while (!queue_empty(q)) {
		int num = queue_size(q);
		result[lvl] = malloc(num * sizeof(int));
		cols[lvl] = num;
		for (int i = 0; i < num; i++) {
			treenode* current = *(treenode**)queue_front(q);
			dequeue(q);
			if (current->left != NULL) {
				enqueue(q, &current->left);
			}
			if (current->right != NULL) {
				enqueue(q, &current->right);
			}
			result[lvl][i] = current->value;
		}
		lvl++;
	}
	queue_destroy(q);
	*return_size = lvl;
	cols = realloc(cols, lvl * sizeof(int));
	*returnCols_size = cols;
	result = realloc(result, lvl * sizeof(int*));
	return result;
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
	arr = dfs_traverse(n1, &n, inorder_itr);
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

	printf("\nBFS: \n");
	int rows, *cols;
	int** sol = bfs(n1, &rows, &cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols[i]; j++) {
			printf("%d ", sol[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < rows; i++) free(sol[i]);
	free(sol);

	destroytree(n1);
}
