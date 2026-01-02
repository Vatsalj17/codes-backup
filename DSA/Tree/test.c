#include "bst.h"
#include <stdio.h>

int main() {
	treenode* root = NULL;
	int n, val;
	printf("Enter the number of vals you want to insert: ");
	scanf("%d", &n);
	printf("Enter the vals to insert in tree: ");
	for (int i = 0; i < n; i++) {
		scanf("%d", &val);
		if (!bst_insert_node(&root, val)) break;
	}
	printtree(root);
	printf("Enter the number you want to find: ");
	scanf("%d", &val);
	if (in_bst(root, val))
		printf("Found\n");
	else
		printf("Not Found\n");
	printf("Enter the number you want to delete: ");
	scanf("%d", &val);
	if (bst_delete_node(&root, val))
		printf("Deleted\n");
	else
		printf("Not Deleted\n");
	printtree(root);
	return 0;
}
