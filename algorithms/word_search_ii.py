#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.com/problems/word-search-ii/


class Solution(object):

    def find_words(self, board, words):
        height, width = len(board), len(board[0])
        trie = self.make_trie(words)

        results = set()
        for row in xrange(height):
            for col in xrange(width):
                letters = list()
                self.travel(row, col, width, height, trie, results, board, letters)
        return list(results)

    def travel(self, row, col, width, height, trie, results, board, letters):
        letter = board[row][col]
        if letter not in trie:
            return
        letters.append(letter)
        trie = trie[letter]
        if None in trie:
            results.add(''.join(letters))

        board[row][col] = 0  # visited
        if col + 1 < width and board[row][col+1]:  # right
            self.travel(row, col+1, width, height, trie, results, board, letters)
        if col - 1 >= 0 and board[row][col-1]:  # left
            self.travel(row, col-1, width, height, trie, results, board, letters)
        if row + 1 < height and board[row+1][col]:  # up
            self.travel(row+1, col, width, height, trie, results, board, letters)
        if row-1 >= 0 and board[row-1][col]:  # down
            self.travel(row-1, col, width, height, trie, results, board, letters)
        board[row][col] = letter  # recover

    def make_trie(self, words):
        root = dict()
        for word in words:
            current = root
            for letter in word:
                current = current.setdefault(letter, {})
            current.setdefault(None, None)
        return root


if __name__ == '__main__':
    board = [
        ['o', 'a', 'a', 'n'],
        ['e', 't', 'a', 'e'],
        ['i', 'h', 'k', 'r'],
        ['i', 'f', 'l', 'v']
    ]
    words = ["oath", "pea", "eat", "rain"]
    print Solution().find_words(board, words)
