#include <stdio.h>
#include <stdlib.h>

// https://leetcode.com/problems/invert-binary-tree/

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode * invert_tree(struct TreeNode *root);
void print_inorder_tree(struct TreeNode *root);


int main()
{
    struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = 1;
    left->val = 2;
    right->val = 3;
    root->left = left;
    root->right = right;
    left->left = NULL;
    left->right = NULL;
    right->left = NULL;
    right->right = NULL;

    print_inorder_tree(root);
    printf("\n");
    print_inorder_tree(invert_tree(root));
    printf("\n");

    free(left);
    free(right);
    free(root);
    left = NULL;
    right = NULL;
    root = NULL;
    return 0;
}

struct TreeNode * invert_tree(struct TreeNode *root)
{
    struct TreeNode *tmp_node;

    if(NULL == root) return root;

    tmp_node = root->left;
    root->left = root->right;
    root->right = tmp_node;

    invert_tree(root->left);
    invert_tree(root->right);

    return root;
}

void print_inorder_tree(struct TreeNode *root)
{
    if(NULL == root) return;
    print_inorder_tree(root->left);
    printf("%d ", root->val);
    print_inorder_tree(root->right);
}
