#include <stdio.h>
#include <stdlib.h>

/*
 * https://leetcode.com/problems/merge-two-sorted-lists/
 */

#define arr_len(arr) ((int)(sizeof(arr) / sizeof(*arr)))

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* merge_two_lists(struct ListNode *l1, struct ListNode *l2)
{
    struct ListNode *head = NULL, *node = NULL, *tmp = NULL;
    struct ListNode *merged = NULL;

    if (NULL != l1 && NULL != l2) {
        if (l1->val < l2->val) {
            merged = l1;
            l1 = l1->next;
        } else {
            merged = l2;
            l2 = l2->next;
        }
        merged->next = NULL;
    } else if (NULL != l1) {
        return l1;
    } else if (NULL != l2) {
        return l2;
    }
    head = merged;

    while (NULL != l1 && NULL != l2) {
        if (l1->val < l2->val) {
            node = l1;
            l1 = l1->next;
        } else {
            node = l2;
            l2 = l2->next;
        }
        node->next = NULL;
        head->next = node;
        head = head->next;
    }

    if (NULL != l1) {
        tmp = l1;
    } else if (NULL != l2) {
        tmp = l2;
    }
    if (NULL != tmp) {
        head->next = tmp;
    }

    return merged;
}

void
init_list(struct ListNode **head, int *nums, int len)
{
    int i;
    struct ListNode *node = NULL, *next = NULL;

    *head = (struct ListNode*)malloc(sizeof(struct ListNode));
    next = *head;
    next->val = nums[0];
    next->next = NULL;
    for (i = 1; i < len; i++) {
        node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->val = nums[i];
        next->next = node;
        node->next = NULL;
        next = node;
    }
}

void
print_list(struct ListNode *head)
{
    while (NULL != head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int
main()
{
    struct ListNode *l1, *l2;
    struct ListNode *merged = NULL;
    int nums1[] = {-10, -9, -6, -4, 1, 9};
    int nums2[] = {-5, -3, 0, 7, 8, 8};
    int len1 = arr_len(nums1);
    int len2 = arr_len(nums2);


    init_list(&l1, nums1, len1);
    init_list(&l2, nums2, len2);
    print_list(l1);
    print_list(l2);

    merged = merge_two_lists(l1, l2);

    print_list(merged);
    free(l1);
    free(l2);

    return 0;
}
