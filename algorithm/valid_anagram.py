# -*- coding: utf-8 -*-

# https://leetcode.com/problems/valid-anagram/


def is_anagram(s, t):
    if len(s) != len(t):
        return False

    hts = dict()
    for c in s:
        hts[c] = hts.get(c, 0) + 1

    htt = dict()
    for c in t:
        htt[c] = htt.get(c, 0) + 1

    for k in hts:
        if k not in htt or htt[k] != hts[k]:
            return False

    return True


if __name__ == '__main__':
    print(is_anagram('anagram', 'nagaram'))
    print(is_anagram('rat', 'car'))
    print(is_anagram('ccac', 'acac'))
