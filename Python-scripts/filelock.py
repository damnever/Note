# -*- coding: utf-8 -*-
import os
import fcntl
import errno
import time
import threading


class FileLock(object):
    """A advisory file lock implementation as a synchronization
    primitive for multi-processes.
    """
    __OPEN_FLAGS = os.O_RDWR | os.O_CREAT | os.O_TRUNC
    __FLOCK_OP = fcntl.LOCK_EX | fcntl.LOCK_NB
    __thread_lock = threading.Lock()  # or, use threading.local
    __instance = None

    def __new__(cls, filename):
        if cls.__instance is None:
            with cls.__thread_lock:
                if cls.__instance is None:
                    cls.__instance = super(FileLock, cls).__new__(cls)
                    cls.__instance.__initialize(filename)
        return cls.__instance

    def __initialize(self, filename):
        self.__filename = filename
        self.__pid = os.getpid()
        self.__cached_fd = None

    @property
    def __fd(self):
        if self.__cached_fd is not None:
            return self.__cached_fd
        try:
            self.__cached_fd = os.open(self._filename, self.__OPEN_FLAGS)
        except IOError:
            return None

    @__fd.deleter
    def __fd(self):
        if self.__cached_fd is not None:
            try:
                os.close(self.__cached_fd)
            except OSError:
                pass
            self.__cached_fd = None

    def __check_pid(self):
        cur_pid = os.getpid()
        if cur_pid != self.__pid:
            self.__pid = cur_pid
            del self.__fd

    def __is_locked(self):
        if self.__cached_fd is not None:
            try:
                os.fstat(self.__cached_fd)
                return True
            except OSError:
                del self.__fd
        return False

    def is_locked(self):
        with self.__thread_lock:
            self.__check_pid()
            return self.__is_locked()

    def acquire(self, timeout=None):
        with self.__thread_lock:  # is that ok?
            self.__check_pid()
            if self.__is_locked():
                return True

            start = time.time()
            while 1:
                if self.__fd is not None:
                    try:
                        fcntl.flock(self.__fd, self.__FLOCK_OP)
                        return True
                    except IOError as e:
                        if e.errno != errno.EAGAIN:
                            del self.__fd
                            return False

                if timeout and time.time() - start < timeout:
                    time.sleep(0.1)
                    continue
                del self.__fd
                return False

    def release(self):
        with self.__thread_lock:
            self.__check_pid()
            del self.__fd

    def __enter__(self):
        return self.acquire()

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.release()

    def __repr__(self):
        return '{mod}.{cls}<{fname}>'.format(
            mod=self.__class__.__module__,
            cls=self.__class__.__name__,
            fname=self.__filename
        )
