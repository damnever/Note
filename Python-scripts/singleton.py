# -*- coding: utf-8 -*-

# Q: 为毛这里有个单例模式？
# A: 提个醒！！！
# Q: 你是上天派来的逗逼？两者有啥区别？
# A: 自己看文档... __new__

import threading


class Singleton(object):

    _thread_lock = threading.Lock()

    def __new__(cls, *args, **kwargs):
        if not hasattr(cls, '_instance'):
            with cls._thread_lock:
                if not hasattr(cls, '_instance'):
                    # cls._instance = super(Singleton, cls).__new__(cls)
                    cls._instance = super(Singleton, cls).__new__(
                        cls, *args, **kwargs)
        return cls._instance

    def __init__(self, bar):
        self._bar = bar

    def print_arg(self):
        print(self._bar)


class SingletonGood(object):

    _thread_lock = threading.Lock()

    @classmethod
    def get_instance(cls, *args, **kwargs):
        if not hasattr(cls, '_instance'):
            with cls._thread_lock:
                if not hasattr(cls, '_instance'):
                    # cls._instance = super(SingletonGood, cls).__new__(cls)
                    # cls._instance.__init__(*args, **kwargs)
                    cls._instance = cls(*args, **kwargs)
        return cls._instance

    def __init__(self, bar):
        self._bar = bar

    def print_arg(self):
        print(self._bar)


if __name__ == '__main__':
    obj1 = Singleton('bar')
    obj2 = Singleton('foobar')
    assert id(obj1) == id(obj2)
    obj1.print_arg()  # foobar
    obj2.print_arg()  # foobar

    print('-' * 10)

    obj3 = SingletonGood.get_instance('bar')
    obj4 = SingletonGood.get_instance('foobar')
    assert id(obj3) == id(obj4)
    obj3.print_arg()  # bar
    obj4.print_arg()  # bar