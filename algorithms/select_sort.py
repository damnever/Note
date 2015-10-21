#!/usr/bin/env python
# -*- coding: utf-8 -*-


def selection_sort(nums):
    if not nums:
        return nums
    length = len(nums)
    if nums < 2:
        return nums

    for l in range(length-1, 0, -1):
        max_idx = 0
        for i in range(1, l+1):
            if nums[i] > nums[max_idx]:
                max_idx = i
        nums[l], nums[max_idx] = nums[max_idx], nums[l]


if __name__ == '__main__':
    nums = [2, 5, 8, 10, 3, 8, 9, 4]
    selection_sort(nums)
    print nums
