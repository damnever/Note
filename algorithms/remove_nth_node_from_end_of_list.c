#include <stdio.h>
#include <stdlib.h>

/*
 * https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 */

// Why not use typedef??????????????????????????????????????????
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *remove_nth_from_end(struct ListNode *head, int n)
{
    int i = 0, size = 0;
    struct ListNode *prev = NULL, *cur = head;

    while(NULL != cur){
        cur = cur->next;
        size++;
    }
    n = size - n;

    cur = head;
    while(i < n && NULL != cur){
        prev = cur;
        cur = cur->next;
        i++;
    }

    if(NULL == prev){
        head = cur->next;
        cur->next = NULL;
    }else{
        prev->next = cur->next;
        cur->next = NULL;
    }
    return head;
}

void print_linkedlist(struct ListNode *head)
{
    while(NULL != head){
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    // unnormal linkedlist
    struct ListNode *head = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *node1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *node2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *node3 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *node4 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *new_head = NULL;

    head->val = 1;
    head->next = node1;
    node1->val = 2;
    node1->next = node2;
    node2->val = 3;
    node2->next = node3;
    node3->val = 4;
    node3->next = node4;
    node4->val = 5;
    node4->next = NULL;

    print_linkedlist(head);
    new_head = remove_nth_from_end(head, 2);
    print_linkedlist(new_head);
    node1->next = NULL;
    print_linkedlist(head);
    new_head = remove_nth_from_end(head, 2);
    print_linkedlist(new_head);

    free(head); free(node1); free(node2); free(node3); free(node4);
    return 0;
}
