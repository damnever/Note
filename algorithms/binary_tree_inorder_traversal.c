/*
 * https://leetcode.com/problems/binary-tree-inorder-traversal/
 */

#include <stdio.h>
#include <stdlib.h>
#include "../cutils/stack.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int * inorderTraversal(struct TreeNode *root, int *returnSize)
{
    int idx, *list = (int *)malloc(sizeof(int) * 256); /* ~~, implement a list? */
    struct TreeNode *node;
    Stack *stack = stack_new(sizeof(struct TreeNode *));

    idx = 0;
    node = root;
    while (node != NULL) {
        stack_push(stack, &node);
        node = node->left;
    }
    while (!stack_is_empty(stack)) {
        stack_pop(stack, &node);
        list[idx++] = node->val;
        node = node->right;
        while (node != NULL) {
            stack_push(stack, &node);
            node = node->left;
        }
    }
    stack_free(stack);

    *returnSize = idx;
    return list;
}
