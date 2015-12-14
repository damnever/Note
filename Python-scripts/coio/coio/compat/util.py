# -*- coding: utf-8 -*-

from __future__ import print_function, division, absolute_import


def with_metaclass(meta, *bases):
    """Create a base class with a metaclass."""
    # NOTE: The origin code from six(https://bitbucket.org/gutworth/six).
    # This requires a bit of explanation: the basic idea is to make
    # a dummy metaclass for one level of class instantination that
    # replaces itself with actual metaclass.
    class MetaClass(meta):
        def __new__(cls, name, _bases, attrs):
            return meta(name, bases, attrs)

    return type.__new__(MetaClass, 'TempMetaClass', (), {})


def errno_from_exception(e):
    """Provides the errno from an Exception object."""
    # NOTE: the origin code from tornado(https://github.com/tornadoweb/tornado)
    if hasattr(e, 'errno'):
        return e.errno
    elif e.args:
        return e.args[0]
    else:
        return None
