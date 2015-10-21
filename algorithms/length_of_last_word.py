#!/usr/bin/env python
# -*- coding: utf-8 -*-


# https://leetcode.com/problems/length-of-last-word/


def length_of_last_word(s):
    s = s.strip()
    return len(s.split()[-1]) if s else 0


if __name__ == '__main__':
    print length_of_last_word("Hello World")
    print length_of_last_word("  ")
