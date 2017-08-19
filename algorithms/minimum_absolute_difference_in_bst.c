// https://leetcode.com/problems/minimum-absolute-difference-in-bst/description/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* fuck me: such an idiot...
    if (n != 0 && list[n-1] > root->val) {
        int j = n - 1;
        for (; j >= 0 && list[j] > root->val; j--) {
            list[j+1] = list[j];
        }
        list[j+1] = root->val;
    } else {
        list[n] = root->val;
    }
*/


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define LEN_MAX 10000
#define abs(n) ({ \
        __typeof__(n) _n = (n); \
        _n > 0 ? _n : -_n; \
    })

int travel(struct TreeNode *root, int *list, int n)
{
    if (root == NULL) {
        return n;
    }
    n = travel(root->left, list, n);
    list[n++] = root->val;
    n = travel(root->right, list, n);
    return n;
}

int getMinimumDifference(struct TreeNode* root)
{
    int list[LEN_MAX] = {0};
    int len = travel(root, list, 0);
    int min = INT_MAX;
    int prev = list[0];
    for (int i = 1; i < len; i++) {
        int v = abs(list[i] - prev);
        prev = list[i];
        if (v < min) {
            min = v;
        }
    }
    return min;
}

int main()
{
    struct TreeNode *tree = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));
    struct TreeNode *left = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));
    struct TreeNode *right = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));
    tree->left = left;
    tree->right = NULL;
    tree->val = 1;
    left->left = NULL;
    left->right = right;
    left->val = 5;
    right->left = NULL;
    right->right = NULL;
    right->val = 3;
    printf("%d\n", getMinimumDifference(tree));
    return 0;
}
