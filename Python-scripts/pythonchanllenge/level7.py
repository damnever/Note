#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------
#   Author           :  Damnever<dxc.wolf@gmail.com>
#   Created Time     :  17:54:42 2015-01-15
#   Last Modified    :  20:26:57 2015-01-15
# ----------------------------------------------------------------------

"""
http://www.pythonchallenge.com/pc/def/oxygen.html

PIL: http://effbot.org/imagingbook/pil-index.htm
"""

# I actually don't know how to do ...
# But nothing can stop me.

import Image, re

# Step 1
# find pixel
fpath = './data/oxygen.png'
img = Image.open(fpath)
width, height = img.size

row = [img.getpixel((x, height/2)) for x in range(0, width, 7)]
ords = [r for r, g, b, a in row if r == g == b]

s = ''.join(map(chr, ords))
print s + '\n'

    # Step 2
    # continue use chr()
    result = ''.join(map(chr, map(int ,re.findall(r'\d+', s))))
    print result
