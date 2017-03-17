import os
import time
import fcntl
import errno
from thrading import Lock


class FileLock(object):
    """A advisory file lock implementation as a synchronization
    primitive for multi-processes.
    """
    __OPEN_FLAGS = os.O_RDWR | os.O_CREAT | os.O_TRUNC
    __FLOCK_OP = fcntl.LOCK_EX | fcntl.LOCK_NB
    __thread_lock = Lock()
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
        if self.__cached_fd is None:
            try:
                self.__cached_fd = os.open(self.__filename, self.__OPEN_FLAGS)
            except IOError:
                return None
        return self.__cached_fd

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
                stat = os.fstat(self.__cached_fd)
                if stat.st_nlink > 0:
                    return True
            except OSError:
                pass
            del self.__fd
        return False

    def is_locked(self):
        with self.__thread_lock:
            self.__check_pid()
            return self.__is_locked()

    def acquire(self, block=False, timeout=None):
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

                if ((timeout is None and block) or
                        (timeout is not None and time.time()-start < timeout)):
                    time.sleep(0.1)
                    continue
                del self.__fd
                return False

    def release(self):
        with self.__thread_lock:
            self.__check_pid()
            del self.__fd

    def __enter__(self):
        return self.acquire(block=True)

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.release()

    def __repr__(self):
        return '{mod}.{cls}<{fname}>'.format(
            mod=self.__class__.__module__,
            cls=self.__class__.__name__,
            fname=self.__filename
        )
