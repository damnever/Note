#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
A powerful dht crawler, the speed more than the traditional.
"""

from __future__ import print_function
from __future__ import division

import socket
import time
import Queue
import threading

from bencode import bencode, bdecode, BTFailure
from utils import random_node_id, decode_nodes, random_chr
from thread_pool import WorkerManager
from log import logger


__all__ = ['DHT', 'ThreadSupport']


K = 8

BOOTSTRAP_NODES = (
    ("router.bittorrent.com", 6881),
    ("dht.transmissionbt.com", 6881),
    ("router.utorrent.com", 6881),
)

INTERVAL = 2


class InvalidArgument(Exception):
    pass


class _Node(object):
    """ The DHT composed of nodes and stores the location of peers,
    nid(node ID) just like KRPC says, (host, port) used to send message.
    """
    __slots__ = ['nid', 'host', 'port']

    def __init__(self, nid, host, port):
        self.nid = nid
        self.host = host
        self.port = port

    def __repr__(self):
        return '<{0}, {1}, {2}>'.format(self.nid, self.host, self.port)

    __str__ = __repr__


class _KRPC(object):
    """ KRPC Protocol, which implements by UDP, just a protocol like
    HTTP.

    By the protocol, we can receive request and send response from
    remote BitTorrent client/server, so we can get what(infohash)
    we want.

    Attention: It doesn't implements routing table and buket(nodes=8),
    because it's no necessary, please see:
     * https://github.com/0x0d/dhtfck/tree/master/btdht
     * https://github.com/laomayi/simDHT

    You can get more detail information from:
    http://www.bittorrent.org/beps/bep_0005.html

    Parameters:
      - node_size: max number of nodes.
      - host: ip adddress, UDP server binded.
      - sock: UDP socket.
    """

    k = K

    def __init__(self, node_size, host, sock):
        self._sock = sock

        self.max_node_size = node_size
        self.nodes = Queue.Queue(maxsize=node_size)

        self._host = host
        self._nid = random_node_id()

    def error_message(self, msg, address):
        error_msg = ' '.join([str(i) for i in msg['e']])
        logger.info('Get error message "%s" from "%s:%d"',
                    error_msg, *address)

    def send_message(self, data, address):
        try:
            msg = bencode(data)
            self._sock.sendto(msg, address)
        except BTFailure:
            logger.error('Bencode message failed!')
        except socket.error:
            logger.error('Send message ot %s:%d failed!',
                         *address, exc_info=True)

    def find_node(self, address, node_id=None):
        sender_id = self.get_neighbor(node_id or random_node_id())
        target = node_id or self._nid
        msg = {
            't': random_chr(),
            'y': 'q',
            'q': 'find_node',
            'a': {'id': sender_id, 'target': target}
        }
        self.send_message(msg, address)
        logger.info('Send FIND_NODE request to %s:%d.', *address)

    def find_node_response(self, msg, address):
        logger.info('Received FIND_NODE response from %s:%d.', *address)
        if not msg['r'].get('nodes', None):
            return
        nodes = decode_nodes(msg['r']['nodes'])
        try:
            for node in nodes:
                (nid, host, port) = node
                if host == self._host:
                    continue
                if port < 1024:
                    continue
                self.nodes.put(_Node(nid, host, port))
        except Exception:  # yield None
            logger.warning('No nodes in FIND_NODE response from %s:%d.',
                           *address)

    def ping_received(self, msg, address):
        logger.info('Received PING request from %s:%d.', *address)
        node_id = msg['a']['id']
        rmsg = {
            't': msg['t'],
            'y': 'r',
            'r': {'id': self.get_neighbor(node_id)}
        }
        self.nodes.put(_Node(node_id, address[0], address[1]))
        self.send_message(rmsg, address)
        logger.info('Send PING response to %s:%d.', *address)

    def find_node_received(self, msg, address):
        logger.info('Reveived FIND_NODE request from %s:%d.', *address)
        target = msg['a']['target']
        node_id = msg['a']['id']
        rmsg = {
            't': msg['t'],
            'y': 'r',
            'r': {'id': self.get_neighbor(target), 'nodes': ''},
        }
        self.nodes.put(_Node(node_id, address[0], address[1]))
        self.send_message(rmsg, address)
        logger.info('Send FIND_NODE response to %s:%d.', *address)

    def get_peers_received(self, msg, address):
        logger.info('Received GET_PEER request from %s:%d', *address)
        infohash = msg['a']['info_hash']
        node_id = msg['a']['id']
        rmsg = {
            't': msg['t'],
            'y': 'r',
            'r': {
                'id': self.get_neighbor(infohash),
                'nodes': '',
                'token': infohash[:4],
            }
        }
        self.nodes.put(_Node(node_id, address[0], address[1]))
        self.send_message(rmsg, address)
        logger.info('Send GET_PEERS response to %s:%d.', *address)

    def announce_peer_received(self, msg, address):
        logger.info('Received ANNOUNCE_PEER request from %s:%d.', *address)
        infohash = msg['a']['info_hash']
        node_id = msg['a']['id']

        if msg['a']['token'] == infohash[:4]:
            self.handle_infohash(infohash, address, time.gmtime())
        rmsg = {
            't': msg['t'],
            'y': 'r',
            'r': {'id': self.get_neighbor(node_id)}
        }
        self.send_message(rmsg, address)
        logger.info('Send ANNOUNCE_PEER response to %s:%d.', *address)

    def get_neighbor(self, target):
        return target[:10] + self._nid[10:]

    def handle_infohash(self, infohash, address, date):
        raise NotImplementedError("Must be implemented by subclass.")


class DHT(_KRPC):
    """ DHT server.

    Parameters:
      - host: ip, UDP socket will bind.
      - port: port, UDP socket will bind.
      - node_size: the number of nodes, passed to KRPC __init__ method.
    """

    address_family = socket.AF_INET
    socket_type = socket.SOCK_DGRAM
    ip_protocol = socket.IPPROTO_UDP

    time_out = 0
    buffer_size = 65507

    bootstrap_nodes = BOOTSTRAP_NODES
    interval = INTERVAL

    def __init__(self, host='0.0.0.0', port=6881, node_size=2**160):
        self.socket = socket.socket(
            self.address_family, self.socket_type, self.ip_protocol)
        # reuse addr
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        # self.socket.setblocking(0)
        self.socket.bind((host, port))
        super(DHT, self).__init__(node_size, host, self.socket)

        self.server_thread = threading.Thread(target=self.serve_forever)
        self.server_thread.daemon = True

        self.message_types = {
            'r': self.find_node_response,
            'q': self.query_received,
            'e': self.error_message,
        }
        self.query_received_actions = {
            'ping': self.ping_received,
            'find_node': self.find_node_received,
            'get_peers': self.get_peers_received,
            'announce_peer': self.announce_peer_received
        }
        self._handlers = []

    def handle_infohash(self, infohash, address, date):
        self.notify_handlers(infohash, address, date)

    def add_handler(self, handler):
        """ Add handler to deal with (infohash, address, time). """
        self._handlers.append(handler)

    def notify_handlers(self, infohash, address, date):
        """ Notify all handlers, when new infohash found. """
        for handler in self._handlers:
            handler.hold(infohash.encode('hex'), address, date)

    def startd(self):
        """ Start server. """
        print('[\(^o^)/~] Start DHT Server ...')
        self.server_thread.start()
        self.auto_find_node()

    def bootstrap(self):
        """ Join into DHT network. """
        logger.info('Join into DHT network ...')
        if self.nodes.qsize() < self.k:
            for address in self.bootstrap_nodes:
                ip = socket.gethostbyname(address[0])
                self.find_node((ip, address[1]))
                time.sleep(self.interval)
        timer = threading.Timer((self.interval * 2), self.bootstrap)
        timer.start()

    def serve_forever(self):
        """ Always receives message from remote host. """
        self.bootstrap()
        while 1:
            try:
                (data, address) = self.socket.recvfrom(self.buffer_size)
                self.handle_recv(data, address)
            except Exception:
                pass

    def auto_find_node(self):
        """ Auto to send find_node message, deppend on node of nodes
        deque.
        """
        wait = 1 / self.max_node_size
        while 1:
            if not self.nodes.empty():
                node = self.nodes.get_nowait()
                self.find_node((node.host, node.port), node.nid)
                self.nodes.task_done()
            else:  # nodes empty
                time.sleep(wait * 10)
            time.sleep(wait)

    def stopd(self):
        """ Stop server. """
        self.socket.close()

    def handle_recv(self, data, address):
        """ Handle message, that we received. """
        try:
            msg = bdecode(data)
            self.message_types[msg['y']](msg, address)
        except BTFailure:
            logger.error('Bdecode message failed!')
        # 'vote'?
        # http://lists.ibiblio.org/pipermail/bittorrent/2011-January/002414.html
        except KeyError:
            logger.error('No method can handle "%s".', msg)

    def query_received(self, msg, address):
        self.query_received_actions[msg['q']](msg, address)


class ThreadSupport(object):
    """ The decorator is used to add a multi-thread support to
    DHT server.

    Parameters:
      - thread_num: the number of thread to handle message from remote
      host, which will pass to thread_pool.WorkerManger __init__ method.
      - q_size: the workers number of thread_pool.WorkManger.work_queue,
      which will pass to thread_pool.WorkerManger __init__ method.
    """

    def __init__(self, cls, thread_num=6, q_size=200):
        self._cls = cls
        self._worker_manager = WorkerManager(thread_num, q_size)

    def __call__(self, *args, **kwargs):

        def _serve_forever(this):
            this.bootstrap()
            while 1:
                try:
                    (data, address) = this.socket.recvfrom(this.buffer_size)
                    self._worker_manager.add_task(
                        this.handle_recv, data, address)
                except socket.error:
                    pass

        def _stopd(this):
            self._worker_manager.kill_all_task()
            this.socket.close()

        # Replace `serve_forever` and `stopd` method of `DHT`.
        # Use thread pool to handle message in `serve_forever`.
        self._cls.serve_forever = _serve_forever
        self._cls.stopd = _stopd
        dht = self._cls(*args, **kwargs)
        return dht
