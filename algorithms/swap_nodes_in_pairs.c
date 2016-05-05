/*
 * https://leetcode.com/problems/swap-nodes-in-pairs/
 */

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode * swap_pairs(struct ListNode *head);
void test(int *nums, int len);
struct ListNode * init_list(int *nums, int len);
void free_list(struct ListNode *head);
void print_list(struct ListNode *head);


int
main()
{
    int empty[] = {};
    int nums[] = {1, 2, 3, 4};
    int nums1[] = {1, 2};

    test(empty, 0);
    test(nums, 4);
    test(nums1, 2);

    return 0;
}


struct ListNode *
swap_pairs(struct ListNode *head)
{
    struct ListNode *prev, *next, *pprev, *current;

    pprev = head;
    current = head;
    for (; current != NULL && current->next != NULL;) {
        prev = current;
        current = current->next;
        next = current->next;

        // exchange
        current->next = prev;
        prev->next = next;
        if (head == prev) {
            head = current;
        } else {
            pprev->next = current;
        }
        pprev = prev;
        current = next;
    }

    return head;
}

void
test(int *nums, int len)
{
    struct ListNode *head, *new_head;

    head = init_list(nums, len);
    print_list(head);

    new_head = swap_pairs(head);
    print_list(new_head);

    free_list(new_head);
}

struct ListNode *
init_list(int *nums, int len)
{
    int i;
    struct ListNode *head, *current, *node;

    head = NULL;
    if (len < 1) return head;

    for (i = 0; i < len; ++i) {
        node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->val = nums[i];
        node->next = NULL;

        if (head == NULL) {
            head = node;
            current = head;
        } else {
            current->next = node;
            current = node;
        }
    }

    return head;
}

void
free_list(struct ListNode *head)
{
    struct ListNode *next;

    for (; head != NULL;) {
        next = head->next;
        free(head);
        head = next;
    }
}

void
print_list(struct ListNode *head)
{
    struct ListNode *next;

    next = head;
    for (; next != NULL;) {
        printf("%d ", next->val);
        next = next->next;
    }
    printf("\n");
}
