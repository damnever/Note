#!/usr/bin/env python
# -*- coding: utf-8 -*-

##
# https://leetcode.com/problems/minimum-depth-of-binary-tree/


class TreeNode(object):

    __slots__ = ['val', 'left', 'right']

    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


def max_depth(root):
    if not root:
        return 0
    return max(max_depth(root.left), max_depth(root.right)) + 1


def min_depth(root):
    if not root:
        return 0
    return dfs(root, 1)

def dfs(node, level):
    if not node:
        return None
    if not node.left and not node.right:
        return level
    level += 1
    lval = dfs(node.left, level)
    rval = dfs(node.right, level)
    if lval and rval:
        return min(lval, rval)
    elif lval:
        return lval
    elif rval:
        return rval


# This solution is borrowed from:
# https://leetcode.com/discuss/42977/easy-reading-12ms-c-solution
def min_depth2(root):
    if not root:
        return 0
    lval = min_depth2(root.left)
    rval = min_depth2(root.right)
    if root.left is None or root.right is None:
        return max(lval, rval) + 1
    return min(lval, rval) + 1


if __name__ == '__main__':
        node1 = TreeNode(3)
        node2 = TreeNode(9)
        node3 = TreeNode(20)
        node4 = TreeNode(15)
        node5 = TreeNode(7)
        node1.left = node2
        node1.right = node3
        node3.left = node4
        node3.right = node5

        print(min_depth(node1))
        print(min_depth2(node1))
        print(max_depth(node1))
        node1.right = None
        print(min_depth(node1))
        print(min_depth2(node1))
        print(max_depth(node1))
