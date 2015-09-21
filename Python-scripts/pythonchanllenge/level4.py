#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------
#   Author           :  Damnever<dxc.wolf@gmail.com>
#   Created Time     :  23:15:52 2015-01-11
#   Last Modified    :  00:48:30 2015-01-12
# ----------------------------------------------------------------------

"""
http://www.pythonchallenge.com/pc/def/linkedlist.php
"""

# I found picture is a link in the source code,
# so I clicked it, the number in current url is 12345,
# then '44827' shows up, then 45439, 94485 ...

# urllib may help. 400 times is more than enough.

import urllib2

URL = 'http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing='
nothing = '12345'
data = None

while 1:
    print 'GET: ' + URL + nothing
    data = urllib2.urlopen(URL + nothing).read()
    match = data.split(' ')[-1]
    if match.isdigit():
        nothing = match
    else:
        print data
        try:
            nothing = raw_input('Keep going: ')
        except KeyboardInterrupt:
            break

print '\nAccept: ', data
