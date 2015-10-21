#include <stdio.h>

/*
 * https://leetcode.com/problems/remove-linked-list-elements/
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode*
remove_elements(struct ListNode *head, int val)
{
    struct ListNode *prev, *current;

    prev = head;
    current = head;

    while (NULL != current) {
        if (val != current->val) {
            prev = current;
            current = current->next;
        } else {
            if (head == current) {
                head = head->next;
                current = head;
                prev = head;
            } else {
                prev->next = current->next;
                current = current->next;
            }
        }
    }

    return head;
}
