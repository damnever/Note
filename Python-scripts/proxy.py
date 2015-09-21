#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
A simple proxy server by Tornado.

Useage:
    ./proxy.py
    ./proxy.py --url=<http(s)://example.com> --port=8888 --debug=True

Reference:
    http://feilong.me/2011/09/tornado-as-a-proxy
"""


import urlparse

import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import tornado.httpclient
from tornado.httpclient import HTTPRequest, AsyncHTTPClient
from tornado.options import define, options


define('port', default=8888, help='run on the given port', type=int)
define('url', default='http://www.soqoo.net', type=str)
define('debug', default=False, type=bool)


class ProxyHandler(tornado.web.RequestHandler):

    @tornado.web.asynchronous
    def get(self):
        url = options.url + self.request.uri

        # Add host to headers
        headers = dict(self.request.headers)
        headers['Host'] = urlparse.urlparse(url).hostname

        # `request.body` is a string, and `AsyncHTTPClient` doesn't suport
        # GET method with a body.
        body = self.request.body
        if not body:
            body = None

        try:
            AsyncHTTPClient().fetch(
                HTTPRequest(url=url, method=self.request.method,
                            body=body, headers=headers,
                            follow_redirects=False),
                self._on_proxy)
        except tornado.httpclient.HTTPError as e:
            if hasattr(e, 'response') and e.response:
                self._on_proxy(e.response)
            else:
                self.set_status(500)
                self.write('Internal server error:\n{0}'.format(e))
                self.finish()

    @tornado.web.asynchronous
    def post(self):
        return self.get()

    def _on_proxy(self, response):
        if response.error and not isinstance(
                response.error, tornado.httpclient.HTTPError):
            self.set_status(500)
            self.write('Internal server error:\n{0}'.format(response.error))
        else:
            self.set_status(response.code)
            for header in ('Date', 'Cache-Control', 'Server',
                           'Content-Type', 'Location'):
                v = response.headers.get(header, None)
                if v:
                    self.set_header(header, v)
            v = response.headers.get_list('Set-Cookie')
            if v:
                for i in v:
                    self.add_header('Set-Cookie', i)
            if response.body:
                self.write(response.body)
            self.finish()


def main():
    # Use `curl_httpclient`
    AsyncHTTPClient.configure("tornado.curl_httpclient.CurlAsyncHTTPClient")
    tornado.options.parse_command_line()
    application = tornado.web.Application(
        [
            (r'/.*', ProxyHandler),
        ],
        **{
            'debug': options.debug,
        })
    http_server = tornado.httpserver.HTTPServer(application)
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()

if __name__ == '__main__':
    main()
