//
// https://leetcode.com/problems/reverse-linked-list/
//

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode * next;
};

struct ListNode* reverseList(struct ListNode * head);

int main()
{
    struct ListNode *head = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *head1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *head2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *new_head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = 1;
    head->next = head1;
    head1->val = 2;
    head1->next = head2;
    head2->val = 3;
    head2->next = NULL;
    new_head = reverseList(head);
    while(new_head){
        printf("%d ", new_head->val);
        new_head = new_head->next;
    }
    return 0;
}

struct ListNode* reverseList(struct ListNode * head)
{
    struct ListNode* tail = NULL;
    struct ListNode* new_head = NULL;
    while(head){
        new_head = head;
        head = head->next;
        new_head->next = tail;
        tail = new_head;
    }
    tail = NULL;
    return new_head;
}
