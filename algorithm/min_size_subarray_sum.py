#!/usr/bin/env python
# -*- coding: utf-8 -*-


class Solution2(object):

    def minSubArrayLen(self, s, nums):
        if not nums or sum(nums) < s:
            return 0
        length = len(nums)
        begin, end = 0, 0
        count = 0
        minlen = length + 1
        while end < length:
            if nums[end] >= s:
                return 1
            if count < s:
                count += nums[end]
                end += 1
            else:
                count -= nums[begin]
                begin += 1
                minlen = min(minlen, end - begin + 1)
        while count >= s:
            count -= nums[begin]
            begin += 1
            minlen = min(minlen, end - begin + 1)
        return minlen if minlen <= length else 0

if __name__ == '__main__':
    nums = [1, 2, 3, 4, 5]
    s = 11
    print Solution2().minSubArrayLen(s, nums)
