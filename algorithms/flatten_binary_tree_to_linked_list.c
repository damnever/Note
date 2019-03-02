// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
#include <stdio.h>
#include "../cutils/stack.h"

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void flatten(struct TreeNode *root) {
    if (root == NULL) {
        return;
    }

    Stack *stack = stack_new(sizeof(struct TreeNode *));
    stack_push(stack, &root);
    struct TreeNode *next = NULL;
    struct TreeNode *node;
    for (; !stack_is_empty(stack);) {
        stack_pop(stack, &node);
        if (node->right != NULL) {
            stack_push(stack, &(node->right));
        }
        if (next == NULL) {
            next = node;
        } else {
            next->right = node;
            next = next->right;
        }

        struct TreeNode *prev = node;
        node = prev->left;
        prev->left = NULL;
        for (; node != NULL;) {
            next->right = node;
            next = next->right;
            if (node->right != NULL) {
                stack_push(stack, &(node->right));
            }
            prev = node;
            node = prev->left;
            prev->left = NULL;
        }
    }

    free(stack);
}
