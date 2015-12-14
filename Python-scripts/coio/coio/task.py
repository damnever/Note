# -*- coding: utf-8 -*-

from __future__ import print_function, division, absolute_import

from .future import Future


class Task(object):

    __slots__ = ('_coroutine', '_future')

    def __init__(self, coroutine):
        self._coroutine = coroutine
        self._future = Future()
        self._future.set_result(None)
        self.next_step(self._future)

    def next_step(self, future):
        try:
            next_future = self._coroutine.send(future.result)
        except StopIteration:
            return

        next_future.add_done_callback(self.next_step)
