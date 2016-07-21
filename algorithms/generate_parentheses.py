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


def _check_balance(s):
    balanced = 0
    for c in s:
        if c == '(':
            balanced += 1
        elif c == ')':
            if balanced == 0:
                return False
            balanced -= 1
    return balanced == 0


if __name__ == '__main__':
    print(all(_check_balance(p) for p in Solution().generateParenthesis(0)))
    print(all(_check_balance(p) for p in Solution().generateParenthesis(1)))
    print(all(_check_balance(p) for p in Solution().generateParenthesis(2)))
    print(all(_check_balance(p) for p in Solution().generateParenthesis(3)))
    print(all(_check_balance(p) for p in Solution().generateParenthesis(4)))
    print(all(_check_balance(p) for p in Solution().generateParenthesis(5)))
