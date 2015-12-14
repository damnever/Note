# -*- coding: utf-8 -*-

from __future__ import print_function, division, absolute_import

from abc import ABCMeta, abstractmethod

from .future import Future
from .compat.util import with_metaclass
from .loop import Loop


class Worker(with_metaclass(ABCMeta)):

    __slots__ = ('_loop', '_futures')

    def __init__(self, loop=None):
        self._loop = loop or Loop.instance()
        self._futures = set()

    def start(self):
        self._loop.call_worker(self)

    def register(self, fd, event, data):
        self._loop._selector.register(fd, event, data)

    def unregister(self, fd):
        self._loop._selector.unregister(fd)

    def modify(self, fd, event, data):
        self._loop._selector.modify(fd, event, data)

    def future(self, fd, event, callback, future=None):
        future = future or Future()
        self.register(fd, event, self._callback_wrap(future, callback))
        self._futures.add(future)
        return future

    def _callback_wrap(self, future, callback):
        def wrapped(fileobj, event_mask):
            try:
                result = callback(fileobj, future, event_mask)
            except Exception as e:
                self.unregister(fileobj)
                future.set_exception(e)
            else:
                self.unregister(fileobj)
                future.set_result(result)
        return wrapped

    def loop_stoped(self):
        return self._loop.stoped()

    def is_done(self):
        all_done = True
        done_futures = set()
        for future in self._futures:
            if future.done:
                done_futures.add(future)
            else:
                all_done = False
        self._futures.difference_update(done_futures)
        return all_done

    @abstractmethod
    def run(self):
        yield None

    @classmethod
    def __subclasshook__(cls, C):
        if cls is Worker:
            if any('run' in B.__dict__ for B in C.__mro__):
                return True
        raise NotImplemented
