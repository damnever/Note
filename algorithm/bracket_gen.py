#!/usr/bin/env python
# -*- coding: utf-8 -*-


"""
给定括号对数量，生成所有有效括号对的组合。
  1: ()
  2: (()), ()()
  3: ((())), ()(()), (())(), (()()), ()()()
  ...
"""

import types


def gen_brackets(num):
    if isinstance(num, types.FloatType) or num < 0:
        raise TypeError("Argument `num` must be positive integer.")
    elif num <= 1:
        return ['()' * num]
    brackets = set()
    for each in gen_brackets(num - 1):
        brackets.add('(' + each + ')')
        brackets.add('()' + each)
        brackets.add(each + '()')
    return list(brackets)


if __name__ == '__main__':
    print gen_brackets(0)
    print gen_brackets(1)
    print gen_brackets(2)
    print gen_brackets(3)
    print gen_brackets(4)
    print gen_brackets(5)
