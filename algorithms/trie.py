#!/usr/bin/env python
# -*- coding: utf-8 -*-


import types


class Trie(object):
    """Trie.

    Example:
    >>> trie = Trie(['who', 'when', 'where'])
    >>> trie.search('who')
    True
    >>> trie.has_prefix('wh')
    True
    >>> trie.get_words_by_prefix('wh')
    ['where', 'when', 'who']
    >>> trie.remove('who')
    >>> trie.search('who')
    False
    >>> trie.get_words()
    ['where', 'when']
    >>> trie.insert('who')
    >>> trie.insert_many(['got', 'god'])
    >>> trie.search('who')
    True
    >>> trie.get_words_by_prefix('go')
    ['got', 'god']
    >>> trie.get_words()
    ['got', 'god', 'where', 'when', 'who']
    """

    _END = None

    def __init__(self, words=None):
        self._root = dict()
        if isinstance(words, (types.TupleType, types.ListType)):
            self.insert_many(words)
        elif isinstance(words, basestring):
            self.insert(words)
        elif words is not None:
            raise TypeError(
                'Argument "{0}" is not basestring/tuple/list.'.format(words))

    def insert_many(self, words):
        for word in words:
            self.insert(word)

    def insert(self, word):
        current = self._root
        for letter in word:
            current = current.setdefault(letter, {})
        current.setdefault(self._END, self._END)

    def remove(self, word):
        current = self._root
        visited = [current]
        append = visited.append
        for letter in word:
            if letter not in current:
                return
            current = current[letter]
            append(current)
        for index, current in enumerate(visited[::-1]):
            if len(current.keys()) == 1:
                continue
            key = word[-index] if index else self._END
            del current[key]
            return

    def search(self, word):
        current = self._root
        for letter in word:
            if letter not in current:
                return False
            current = current[letter]
        else:
            if self._END in current:
                return True
            else:
                return False

    def has_prefix(self, prefix):
        current = self._root
        for letter in prefix:
            if letter not in current:
                return False
            current = current[letter]
        return True

    def get_words_by_prefix(self, prefix):
        current = self._root
        for letter in prefix:
            if letter not in current:
                return []
            current = current[letter]
        words = self.get_words(current, prefix)
        return words

    def get_words(self, root=None, prefix=''):
        def _recursion(prefix, node, words):
            for letter in node:
                if letter is self._END:
                    words.append(''.join(prefix))
                    continue
                prefix.append(letter)
                _recursion(prefix, node[letter], words)
                prefix.pop()
        node = root or self._root
        prefix = list(prefix)
        words = list()
        _recursion(prefix, node, words)
        return words


if __name__ == '__main__':
    import doctest
    doctest.testmod()
