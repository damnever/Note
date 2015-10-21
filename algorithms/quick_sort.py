#!/usr/bin/env python
# -*- coding: utf-8 -*-


def quick_sort(nums, start, end):
    if start > end:
        return
    pos = partition(nums, start, end)
    quick_sort(nums, start, pos-1)
    quick_sort(nums, pos+1, end)


def partition(nums, left, right):
    pivot = nums[left]
    start = left
    left += 1
    while 1:
        while left <= right and nums[left] <= pivot:
            left += 1
        while left <= right and nums[right] > pivot:
            right -= 1
        if left > right:
            break
        else:
            nums[left], nums[right] = nums[right], nums[left]
    nums[start], nums[right] = nums[right], nums[start]
    return right


if __name__ == '__main__':
    import random
    nums = range(20)
    random.shuffle(nums)
    print nums
    quick_sort(nums, 0, len(nums) - 1)
    print nums
