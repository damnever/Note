// https://leetcode.com/problems/validate-binary-search-tree/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../cutils/stack.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isValidBST(struct TreeNode *root) {
    if (root == NULL) {
        return true;
    }

    Stack *stack = stack_new(sizeof(struct TreeNode *));
    stack_push(stack, &root);
    int prev;
    bool hasprev = false;
    for (; !stack_is_empty(stack);) {
        struct TreeNode *node;
        stack_peek(stack, &node);
        for (node = node->left; node != NULL; node = node->left) {
            stack_push(stack, &node);
        }

        for (; !stack_is_empty(stack);) {
            stack_pop(stack, &node);
            if (hasprev && node->val <= prev) {
                stack_free(stack);
                return false;
            }
            prev = node->val;
            hasprev = true;

            if (node->right != NULL) {
                stack_push(stack, &(node->right));
                break;
            }
        }
    }

    stack_free(stack);
    return true;
}

int main(int argc, const char *argv[]) {
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    struct TreeNode *node1 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    struct TreeNode *node2 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = 2;
    node->left = node1;
    node->right = node2;
    node1->val = 1;
    node1->left = NULL;
    node1->right = NULL;
    node2->val = 3;
    node2->left = NULL;
    node2->right = NULL;

    printf("%s\n", isValidBST(node) ? "true" : "false");

    free(node1);
    free(node2);
    free(node);
    return 0;
}
