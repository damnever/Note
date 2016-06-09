/*
 * https://leetcode.com/problems/binary-search-tree-iterator/
 *
 * Your BSTIterator will be called like this:
 * struct BSTIterator *i = bstIteratorCreate(root);
 * while (bstIteratorHasNext(i)) printf("%d\n", bstIteratorNext(i));
 * bstIteratorFree(i);
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Stack {
    struct TreeNode **nodes;
    int size;
    int capacity;
};

struct BSTIterator {
    struct Stack *stack;
};

struct BSTIterator *bstIteratorCreate(struct TreeNode *root);
bool bstIteratorHasNext(struct BSTIterator *iter);
int bstIteratorNext(struct BSTIterator *iter);
void bstIteratorFree(struct BSTIterator *iter);

struct Stack *stackCreate(int cap);
bool stackIsEmpty(struct Stack *stack);
void stackPush(struct Stack *stack, struct TreeNode *node);
struct TreeNode *stackPop(struct Stack *stack);
void stackFree(struct Stack *stack);

struct TreeNode * treeCreate(int *nums, int len);
struct TreeNode * treeInsert(struct TreeNode *node, int num);
struct TreeNode *treeNodeCreate(int num);
void treePrint(struct TreeNode *tree);


void test(int *nums, int len)
{
    struct TreeNode *tree = treeCreate(nums, len);
    treePrint(tree);
    printf("--\n");

    struct BSTIterator *iter = bstIteratorCreate(tree);
    while (bstIteratorHasNext(iter)) {
        printf("%d\n", bstIteratorNext(iter));
    }
    bstIteratorFree(iter);
}

int main() {
    int nums1[8] = {2, 4, 16, 1, 0, 8, 4, 3};
    int nums2[] = {};
    int nums3[6] = {9, 8, 7, 4, 5, 6};
    test(nums1, 8);
    printf("*****\n");
    test(nums2, 0);
    printf("*****\n");
    test(nums3, 6);

    return 0;
}

struct BSTIterator *bstIteratorCreate(struct TreeNode *root)
{
    struct TreeNode *node;
    struct BSTIterator *iter;

    if (root == NULL) return NULL;

    iter = (struct BSTIterator*)malloc(sizeof(struct BSTIterator));
    iter->stack = stackCreate(10);
    node = root;
    while (node != NULL) {
        stackPush(iter->stack, node);
        node = node->left;
    }
    return iter;
}

/** @return whether we have a next smallest number */
bool bstIteratorHasNext(struct BSTIterator *iter)
{
    if (iter == NULL) return false;
    return !stackIsEmpty(iter->stack);
}

/** @return the next smallest number */
int bstIteratorNext(struct BSTIterator *iter)
{
    struct TreeNode *tmp, *node;

    node = stackPop(iter->stack);
    tmp = node->right;
    while (tmp != NULL) {
        stackPush(iter->stack, tmp);
        tmp = tmp->left;
    }

    return node->val;
}

/** Deallocates memory previously allocated for the iterator */
void bstIteratorFree(struct BSTIterator *iter)
{
    if (iter == NULL) return;
    stackFree(iter->stack);
    free(iter);
    iter = NULL;
}

/** Stack **/
struct Stack *stackCreate(int cap)
{
    struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = cap;
    stack->size = 0;
    stack->nodes = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * cap);
    return stack;
}

bool stackIsEmpty(struct Stack *stack)
{
    if (stack == NULL) return true;
    return (stack->size == 0);
}

void stackPush(struct Stack *stack, struct TreeNode *node)
{
    if (stack->size >= stack->capacity) {
        stack->capacity *= 2;
        stack->nodes = (struct TreeNode **)realloc(stack->nodes, stack->capacity * sizeof(struct TreeNode*));
    }
    stack->nodes[stack->size++] = node;
}

struct TreeNode *stackPop(struct Stack *stack)
{
    if (stack->size == 0) {
        return NULL;
    }
    return stack->nodes[--stack->size];
}

void stackFree(struct Stack *stack)
{
    if (stack == NULL) return;
    free(stack->nodes);
    free(stack);
    stack = NULL;
}

/** Help functions **/
void treePrint(struct TreeNode *tree)
{
    if (tree == NULL) return;
    if (tree->left != NULL) treePrint(tree->left);
    printf("%d\n", tree->val);
    if (tree->right != NULL) treePrint(tree->right);
}

struct TreeNode * treeCreate(int *nums, int len)
{
    int idx;
    struct TreeNode *tree;

    tree = NULL;
    for (idx = 0; idx < len; ++idx) {
        tree = treeInsert(tree, nums[idx]);
    }
    return tree;
}

struct TreeNode * treeInsert(struct TreeNode *node, int num)
{
    if (node == NULL) {
        return treeNodeCreate(num);
    } else {
        if (num <= node->val) {
            node->left = treeInsert(node->left, num);
        } else {
            node->right = treeInsert(node->right, num);
        }
        return node;
    }
}

struct TreeNode *treeNodeCreate(int num)
{
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = num;
    node->left = NULL;
    node->right = NULL;
    return node;
}
