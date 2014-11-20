#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
    协程实现的'生产者-消费者'模型，整个过程无锁，有一个线程执行，
通过两个子程序（函数）协作完成任务，所以称为"协程"。

consumer函数是一个generator，把consumer传入produce后:
    1 首先调用c.next()启动生成器
    2 一旦生产了东西，通过c.send(n)切换到consumer执行
    3 consumer通过yield拿到消息，处理,又通过yield把结果传回
    4 prouce拿到consumer处理结果，继续生产下一条消息
    5 produce不生产了，通过c.close()关闭consumer，结束
"""

import time

def consumer():
    r = ''
    while True:
        n = yield r
        if not n:
            return
        print "[CONSUMER] consuming {}...".format(n)
        time.sleep(1)
        r = '200 ok'

def produce(c):
    c.next()
    n = 0
    while n < 5:
        n += 1
        print "[PRODUCER] producing {}...".format(n)
        r = c.send(n)
        print "[PRODUCER] consumer return: {}".format(r)
    c.close()

if __name__ == "__main__":
    c = consumer()
    produce(c)
