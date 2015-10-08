#include <stdio.h>

/*
 * https://leetcode.com/problems/remove-duplicates-from-sorted-list/
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode*
delete_duplicates(struct ListNode *head)
{
    struct ListNode *start, *end;

    start = head;
    while (NULL != start) {
        end = start->next;
        while (NULL != end && end->val == start->val) {
            end = end->next;
        }
        if (end != start->next) {
            start->next = end;
        }
        start = end;
    }

    return head;
}
