#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# https://leetcode.com/problems/generate-parentheses/

class Solution(object):
    def generateParenthesis(self, num):
        if num <= 1:
            return ['()' * num]

        parentheses = set()
        for each in self.generateParenthesis(num - 1):
            for i in range(1, len(each)):
                parentheses.add(each[:i] + '()' + each[i:])
            parentheses.add('()' + each)
            parentheses.add(each + '()')
        return list(parentheses)


if __name__ == '__main__':
    print Solution().generateParenthesis(0)
    print Solution().generateParenthesis(1)
    print Solution().generateParenthesis(2)
    print Solution().generateParenthesis(3)
    print Solution().generateParenthesis(4)
    print Solution().generateParenthesis(5)
