#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Logging support with colors, just available in *unix.

Borrow from `tornado.log`:
    https://github.com/tornadoweb/tornado/blob/master/tornado/log.py
"""


import logging
import logging.handlers
import sys
try:
    import curses
except ImportError:
    curses = None


logger = logging.getLogger("DHT")


def enable_pretty_logging(log_level="info", log_file_options=None,
                          logger=logger):
    logger.setLevel(getattr(logging, log_level.upper()))

    stream_handler = logging.StreamHandler()
    stream_handler.setFormatter(LogFormatter())
    logger.addHandler(stream_handler)

    if log_file_options:
        file_handler = logging.handlers.RotatingFileHandler(
            filename=log_file_options['log_file_prefix'],
            maxBytes=log_file_options['log_file_max_size'],
            backupCount=log_file_options['log_file_num_backups'])
        file_handler.setFormatter(LogFormatter(color=False))
        logger.addHandler(file_handler)


class LogFormatter(logging.Formatter):

    DEFAULT_FORMAT = "%(color)s[%(levelname)1.1s %(asctime)s %(module)s:%(lineno)d]%(end_color)s %(message)s"
    DEFAULT_DATE_FORMAT = "%y-%m-%d %H:%M:%S"
    DEFAULT_COLORS = {
        logging.DEBUG: 4,  # Blue
        logging.INFO: 2,  # Green
        logging.WARNING: 3,  # Yellow
        logging.ERROR: 1,  # Red
    }

    def __init__(self, color=True, fmt=DEFAULT_FORMAT, datefmt=DEFAULT_DATE_FORMAT,
                 colors=DEFAULT_COLORS):
        logging.Formatter.__init__(self, datefmt=datefmt)
        self._fmt = fmt

        self._colors = {}
        if color and _stderr_supports_color():
            fg_color = (curses.tigetstr("setaf") or
                        curses.tigetstr("setf") or "")
            for levelno, code in colors.items():
                self._colors[levelno] = unicode(curses.tparm(fg_color, code),
                                                "ascii")
            self._normal = unicode(curses.tigetstr("sgr0"), "ascii")
        else:
            self._normal = ""

    def format(self, record):
        try:
            message = record.getMessage()
            assert isinstance(message, basestring)
            record.message = _safe_unicode(message)
        except Exception as e:
            record.message = "Bad message (%s): %r" % (e, record.__dict__)

        record.asctime = self.formatTime(record, self.datefmt)

        if record.levelno in self._colors:
            record.color = self._colors[record.levelno]
            record.end_color = self._normal
        else:
            record.color = record.end_color = ""

        formatted = self._fmt % record.__dict__

        if record.exc_info:
            if not record.exc_text:
                record.exc_text = self.formatException(record.exc_info)
        if record.exc_text:
            lines = [formatted.rstrip()]
            lines.extend(_safe_unicode(ln) for ln in record.exc_text.split('\n'))
            formatted = '\n'.join(lines)

        return formatted.replace('\n', '\n    ')


def _stderr_supports_color():
    color = False
    if curses and hasattr(sys.stderr, 'isatty') and sys.stderr.isatty():
        try:
            curses.setupterm()
            if curses.tigetnum("colors") > 0:
                color = True
        except Exception:
            pass
    return color


def _safe_unicode(s):
    if isinstance(s, (unicode, type(None))):
        return s
    if not isinstance(s, bytes):
        raise TypeError("Excepted bytes, unicode, None; got %r" % type(s))
    try:
        return s.decode("utf-8")
    except UnicodeDecodeError:
        return repr(s)

if __name__ == "__main__":
    enable_pretty_logging()
    try:
        1 / 0
    except ZeroDivisionError:
        # logger.error("error", exc_info=sys.exc_info())
        logger.error("error", exc_info=True)
