// https://leetcode.com/problems/sum-of-left-leaves/description/

#include <stdio.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int travelAndSum(struct TreeNode* node, bool isleft)
{
    if (node == NULL) return 0;
    if (node->left == NULL && node->right == NULL) {
        if (isleft) {
            return node->val;
        }
        return 0;
    }
    return travelAndSum(node->left, true) + travelAndSum(node->right, false);
}

int sumOfLeftLeaves(struct TreeNode* root)
{
    return travelAndSum(root, false);
}
