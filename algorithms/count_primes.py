#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
https://leetcode.com/problems/count-primes/
"""


class Solution(object):

    def count_primes(self, n):
        if n < 3:
            return 0
        bls = [1 for i in xrange(n)]
        bls[0], bls[1] = 0, 0
        for i in xrange(2, n):
            if bls[i]:
                j = 2
                not_prime = i * j
                while not_prime < n:
                    bls[not_prime] = 0
                    j += 1
                    not_prime = i * j
        return sum(bls)

if __name__ == '__main__':
    print Solution().count_primes(1500000)
