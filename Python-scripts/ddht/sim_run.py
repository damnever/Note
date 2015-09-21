#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os

from powerdht.app import App
from powerdht.handler import StreamHandler, FileHandler


if __name__ == '__main__':
    App.configure_options(
        host='0.0.0.0',
        port=6881,
        node_size=100000,
        log_file_prefix='dht.log')
    app = App.instance("SingleThread")
    app.add_handler(StreamHandler())
    app.add_handler(
        FileHandler(os.path.join(os.path.dirname(__file__), 'infohash.txt')))
    app.startd()
