# -*- coding: utf-8 -*-

import os
import json
import importlib
import logging

import tornado.websocket
import tornado.web
import tornado.httpserver
import tornado.ioloop
from tornado.options import define, options


define('use', default='trie', help='Argument must be "trie" or "redis"')

logger = logging.getLogger('autocomplete')


class IndexHandler(tornado.web.RequestHandler):

    def get(self):
        self.render('index.html')


class AutoCompleteHandler(tornado.websocket.WebSocketHandler):

    def check_origin(self, origin):
        return True

    def open(self):
        logger.info('WebSocket opened')
        self.set_nodelay(True)

    def on_message(self, message):
        message = json.loads(message)
        logger.info('Got message: {0}'.format(message))
        if message['type'] == 'new':
            self.ds.add_word(message['text'])
        elif message['type'] == 'prefix':
            self.write_message(
                {'suggestions': list(self.ds.get_matchs(message['text']))})

    def on_close(self):
        logger.info('WebSocket closed: {0} {1}'.format(
            self.close_code, self.close_reason))

    @property
    def ds(self):
        return options.data_structure


if __name__ == '__main__':
    options.parse_command_line()
    module = importlib.import_module('use_{0}'.format(options.use))
    data_structure = getattr(module, options.use)
    define('data_structure', default=data_structure())

    app = tornado.web.Application(
        [
            ('/', IndexHandler),
            ('/autocomplete', AutoCompleteHandler),
        ],
        {
            'template_path': os.path.dirname(__file__),
            'debug': True,
        })
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(9487)
    tornado.ioloop.IOLoop.instance().start()
