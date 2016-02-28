#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
 * https://leetcode.com/problems/palindrome-linked-list/
 */

#define arr_len(arr) ((int)(sizeof(arr) / sizeof(*arr)))

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *create_list(int *nums, int len);
bool is_palindrome(struct ListNode *head);


int main()
{
    struct ListNode *head = NULL;
    int nums[] = {1, 2};
    int nums1[] = {1, 1};
    int nums2[] = {1, 6, 4, 6, 1};

    head = create_list(nums, arr_len(nums));
    printf("%s\n", is_palindrome(head) ? "true" : "false");
    free(head);
    head = NULL;

    head = create_list(nums1, arr_len(nums1));
    printf("%s\n", is_palindrome(head) ? "true" : "false");
    free(head);
    head = NULL;

    head = create_list(nums2, arr_len(nums2));
    printf("%s\n", is_palindrome(head) ? "true" : "false");
    free(head);
    head = NULL;

    return 0;
}

struct ListNode *create_list(int *nums, int len)
{
    int i;
    struct ListNode *head, *node, *tmp_head;

    head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = nums[0];
    head->next = NULL;
    tmp_head = head;

    for (i = 1; i < len; ++i) {
        node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->val = nums[i];
        node->next = NULL;
        tmp_head->next = node;
        tmp_head = tmp_head->next;
    }

    return head;
}

bool is_palindrome(struct ListNode *head)
{
    struct ListNode *mid, *end, *tmp_head, *left, *right, *tail;

    if (head == NULL) {
        return true;
    }

    // Find the middle of the linked list.
    mid = head;
    right = head;
    end = head;
    for (; end != NULL && end->next != NULL;) {
        mid = right;
        right = right->next;
        end = end->next->next;
    }

    if (right == end) {
        return true;
    }

    // Reverse the left side of linked list;
    // BIG HOLE AT HERE...
    tmp_head = head;
    left = NULL;
    tail = NULL;
    for (;left != mid;) {
        left = tmp_head;
        tmp_head = tmp_head->next;
        left->next = tail;
        tail = left;
    }

    // Compare.
    if (end != NULL) {
        right = right->next;
    }
    for (; right != NULL; right = right->next, left = left->next) {
        if (left == NULL || right->val != left->val) {
            return false;
        }
    }

    return (left == NULL);
}
