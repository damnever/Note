#!/usr/bin/env python
# -*- coding: utf-8 -*-

# LRU Cache: https://leetcode.com/problems/lru-cache/

# import collections

class Solution(object):

    def __init__(self, capacity):
        self._count = 0  # count number is faster than len
        self._capacity = capacity
        self._keys = []
        self._cache = dict()

    def get(self, key):
        if key in self._keys:
            self._keys.remove(key)
            self._keys.append(key)
        return self._cache.get(key, -1)

    def set(self, key, value):
        if key in self._keys:
            self._keys.remove(key)
            self._keys.append(key)
        elif self._count < self._capacity:
            self._count += 1
            self._keys.append(key)
        else:
            old_key = self._keys.pop(0)
            self._keys.append(key)
            del self._cache[old_key]
        self._cache[key] = value


# Two times faster!!!
import collections

class Solution2(object):

    def __init__(self, capacity):
        self._count = 0  # or len(self._cache.keys()), which is slow way
        self._capacity = capacity
        self._cache = collections.OrderedDict()

    def get(self, key):
        if key in self._cache:
            value = self._cache.pop(key)
            self._count -= 1
            self.set(key, value)
        return self._cache.get(key, -1)

    def set(self, key, value):
        if key in self._cache:
            self._cache.pop(key)
        elif self._count < self._capacity:
            self._count += 1
        else:
            self._cache.popitem(False)  # FIFO
        self._cache[key] = value


if __name__ == '__main__':
    slt = Solution2(2)
    slt.set(2, 1)
    slt.set(1, 1)
    print slt.get(2)
    slt.set(4, 1)
    print slt.get(1)
    print slt.get(2)
