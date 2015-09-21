#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
The module provides some handlers to handle (infohash, address, date),
whatever, you can inherit from `Handler` to customize handler as you
wish, add somthing like Bloom Filter or other infohash reduplication
removing algorithm, or persistent data.
"""

import abc
import time
import threading


__all__ = ['Handler', 'StreamHandler', 'FileHandler']


class Handler(object):
    """ Abstract class `Handler`, `hold` method must be implement by
    subclass.
    """

    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def hold(self, infohash, address, date):
        """ Handle a tuple of (infohash, address, date). """
        pass


class StreamHandler(Handler):
    """ StreamHandler object, which prints data in screen only. """

    def hold(self, infohash, address, date):
        print('magnet:?xt=urn:btih:{0}  {1[0]}:{1[1]}{2}{3}'.format(
            infohash, address, ' ' * (21 - len(address[0] + str(address[1]))),
            time.strftime("%Y-%m-%d %H:%M:%S", date)))


class FileHandler(Handler):
    """ FileHandler object, which can write data to file. """

    _thread_lock = threading.Lock()

    def __init__(self, fpath):
        self._fpath = fpath

    def hold(self, infohash, address, date):
        line = 'magnet:?xt=urn:btih:{0}  {1[0]}:{1[1]}{2}{3}\n'.format(
            infohash, address, ' ' * (21 - len(address[0] + str(address[1]))),
            time.strftime('%Y-%m-%d %H:%M:%S', date))
        with self._thread_lock, open(self._fpath, 'a+') as f:  # FILO
            f.write(line)
