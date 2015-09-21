#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------
#   Author           :  Damnever<dxc.wolf@gmail.com>
#   Created Time     :  22:51:20 2015-01-11
#   Last Modified    :  23:15:42 2015-01-11
# ----------------------------------------------------------------------

"""
http://www.pythonchallenge.com/pc/def/equality.html
"""

import urllib2
import re

URL = 'http://www.pythonchallenge.com/pc/def/equality.html'

html = urllib2.urlopen(URL).read()
pos = html.find('<!--')
data = html[pos+4: -4]

pattern = re.compile('[^A-Z][A-Z]{3}([a-z])[A-Z]{3}[^A-Z]')
result = pattern.findall(data)

print ''.join(result)
