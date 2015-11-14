# -*- coding: utf-8 -*-

import sys


class Trie(object):

    def __init__(self):
        self._root = TrieNode(' ')

    def add_word(self, word):
        node = self._root
        for c in _to_unicode(word):
            node = node.add_child(c)

    def has_prefix(self, prefix):
        prefix = _to_unicode(prefix)
        return (self._next_node_in_prefix(prefix) is not None)

    def _next_nodes_in_prefix(self, prefix):
        node = self._root
        for c in prefix:
            node = node.get_child(c)
            if node is None:
                return None
        return node

    def get_matchs(self, prefix):
        def _recursion(node, prefix):
            if not node.childs:
                yield prefix
            for nd in node.childs:
                for match in _recursion(nd, prefix + nd.value):
                    yield match

        prefix = _to_unicode(prefix)
        node = self._next_nodes_in_prefix(prefix)
        if node is None:
            return []
        return _recursion(node, prefix)


class TrieNode(object):

    __slots__ = ['_val', '_childs']

    def __init__(self, c):
        self._val = c
        self._childs = dict()

    @property
    def value(self):
        return self._val

    @property
    def childs(self):
        return self._childs.values()

    def add_child(self, c):
        if c not in self._childs:
            self._childs[c] = TrieNode(c)
        return self._childs[c]

    def get_child(self, c):
        return self._childs.get(c, None)


def _to_unicode(s):
    if sys.version_info[0] < 3:
        unicode_type = unicode
    else:
        unicode_type = str
    if isinstance(s, unicode_type):
        return s
    return s.decode('utf-8')
