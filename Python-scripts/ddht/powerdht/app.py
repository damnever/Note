#!/usr/bin/env python
# -*- coding: utf-8 -*-


from btdht import DHT, ThreadSupport
from log import enable_pretty_logging


class App(object):
    """App is used to invoke by user.
    `configure_options` set up settings, `instance` is a factory method
    that will initialize a DHT object."""

    @classmethod
    def configure_options(cls, **options):
        """Call the method to set up some arguments, all optional.

        You can set keyword arguments as follow:
         - host: Ip address. Default to `0.0.0.0`.
         - port: port, which server will listen. Default to 6881.
         - node_size: max size is 2**160, that's capacity of DHT
         network. Default to 2**160.
         - thread_num: Thread numbers, thread pool required. Default
         to 8.
         - q_size: Thread worker queue size, thread pool required.
         Default to 200.
         - log_level: Which level message you want to see. It can be
         "debug", "info", "warning", "error". Default to "info".
         - log_file_prefix: Log file name. Default to None.
         - log_file_max_size: Bytes, the capacity of log file. Default
         to 0, disallow the file to rollover at a predetermined size.
         - log_file_num_backups: If it is non-zero, the argument
         `log_file_max_size` must non-zero. If `log_file_max_size` is
         about to be exceeded, the file is closed and new log file is
         silently opened for output, file name like `log.1`, `log.2`.
         Default to 0, just like `log_file_max_size`.
        """
        cls._options = dict()
        cls._options.update(options)

        log_level = options.get('log_level', "info")
        log_file_prefix = options.get('log_file_prefix', None)
        log_file_options = None
        if log_file_prefix:
            log_file_options = {
                'log_file_prefix': log_file_prefix,
                'log_file_max_size': options.get('log_file_max_size', 0),
                'log_file_num_backups': options.get('log_file_num_backups', 0),
            }
        enable_pretty_logging(log_level, log_file_options)

    @classmethod
    def instance(cls, name="SingleThread"):
        """Argument `name` accepted `SingleThread` or `MultiThread`."""
        # globals()[name]
        if not hasattr(cls, '_options'):
            cls._options = dict()
        host = cls._options.get('host', '0.0.0.0')
        port = cls._options.get('port', 6881)
        node_size = cls._options.get('node_size', 2**160)
        if name == "SingleThread":
            return DHT(host, port, node_size)
        if name == "MultiThread":
            thread_num = cls._options.get('thread_num', 8)
            q_size = cls._options.get('q_size', 200)
            return ThreadSupport(DHT, thread_num, q_size)(host, port, node_size)
        else:
            raise ValueError(
                'Excepted "SingleThread" or "MultiThread", got "%s".' % name)
