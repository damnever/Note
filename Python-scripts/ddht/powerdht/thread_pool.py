#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
A simple thread pool.

Queue is a synchronized queue class, which is safe in multiple threads.
"""


import Queue
import threading

from log import logger


class WorkerManager(object):
    """ WorkerManger object manage Workers, Ｏ（∩＿∩）Ｏ～.

    Parameters:
       - thread_num: max number of thread to process task.
       - q_size: max number of work_queue, if it less than or equal to 0,
       the memory will rise violently, at least in my Ubuntu server 14.04.
    """

    _intsance_lock = threading.Lock()

    def __new__(cls, *args, **kwargs):
        if not hasattr(cls, '_instance'):
            with cls._intsance_lock:
                if not hasattr(cls, '_instance'):
                    # New instance after double check
                    cls._instance = super(WorkerManager, cls).__new__(
                        cls, *args, **kwargs)
        return cls._instance

    def __init__(self, thread_num=5, q_size=200):
        self.work_queue = Queue.Queue(q_size)
        self.workers = []
        self._init_thread_pool(thread_num)

    def _init_thread_pool(self, thread_num):
        for i in xrange(thread_num):
            self.workers.append(Worker(self.work_queue))

    def add_task(self, func, *args, **kwargs):
        self.work_queue.put(Task(1, func, args, kwargs))

    def kill_all_task(self):
        for worker in self.workers:
            worker.dead()
        for worker in self.workers:
            worker.join()
        del self.workers


class Worker(threading.Thread):
    """ A worker object is a thread. It will check if work queue is empty,
    if not, process task, else keep check.

    - work_queue: WrokerManger.work_queue.
    """

    def __init__(self, work_queue):
        threading.Thread.__init__(self)
        # self.daemon = True
        self.work_queue = work_queue
        self.start()

    def run(self):
        while 1:
            try:
                task = self.work_queue.get(block=False)
                if not task.run:
                    self.work_queue.task_done()
                    break
            except Queue.Empty:
                continue
            else:
                try:
                    task.func(*task.args, **task.kwargs)
                except Exception:
                    logger.error('Error occured when execute task:',
                                 exc_info=True)
                finally:
                    self.work_queue.task_done()

    def dead(self):
        self.work_queue.put(Task(0, None, None, None))


class Task(object):
    """ Task object is used to encapsulate the task function.

    Parameters:
      - run: if True, Worker will process task, else quit.
      - func: task what you want to process.
      - args: *args might be passed to "func".
      - kwargs: **kwargs might be passed to "func".
    """
    __slots__ = ['run', 'func', 'args', 'kwargs']

    def __init__(self, run, func, args, kwargs):
        self.run = run
        self.func = func
        self.args = args
        self.kwargs = kwargs
