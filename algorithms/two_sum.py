#!/usr/bin/env python
# -*- coding: utf-8 -*-


class Solution(object):

    def two_sum(self, nums, target):
        ht = dict()
        for index, num in enumerate(nums):
            if num not in ht:
                ht[target - num] = index + 1
            else:
                return ht[num], index + 1 # ht[num] == index(target - num])

if __name__ == '__main__':
    nums = [2, 7, 11, 15]
    print Solution().two_sum(nums, 9)
