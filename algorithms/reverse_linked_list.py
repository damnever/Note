#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.com/problems/reverse-linked-list/


class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution(object):
    def reverse_list(self, head):
        tail = None
        while head:
            new_head = head
            head = head.next
            new_head.next = tail
            tail = new_head
        return tail

if __name__ == '__main__':
    head = ListNode(1)
    head1 = ListNode(2)
    head2 = ListNode(3)
    head3 = ListNode(4)
    head.next = head1
    head1.next = head2
    head2.next = head3
    new_list = Solution().reverse_list(head)
    while new_list:
        print new_list.val
        new_list = new_list.next
