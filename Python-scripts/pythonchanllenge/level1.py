#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------
#   Author           :  Damnever<dxc.wolf@gmail.com>
#   Created Time     :  22:06:26 2015-01-10
#   Last Modified    :  14:36:46 2015-01-11
# ----------------------------------------------------------------------

"""
http://www.pythonchallenge.com/pc/def/map.html
"""

RAW_WORDS = '''g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq
ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq
qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj.
'''

import string

# Step 1:
# Move letter back two according to alphabet.
letters = string.lowercase
letter_dict = dict(zip(letters, letters[2:] + letters[:2]))

replace = lambda letter: letter_dict.get(letter, letter)

new_words = ''.join(map(replace, RAW_WORDS))
print new_words

# Step 2:
# Translate 'map'.
letter_map = string.maketrans(letters, letters[2:] + letters[:2])
print 'map'.translate(letter_map)
