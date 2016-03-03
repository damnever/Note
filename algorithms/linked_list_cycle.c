#include <stdio.h>
#include <stdbool.h>

/*
 * https://leetcode.com/problems/linked-list-cycle/
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

bool has_cycle(struct ListNode *head)
{
    struct ListNode *low, *fast;

    if (head == NULL) {
        return false;
    }

    low = head;
    fast = head->next;

    for (;;) {
        if (fast == NULL || fast->next == NULL) {
            return false;
        }
        if (low == fast) {
            return true;
        }
        low = low->next;
        fast = fast->next->next;
    }
}
