#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------
#   Author           :  Damnever<dxc.wolf@gmail.com>
#   Created Time     :  22:10:32 2015-01-11
#   Last Modified    :  22:59:25 2015-01-11
# ----------------------------------------------------------------------

"""
http://www.pythonchallenge.com/pc/def/ocr.html
"""

import urllib2
import string

URL = 'http://www.pythonchallenge.com/pc/def/ocr.html'

html = urllib2.urlopen(URL).read()

# Find HTML comments that we need
pos_ignore = html.find('<!--')
pos = html[pos_ignore+4:].find('<!--')
data = html[pos_ignore+pos+8: -4]

letters = string.lowercase

# Find characters.
words = [each for each in data if each in letters]

print ''.join(words)
