# -*- coding: utf-8 -*-

"""
Made a copy from https://github.com/RJ/ketama/blob/master/libketama/ketama.c..
"""

from __future__ import division

import hashlib
from collections import namedtuple
from operator import attrgetter
import __builtin__
__builtin__.range = __builtin__.xrange


ServerInfo = namedtuple('ServerInfo', ['addr', 'weight', 'point'])


def ketama_hashi(descri, offset):
    digest = hashlib.md5(descri).digest()
    return ((ord(digest[3+offset*4]) << 24) |
            (ord(digest[2+offset*4]) << 16) |
            (ord(digest[1+offset*4]) << 8) |
            (ord(digest[offset*4]))) & 0xffffffff


class Continuum(object):

    def __init__(self, servers):
        self._servers = []
        self._num_points = 0
        self._init_continuum(servers)

    def _init_continuum(self, serverinfos):
        servers = []
        num_points = 0

        for (addr, weight) in serverinfos:
            num_srvs = weight * 160
            num_points += num_srvs
            for s in range(num_srvs//4):
                descri = '{0}-{1}'.format(addr, s)
                for h in range(4):
                    point = ketama_hashi(descri, h)
                    srvinfo = ServerInfo(addr=addr, weight=weight, point=point)
                    servers.append(srvinfo)

        sorted(servers, key=attrgetter('point'))
        self._servers = servers
        self._num_points = num_points

    def get_server(self, key):
        h = ketama_hashi(key, 0)
        high = self._num_points
        low = 0

        while low <= high:
            mid = (low + high) // 2

            if mid == self._num_points:
                return self._servers[0]

            mid_val = self._servers[mid].point
            if mid == 0:
                low_val = 0
            else:
                low_val = self._servers[mid-1].point

            if low_val < h <= mid_val:
                return self._servers[mid]

            if mid_val < h:
                low = mid + 1
            else:
                high = mid - 1

        return self._servers[0]
