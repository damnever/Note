# -*- coding: utf-8 -*-

# https://leetcode.com/problems/implement-stack-using-queues/
#

class Stack(object):
    def __init__(self):
        self._queue1 = list()
        self._queue2 = list()
        self._count = 0
        self._curq = self._queue1

    def push(self, x):
        self._curq.append(x)
        self._count += 1

    def pop(self):
        self._count -= 1
        tmpq = None
        if self._curq == self._queue1:
            self._curq = self._queue2
            tmpq = self._queue1
        else:
            self._curq = self._queue1
            tmpq = self._queue2
        for i in range(self._count):
            elem = tmpq.pop(0)
            self._curq.append(elem)
        tmpq.pop(0)

    def top(self):
        tmpq = None
        if self._curq == self._queue1:
            self._curq = self._queue2
            tmpq = self._queue1
        else:
            self._curq = self._queue1
            tmpq = self._queue2
        for i in range(self._count - 1):
            elem = tmpq.pop(0)
            self._curq.append(elem)
        value = tmpq.pop(0)
        self._curq.append(value)
        return value

    def empty(self):
        return self._count == 0

if __name__ == '__main__':
    stack = Stack()
    stack.push(0)
    stack.push(1)
    print(stack.top())
    stack.pop()
    print(stack.top())
    stack.push(3)
    print(stack.top())
    stack.pop()
    stack.pop()
    print(stack.empty())
