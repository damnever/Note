#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------
#   Author           :  Damnever<dxc.wolf@gmail.com>
#   Created Time     :  20:27:09 2015-01-15
#   Last Modified    :  20:38:49 2015-01-15
# ----------------------------------------------------------------------

"""
http://www.pythonchallenge.com/pc/def/integrity.html
"""
import bz2

# Clicks `../return/good.html`, which need user name and password.
# HTML comments contains 'un' and 'pw', so ...

# 'BZh91AY' is the flag of bzip2 compress method.
# BTW: 'PK/x03/x04' for zip, '/x25/xD5/b/b' for gzip.

# I don't know the area tag for what.

un = 'BZh91AY&SYA\xaf\x82\r\x00\x00\x01\x01\x80\x02\xc0\x02\x00 \x00!\x9ah3M\x07<]\xc9\x14\xe1BA\x06\xbe\x084'
pw = 'BZh91AY&SY\x94$|\x0e\x00\x00\x00\x81\x00\x03$ \x00!\x9ah3M\x13<]\xc9\x14\xe1BBP\x91\xf08'

print 'User name:', bz2.decompress(un)
print 'Password:', bz2.decompress(pw)
