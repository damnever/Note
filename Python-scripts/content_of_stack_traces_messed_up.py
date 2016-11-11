# -*- coding: utf-8 -*-

print("changing {} ..".format(__file__))

with open(__file__, 'rb') as fi:
    lines = fi.readlines()

with open(__file__, 'wb') as fo:
    lines = lines[:-1] + ['# What are you looking for ???\n'] + lines[-1:]
    fo.writelines(lines)

print("changed {} ..".format(__file__))

raise RuntimeError('nothing, never mind')
