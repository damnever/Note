#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------
#   Author           :  Damnever<dxc.wolf@gmail.com>
#   Created Time     :  00:48:37 2015-01-12
#   Last Modified    :  18:49:14 2015-01-12
# ----------------------------------------------------------------------

"""
http://www.pythonchallenge.com/pc/def/peak.html
"""

# peak hell sounds familiar ?
# wo de English is ru ci lan.
# So, pickle

import urllib2
try:
    import cPickle as pickle
except:
    import pickle

# Step 1
def get_data(url):
    data = urllib2.urlopen(url).read()
    return data

def load(data):
    return pickle.loads(data)

# Step 2
# Gets a lot of list, It contains ' ' and '#' ...
# Search the problem ... print it

def draw_line(line):
    print ''.join(each[0] * each[1] for each in line)

def draw(lines):
    for line in lines:
        draw_line(line)

if __name__ == '__main__':
    URL = 'http://www.pythonchallenge.com/pc/def/banner.p'
    draw(load(get_data(URL)))
