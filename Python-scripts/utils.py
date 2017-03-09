# -*- coding: utf-8 -*-
import os
import fcntl
import errno
import time
import functools
from threading import Lock

try:
    from gevent import spawn
    from gevent.pool import Pool as WorkerPool
except ImportError:
    from queue import Queue, Empty
    from threading import Event, Thread

    def spawn(func, *args, **kwargs):
        class _T(Thread):
            def kill(self, block=True, timeout=None, **_kws):
                # TODO !!!!!!
                self.join(timeout=0.1)
        t = _T(target=func, args=args, kwargs=kwargs)
        t.daemon = True
        t.start()
        return t

    class WorkerPool(object):
        def __init__(self, size=None):
            self._queue = Queue()
            self._workers = set()
            self._stop = Event()
            self._launch_workers(size)

        def _launch_workers(self, size):
            for _ in range(size):
                t = spawn(self._worker_run)
                self._workers.add(t)

        def _kill_workers(self):
            for t in self._workers:
                if t.is_alive():
                    t.kill(block=False)

        def _worker_run(self):
            while not self._stop.is_set():
                try:
                    func, args, kwargs = self._queue.get(timeout=1)
                    try:
                        self._exec_func(func, args, kwargs)
                    except Exception:
                        pass
                    finally:
                        self._queue.task_done()
                except Empty:
                    time.sleep(0.5)

        def _exec_func(self, func, args, kwargs):
            if args and kwargs:
                func(*args, **kwargs)
            elif args:
                func(*args)
            elif kwargs:
                func(**kwargs)
            else:
                func()

        def apply_async(self, func, args=None, kwargs=None):
            self._queue.put_nowait((func, args, kwargs))

        def join(self, timeout=None, raise_error=None):
            self._stop.set()
            if timeout is None:
                self._queue.join()
            else:
                time.sleep(timeout)
            self._kill_workers()

        def kill(self, block=True, timeout=None):
            self._stop.set()
            if timeout is None:
                if block:
                    self._queue.join()
            else:
                time.sleep(timeout)
            self._kill_workers()


def errno_from_exception(e):
    if hasattr(e, 'errno'):
        return e.errno
    elif e.args:
        return e.args[0]
    else:
        return None


def retry(count, interval=0.1):
    def _deco(func):
        @functools.wraps(func)
        def _wrap(*args, **kwargs):
            err = None
            for i in range(count+1):
                try:
                    return func(*args, **kwargs)
                except Exception as e:
                    err = e
                    if i != count:
                        time.sleep(interval)
            if err is None:
                raise RuntimeError('retry count must be positive integer')
            raise err
        return _wrap
    return _deco


class Constants(dict):

    def __init__(self, *args, **kwargs):
        super(Constants, self).__init__(*args, **kwargs)

    def __setattr__(self, name, value):
        if name in self:
            raise RuntimeError('can not change value of "{}"'.format(name))
        self[name] = value

    def __getattr__(self, name):
        if name not in self:
            raise AttributeError('attribute "{}" does not exists'.format(name))
        return self[name]

    def __delattr__(self, name):
        raise RuntimeError('can not delete "{}"'.format(name))

    def contain_value(self, value):
        return value in self.itervalues()


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


class Configurable(object):
    """A configurable interface is an (abstract) class whose constructor
    acts as a factory function for one of its implementation subclasses.
    The implementation subclass as well as optional keyword arguments to
    its initializer can be set globally at runtime with `configure`.
    """
    __impl_class = None
    __impl_kwargs = None

    def __new__(cls, *args, **kwargs):
        base = cls.configurable_base()
        init_kwargs = {}
        if cls is base:
            impl = cls.configured_class()
            if base.__impl_kwargs:
                init_kwargs.update(base.__impl_kwargs)
        else:
            impl = cls
        init_kwargs.update(kwargs)
        instance = super(Configurable, cls).__new__(impl)
        instance.initialize(*args, **kwargs)
        return instance

    def initialize(self, *args, **kwargs):
        pass

    @classmethod
    def configurable_base(cls):
        raise NotImplementedError()

    @classmethod
    def configurable_default(cls):
        raise NotImplementedError()

    @classmethod
    def configure(cls, impl, **kwargs):
        base = cls.configurable_base()
        if not issubclass(impl, cls):
            raise ValueError('Invalid subclass of {}'.format(cls))
        base.__impl_class = impl
        base.__impl_kwargs = kwargs

    @classmethod
    def clear_configure(cls):
        base = cls.configurable_base()
        base.__impl_class = None
        base.__impl_kwargs = None

    @classmethod
    def configured_class(cls):
        base = cls.configurable_base()
        if cls.__impl_class is None:
            base.__impl_class = cls.configurable_default()
        return base.__impl_class
