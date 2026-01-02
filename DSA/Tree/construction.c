#include "../Hash/hash_map.h"
#include "bt.h"

typedef treenode* (*construct) (int*, int, int, int*, int, int, map_t*);

treenode* from_inorder_preorder(int* preorder, int preStart, int preEnd, int* inorder, int inStart, int inEnd, map_t* inMap) {
	if (preStart > preEnd || inStart > inEnd) return NULL;
	treenode* root = tree_node_init(preorder[preStart]);
	int inRoot = map_lookup(inMap, root->value);
	int nums_left = inRoot - inStart;
	root->left = from_inorder_preorder(preorder, preStart + 1, preStart + nums_left, inorder, inStart, inRoot - 1, inMap);
	root->right = from_inorder_preorder(preorder, preStart + nums_left + 1, preEnd, inorder, inRoot + 1, inEnd, inMap);
	return root;
}

treenode* from_inorder_postorder(int* postorder, int postStart, int postEnd, int* inorder, int inStart, int inEnd, map_t* inMap) {
	if (postStart > postEnd || inStart > inEnd) return NULL;
	treenode* root = tree_node_init(postorder[postEnd]);
	int inRoot = map_lookup(inMap, root->value);
	int nums_left = inRoot - inStart;
	root->left = from_inorder_postorder(postorder, postStart, postStart + nums_left - 1, inorder, inStart, inRoot - 1, inMap);
	root->right = from_inorder_postorder(postorder, postStart + nums_left, postEnd - 1, inorder, inRoot + 1, inEnd, inMap);
	return root;
}

treenode* buildTree(int* inorder, int inorderSize, int* post_pre_order, int post_pre_orderSize, construct func) {
	map_t* inMap = map_init(2 * post_pre_orderSize);
	for (int i = 0; i < inorderSize; i++) map_insert(inMap, inorder[i], i);
	treenode* root = func(post_pre_order, 0, post_pre_orderSize - 1, inorder, 0, inorderSize - 1, inMap);
	map_destroy(inMap);
	return root;
}

int main(void) {
	int preorder[5] = {3, 9, 20, 15, 7};
	int inorder[5] = {9, 3, 15, 20, 7};
	int postorder[5] = {9, 15, 7, 20, 3};
	// int preorder[2] = {3, 9};
	// int inorder[2] = {9, 3};
	// int preorder[3] = {1, 2, 3};
	// int inorder[3] = {3, 2, 1};
	treenode* root = buildTree(inorder, sizeof(inorder) / sizeof(inorder[0]), postorder, sizeof(postorder) / sizeof(postorder[0]), from_inorder_postorder);
	treenode* root2 = buildTree(inorder, sizeof(inorder) / sizeof(inorder[0]), preorder, sizeof(preorder) / sizeof(preorder[0]), from_inorder_preorder);
	printtree(root);
	printtree(root2);
	destroytree(root);
	destroytree(root2);
}
