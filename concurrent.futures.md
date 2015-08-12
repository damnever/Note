## concurrent.futures -- Launching parallel tasks

> 此文是 [Python 3 concurrent.futures (New in 3.2)](https://docs.python.org/3/library/concurrent.futures.html#module-concurrent.futures) 标准库版的简单翻译，第三方库 [concurrent.futures](http://pythonhosted.org/futures/) 基本一样。

---

*   [Executor Objects](#Executor-Object)
    *   [class concurrent.futures.Executor](#Executor)
*   [ThreadPoolExecutor](#ThreadPoolExecutor)
	*   [class concurrent.futures.ThreadPoolExecutor(max_workers)](#ThreadPoolExecutor-Object)
	*   [ThreadPoolExecutor Example](#ThreadPoolExecutor-Example)
*   [ProcessPoolExecutor](#ProcessPoolExecutor)
	*   [class concurrent.futures.ProcessPoolExecutor(max_workers=None)](#ProcessPoolExecutor-Object)
	*   [ProcessPoolExecutor Example](#ProcessPoolExecutor-Example)
*   [Future Objects](#Future-Objects)
	*   [class concurrent.futures.Future](#Future)
*   [Module Functions](# Module-Functions)
*   [Exception classes](#Exception-classes)


---

`concurrent.futures`模块给异步调用提供了一个高级接口。

异步执行的可以是线程，通过使用`ThreadPoolExecutor`，也可以进程，通过使用`ProcessPoolExecutor`。都实现了由抽象类`Executor`所定义的一致接口。

<h3 id="Executor-Object">Executor Objects</h3>

<h5 id="Executor">class concurrent.futures.Executor</h5>

一个提供了方法去执行异步调用的抽象类。这个类不应该被直接使用，而应该通过具体的子类来使用。

- `submit(fn, *args, **kwargs)`

 通过调度 callable、fn 以`fn(*args **kwargs)`的形式执行，并且返回一个`Future`对象来表示 callable 的执行。

```Python
with ThreadPoolExecutor(max_workers=1) as executor:
    future = executor.submit(pow, 323, 1235)
    print(future.result())
```

- `map(func, *iterables, timeout=None)`

 等价于`map(func, *iterables)`，除了`func`是被异步执行并且这些函数调用可能同时发生。如果迭代器的`__next__()`被调用并且`Executor.map()`从开始调用的`timeout`秒之后还没有得到有效结果，将会引发`TimeoutError`。参数`timeout`可以是一个整数(int)或者浮点数(float)，如果没有给定`timeout`或者给定的值为`None`，不会有等待时间的限制。如果一个调用引发了一个异常，异常会在它的值从迭代器重新取回时引发。

- `shutdown(wait=True)`

 给`executor`发送信号，告诉它应该释放当前已经完成执行的`futures`所使用的资源。在调用此方法之后再次调用`Executor.submit()`和`Executor.map()`将会引发`RuntimeError`异常。

 如果`wait`为`True`，直到**所有**正在执行的`futures`完成执行，并且相关的资源被释放掉，这个方法才会返回。如果`wait`为`False`，这个方法将会立即返回，并且释放掉已经执行完成的`futures`所占用的资源。不管等待的耗费，在所有的`futures`完成执行之前整个`Python`程序都不会退出。

 你应该避免调用这个方法如果你使用`with`语句的话，上下文管理器将会自动的关闭`Executor`（它会等待并调用`wait`设为`True`的`Executor.shutdown()`）。

```Python
import shutil
with ThreadPoolExecutor(max_workers=4) as e:
    e.submit(shutil.copy, 'src1.txt', 'dest1.txt')
    e.submit(shutil.copy, 'src2.txt', 'dest2.txt')
    e.submit(shutil.copy, 'src3.txt', 'dest3.txt')
    e.submit(shutil.copy, 'src3.txt', 'dest4.txt')
```

<h3 id="ThreadPoolExecutor">ThreadPoolExecutor</h3>

`ThreadPoolExecutor`是`Executor`的一个子类，以线程池的方式实现异步调用。

当一个与`Future`相关的调用正在等待另一个`Future`的结果，可能会引发死锁。

```Python
import time
def wait_on_b():
    time.sleep(5)
    print(b.result()) # b will never complete because it is waiting on a.
    return 5

def wait_on_a():
    time.sleep(5)
    print(a.result()) # a will never complete because it is waiting on b.
    return 6


executor = ThreadPoolExecutor(max_workers=2)
a = executor.submit(wait_on_b)
b = executor.submit(wait_on_a)
```

这种情况也是：

```Python
def wait_on_future():
    f = executor.submit(pow, 5, 2)
    # This will never complete because there is only one worker thread and
    # it is executing this function.
    print(f.result())

executor = ThreadPoolExecutor(max_workers=1)
executor.submit(wait_on_future)
```

<h5 id="ThreadPoolExecutor-Object">class concurrent.futures.ThreadPoolExecutor(max_workers)</h5>

一个`Executor`的子类，使用线程数最多为`max_workers`的池来实现异步调用。

<h4 id="ThreadPoolExecutor-Example">ThreadPoolExecutor Example</h4>

```Python
import concurrent.futures
import urllib.request

URLS = ['http://www.foxnews.com/',
        'http://www.cnn.com/',
        'http://europe.wsj.com/',
        'http://www.bbc.co.uk/',
        'http://some-made-up-domain.com/']

# Retrieve a single page and report the url and contents
def load_url(url, timeout):
    with urllib.request.urlopen(url, timeout=timeout) as conn:
        return conn.read()

# We can use a with statement to ensure threads are cleaned up promptly
with concurrent.futures.ThreadPoolExecutor(max_workers=5) as executor:
    # Start the load operations and mark each future with its URL
    future_to_url = {executor.submit(load_url, url, 60): url for url in URLS}
    for future in concurrent.futures.as_completed(future_to_url):
        url = future_to_url[future]
        try:
            data = future.result()
        except Exception as exc:
            print('%r generated an exception: %s' % (url, exc))
        else:
            print('%r page is %d bytes' % (url, len(data)))
```

<h3 id="ProcessPoolExecutor">ProcessPoolExecutor</h3>

`ProcessPoolExecutor`是`Executor`的子类，通过进程池来实现异步调用。`ProcessPoolExecutor`使用了`multiprocessing `模块，这个模块避开了全局解释器锁（Global Interpreter Lock），但也意味着只有可pickle（序列化？）的对象能执行并返回。

对于`__main__`模块来说工作子进程必须是可导入的。也就是说`ProcessPoolExecutor`在交互解释器下是无法工作的。

从一个 callable 提交到`ProcessPoolExecutor`时调用`Executor`或者`Future`的方法会导致死锁。

<h5 id="ProcessPoolExecutor-Object">class concurrent.futures.ProcessPoolExecutor(max_workers=None)</h5>

`Executor`的子类，用进程数最多为`max_workers`的池来实现异步调用。如果没有给定`max_workers`或者为`None`，默认为机器处理器的数量。

> Change in version3.3: 如果一个工作进程突然终止了，会引发一个`BrokenProcessPool`异常。在以前的版本中，这样的行为是未定义的（不确定的），仅在 executor 中的操作，或者 future 会经常死掉，或者死锁。

<h4 id="ProcessPoolExecutor-Example">ProcessPoolExecutor Example</h4>

```Python
import concurrent.futures
import math

PRIMES = [
    112272535095293,
    112582705942171,
    112272535095293,
    115280095190773,
    115797848077099,
    1099726899285419]

def is_prime(n):
    if n % 2 == 0:
        return False

    sqrt_n = int(math.floor(math.sqrt(n)))
    for i in range(3, sqrt_n + 1, 2):
        if n % i == 0:
            return False
    return True

def main():
    with concurrent.futures.ProcessPoolExecutor() as executor:
        for number, prime in zip(PRIMES, executor.map(is_prime, PRIMES)):
            print('%d is prime: %s' % (number, prime))

if __name__ == '__main__':
    main()
```

<h3 id="Future-Objects">Future Objects</h3>

`Future`类封装了一个 callable 的异步执行。`Future`实例通过`Executor.submit()`创建。

<h5 id="Future">class concurrent.futures.Future</h5>

封装了一个 callable 的异步执行。`Future`实例被`Executor.submit()`创建，不应该被直接创建除了测试。

 - `cancel()`

 尝试取消调用。如果调用是当前正在执行的并且不能被取消，这个方法返回`False`。否则这个调用会被取消并返回`True`。

 - `cancelled()`

 返回`True`，如果调用被成功取消了。

 - `running()`

 返回`True`，如果调用当前正在执行并且不能被取消。

 - `done()`

 返回`True`，如果调用被成功取消了，或者已完成了运行。

 - `result(timeout=None)`

 返回由调用返回的值。如果调用还未完成，这个方法将会等上`timeout`秒。如果调用在`timeout`秒之内都未完成，`TimeoutError`异常将会被抛出。`timeout`可以是整型(int)或浮点型(float)，如果没有给定或者为`None`，等待时间是没有限制的。

 - `exception(timeout=None)`

 返回一个由调用引发的异常。如果调用还未完成，这个方法将会等上`timeout`秒。如果调用在`timeout`秒之内都未完成，`TimeoutError`异常将会被抛出。`timeout`可以是整型(int)或浮点型(float)，如果没有给定或者为`None`，等待时间是没有限制的。

 如果 future 在完成之前被取消了，`CancelledError `将会被抛出。

 如果调用已完成且没有异常，返回`None`。

 - `add_done_callback(fn)`

 将可调用的`fn`附在 future 上。以 future 作为唯一参数的`fn`将会被调用，当 future 被取消或者完成运行时。

 被添加的 callable 按被添加的顺序调用，并且始终由属于添加它们的进程的线程调用。如果 callable 抛出的异常是`Exception`的子类，异常会被记录并忽略。如果 callable 抛出的异常是`BaseException`的子类，这种行为是未定义的（不确定的）。

 如果 callable 已经完成或者被取消了，`fn`会立即执行。

下面的`Future`方法只应该用在单元测试或者`Executor`的实现中：

 - `set_running_or_notify_cancel()`

 这个方法仅应该被`Executor`的实现调用，在单元测试之前执行与`Future`相关的工作。

 如果方法返回`False`那么`Future`已经被取消了，例如，`Future.cancel()`被调用并且返回`True`。任何正在等待`Future`完成（例如，传给`as_completed()`或`wait()`的 future）的线程都会被唤醒。

 如果返回`True`那么`Future`未被取消并被传到运行状态，例如，调用`Future.running()`会返回`True`。
 
 这个方法只能被调用一次，并且不能在`Future.set_result()`和`Future.set_exception()`调用之后调用。

 - `set_result(result)`

 给与`Future`相关的工作设置一个返回结果。

 这个方法应该仅仅用于`Executor`的实现或者单元测试中。

 - `set_exception(exception)`

 给与`Future`相关的工作的结果设置一个`Exception`异常。

 这个方法应该仅仅用于`Executor`的实现或者单元测试中。

<h3 id=" Module-Functions">Module Functions</h3>

- `concurrent.futures.wait(fs, timeout=None, return_when=ALL_COMPLETED)`

 等待由`fs`传入的所有`Future`实例（可能由不同的`Executor`创建）完成执行。返回一个已命名集合组成的二元组，第一个集合，叫`done`，包含等待完成之前（函数完成前？？）所有已完成（完成或被取消）的 futures，第二个集合叫`not_done`，包含未完成的 futures。

 `timeout`用来控制返回之前的最大等待时间（秒）。`timeout`可以是 int 或 float，如果没有给定或者为`None`，等待时间无限制。

 `return_when `表示什么时候函数应该返回。其值应该是一下常量之一：
 
 |Constant|Description|
 |--------|-----------|
 |FIRST_COMPLETED|只要有任何一个 future 完成或取消，函数就会返回|
 |FIRST_EXCEPTION|只要有任何一个 future 完成的时候发生异常，函数就会返回。如果没有一个 future 引发异常，等价于 ALL_COMPLETED|
 |ALL_COMPLETED|所有的 future 都完成或者被取消，函数才会返回|
 
- `concurrent.futures.as_completed(fs, timeout=None)`

 返回一个迭代器，并依次返回作为`fs`传入的已完成（完成或被取消）的`Future`实例（可能由不同的`Executor`创建）。`fs`中任何重复的都只会返回一次。任何在调用`as_completed()`函数之前完成的 futures，将会被迭代器立即返回。如果迭代器的`__next__()`被调用了，并且在`as_completed()`被调用的`timeout`秒之后还未产生有效的值，将会引发`TimeoutError`。`timeout`可以是 int 或 float，如果没有给定或者为`None`，等待时间无限制。

> See also:
> [PEP 3148](http://www.python.org/dev/peps/pep-3148) – futures - execute computations asynchronously
The proposal which described this feature for inclusion in the Python standard library.

<h3 id="Exception-classes">Exception classes</h3>

- `exception concurrent.futures.process.BrokenProcessPool`

 从`RunTimeError`派生，当`ProcessPoolExecutor `的一个工作进程在 non-clean fasion （例如，从外部被杀死）中被终止。