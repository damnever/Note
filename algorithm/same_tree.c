#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// https://leetcode.com/problems/same-tree/

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool is_same_tree(struct TreeNode *p, struct TreeNode *q);
void init_tree(struct TreeNode *tree, int val, struct TreeNode *left, struct TreeNode *right);


int main()
{
    struct TreeNode *p = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *q = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *pl = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *pr = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *ql = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode *qr = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    init_tree(pl, 2, NULL, NULL);
    init_tree(pr, 3, NULL, NULL);
    init_tree(ql, 2, NULL, NULL);
    init_tree(qr, 3, NULL, NULL);
    init_tree(p, 1, pl, pr);
    init_tree(q, 1, ql, qr);

    printf("%d\n", is_same_tree(NULL, NULL));
    printf("%d\n", is_same_tree(p, q));
    printf("%d\n", is_same_tree(p, NULL));

    free(pl); free(pr); free(ql); free(qr); free(p); free(q);
    return 0;
}

bool is_same_tree(struct TreeNode *p, struct TreeNode *q)
{
    if (NULL == p && NULL == q) {
        return true;
    } else if ((NULL == p && NULL != q) || (NULL != p && NULL == q)) {
        return false;
    } else if (p->val != q->val) {
        return false;
    }
    return is_same_tree(p->left, q->left) && is_same_tree(p->right, q->right);
}

void init_tree(struct TreeNode *tree, int val, struct TreeNode *left, struct TreeNode *right)
{
    tree->val = val;
    tree->left = left;
    tree->right = right;
}
