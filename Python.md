#Python(2&3) Learning
***

---

[TOC]

---
***
##==The Zen of Python==
-- by Tim Peters

	Beautiful is better than ugly.
	Explicit is better than implicit.
	Simple is better than complex.
	Complex is better than complicated.
	Flat is better than nested.
	Sparse is better than dense.
	Readability counts.
	Special cases aren't special enough to break the rules.
	Although practicality beats purity.
	Errors should never pass silently.
	Unless explicitly silenced.
	In the face of ambiguity, refuse the temptation to guess.
	There should be one-- and preferably only one --obvious way to do it.
	Although that way may not be obvious at first unless you're Dutch.
	Now is better than never.
	Although never is often better than *right* now.
	If the implementation is hard to explain, it's a bad idea.
	If the implementation is easy to explain, it may be a good idea.
	Namespaces are one honking great idea -- let's do more of those!

[禅译](http://wiki.woodpecker.org.cn/moin/PythonZen)

---

##==资源列表==
 - [码农IO Python 精选](http://baoz.me/446252)
 - [官方文档](https://docs.python.org/3.4/)
 - [免费的编程中文书籍索引](https://github.com/justjavac/free-programming-books-zh_CN)

---
***
##==编码==
#####注释
```
  Licensed Materials - Property of CorpA
  (C) Copyright A Corp. 1999, 2011 All Rights Reserved
  CopyRight statement and purpose...
--------------------------------------------------------------------------
File Name : comments.py
Description : description what the main function of this file
Author: Author name
Change Activity:
    list the change activity and time and author information.
```
---
#####参考
 - [符合语言习惯的 Python 编程](http://xiaocong.github.io/slides/idiomatic-python-code/#/main)
 - [10 个常见错误](http://blog.jobbole.com/68256/)
 - [30 个小技巧](http://blog.jobbole.com/63320/)
 - [Python 语言特性和技巧](http://sahandsaba.com/thirty-python-language-features-and-tricks-you-may-not-know.html)
 - [IBM 文档库](https://www.ibm.com/developerworks/cn/views/linux/libraryview.jsp?type_by=%E6%8A%80%E6%9C%AF%E6%96%87%E7%AB%A0&expand=&sort_order=desc&search_by=%E5%8F%AF%E7%88%B1%E7%9A%84+Python&show_abstract=true&sort_by=%E6%97%A5%E6%9C%9F&view_by=search)

---
***
##==正则表达式==
> **方法:**
 - match(): 匹配字符串开始位置。(只匹配开头，有且一个)
 - search(): 扫描字符串,找到第一个位置。(匹配第一次出现的，有且一个)
 - findall(): 找到全部匹配,以列表返回。
 - finditer(): 找到全部匹配,以迭代器返回
 - group(): 返回匹配的完整字符串;可接收多个参数,返回指定序号的分组。
 - start(): 匹配的开始位置; 同样能接收分组序号。和 group() 一样,序号 0 表示整体匹配结果。
 - end(): 匹配的结束位置； 同上。
 - span(): 包含起始、结束位置的元组； 同上。
 - groups(): 返回分组信息。
 - groupdict(): 返回命名分组信息
 - split(): 用 pattern 做分隔符切割字符串。如果用 "(pattern)",那么分隔符也会返回。
 - sub(): 替换子子串。可指定替换次数。sub(pattern, new, s, counts)。
 - subn(): 和 sub() 差不多,不过返回 "(新字符串,替换次数)",可以将替换字符串改成函数,以便替换成不同的结果。

> **编译标志:**(可以用 re.I、re.M 等参数,也可以直接在表达式中添加 "(?iLmsux)" 标志)
 - s: 单行。"." 匹配包括换行符在内的所有字符。
 - i: 忽略大小写。
 - L: 让 "\w" 能匹配当地字符,貌似对中文支支持不好。
 - m: 多行行。
 - x: 忽略多余的空白字符,让表达式更易阅读。
 - u: Unicode。
```
>>> re.findall(r"(?i)[a-z]+", "123ABc123Dxc")
['ABc', 'Dxc']
>>> re.findall(r"[a-z]+", "123ABc123Dxc", re.I)
['ABc', 'Dxc']
```

 - [正则表达式指南](http://blog.jobbole.com/75188/)
 - [高级正则表达式](http://blog.jobbole.com/65605/)
 - [正则表达式的 7 个使用范例](http://blog.jobbole.com/74844/)

---
***
##==援疑质理==
#####动态类型
　**引用和对象**：对象是内存中储存数据的实体，引用指向对象。
 - 可变数据对象(**mutable** object)【列表，字典】，通过改变对象自身而改变对其的引用。
 - 不可变数据对象(**immutable** object)【数字，字符串，元组...】，不能改变对象本身，只能改变引用的指向。

---
#####格式化
 - [关于格式化规范的迷你语言](https://docs.python.org/3.1/library/string.html#format-specification-mini-language)

---
#####文件
> 如果要把数据写到磁盘上,除调用 `flush()` 外,还得用 `sync()`,以确保数据从系统缓冲区同步到磁盘。`close()` 总是会调用用这两个方法。
读方法总能判断不同平台的换行标记,但写方法不会添加任何换行字符,包括 `writelines`。(如必须按不同平台写入换行标记,可使用 `os.linesep`。)
通常建议用迭代器或 `xreadlines()` 代替 `readlines()`,后者默认一次性读取整个文件。

---
#####类
> **实例方法的特殊性**: 当用实例调用时,它是个 bound method,动态绑定到对象实例。而当用类型调用时,是 unbound method,必须显式传递 self 参数。

> **字段 (Field) 和 属性 (Property) 是不同的。**
 - 实例字段存储在 `instance.__dict__`,代表单个对象实体的状态。
 - 静态字段存储在 `class.__dict__`,为所有同类型实例共享。
 - 必须通过类型和实例对象才能访问字段。
 - 以双下划线开头的 class 和 instance 成员视为私有,会被重命名为 `_<class>__<name>` 形式。(module 成员不变)

> 某些时候,既想使用用私有字段,又又不想放弃外部访问权限。
 - 用用重命名后的格式访问。
 - 只用一个下划线,仅提醒,不重命名。

> **继承**
 - super 的类型参数决定了在 mro(多重继承成员搜索顺序) 列表中的搜索起始位置,总是返回该参数后续类型的成员。单继承时总是搜索该参数的基类型。
 - 在多重继承初始化方法中使用用 super 可能会引发一一些奇怪的状况。

> **抽象类**
 - `from abc import ABCMeta, abstractmethod, abstractproperty` #创建抽象类的类型，抽象方法，抽象属性 ，`__metaclass__ = ABCMeta`标明此类为抽象类
 - 抽象类 (Abstract Class) 无无法实例化,且派生类必须 "完整" 实现所有抽象成员才可创建实例。
 - 如果派生类也是抽象类型,那么可以部分实现或完全不实现基类抽象成员。

> **`__getattr__` (访问不存在的成员)，`__setattr__` (对任何成员的赋值操作), `__delattr__` (删除成员操作), `__getattribute__` (访问任何存在或不存在的成员,包括 __dict__)。**
不要在这几个方法里直接访问对象成员,也不要用 hasattr/getattr/setattr/delattr 函数,因为它们会被再次拦截,形成无限循环。正确的做法是直接操作 `__dict__`。而 `__getattribute__` 连 `__dict__` 都会拦截,只能用基类的 `__getattribute__` 返回结果。
```
>>> class A(object):
...     def __init__(self, x):
...         self.x = x
...     def __getattr__(self, name):
...         print "get: ", name
...         return self.__dict__.get(name)
...     def __setattr__(self, name, value):
...         print "set: ", name, value
...         self.__dict__[name] = value
...     def __delattr__(self, name):
...         print "del: ", name
...         self.__dict__.pop(name, None)
...     def __getattribute__(self, name):
...         print "attribute: ", name
...         return object.__getattribute__(self, name)
... 
>>> a = A(10)       # __init__ 里面的 self.x=x 会被 __setattr__ 捕获
set:  x 10
attribute:  __dict__
>>> a.x             # 访问已存在的字段，仅被 __getattribute__捕获
attribute:  x
10
>>> a.y = 20        # 创建新字段，被 __setattr__ 捕获
set:  y 20
attribute:  __dict__
>>> a.z             # 访问不存在字段，被 __getattr__ 捕获
attribute:  z
get:  z
attribute:  __dict__
>>> del a.y         # 删除字段，被 __delattr__ 捕获
del:  y
attribute:  __dict__
```

> **描述符**
 - 实现 `__get__` 和 `__set__` 方法,称为 data descriptor
 - 仅有 `__get__` 方法的,称为 non-data descriptor
 - `__get__` 对 owner_class、owner_instance 访问有效
 - `__set__`、`__delete__` 仅对 owner_instance 访问有效
 - 更多详见 ./Data 下 python 笔记第十章

- [Python自省（反射）指南](http://www.cnblogs.com/huxi/archive/2011/01/02/1924317.html)

---
#####元类 (metaclass)
> **类型对象,负责创建对象实例,控制对象行为 (方法)。而创建类型对象的是元类 (metaclass),也就是类型的类型。**
当解释器创建类型对象时,会按以下顺序查找` __metaclass__` 属性。(这也是为什么在模块中可以用 `__metaclass__` 为所有类型指定默认元类的缘故。)
**`class.__metaclass__ -> bases.__metaclass__ -> module.__metaclass__ -> type`**

 - [深刻理解 Python**2** 中的元类](http://blog.jobbole.com/21351/)
 - [Python**3** 初探](https://www.ibm.com/developerworks/cn/linux/l-python3-2/)

---
#####上下文与 with
> **上下文管理协议 (Context Management Protocol) 为代码块提供了包含初始化和清理操作的安全上下文环境。即便代码块发生异常,清理操作也会被执行。**
 + `__enter__`: 初始化环境,返回上下文对象。
 + `__exit__`: 执行行清理操作。返回 True 时,将阻止异常向外传递。

> 可以在一个 with 语句中使用用多个上下文对象,依次按照 *FILO* 顺序调用。

 - [理解 Python 的 with 语句](http://python.42qu.com/11155501)

---
#####装饰器"@" (decorator)
> **若需要增强某函数的功能，但又不希望修改该函数的定义，这种在代码运行期间动态增加功能的方式，称之为“装饰器”（Decorator）。**
装饰器不一定非得是个函数返回包装对象,也可以是个类,通过 `__call__` 完成目标调用。
装饰器不管被装饰函数有没有参数，都应该有接收参数的功能，这样才能完整的包装而不丢失信息。
```
@decorator
def func():
    pass
# 等价于
def func():
    pass
func = @decorator(func)
```


 - [装饰器](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/001386819879946007bbf6ad052463ab18034f0254bf355000)
 - [Python 修饰器的函数式编程](http://coolshell.cn/articles/11265.html)

---
#####偏函数 (partial)
>  **当函数的参数个数太多，需要简化时，使用functools.partial可以创建一个新的函数，这个新函数可以固定住原函数的部分参数，从而在调用时更简单。**
创建偏函数时，要从**右到左固定参数**，就是说，对于函数f(a1, a2, a3)，可以固定a3，也可以固定a3和a2，也可以固定a3，a2和a1，但不要跳着固定，比如只固定a1和a3，把a2漏下了

---
#####@classmethod @staticmethod
- [静态方法和类方法](http://www.libaoyin.com/2013/08/06/pyhton-staticmethod-classmethod/)
- [它们的权限](http://zhuanlan.zhihu.com/guagua/19760452)

---
#####yield (generator)
 - [Python yield 使用浅析](https://www.ibm.com/developerworks/cn/opensource/os-cn-python-yield/)
 - [生成器](http://sebug.net/paper/books/dive-into-python3/generators.html#generators)

---
#####协程
> **协程(Coroutine)，又称微线程，纤程。
子程序调用总是一个入口，一次返回，调用顺序是明确的。而协程的调用和子程序不同。协程看上去也是子程序，但执行过程中，在子程序内部可中断(不是函数调用，有点类似CPU的中断)，然后转而执行别的子程序，在适当的时候再返回来接着执行。**

 - [协程](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/0013868328689835ecd883d910145dfa8227b539725e5ed000)

---
#####闭包 (Closures)
> **当函数离开创建环境后，依然持有其上下文状态。**

 - [有趣的 Python 闭包](http://feilong.me/2012/06/interesting-python-closures)
 - [闭包和后期绑定](http://shentar.me/%E5%85%B3%E4%BA%8Epython%E7%9A%84%E9%97%AD%E5%8C%85%E5%92%8C%E5%90%8E%E6%9C%9F%E7%BB%91%E5%AE%9A/)
 - [闭包](http://www.cnblogs.com/vamei/archive/2012/12/15/2772451.html)
 - [Python闭包详解](http://www.cnblogs.com/ChrisChen3121/p/3208119.html) *脑大*

---
#####数据结构和算法
> **++bisect++** 使用二分法在一个 "已排序 (sorted) 序列" 中查找合适的插入位置。
 - 只查找可插入位置，不插入
  + `bisect(l, a)` # 查找 a 在序列 l 中的合适插入位置,默认插入以存在元素右侧。
  + `bisect_left(l, a)` # 如果待查找元素在列表中存在,则返回左侧插入位置。
  + `bisect_right(l, a)` # 如果待查找元素在列表中存在,则返回右侧插入位置。
 - 直接插入
  + `insort(l, a)` # 同理，但直接插入
  + `insort_left(l, a)` # 同理，但直接插入
  + `insort_right(l, a)` # 同理，但直接插入


> **++heapq++** 最小堆 (完全平衡二叉树，每个父节点小于等于其左右子节点)
 - `heappush(heap, item)` # 将 item 压入堆中
 - `heappop(heap)` # 总是弹出最小 item（堆顶）
 - `heappushpop(heap, item)` # 先push , 再pop, 弹出值小于等于 item
 - `heapreplace(heap, item)` # 先pop, 再push, 弹出值可能大于 item
 - `heapify(list)` # 将序列转换成堆
 - `nlargest/nsmallest(n, l)` # 从列表(不一定是堆)有序返回最大(最小)的 n 个元素

> **++Queue++** 队列（在 Python3 里为 queue）
Queue： FIFO 队列 / LifoQueue： LIFO 队列（似栈）/ PriorityQueue： 优先级队列，级别低先出
 - `put(item, [, block[, timeout]]) / get([, block[, timeout]])` # 压入/取出元素。**put**：如果 block 为 True，timeout 不为 None，在等待时间 timeout 内队列一直为满，引发 Queue.Full 异常；如果 block 为 False，则timeout被忽略，只要入队的时候队列为满，立即引发 Queue.Full 异常。**get**： 同理引发 Queue.Empty 异常。
 - `put_nowait(item) / get_nowait()` # 相当于 `put(item, False) / get(False)`
 - `empty() / full()` # 返回 bool 型
 - `task_done()` # 在完成一项任务后，向任务已完成的队列发送一个信号
 - `join()` # 等待直到队列为空(阻塞直到任务完成)， 再执行别的操作


- [导航](http://hujiaweibujidao.github.io/python/)

---
#####性能和内存管理
 + 对于频繁增删元素的大大型列表,应该考虑用用链表等数据结构代替。
 + 如果需要创建 "海量" 对象实例,优先考虑 `__slots__`(**`__slots__` 属性会阻止虚拟机创建实例 `__dict__`,仅为名单中的指定成员分配内存空间。这有助于减少内存占用,提升执行行性能,尤其是在需要大量此类对象的时候。**) 。其派生类同样必须用` __slots__` 为新增字段分配存储空间 (即便是空 `__slots__ = []`),否则依然会创建 __dict__,反而导致更慢的执行行效率。。
 - [18 条 Python 代码性能优化小贴士](http://infiniteloop.in/blog/quick-python-performance-optimization-part-i/)
 - [Python 代码优化指南](http://www.ibm.com/developerworks/cn/linux/l-cn-python-optim/)
 - [Python 性能分析指南](http://www.oschina.net/translate/python-performance-analysis)
 - [内存管理](http://www.cnblogs.com/vamei/p/3232088.html)

---
***
##==标准库==
	如果一定要推荐一些 python 的源码去读，我的建议是标准库里关于网络的代码。从 SocketServer 开始，补上 socket 模块的知识，熟悉 TCP/UDP 编程，然后了解 Mixin 机制的最佳示例 SocketServer.{ForkingMixIn|ThreadingMixIn}，借这个机会了解 thread/threading 模块，这时会对并发量提出新的要求，就可以读 select 模块，开始对 select/{epoll|kqueue} 有深刻理解，搞懂以后就可以接触一下异步框架 asyncore 和 asynchat。这时开始出现分岔。如果是做 game 等以 TCP/UDP 协议为基础的应用，可以去读 greenlet 和 gevent，如果是做 web，则走下一条路。

	做 web，读 BaseHTTPServer、SimpleHTTPServer 和 CGIHTTPServer，读 cgi/cgitb，自己随意写框架，读cookielib，读 wsgiref，这时候自己写一个简便的 web framework 就 so easy 了，老板再也不担心你写 web 了，选择 flask/web.py/django/pyramid 都心中有数了。因为走的是 web 的路，所以难免要调用一下别人的 api，搞懂一下 httplib/urllib/urllib/urlparse。
                                                                                                      --引用自某位知友

- [走马观花](http://www.cnblogs.com/vamei/archive/2012/09/13/2682778.html)

#####struct & array
> struct： 在网络传输中，对于 C 语言的 struct 类型将会无法识别，通过此模块来进行 struct 类型和 Python 类型之间的转换。
 - pack(fmt, v1, v2) 转换成 fmt 中描述的 struct类型的二进制形式
 - unpack(fmt, v1, v2) 将二进制形式的 struct 类型通过 fmt 格式转换成 Python 类型

> array： 将 Python 类型的数据（二进制、序列、文件内容）转换成给定类型的 C 数组

#####Time 模块
 - **时间戳（timestamp）**的方式：通常来说，时间戳表示的是从 1970 年 1 月 1 日 00:00:00 开始按秒计算的偏移量（time.gmtime(0)）此模块中的函数无法处理 1970 纪元年以前的日期和时间或太遥远的未来（处理极限取决于 C 函数库，对于 32 位系统来说，是 2038 年）。
 - **UTC**（Coordinated Universal Time，世界协调时）也叫格林威治天文时间，是世界标准时间。在中国为 UTC+8。
 - **DST**（Daylight Saving Time）即夏令时的意思。
 - [time模块详解](http://bbs.fishc.com/thread-51326-1-1.html)
 - [Python 时间和日期](http://www.yiibai.com/python/python_date_time.html#python_date_time)
```
# clock: 返回当前进程消耗的CPU时间 (秒)。
# sleep: 暂停进程 (秒,可以是小小数,以便设置毫秒、微秒级暂停)。
>>> time.clock()
0.027975
>>> time.sleep(1)
# strftime: 将 struct_time 格式化为字符串。
# strptime: 将字符串格式化为 struct_time。
# %H 24小时制, %l 12小时制, %a/%A 简化（完整星期名称）
>>> time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(time.time()))
'2014-09-28 17:44:28'
# timezone: 与 UTC 的时差
# tzname: 当前时区名称
>>> time.timezone / 3600
-8
>>> time.tzname      # 北京时间, China Standard Time
('CST', 'CST')
 ```

---
#####urllib / urllib2
> **++urllib++** 同 Python3 中整合更好的 urllib.parse
 - `urlopen(url[, data[, proxies]])` # 创建一个表示远程 url 的类文件对象，然后像本地文件一样操作这个类文件对象来获取远程数据。参数data表示以post方式提交到 url 的数据。
```
 >>> doc = urllib.urlopen("http://www.baidu.com/")
>>> doc.info()
<httplib.HTTPMessage instance at 0x7f008dbf0710>
>>> doc.info().getheader('Content-Type')
'text/html; charset=utf-8'
```
 - `urlretrieve(url[, filename[, reporthook[, data]]])` # 同上，可以将内容保存在本地文件中，如果获取的内容大小小于原始大小，会引发异常。[ reporthook(blocknum, blocksize, totalsize) 是一个回调函数，可以用来获得文件下载进度]
 - [上述方法的实例](http://www.jb51.net/article/42630.htm)
 - `quote(string[, safe])` # 对字符串进行编码。参数safe指定了不需要编码的字符。
 - `quote(string[, safe])` # 同 quote，但是将空格替换成 + 号。
 - `unquote(string)` # 对字符串进行解码。
 - `unquote_plus(string)` # 同 unquote，但是将 + 替换成空格。
 - `urlencode(query[, doseq])` # 将 dict 或者包含两个元素的元组列表转换成url参数。如果某个键对应的值是一个序列，将 doseq 设置为 True，会生成用 & 分割开的多个值对应同一个键的形式。
```
 >>> urllib.urlencode({"name": ["user", "user2"], "age": 20})
'age=20&name=%5B%27user%27%2C+%27user2%27%5D'
>>> urllib.urlencode({"name": ["user", "user2"], "age": 20}, False)
'age=20&name=%5B%27user%27%2C+%27user2%27%5D'
>>> urllib.urlencode({"name": ["user", "user2"], "age": 20}, True)
'age=20&name=user&name=user2'
```
 - `pathname2url(path)` # 将本地路径转换成url路径，返回值已用quote编码。
```
 >>> urllib.pathname2url("D:\home\lastd\Documents")
'D%3A%5Chome%5Clastd%5CDocuments' # 不再被解析成路径
```
 - `url2pathname(path)` # 将 url 路径转换成本地路径，并用 unquote 解码。
```
 >>> urllib.url2pathname("D%3A%5Chome%5Clastd%5CDocuments")
'D:\\home\\lastd\\Documents'   # \ 被转义, 同 /
```


---
#####网络【socket, socketserver, http.server】
 - [Python socket 网络服务器](http://www.cnblogs.com/vamei/archive/2012/10/30/2744955.html)


---
***
##==网站开发==
 - [42区.漫游指南](http://matrix.42qu.com/)
 - [廖雪峰 Python 实战](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/001397616003925a3d157284cd24bc0952d6c4a7c9d8c55000)

---
***
##==Flask==
#####使用
 - [教程 En](http://blog.miguelgrinberg.com/post/the-flask-mega-tutorial-part-i-hello-world)
 - [Jinja2 官方文档 2.7](http://docs.jinkan.org/docs/jinja2)
 - [Flask 官方文档 0.10.1](https://dormousehole.readthedocs.org/en/latest/)

---
#####扩展
 - [Flask-SQLALchemy](http://docs.jinkan.org/docs/flask-sqlalchemy/) or [SQLALchemy](http://docs.jinkan.org/docs/flask/patterns/sqlalchemy.html)
 - Flask-WTF 处理 Web 表单 [英文-0.95](https://flask-wtf.readthedocs.org/en/latest/quickstart.html) or [中文-0.93](http://docs.jinkan.org/docs/flask-wtf/form.html)
 - [Flask-Babel  i18n&l10n 支持](https://pythonhosted.org/Flask-Babel/)
 - [登录/权限扩展](https://github.com/mattupstate/flask-security)
 - [Flask-Login](https://flask-login.readthedocs.org/en/latest/)
 - [Flask-OpenID](https://pythonhosted.org/Flask-OpenID/)
 - [Flask-Uploads](https://pythonhosted.org/Flask-Uploads/)
 - [用户头头像](http://en.gravatar.com/site/implement/images/python/)

---
***
##==Tornado==
#####使用
> **++HTTP状态码++** 可以使用 RequestHandler 类的`set_status()`方法显式地设置。在某些情况下，Tornado会自动地设置HTTP状态码。【如果你想使用自己的方法代替默认的错误响应，你可以重写`write_error`方法在你的 RequestHandler 类中】下面是一个常用情况的纲要：
 - **404 Not Found**
	Tornado会在HTTP请求的路径无法匹配任何RequestHandler类相对应的模式时返回404（Not Found）响应码。
 - **400 Bad Request**
	如果你调用了一个没有默认值的get_argument函数，并且没有发现给定名称的参数，Tornado将自动返回一个400（Bad Request）响应码。
 - **405 Method Not Allowed**
	如果传入的请求使用了RequestHandler中没有定义的HTTP方法（比如，一个POST请求，但是处理函数中只有定义了get方法），Tornado将返回一个405（Methos Not Allowed）响应码。
 - **500 Internal Server Error**
	当程序遇到任何不能让其退出的错误时，Tornado将返回500（Internal Server Error）响应码。你代码中任何没有捕获的异常也会导致500响应码。
 - **200 OK**
	如果响应成功，并且没有其他返回码被设置，Tornado将默认返回一个200（OK）响应码。

> **++`static_url`++**的疑惑， 为什么不在你的模板中硬编码？有如下几个原因。其一，`static_url`函数创建了一个基于文件内容的 hash 值，并将其添加到 URL 末尾（查询字符串的参数v）。这个 hash 值确保浏览器总是加载一个文件的最新版而不是之前的缓存版本。无论是在你应用的开发阶段，还是在部署到生产环境使用时，都非常有用，因为你的用户不必再为了看到你的静态内容而清除浏览器缓存了。

> **UI模块**是封装模板中包含的标记、样式以及行为的可复用组件。它所定义的元素通常用于多个模板交叉复用或在同一个模板中重复使用。模块本身是一个继承自Tornado的UIModule类的简单Python类，并定义了一个render方法。当一个模板使用{% module Foo(...) %}标签引用一个模块时，Tornado的模板引擎调用模块的render方法，然后返回一个字符串来替换模板中的模块标签。UI模块也可以在渲染后的页面中嵌入自己的JavaScript和CSS文件，或指定额外包含的JavaScript或CSS文件。你可以定义可选的embedded_javascript、embedded_css、javascript_files和css_files方法来实现这一方法。

> **++模板++** (tornado.template)
 - 使用
```
# 设置本地变量，执行函数
{% set *x* = *y* %}
{% apply *function* %} ... {% end %}    # 有待研究
# 转义
{% autoescape *function* %}
{% raw *expr* %}
# 注释
{% comment ... %}
# 外部文件
{% extends *filename* %}
{% block *name* %} ... {% end %}
{% include *filename* %}
{% module *expr* %}    # 渲染 UIModule
# 导入
{% from *x* import *y* %}  # 和 Python语句一样, 有待研究
{% import *module* %}
# 流程控制
{% for *var* in *expr* %} ... {% end %}
{% if *condition* %} ... {% elif *condition* %} ... {% else %} ... {% end %}
{% while *condition* %} ... {% end %}
{% try %} ... {% except %} ... {% else %} ... {% finally %} ... {% end %}
```
 - 默认提供了一些方法: escape(), url_escape(), json_encode(), squeeze().
 - 可以添加任意自命名的方法 (在 tornado.web.RquestHandler 里, 可重写 get_template_namespace):
```
# Python code
def add(x ,y):
       return x + y
tornado.template.execute(add = add)
# the template
{{ add(1, 2) }}
```

> ++HTTP长轮询++在站点或特定用户状态的高度交互反馈通信中非常有用。

 - [Introduction to Tornado](http://www.pythoner.com/tag/tornado)
 - [官方文档中译版](http://www.tornadoweb.cn/documentation#_13)
 - [官方文档4.0.1](http://www.tornadoweb.org/en/stable/)

---
#####源码剖析
 - [Tornado 源码分析系列 (cnblogs.com)](http://www.cnblogs.com/Bozh/archive/2012/07/22/2603976.html)
 - [Tornado 源码解析篇 (nowamagic.net)](http://www.nowamagic.net/librarys/veda/detail/2566)

---