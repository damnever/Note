#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Reverse words in string: https://leetcode.com/problems/reverse-words-in-a-string/


class Solution(object):
	# Splitting an empty string with a specified separator returns [''].

    def reverse_words(self, s):
        return ' '.join(s.split()[::-1])
