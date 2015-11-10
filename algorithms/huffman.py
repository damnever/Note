# -*- coding: utf-8 -*-

from __future__ import division, print_function

import string
import bisect
import collections


TreeNode = collections.namedtuple('TreeNode',
                                  ['symbol', 'frequency', 'left', 'right'])


def build_priority_queue(
        letters=(string.ascii_letters + ' !?,."\':;<>(){}[]@')):
    nodes = [TreeNode(l, n, None, None)
             for l, n in zip(letters, range(len(letters)))]
    # sorted(nodes, key=operator.attrgetter('frequency'))
    return nodes


def build_binary_tree(priority_queue):
    count = len(priority_queue)
    while count != 1:
        left = priority_queue.pop(0)
        right = priority_queue.pop(0)
        parrent_frequency = left.frequency + right.frequency
        parrent = TreeNode('', parrent_frequency, left, right)
        index = bisect.bisect_left([item.frequency for item in priority_queue],
                                   parrent_frequency)
        priority_queue.insert(index, parrent)
        count -= 1
    return priority_queue[-1]


def code_table(tree):
    def _df_traversal(node, codes=None):
        if codes is None:
            codes = list()
        if node.left is None and node.right is None:
            yield (node.symbol, ''.join(codes))
        else:
            if node.left:
                codes.append('0')
                for item in _df_traversal(node.left, codes):
                    yield item
                codes.pop()
            if node.right:
                codes.append('1')
                for item in _df_traversal(node.right, codes):
                    yield item
                codes.pop()

    return dict(_df_traversal(tree))


def encode(table, s):
    return ''.join([table[l] for l in s])


def decode(table, encoded):
    search_table = {v: k for k, v in table.items()}
    s = str(encoded)

    start_point = 0
    result = list()
    for idx in range(1, len(s) + 1):
        if s[start_point: idx] in search_table:
            result.append(search_table[s[start_point: idx]])
            start_point = idx

    return ''.join(result)


def test(s):
    table = code_table(build_binary_tree(build_priority_queue()))
    print('INPUT: {0}'.format(s))
    encoded = encode(table, s)
    print('ENCODED: {0}'.format(encoded))
    print('DECODED: {0}'.format(decode(table, encoded)))


if __name__ == '__main__':
    test('Let\'s go!!!')
    print('-' * 20)
    test('huffman.py')
    print('-' * 20)
    test('<<Algorithms>> by Damnever(dxc.wolf@gmail.com)')
