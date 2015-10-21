#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.com/problems/reverse-integer/


class Solution(object):

    def reverse(self, x):
        maxint = pow(2, 31) / 10
        sign = 1
        if x < 0:
            sign = -1
            x = -x
        result = 0
        while x:
            if result > maxint or result < -1 * maxint:
                return 0
            x, mod = divmod(x, 10)
            result *= 10
            result += mod
        return result * sign


if __name__ == '__main__':
    print Solution().reverse(-123)
