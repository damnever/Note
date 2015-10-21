#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.com/problems/contains-duplicate-ii/


def contain_nearby_duplicate(nums, k):
    ht = dict()
    for idx, num in enumerate(nums):
        if num in ht and idx - ht[num] <= k:
            return True
        else:
            ht[num] = idx
    return False


if __name__ == '__main__':
    print(contain_nearby_duplicate([1, 1], 1))
    print(contain_nearby_duplicate([1, 2, 3, 4, 1], 6))
    print(contain_nearby_duplicate([1, 2, 3, 4, 1], 3))
