# -*- coding: utf-8 -*-

# https://leetcode.com/problems/binary-tree-paths/
#
# Use Generator.


class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution(object):

    def binaryTreePaths(self, root):
        if root is None:
            return []
        return list(self.getPath(root))

    def getPath(self, root, path=None):
        if path is None:
            path = list()
        path.append(root.val)
        if root.left is None and root.right is None:
            yield '->'.join([str(num) for num in path])
        else:
            if root.left:
                for item in self.getPath(root.left, path):
                    yield item
                path.pop()
            if root.right:
                for item in self.getPath(root.right, path):
                    yield item
                path.pop()


if __name__ == '__main__':
    root = TreeNode(1)
    node1 = TreeNode(2)
    node2 = TreeNode(3)
    node3 = TreeNode(5)
    root.left = node1
    root.right = node2
    node1.right = node3

    print(Solution().binaryTreePaths(root))
