# -*- coding: utf-8 -*-

from __future__ import print_function, division, absolute_import


class Future(object):

    __slots__ = ('_result', '_exception', '_done', '_callbacks')

    def __init__(self):
        self._result = None
        self._exception = None
        self._done = False
        self._callbacks = list()

    def add_done_callback(self, callback):
        self._callbacks.append(callback)

    def set_result(self, result):
        self._result = result
        self._run_callbacks()

    def set_exception(self, exception):
        self._exception = exception
        self._run_callbacks()

    def _run_callbacks(self):
        for callback in self._callbacks:
            callback(self)
        self._done = True

    @property
    def result(self):
        return self._result

    @property
    def exception(self):
        return self._exception

    @property
    def done(self):
        return self._done
