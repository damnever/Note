# -*- coding: utf-8 -*-

# https://leetcode.com/problems/summary-ranges/


class Solution(object):
    def summaryRanges(self, nums):
        """
        :type nums: List[int]
        :rtype: List[str]
        """
        if not nums:
            return []
        results = list()
        start, end = 0, 0
        fmt = lambda s, e: ('{0}->{1}'.format(nums[s], nums[e])
                            if s != e else str(nums[e]))

        for i in range(len(nums)):
            if i > 0 and nums[i] - 1 == nums[i - 1]:
                end = i
            elif i > 0:
                results.append(fmt(start, end))
                start, end = i, i

        results.append(fmt(start, end))
        return results


if __name__ == '__main__':
    print(Solution().summaryRanges([0, 1, 2, 4, 5, 7, 8]))
