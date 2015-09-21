#!/usr/bin/env python
# -*- coding: utf-8 -*-


def insertion_sort(nums):
    if not nums:
        return
    length = len(nums)
    if length < 2:
        return

    for i in range(1, length):
        j = i - 1
        value = nums[i]
        while value < nums[j] and j >= 0:
            nums[j+1] = nums[j]
            j -= 1
        if j < i-1:
            nums[j+1] = value

if __name__ == '__main__':
    nums = [2, 9, 1, 5, 4, 3, 10, 8]
    insertion_sort(nums)
    print nums
