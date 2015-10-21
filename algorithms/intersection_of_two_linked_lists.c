#include <stdio.h>

/*
 * https://leetcode.com/problems/intersection-of-two-linked-lists/
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *
getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
    struct ListNode *nodeA, *nodeB;
    int lenA = 0, lenB = 0, gap;
    if(NULL == headA && NULL == headB) {
        return NULL;
    }
    nodeA = headA;
    nodeB = headB;

    while(NULL != nodeA){
        lenA++;
        nodeA = nodeA->next;
    }
    while(NULL != nodeB){
        lenB++;
        nodeB = nodeB->next;
    }

    nodeA = headA;
    nodeB = headB;
    if(lenA > lenB) {
        gap = lenA - lenB;
        while((gap--) > 0 && NULL != nodeA) {
            nodeA = nodeA->next;
        }
    } else if (lenA < lenB) {
        gap = lenB - lenA;
        while((gap--) > 0 && NULL != nodeB) {
            nodeB = nodeB->next;
        }
    }
    if(NULL == nodeA || NULL == nodeB) return NULL;
    while(nodeA != nodeB) {
        nodeA = nodeA->next;
        nodeB = nodeB->next;
        if(NULL == nodeA || NULL == nodeB) return NULL;
    }
    return nodeA;
}
