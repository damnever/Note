#!/usr/bin/env python
# -*- coding: utf-8 -*-


def bubble_sort(nums):
    length = len(nums)
    if not nums or length < 2:
        return nums

    length -= 1
    while length > 0:
        for i in range(length):
            if nums[i] > nums[i+1]:
                nums[i], nums[i+1] = nums[i+1], nums[i]
        length -= 1


if __name__ == '__main__':
    nums = [2, 8, 10, 6, 4, 9]
    bubble_sort(nums)
    print nums
