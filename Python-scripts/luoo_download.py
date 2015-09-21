#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
A script to download music from luoo.net.
"""

from __future__ import print_function

import re
import os
import sys
import urllib2

class Download(object):

    def __init__(self, url):
        self._url = url

    def __enter__(self):
        try:
            self._f = urllib2.urlopen(self._url)
        except urllib2.URLError as e:
            print("{0}\n {1}".format(self._url, e.reason))
        except urllib2.HTTPError as e:
            print("{0}\n {1}".format(e.code, e.reason))
        else:
            return self._f

    def __exit__(self, exc_type, exc_val, exc_tb):
        if hasattr(self, '_f'):
            self._f.close()


class Luoo(object):

    MUSIC_URL = 'http://mp3.luoo.net/low/luoo/radio{0}/{1:0>2}.mp3'
    TITLE_URL = 'http://www.luoo.net/music/{0}'

    TITLE_RE = r'.+?class="trackname btn-play">{0:0>2}\. (.+?)<.+?class="artist btn-play">(.+?)<'

    def __init__(self, journal, order_num):
        self._music_url = self.get_music_url(journal, order_num)
        self._file = self.get_title(journal, order_num) + '.mp3'

    def write_to(self, path='./'):
        fpath = os.path.join(os.path.abspath(path), self._file)
        with Download(self._music_url) as fi, open(fpath, 'wb') as fo:
            fo.write(fi.read())

    def get_title(self, journal, order_num, baseurl=TITLE_URL):
        with Download(baseurl.format(journal)) as f:
            html = f.read()
            pattern = re.compile(self.TITLE_RE.format(order_num), re.S)
            title = pattern.findall(html)
        return '-'.join(title[0]) if title else 'unknown'

    def get_music_url(self, journal, order_num, baseurl=MUSIC_URL):
        return baseurl.format(journal, order_num)

def main():
    if len(sys.argv) == 3:
        journal, order_num = sys.argv[1:]
        Luoo(journal, order_num).write_to('./')
    else:
        print("The program must take 2 arguments!\n \
                Now just a example for: python luoo_download.py 621 3")
        Luoo(621, 3).write_to('./')

if __name__ == '__main__':
    main()
