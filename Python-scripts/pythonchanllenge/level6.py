#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------
#   Author           :  Damnever<dxc.wolf@gmail.com>
#   Created Time     :  19:12:40 2015-01-12
#   Last Modified    :  20:14:31 2015-01-12
# ----------------------------------------------------------------------

"""
http://www.pythonchallenge.com/pc/def/channel.html
"""

import zipfile

def next_file(zf, file):
    data = zf.read(file + '.txt')
    file = data.split(' ')[-1]
    return data, file

# Step 1
# Download zip file and find the next nothing ...
def find_out(zf, file='90052'):
    data = None
    while file.isdigit():
        data, file = next_file(zf, file)
        print data
    else:
        return data

# Step 2
# Collect the comments ...
def collect_comment(zf, file):
    comments = []
    while file.isdigit():
        comment = zf.getinfo(file + '.txt').comment
        comments.append(comment)
        _, file = next_file(zf, file)
    else:
        return ''.join(comments)

# Step 3
# Bingo, I think ... "it's in the air. look at the letters."
# Looks 'HOCKEY' casefully, it is made of 'oxygen'.

if __name__ == '__main__':
    path = './data/channel.zip'
    file = '90052'
    zf = zipfile.ZipFile(path, 'r')
    print '-'*80 + '\n' + find_out(zf, file)
    print '-'*80 + '\n' + collect_comment(zf, file)
    zf.close()
