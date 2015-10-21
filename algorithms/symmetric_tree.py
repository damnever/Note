#!/usr/bin/env python
# -*- coding: utf-8 -*-


class TreeNode(object):

    __slots__ = ['val', 'left', 'right']

    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


def is_symmetric(root):
    if root is None:
        return True
    stack = [root.left, root.right]
    top = 2
    while top:
        right = stack.pop()
        left = stack.pop()
        top -= 2
        if left is None and right is None:
            continue
        elif left is None or right is None:
            return False
        if left.val != right.val:
            return False
        stack.extend([left.right, right.left, left.left, right.right])
        top += 4
    return True

if __name__ == '__main__':
    node1 = TreeNode(1)
    node2 = TreeNode(2)
    node3 = TreeNode(2)
    node4 = TreeNode(3)
    node5 = TreeNode(3)
    node1.left = node2
    node1.right = node3
    node2.left = node4
    node3.left = node5

    print(is_symmetric(node1))
    node3.left = None
    node3.right = node5
    print(is_symmetric(node1))
