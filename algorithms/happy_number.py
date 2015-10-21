#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
https://leetcode.com/problems/happy-number/
"""


class Solution(object):

    def is_happy(self, n):
        if n < 1:
            return False
        ready = {str(k): k**2 for k in xrange(10)}
        ht = set()
        n = str(n)
        while n != '1':
            if n in ht:
                return False
            ht.add(n)
            n = str(sum([ready[ch] for ch in n]))
        return True


if __name__ == '__main__':
    print Solution().is_happy(1)
    print Solution().is_happy(7)
    print Solution().is_happy(11)
    print Solution().is_happy(19)
