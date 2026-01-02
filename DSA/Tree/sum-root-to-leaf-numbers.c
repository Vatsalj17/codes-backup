#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

int add(struct TreeNode* root, int num, int* sum) {
	if (root == NULL || root->left == NULL || root->right == NULL) {
		if (root != NULL)
			*sum += 10 * num + root->val;
		else
			*sum += num;
		return 0;
	}
	if (root->left != NULL) add(root->left, 10 * num + root->val, sum);
	if (root->right != NULL) add(root->right, 10 * num + root->val, sum);
	return root->val;
}

int sumNumbers(struct TreeNode* root) {
	int sum = 0;
	add(root, 0, &sum);
	return sum;
}
