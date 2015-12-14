# -*- coding: utf-8 -*-

from __future__ import print_function, division, absolute_import

try:
    import selectors  # Py3.4+
except:
    from .compat import selectors

from .task import Task


class NotWorkerError(Exception):
    pass


class Loop(object):

    @classmethod
    def instance(cls):
        if not hasattr(cls, '_instance'):
            cls._instance = cls()
        return cls._instance

    def __new__(cls):
        if not hasattr(cls, '_instance'):
            cls._instance = super(Loop, cls).__new__(cls)
            cls._instance.initialize()
        return cls._instance

    def initialize(self):
        self._selector = selectors.DefaultSelector()
        self._workers = set()
        self._stoped = False

    def call_worker(self, worker):
        self._workers.add(worker)
        Task(worker.run())

    #  def add_callback(self, fd, event, callback, future=None):
    #  class _Worker(Worker):
    #  def run(self):
    #  yield self.future(fd, event, callback, future)
    #      self.call_worker(_Worker(self))

    def serve_forever(self):
        while not self._stoped:
            self._proceed()
        self._selector.close()

    def run_until_complete(self):
        while not self._stoped and not self.all_done():
            self._proceed()
        self._selector.close()

    def all_done(self):
        done = True
        done_workers = set()
        for worker in self._workers:
            if worker.is_done():
                done_workers.add(worker)
            else:
                done = False
        self._workers.difference_update(done_workers)
        return done

    def _proceed(self):
        events = self._selector.select()
        for event_key, event_mask in events:
            callback = event_key.data
            callback(event_key.fileobj, event_mask)

    def stoped(self):
        return self._stoped

    def stop(self):
        self._stoped = True
