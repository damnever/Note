#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
A command line program, which imitate 'tree' on *unix.

usage: cmd_tree.py [-h] [-P path] [-L level]

List directory as a tree.

optional arguments:
  -h, --help  show this help message and exit
  -P path     Given a path to show, default is current directory.
  -L level    Directories' recursion depth..
"""

import os
import argparse

FILE_PREFIX = '├── '
DIR_PREFIX = '│   '
LAST_PREFIX = '└── '

def print_files(path, level=None, prefix=''):
    """ Print recursive listing of contents of path.
    Args:
      - path: a directory path will be list.
      - level: the depth of the recursion, in other words,
      the layer number of directory.
      - prefix: does not matter, for recursion.
    """
    if prefix == '':       # the root directory
        print '* ' + os.path.abspath(path)
        prefix = [FILE_PREFIX]

    dirlist, count = get_dirlist(path)
    for i, f in enumerate(dirlist):
        if i == count - 1:    # last file of the current directory.
            prefix[-1] = LAST_PREFIX
        else:
            prefix[-1] = FILE_PREFIX
        fullname = os.path.join(path, f)
        is_dir = os.path.isdir(fullname)
        print_name = (''.join(prefix) + f + '/') if is_dir \
                else (''.join(prefix) + f)
        print print_name
        # next level.
        if is_dir and (level == None or level > 1):
            deep = level
            if level != None:
                deep = level - 1
            prefix[-1] = DIR_PREFIX
            print_files(fullname, deep, prefix + ['├── '])

def get_dirlist(path):
    ''' Return a sorted list and files' count of entries in path. This returns just
    names, not the full path to the name. '''
    dirlist = os.listdir(path)
    dirlist.sort()
    return dirlist, len(dirlist)

def parse_arg():
    """ Supports command line parameters. """
    parser = argparse.ArgumentParser(description='List directory as a tree.')
    parser.add_argument(\
            '-P', type=path_check, default=os.getcwd(), \
            help='Given a path to show, default is current directory.', \
            metavar='path', dest='path')
    parser.add_argument(\
            '-L', type=level_check, default=None, \
            help='Directories\' recursion depth.', \
            metavar='level', dest='level')
    args = parser.parse_args()
    return args.path, args.level

def path_check(arg):
    """ Check whether the path is legal. for `type` of `add_argument`."""
    if os.path.exists(arg):
        return arg
    raise argparse.ArgumentTypeError('Invalid path, must be exists.')

def level_check(arg):
    """ Checks whether the level is legal, for `type` of `add_argument`. """
    try:
        value = int(arg)
    except ValueError:
        raise argparse.ArgumentTypeError('Invalid level, must be a integer.')
    if value <= 0:
        raise argparse.ArgumentTypeError(\
                'Invalid level, must be greater than 0.')
    return value

if __name__ == '__main__':
    path, level = parse_arg()
    print_files(path, level=level)
