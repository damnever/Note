#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
https://leetcode.com/problems/isomorphic-strings/

54ms cool!
"""


class Solution(object):
    def is_isomorophic(self, s, t):
        if len(s) != len(t):
            return False
        ht = dict()
        for index, ch in enumerate(s):
            if ch in ht:
                if ht[ch] != t[index]:
                    return False
            else:
                if t[index] in t[:index]:
                    return False
                ht[ch] = t[index]
        return True


if __name__ == '__main__':
    slt = Solution()
    print slt.is_isomorophic('add', 'egg')
    print slt.is_isomorophic('foo', 'bar')
    print slt.is_isomorophic('paper', 'title')
