# -*- coding: utf-8 -*-

# https://leetcode.com/problems/top-k-frequent-elements/

import heapq


class Solution(object):
    def topKFrequent(self, nums, k):
        counter = dict()  # defaultdict is a little slow..., Counter...
        count = 0
        top_k = list()

        for num in nums:
            if num in counter:
                counter[num] += 1
            else:
                counter[num] = 1

        # Or, heapfy? ....
        # Or, sorted(counter.iteritems(), key=lambda x: x[1], reverse=True)
        for n, c in counter.iteritems():
            if count < k:
                heapq.heappush(top_k, (c, n))
                count += 1
            else:
                heapq.heappushpop(top_k, (c, n))

        return [heapq.heappop(top_k)[1] for _ in xrange(k)][::-1]


if __name__ == '__main__':
    import timeit
    print(Solution().topKFrequent([1, 1, 2, 1, 2, 4, 3, 5, 3, 1, 3], 3))
    print(timeit.timeit("Solution().topKFrequent([1, 1, 2, 1, 2, 4, 3, 5, 3, 1, 3], 3)",
                        setup="from __main__ import Solution"))
