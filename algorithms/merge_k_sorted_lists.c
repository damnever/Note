#include <stdio.h>
#include <stdlib.h>

/*
 * https://leetcode.com/problems/merge-k-sorted-lists/
 *
 * THOUGHT:
 *   binary search? skiplist...
 */

struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    struct ListNode *rlist = NULL;

    while (1) {
        int c = 0;
        struct ListNode *node;

        for (int i = 0; i < listsSize; i++) {
            node = lists[i];
            if (node == NULL) {
                continue;
            }
            c += 1;
            lists[i] = node->next;
            node->next = NULL;

            if (rlist == NULL) {
                rlist = node;
                continue;
            }

            // insert ...
            struct ListNode *prev, *next;
            for (prev = next = rlist;
                    next && node->val <= next->val;
                    prev = next, next = next->next)
                ;
            if (prev == next) {
                rlist = node;
                rlist->next = prev;
            } else if (next == NULL) {
                prev->next = node;
            } else {
                prev->next = node;
                node->next = next;
            }
        }

        if (c == 0) {
            break;
        }
    }

    // reverse ...
    struct ListNode *list, *head, *node;
    list = NULL;
    head = rlist;
    while (head) {
        node = head;
        head = head->next;
        node->next = list;
        list = node;
    }

    return list;
}

void initlist(struct ListNode ***lists, int (*nums)[5], int len, int *lens)
{
    *lists = (struct ListNode**)malloc(sizeof(struct ListNode*) * len);

    for (int i = 0; i < len; i++) {
        struct ListNode *head = (struct ListNode*)malloc(sizeof(struct ListNode));
        int *start = *(nums + i);
        head->next = NULL;
        head->val = *start;
        (*lists)[i] = head;

        for (int j = 1; j < lens[i]; j++) {
            struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
            node->next = NULL;
            node->val = *(start + j);
            head->next = node;
            head = head->next;
        }
    }
}

void printlist(struct ListNode *list)
{
    struct ListNode *head = list;
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    struct ListNode **lists = NULL, *list = NULL;
    int nums[][5] = {
        {2, 5, 6, 9, 22},
        {1, 10, 33},
        {3, 7, 23},
        {4, 8, 12, 20},
    };

    int lens[] = {5, 3, 3, 4};
    initlist(&lists, nums, 4, lens);

    list = mergeKLists(lists, 4);
    printlist(list);

    return 0;
}
