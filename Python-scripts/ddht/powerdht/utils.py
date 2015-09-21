#!/usr/bin/env python
# -*- coding: utf-8 -*-

# some utils, which will use in KRPC

from __future__ import print_function

import random
import hashlib
import socket
import struct

TRANSATION_ID_BYTES = 2
NODE_ID_BYTES = 20


def random_chr(length=TRANSATION_ID_BYTES):
    """ Generate A string of length "length", which consists of
    random ASCII char. """
    return ''.join(chr(random.randint(0, 255)) for _ in xrange(length))


def random_node_id(length=NODE_ID_BYTES):
    """ Generates random node ID. """
    return hashlib.sha1(random_chr(length)).digest()


def s2int(node_id):
    """ Convert node ID (SHA1 string) to hex, then integer. """
    return long(node_id.encode('hex'), 16)


def encode_nodes(nodes):
    """ Encode a list of node(node ID, ip, port) to node contact info, which
    consists of 20-byte node ID, 4-byte IP and 2-byte port in network byte
    order.
    """
    new_nodes = []
    for node in nodes:
        new_nodes.extend([node.ID, socket.inet_aton(node.ip), node.port])
    return struct.pack('!' + '20s4sH' * len(nodes), *new_nodes)


def decode_nodes(nodes):
    """ Decode node contact info into a list of node(node ID, host/ip, port).
    """
    length = len(nodes)
    try:
        for i in xrange(0, length, 26):
            ID = nodes[i: i + 20]
            ip = socket.inet_ntoa(nodes[i + 20: i + 24])
            port = struct.unpack("!H", nodes[i + 24: i + 26])[0]
            yield ID, ip, port
    except Exception:
        yield None


def sort_nodes(nodes, target):
    """ Quick sort nodes deppend distance of node id and get K(8) nodes which
    are the smallest distance(A, B) = |A xor B|.

    In python 2:
      nodes.sort(lambda x, y, t=target_num: cmp(t^s2int(x.ID), t^s2int(y.ID)))
    But I want python 3 to be compatible with the program.
    """
    if len(nodes) <= 1:
        return nodes
    random_index = random.randint(0, len(nodes) - 1)
    pivot = nodes[random_index]
    pivot_dis = s2int(pivot.ID) ^ target
    nodes[0], nodes[random_index] = nodes[random_index], nodes[0]
    return (sort_nodes(
        [x for x in nodes[1:] if s2int(x.ID) ^ target < pivot_dis],
        target) +
        [pivot] +
        sort_nodes(
            [x for x in nodes[1:] if s2int(x.ID) ^ target >= pivot_dis],
            target))
