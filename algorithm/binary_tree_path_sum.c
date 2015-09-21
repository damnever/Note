#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// https://leetcode.com/problems/path-sum/
//

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool has_path_sum(struct TreeNode *root, int sum);


int main()
{

    struct TreeNode *node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *node1 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *node2 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *node3 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *node4 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *node5 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = 5;
    node->left = node1;
    node->right = node2;
    node1->val = 4;
    node1->left = node3;
    node1->right = NULL;
    node2->val = 7;
    node2->left = node4;
    node2->right = node5;
    node3->val = 5;
    node3->left = NULL;
    node3->right = NULL;
    node4->val = 1;
    node4->left = NULL;
    node4->right = NULL;
    node5->val = 2;
    node5->left = NULL;
    node5->right = NULL;

    printf("%d\n", has_path_sum(node, 14));
    printf("%d\n", has_path_sum(node, 13));
    printf("%d\n", has_path_sum(node, 20));

    free(node); free(node1); free(node2); free(node3); free(node4); free(node5);
    return 0;
}

bool has_path_sum(struct TreeNode *root, int sum)
{
    if (NULL == root)  // only root trigger this
        return false;
    sum -= root->val;
    if (0 == sum && NULL == root->left && NULL == root->right)
        return true;
    return has_path_sum(root->left, sum) || has_path_sum(root->right, sum);
}
