#!/usr/bin/env python
# -*- coding: utf-8 -*-


# https://leetcode.com/problems/roman-to-integer/


def roman_to_integer(s):
    s = s.upper()
    rimap = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
    result = 0
    next_ = rimap[s[-1]]

    for idx, r in enumerate(s[:-1]):
        current = rimap[r]
        next_ = rimap[s[idx+1]]
        if current < next_:
            result -= current
        else:
            result += current
    result += next_
    return result


if __name__ == '__main__':
    print roman_to_integer('D')  # 500
    print roman_to_integer('XL')  # 40
    print roman_to_integer('XIV')  # 14
    print roman_to_integer('MMMCCCXXXIII')  # 3333
    print roman_to_integer('MCM')  # 1900
    print roman_to_integer('MCDXXXVII')  # 1437
