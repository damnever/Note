# -*- coding: utf-8 -*-

import socket

from coio import Loop, Worker
from coio import selectors

from addr import ADDR


EVENT_READ = selectors.EVENT_READ
EVENT_WRITE = selectors.EVENT_WRITE


class Server(Worker):

    def __init__(self):
        super(Server, self).__init__()
        self.server = socket.socket(socket.AF_INET,
                                    socket.SOCK_STREAM,
                                    socket.IPPROTO_TCP)
        self.server.setblocking(0)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server.bind(ADDR)
        self.server.listen(10)

    def run(self):
        while not self.loop_stoped():
            conn, addr = yield self.future(self.server,
                                           EVENT_READ,
                                           self.accept_conn)
            conn.setblocking(0)
            ServeConn(conn, addr).start()
        self.server.close()

    def accept_conn(self, fileobj, future, event_mask):
        return self.server.accept()


class ServeConn(Worker):

    def __init__(self, conn, addr):
        super(ServeConn, self).__init__()
        self.conn = conn
        self.addr = addr
        self.stop = False

    def run(self):
        while not self.stop:
            yield self.future(self.conn,
                              EVENT_READ | EVENT_WRITE,
                              self.callback)
        self.conn.close()

    def callback(self, fileobj, future, event_mask):
        if event_mask & EVENT_READ:
            self.handle_read()
        elif event_mask & EVENT_WRITE:
            self.handle_write()

    def handle_read(self):
        data = self.conn.recv(1024)
        if data:
            print("Recv data from {0}: {1}".format(self.addr, data))
        else:
            self.stop = True

    def handle_write(self):
        data = "Hello, {0}, I am GODFATHER!".format(self.addr)
        self.conn.send(data)
        print("Send to {0}: {1}".format(self.addr, data))


if __name__ == '__main__':
    Server().start()
    try:
        Loop().serve_forever()
    except KeyboardInterrupt:
        Loop().stop()
