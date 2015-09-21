#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
A powerful DHT crawler.

NOTE:
    I don't imlepment Bloom Filter or other infohash reduplication
    removing algorithm. If you want, you can see pybloom module or
    implements by yourself, and you can do those things with
    subclass of `handler.Handler`.
"""

__author__ = "Damnever <dxc.wolf@gmail.com>"

__version__ = "0.8"


def get_author():
    return __author__


def get_version():
    return __version__
