# -*- coding: utf-8 -*-

import random
import string
import socket
import multiprocessing

from addr import ADDR


def random_msg():
    msg = list(string.ascii_letters)
    random.shuffle(msg)
    return ''.join(msg[random.randint(0, 9): random.randint(15, 25)]) + '\n'


def request():
    client = socket.socket(socket.AF_INET,
                           socket.SOCK_STREAM,
                           socket.IPPROTO_TCP)
    client.connect(ADDR)
    for i in range(10):
        msg = random_msg()
        client.send(msg)
        print('Send to server: {0}'.format(msg))
        print('Recv from server: {0}'.format(client.recv(1024)))
    client.close()


def ccrequest():
    processes = list()
    for i in range(10):
        p = multiprocessing.Process(target=request, args=())
        p.daemon = True
        p.start()
        processes.append(p)

    for p in processes:
        p.join()


if __name__ == '__main__':
    ccrequest()
