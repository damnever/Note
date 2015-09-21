#!/usr/bin/env python
# -*- coding: utf-8 -*-


def merge_sort(nums):
    length = len(nums)
    if length < 2:
        return nums

    def _merge(left, right):
        merged = []
        while left and right:
            merged.append(left.pop(0) if left[0] <= right[0] else right.pop(0))
        while left:
            merged.append(left.pop(0))
        while right:
            merged.append(right.pop(0))
        return merged

    mid = length // 2
    left = merge_sort(nums[:mid])
    right = merge_sort(nums[mid:])
    return _merge(left, right)


if __name__ == '__main__':
    import random
    nums = range(20)
    random.shuffle(nums)
    print nums
    print merge_sort(nums)
