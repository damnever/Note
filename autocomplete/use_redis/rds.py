# -*- coding: utf-8 -*-

import sys

import redis


class Rds(object):

    # Sorted Set.
    _WORD_PREFIX_SS = 'word:prefix:{0}'
    # Hash Map.
    _WORDS_FULL_HM = 'words:all:full'
    # String.
    _WORD_COUNT_S = 'words:count'

    def __init__(self, host='localhost', port=6379, db=4):
        self._redis = redis.StrictRedis(host=host, port=port, db=db)

    def add_word(self, word):
        word = _to_unicode(word)
        index = self._get_count() + 1

        pipeline = self._redis.pipeline()
        pipeline.hmset(self._WORDS_FULL_HM, {index: word})
        for idx in range(1, len(word) + 1):
            pipeline.zadd(self._WORD_PREFIX_SS.format(word[0:idx]), 0, index)
        pipeline.incr(self._WORD_COUNT_S)
        pipeline.execute()

    def get_matchs(self, prefix):
        prefix = _to_unicode(prefix)
        idxs = self._redis.zrangebyscore(self._WORD_PREFIX_SS.format(prefix),
                                         '-inf', '+inf')
        if not idxs:
            return []
        return self._redis.hmget(self._WORDS_FULL_HM, *idxs[::-1])

    def incr_score(self, prefix):
        pass

    def clear(self):
        self._redis.flushdb()

    def _get_count(self):
        return int(self._redis.get(self._WORD_COUNT_S) or '0')


def _to_unicode(s):
    if sys.version_info[0] < 3:
        unicode_type = unicode
    else:
        unicode_type = str
    if isinstance(s, unicode_type):
        return s
    return s.decode('utf-8')
