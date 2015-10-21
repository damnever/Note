#!/usr/bin/env python
# -*- coding: utf-8 -*-


def counting_sort(nums):
    max_num = max(nums)
    cnums = [0 for i in range(max_num)]  # [0] * max_num

    for num in nums:
        cnums[num - 1] += 1

    index = 0
    for idx, num in enumerate(cnums):
        while num > 0:
            nums[index] = idx + 1
            index += 1
            num -= 1


if __name__ == '__main__':
    import random
    nums = range(1, 21)
    random.shuffle(nums)
    print nums
    counting_sort(nums)
    print nums
