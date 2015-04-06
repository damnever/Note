<h1 style="color:#2bb24c;">Python Learning</h1>

-- [Damnever](http://damnever.github.io/) 倾情奉献

***
待学列表而已 ... 悲哉？
python -m antigravity

---

*   [The Zen of Python](#python-zen)
*   [资源碎片](#python-resource)
*   [编码](#python-code)
    *   [规范](#code-standard)
    *   [调试](#code-debug)
*   [Python 技巧](#python-trick)
*   [正则表达式](#python-regex)
    *   [概览](#regex-overview)
    *   [方法](#regex-method)
    *   [模式功能](#regex-pattern)
    *   [编译标志](#regex-flag)
*   [援疑质理](#faq)
    *   [其它](#faq-other)
    *   [解释器](#faq-interpreter)
    *   [GIL](#faq-gil)
    *   [None 和 空](#faq-none-no)
    *   [is 和 ==](#faq-is-equal)
    *   [编码和解码](#faq-encoding)
    *   [可变对象和不可变对象](#faq-object)
    *   [默认参数值](#faq-default-arg)
    *   [传值还是传引用](#faq-func-pass-value)
    *   [格式化](#faq-format)
    *   [文件](#faq-file)
    *   [函数](#faq-func)
        *   [内置函数](#faq-func-built-in)
        *   [函数式编程](#faq-func-functional-programing)
    *   [偏函数 (partial)](#faq-partial)
    *   [类](#faq-class)
        *   [名称空间](#faq-class-namespace)
        *   [继承](#faq-class-inheritance)
        *   [抽象类](#faq-class-abclass)
        *   [魔术方法](#faq-class-overwrite)
        *   [描述器](#faq-class-descriptor)
        *   [属性 @property](#faq-class-property)
        *   [@classmethod & @staticmethod](#faq-class-func)
    *   [元类 (metaclass)](#faq-metaclass)
    *   [MixIn](#faq-mixin)
    *   [自省](#faq-introspection)
    *   [上下文与 with](#faq-with)
    *   [闭包 (closure)](#faq-closure)
    *   [装饰器"@" (decorator)](#faq-decorator)
    *   [yield & generator](#faq-yield)
    *   [协程](#faq-coroutine)
    *   [数据结构和算法](#faq-algorithm)
    *   [性能和内存管理](#faq-performance)
*   [标准库](#standard-library)
    *   [unittest & doctest](#lib-test)
    *   [collections [Counter, deque, namedtuple, defaultdict, OrderedDict]](#lib-collections)
    *   [itertools](#lib-itertools)
    *   [struct & array](#lib-struct)
    *   [time & datetime](#lib-datetime)
    *   [anydbm & shelve & pickle(cPickle)](#lib-serializable)
    *   [hashlib & hmac & md5 & sha](#lib-encryption)
    *   [json & base64 & uuid](#lib-json)
    *   [threading & Event & Timer](#lib-thread)
    *   [smtplib & email & poplib](#lib-email)
    *   [Cookie & cookielib](#lib-cookie)
    *   [urlparse & urllib & urllib2](#lib-url)
    *   [os](#lib-os)
    *   [sys](#lib-sys)
    *   [SocketServer & SimpleHTTPServer & etc.](#lib-socket)
    *   [select & epoll](#lib-async-1)
    *   [asyncore & asynchat](#lib-async-2)
*   [Web 开发](#web-dev)
*   [Flask](#flask)
    *   [使用](#flask-use)
    *   [插件扩展](#flask-plugin)
*   [Tornado](#tornado)
    *   [使用](#tornado-use)
    *   [源码剖析](#tornado-source-code)

---
***

<h2 id="python-zen" style="color:#c0392b;">The Zen of Python</h2>

-- by Tim Peters
```
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
In the face of ambiguity, refuse the temptation to guess.down
There should be one-- and preferably only one --obvious way to do it.
Although that way may not be obvious at first unless you're Dutch.
Now is better than never.
Although never is often better than *right* now.
If the implementation is hard to explain, it's a bad idea.
If the implementation is easy to explain, it may be a good idea.
Namespaces are one honking great idea -- let's do more of those!
```

=> [禅译](http://wiki.woodpecker.org.cn/moin/PythonZen)

=> [实例](http://artifex.org/~hblanks/talks/2011/pep20_by_example.html)

---
<h2 id="python-resource" style="color:#c0392b;">资源碎片</h2>

 - [The Python(2.7+) Standard Library](https://docs.python.org/2/library/)
 - [Python 标准库 - 德云](http://digitser.net/python/2.7.8/zh-CN/library/index.html)
 - [免费的编程中文书籍索引](https://github.com/justjavac/free-programming-books-zh_CN)
 - [Popular Python recipes](http://code.activestate.com/recipes/langs/python/)
 - [Python 技术文章的收集](http://pyzh.readthedocs.org/en/latest/index.html)
 - [Python 书籍大全](http://www.pythontip.com/study/share_yunpan)
 - [Python 日报](http://py.memect.com/)
 - [码农IO Python 精选](http://baoz.me/446252)
 - [python 模块文档汇总](http://automationtesting.sinaapp.com/blog/python_modules)
 - [ZQ's SCRAPBOOK](http://pythonic.zoomquiet.io/tree/index.html)
 - [Awesome-Python @vinta](https://github.com/vinta/awesome-python)
 - [Top of 2014](http://pycoders.com/2014/) & [译文](http://weekly.pychina.org/issue/issue-147-top2014.html)
 - [PythonShare](https://github.com/Yixiaohan/codeparkshare/blob/master/README.md)
 - [stackoverflow 上 Python 相关回答整理翻译](https://github.com/wklken/stackoverflow-py-top-qa)
 - [收集 @Wilbeibi](https://github.com/Wilbeibi/NotesIndex/blob/master/Python_Index.md)
 - [Python Cheat Sheet](http://crazyguitar.github.io/cheatsheet/python-cs.html)

---
***
<h2 id="python-code" style="color:#c0392b;">编码</h2>

<h3 id="code-standard" style="color:#d35400;">规范</h3>

 - [PEP-0008](http://www.Python.org/dev/peps/pep-0008/) & [中文](https://code.google.com/p/zhong-wiki/wiki/PEP8)
 - [Google Python 风格指南](http://zh-google-styleguide.readthedocs.org/en/latest/google-python-styleguide/)

---
<h3 id="code-debug" style="color:#d35400;">调试</h3>

 - [pdb](https://docs.python.org/2/library/pdb.html)
 - [logging](https://docs.python.org/2/library/logging.html)
 - [doctest](https://docs.python.org/2/library/doctest.html)
 - [unittest](https://docs.python.org/2/library/unittest.html)

---
***
<h2 id="python-trick" style="color:#c0392b;">Python 技巧</h2>

 - [符合语言习惯的 Python 编程 @xiaocong](http://xiaocong.github.io/slides/idiomatic-python-code/#/main)
 - [Python 高级编程 @Dongweiming](http://dongweiming.github.io/Expert-Python/)
 - [10 个常见错误](http://blog.jobbole.com/68256/)
 - [30 Python Language Features and Tricks You May Not Know About](http://sahandsaba.com/thirty-python-language-features-and-tricks-you-may-not-know.html)
 - [Hidden features of Python](http://stackoverflow.com/questions/101268/hidden-features-of-python) & [译文](http://pyzh.readthedocs.org/en/latest/python-hidden-features.html)
 - [《编写高质量代码：改善Python程序的91个建议》](http://book.douban.com/subject/25910544/)

---
___
***
<h2 id="python-regex" style="color:#c0392b;">正则表达式</h2>

- <h3 id="regex-overview" style="color:#d35400;">概览</h3>

 ![](./data/regex.png)

- <h3 id="regex-method" style="color:#d35400;">方法</h3>

 多使用编译对象 compile.
 - `match()` 可指定位置段，默认从开头开始匹配；有且一个。
 - `search()` 可指定位置段，扫描字符串,找到一个为止；有且一个。
 - `findall()` 找到全部匹配,以列表返回。
 - `finditer()` 找到全部匹配,以迭代器返回
 - `group()` 返回匹配的完整字符串;可接收多个参数,返回一个包含那些组所对应值的元组。
 - `start()` 匹配的开始位置; 同样能接收分组序号。和 group() 一样,序号 0 表示整体匹配结果。
 - `end()` 匹配的结束位置； 同上。
 - `span()` 包含起始、结束位置的元组； 同上。
 - `groups()` 返回所有分组信息，从第一组开始。
 - `groupdict()` 返回命名分组信息
 - `split()` 用 pattern 做分隔符切割字符串。如果用 "(pattern)",那么分隔符也会返回。
 - `sub()` 替换子串。缺省次数是0表示替换所有的匹配。sub(pattern, new, s, counts)。
 - `subn()` 和 sub() 差不多,不过返回 "(新字符串,替换次数)",可以将替换字符串改成函数,以便替换成不同的结果。
```Python
## 空匹配只有在它们没有紧挨着前一个匹配时才会被替换掉；‘p’后面的空匹配没被替换
>>> p = re.compile('p*')
>>> p.sub('-', 'abpd')
'-a-b-d-'
## 逆向引用，可以在替换后的字符串中插入原始文本的一部分
## \1 表示匹配到的分组 1，①或者用\g<1>引用分组；②也可以通过 (?P<name>...) 指定分组名，然后通过 \g<name> 来引用匹配到的分组
>>> p = re.compile('section{ ( [^}]* ) }', re.VERBOSE) # 忽略空格
>>> p.sub(r'subsection{\1}', 'section{First} section{Second}')
'subsection{First} subsection{Second}'
## 使用函数作为替换规则；每次调用时，函数会被传入一个 `MatchObject` 的对象作为参数
>>> hex_replace = lambda match: hex(int(match.group()))
>>> p.sub(hex_replace, 'call 65490 for printing, 49152 for user code.')
'call 0xffd2 for printing, 0xc000 for user code.'
```

- <h3 id="regex-pattern" style="color:#d35400;">模式功能</h3>

 - 前向界定符
 	+ `(?=...)` 前向肯定符，当前位置有匹配时成功，否则失败，不再进行后续匹配。
    + `(?!...)` 前向否定符，当前位置不匹配时成功，尝试模式的的其余部分，否则失败。
 - 条件模式
  	+ `(?(id/name)yes-pattern|no-pattern)` 条件为捕获到的分组 id 或名字。

- <h3 id="regex-flag" style="color:#d35400;">编译标志</h3>

 |标志 | 含义|
|----|----|
|DEBUG  |显示表达式编译调试的信息 |
|DOTALL, S	|使 '.' 特殊字符匹配所有任意字符 (包括换行符) |
|IGNORECASE, I	|使匹配对大小写不敏感 |
|LOCALE, L	|使 \w、\W、\b、\B、\s、\S 依赖当前区域设置|
|MULTILINE, M	|多行匹配，影响 ^ 和 $|
|VERBOSE, X	|使表达式易读，忽略空格，注释等|
|UNICODE, U |使 \w、\W、\b、\B, \d、\D、\s、\S 从属 Unicode 字符特性数据库|
```Python
# 使用编译标识的另一种方法 (?iLmsux)
>>> re.findall(r"(?i)[a-z]+", "123ABc123Dxc")
['ABc', 'Dxc']
>>> re.findall(r"[a-z]+", "123ABc123Dxc", re.I)
['ABc', 'Dxc']
```

 => [Python正则表达式操作指南](http://wiki.ubuntu.org.cn/Python%E6%AD%A3%E5%88%99%E8%A1%A8%E8%BE%BE%E5%BC%8F%E6%93%8D%E4%BD%9C%E6%8C%87%E5%8D%97)

 =>  [高级正则表达式](http://blog.jobbole.com/65605/)

---
___
***
<h2 id="faq" style="color:#c0392b;">援疑质理</h2>

 =>  [技能点扫盲](http://www.douban.com/group/topic/28872729/)

---
<h3 id="faq-other" style="color:#d35400;">其它</h3>

1. **`Expression & statement`**: An `expression` is a combination of values, variables, and operators. A `statement` is a unit of code that the Python interpreter can execute.Technically an expression is also a statement, but it is probably simpler to think of them as different things. The important difference is that **`an expression has a value; a statement does not`**.

2. **else** 除常见的 `if ... else ...` 之外，`else` 在 Python 中还有很多其它的用途: `while ... else ...`，`for ... else ...`，`try ... except ... else ...`，在这些情况下，只有循环正常结束(break是非正常结束)或者except没有捕获到异常时，`else`里的代码块才会执行。

3. **浮点数** 运算有陷阱。不要直接比较小数是否相等，最好判断它们是否近似相等，或者使用精准性高的 decimal 模块。
```Python
>>> sum(0.1 for i in range(10)) == 1.0
False
>>> fequal = lambda x, y, places=7: round(abs(x-y), places) == 0
>>> fequal(sum(0.1 for i in range(10)), 1.0)
True
>>> from decimal import Decimal
>>> sum(Decimal('0.1') for i in range(10)) == Decimal('1.0')
True
```

4. **字典(dict)** 的`setdefault(key[, default])`方法只有当键不存在时才会设置默认值；`fromkeys(seq[, value])`设置一组键的默认值，可以用来去重（`{}.fromkeys(seq).keys()`或者`list(set(seq))`）；`view keys()/values()/items()`用于像集合那样操作字典。在 Python 3 中`keys()/values()/items()`都是可迭代的。

5. `python -m` 可以直接运行一些 python 模块。参考：[使用Python解释器的一句话命令](http://pyzh.readthedocs.org/en/latest/single-line-command-with-python.html)

---
___
<h3 id="faq-interpreter" style="color:#d35400;">解释器</h3>

 - [Introduction to the Python Interpreter](http://akaptur.github.io/blog/categories/python-internals/)
 - 中文翻译
  - [函数对象](http://blog.jobbole.com/55327/)
  - [代码对象](http://blog.jobbole.com/56300/)
  - [理解字节码](http://blog.jobbole.com/56761/)
  - [动态语言](http://blog.jobbole.com/57381/)

---
___
<h3 id="faq-gil" style="color:#d35400;">GIL</h3>

GIL(global intepreter lock)，全局解释器锁。在解释器执行任何 Python 代码时，都需要先获得这把锁，在遇到 I/O 操作时会释放这把锁。同一时间只有一个获得了 GIL 的线程在执行，其它线程处于等待状态。可以通过 ctypes 和 C 动态库来让 python 充分利用物理内核的计算能力。

=> [python 线程，GIL 和 ctypes](http://zhuoqiang.me/python-thread-gil-and-ctypes.html)

---
___
<h3 id="faq-none-no" style="color:#d35400;">None 和 空</h3>

Python 通过获取`__nonzero__()`(Python 3 为`__bool__()`)或者`__len__()`方法的调用结果来进行空值判断。

以下数据被当作空：
 - 常量 None
 - 常量 False
 - 数值 0、0L、0.0、0j
 - 空序列或字典，如 ''、()、set()、list()、[]、dict()、{}
 - 类中自定义了`__nonzero__()`方法或`__len__()`方法，并且该方法返回整数0或者False时。

None的类型是NoneType。None可以当作空来处理，但是空并不代表为None。
```Python
>>> def mm(arg):
...     if arg is not None:
...         print arg, 'is not None'
...     if arg is None:
...         print arg, 'is None'
...     if arg:
...         print arg, 'is not empty'
...     if not arg:
...         print arg, 'is empty'
... 
>>> mm([])
[] is not None
[] is empty
```

---
___
<h3 id="faq-is-equal" style="color:#d35400;">is 和 ==</h3>

判断对象(id 值)是否相等用 is，判断值是否相等用 ==。

| 操作符 | 意义 |
|-------|------|
| is | object identity |
| == | equal |

Python 中的string interning(字符串驻留机制)：对于较小的字符串，为了提高系统性能会保留其值的一个副本，创建新的值相同的字符串时直接指向该副本即可。
```Python
>>> a = 'Hello'
>>> b = 'Hello'
>>> a is b
True
>>> a == b
True
>>> id(a) == id(b)
True
>>>
>>> c = 'long string'
>>> d = 'long string'
>>> c is d
False
>>> c == d
True
>>> id(c) == id(d)
False
```

---
___
<h3 id="faq-encoding" style="color:#d35400;">编码和解码</h3>

**规则：unicode.encode() -> bytes，bytes.decode() -> unicode**

str 类型在 Python2 中存储的是 bytes，Python 3 中为 unicode，存储的是 code points。

在 Python 2 中将 byte 字符串和 unicode 字符串连接起来，byte 自动解码成 unicode，生成一个新的 unicode 字符串。但是 byte 字符串到 unicode 字符串可能会失败。

`from __future__ import unicode_literals` 使用 Python 3 特性，把　str　变成　unicode.
```Python
>>> s = '中文'
>>> s; len(s); type(s)
'\xe4\xb8\xad\xe6\x96\x87'
6down
<type 'str'>
>>> us = s.decode('utf-8')
>>> us; len(us); type(us)
u'\u4e2d\u6587'
2
<type 'unicode'>
>>> from __future__ import unicode_literals # Python 3 的特性
>>> s = '中文'; s; len(s)
u'\u4e2d\u6587'
2
```
=> [Unicode 之痛](http://pycoders-weekly-chinese.readthedocs.org/en/latest/issue5/unipain.html)

---
___
<h3 id="faq-object" style="color:#d35400;">可变对象和不可变对象</h3>

**引用和对象**：对象是内存中储存数据的实体，引用指向对象。`a = 1; b = 'str'`中`1`和`'str'`是对象， `a`和`b`是对其的引用，相当于一个标示。

 - 可变数据对象(*mutable* object)【列表，字典，字节数组】，可变对象的更改会直接影响原对象。list 的切片操作可以看做深拷贝，但重新生成一个对象。
 - 不可变数据对象(*immutable* object)【数字，字符串，元组】，对不可变对象的操作会直接创造一个新的对象；字符串对象不允许以索引的方式赋值就是因为其不可变性。
```Python
>>> s = 'Hello, world!'
>>> s[7] = 'W'
Traceback (most recent call last):
  ...
TypeError: 'str' object does not support item assignment
```

对于可变对象：
- list: append, extend, remove, insert 等都不会改变原对象(id)
- dict: 操作键值对 d[k] = v, update, pop 等都不会改变原对象(id)

但是如`a = []; a = [1]`，此时 a 已经是另一个对象了， a 先是`[]`的引用，然后是`[1]`的引用。其实要就是**对象和引用**不能搞混了。

**浅拷贝和深拷贝**间差别仅适于复合对象 (含有其它对象的对象，诸如：列表、字典、类实例):
- 浅拷贝会构筑新复合对象，然后 (尽可能) 把 references (引用) 插入原对象发现复合对象中。
- 深拷贝会构筑新复合对象，然后把 copies (副本) 递归插入原对象发现复合对象中。

```Python
>>> d1 = {'a': 1}
>>> d2 = d1
>>> d2['b'] = 2
>>> d1
{'a': 1, 'b': 2}
>>> d2
{'a': 1, 'b': 2}
>>> id(d1); id(d2)
140710557653544
140710557653544
>>> d2 = {} # 注意对象和引用，我总是搞混 ……
>>> d1
{'a': 1, 'b': 2}
>>> d2
{}
>>> id(d1); id(d2)
140710557653544
140710557663872
>>> 
>>> import copy
>>> d3 = {'a': 1}
>>> d4 = copy.deepcopy(d3)
>>> id(d3); id(d4)
140710557664432
140710557666392
>>> d4['b'] = 2
>>> d4
{'a': 1, 'b': 2}
>>> d3
{'a': 1}
```

---
___
<h3 id="faq-default-arg" style="color:#d35400;">默认参数值</h3>

**用 None 或不可变对象作为函数中的默认参数**

默认参数在函数被调用的时候仅仅被评估一次，以后都会使用第一次的评估结果，如果使用可变对象会带来隐患(如list等)。
```Python
>>> def foo(a, b=[]):
...     b.append(a)
...     print '{0:#x} -> {1}'.format(id(b), b)
... 
>>> foo(1, [])   # 还挺正常的
0x7fd42d897ea8 -> [1]
>>> foo(2, [])
0x7fd42d897ea8 -> [2]
>>> l = [3]      # 这里因为 l 是全局可变对象，参见下面<传值还是传引用>
>>> foo(4, l)
0x7fd42d897e18 -> [3, 4]
>>> foo(5, l)
0x7fd42d897e18 -> [3, 4, 5]
>>> l
[3, 4, 5]
>>> foo(6)      # 使用默认参数值
0x7fd42d883998 -> [6]
>>> foo(7)
0x7fd42d883998 -> [6, 7]   # 仅仅被评估一次
>>> # 改进一下，不再使用可变对象作为默认参数值。
>>> def bar(a, b=None):
...     if b == None: b = []
...     b.append(a)
...     print '{0:#x} -> {1}'.format(id(b), b)
... 
>>> bar(1)
0x7fd42d897ea8 -> [1]
>>> bar(2)
0x7fd42d897ea8 -> [2]   # 仅仅被评估一次
```

=> [Default Parameter Values in Python](http://effbot.org/zone/default-values.htm) & [译文](http://blog.jobbole.com/40088/)

---
___
<h3 id="faq-func-pass-value" style="color:#d35400;">传值还是传引用？</h3>

传对象，不可变对象和可变对象有区别。

函数参数在传递的过程中将整个对象传入，对可变对象的修改在函数外部以及内部都可见，调用者和被调用者之间共享这个对象；而对于不可变对象，由于并不能被改变，因此修改都是通过通过生成一个新的对象然后赋值来实现的。
```Python
>>> ######################## 可变对象传引用
>>> def foo(lst):
...     lst.append('NEW')
...     return lst
... 
>>> lst = [1, 2, 3]
>>> id(lst)
140492465764760
>>> new_lst = foo(lst)
>>> id(new_lst)
140492465764760
>>> new_lst
[1, 2, 3, 'NEW']
>>> lst
[1, 2, 3, 'NEW']
>>> ######################## 可变对象传引用？？？？？
>>> def foo(lst):
...     lst = ['NEW', '???']
...     return lst
... 
>>> lst = [1, 2, 3]
>>> id(lst)
140492465847904
>>> new_lst = foo(lst)
>>> id(new_lst)
140492465848120
>>> new_lst
['NEW', '???']
>>> lst
[1, 2, 3]
```

---
___
<h3 id="faq-format" style="color:#d35400;">格式化</h3>

`'{}, {}'.format('a', 'b')` # 2.7+ only
```Python
>>> class Test:
...     def __str__(self):
...         return '__str__'
...     def __repr__(self):
...         return '__repr__'
... 
>>> 'str: {0!s}'.format(Test())       ## 调用了 str()
'str: __str__'
>>> 'repr: {key!r}'.format(key=Test())      ## 调用了 repr()
'repr: __repr__'
>>> '{2}, {1}, {0}'.format(*args)     ## 解包，list，dict
'3, 2, 1'
>>> import os; 'OS name: {.name}'.format(os)   ## 访问属性
'OS name: posix'
>>> 'One:{lst[0]}, Two:{lst[1]}, Three:{lst[2]}'.format(lst=[1, 2, 3])  ## 访问索引
'One:1, Two:2, Three:3'
>>> '[{0:<10}][{1:*^20}][{2:>10}]'.format('left', 'center|fill', 'right')   ## 对齐，填充
'[left      ][****center|fill*****][     right]'
>>> 'int:{0:d}, hex:{0:x}, oct:{0:o}, bin:{0:b}'.format(23) ## 进制转换
'int:23, hex:17, oct:27, bin:10111'
>>> 'int:{0:d}, hex:{0:#x}, oct:{0:#o}, bin:{0:#b}'.format(23) ## 显示前缀
'int:23, hex:0x17, oct:0o27, bin:0b10111'
>>> '{:,}'.format(1234567890)   ## 把‘,’作为千位分隔符
'1,234,567,890'
>>> import datetime; 'Now: {0:%Y-%m-%d %H:%M:%S}'.format(datetime.datetime.now())  ##格式化时间
'Now: 2015-01-10 21:04:42'
```
使用 indent 来打印 JSON 数据
```Python
>>> import json; data = {u'status': u'OK', u'count': 2, u'results': [{u'age': 27, u'name': u'Oz', u'lactose_intolerant': True}, {u'age': 29, u'name': u'Joe', u'lactose_intolerant': False}]}
>>> print json.dumps(data)
{"status": "OK", "count": 2, "results": [{"age": 27, "name": "Oz", "lactose_intolerant": true}, {"age": 29, "name": "Joe", "lactose_intolerant": false}]}
>>> print json.dumps(data, indent=2)
{
  "status": "OK", 
  "count": 2, 
  "results": [
    {
      "age": 27, 
      "name": "Oz", 
      "lactose_intolerant": true
    }, 
    {
      "age": 29, 
      "name": "Joe", 
      "lactose_intolerant": false
    }
  ]
}
```

=> [关于格式化规范的迷你语言](http://digitser.net/python/2.7.8/zh-CN/library/string.html#format-string-syntax)

---
___
<h3 id="faq-file" style="color:#d35400;">文件</h3>

如果要把数据写到磁盘上,除调用 `flush()` 外,还得用 `sync()`,以确保数据从系统缓冲区同步到磁盘。`close()` 总是会调用用这两个方法。

读方法总能判断不同平台的换行标记,但写方法不会添加任何换行字符,包括 `writelines`。(如必须按不同平台写入换行标记,可使用 `os.linesep`。)

通常建议用迭代器或 `xreadlines()` 代替 `readlines()`，后者默认一次性读取整个文件。d#tornado-source-code

---
___
<h3 id="faq-func" style="color:#d35400;">函数</h3>

<h4 id="faq-func-built-in" style="color:#f39c12;">内置函数</h4>

 - `lambda` 匿名函数，不显式地定义函数，不需要 return，返回值就是表达式的结果。

 - `map(function, sequence[, sequence, ...])` 将传入的函数行为映射到传入的序列的每个元素上，并返回一个 list。

 - `reduce(function, iterable[, initializer])` 传入的函数必须接收两个参数；把函数返回值和后一个列表元素传入函数，如此循环。可选参数`initializer`为一个初始值，没有的话为序列的第一项。

 - `filter(function, iterable)` 把传入的函数依次作用于每个元素，然后根据返回值是 True 还是 False 决定保留还是丢弃该元素。

 - `all(iterable)` 若可迭代序列的**所有**元素都为 True，或序列为空，返回 True。

 - `any(iterable)` 若可迭代序列**任一**元素为 True，返回 True；为空返回 False。

 - `iter(o[, sentinel])` 传入一个序列，返回可迭代对象，可选参数`sentinel`是一个终止标识。

 - 在 Python 3 中`map/filter/zip`都返回可迭代序列，Python 2 `itertools`中相应的`i*`被移除；Python 3 中`reduce`被移至`functools`模块。

```Python
# 一种有用形式，读取文件，直到readline()返回空字符串为止
with open('mydata.txt') as fp:
    for line in iter(fp.readline, ''):
        process_line(line)
```

- `execfile(filename[, globals[, locals]])` (1) 可以用来执行一个文件(Python)，默认传入执行环境的全局名称空间`globals()`和局部名称空间`locals()`；如果只传入`globals`那么`locals`与`globals`相同。(2) `filename`内的全局变量会被默认插入`locals()`，除非使用`global`关键字显示声明；在`filename`内可以改变`globals()`，但是无法改变`locals()`。(3) 如果不使用执行环境的默认名称空间，可以传入`{}`。[**在 Python 3 中被移除，使用`exec(open(fn).read()[, globals[, locals]])`代替**]

```Python
# 使用 tornado.options.parse_config_file 时必须先 define 的一种解决方式
# 来自 https://bitbucket.org/felinx/poweredsites/src/6040f8cf119ca530c9359275f3beaf63d5fc441d/poweredsites/libs/utils.py?at=default
def _parse_config_file(path):
    config = {}
    execfile(path, config, config)
    for name in config:
        if name in options:
            options[name].set(config[name])
        else:
            define(name, default=config[name])
```

=> [名称空间和execfile函数](https://execfile.readthedocs.org/en/latest/)

=> [Python Built-in Functions](https://docs.python.org/2/library/functions.html)

<h4 id="faq-func-functional-programing" style="color:#f39c12;">函数式编程</h4>

Functional Programing，一种抽象程度很高的编程范式，把运算过程尽量写成一系列嵌套的函数调用，函数仅接收输入并产生输出。
```Python
>>> # 找出一个序列中的偶数并将它们乘以3
>>> def even_filter(nums):
...     return filter(lambda x: x%2==0, nums)
... 
>>> def multiply_by_three(nums):
...     return map(lambda x: x*3, nums)
... 
>>> def convert_to_string(nums):
...     return map(lambda x: 'The number: %s' % x, nums)
... 
>>> def pipeline_func(data, fns):
...     return reduce(lambda a, x: x(a), fns, data)
... 
>>> def print_result(pipeline):
...     for each in pipeline:
...         print each
... 
>>> print_result(pipeline_func(range(1, 11), (even_filter, multiply_by_three, convert_to_string)))
The number: 6
The number: 12
The number: 18
The number: 24
The number: 30
```
 => **[函数式编程](http://coolshell.cn/articles/10822.html)**

 => [An introduction to functional programming](https://codewords.hackerschool.com/issues/one/an-introduction-to-functional-programming)

 => [Python函数式编程指南（一）：概述](http://www.cnblogs.com/huxi/archive/2011/06/18/2084316.html)

---
___
<h3 id="faq-partial" style="color:#d35400;">偏函数 (partial)</h3>

**当函数的参数个数太多，需要简化时，使用functools.partial可以创建一个新的函数，这个新函数可以固定住原函数的部分参数，从而在调用时更简单。**

固定参数时，(1)若指定了关键字，就如同函数的关键字参数，必须从右至左固定，不能跳过参数，也就是说最右边的参数必须被先固定。(2)若没有指定关键字，自动从最左边开始固定，传入参数亦同可变长参数(首先`args = (...)`然后`args += (...)`)。
```Python
>>> def f(a, b, c):
...     print 'a={}, b={}, c={}'.format(a, b, c)
...
>>> f(1, 2, 3)
a=1, b=2, c=3
>>> import functools
>>> ff = functools.partial(f, a=1, c=3); ff(2) # (1)不能跳着固定
Traceback (most recent call last):
  ...
TypeError: f() got multiple values for keyword argument 'a'
>>> ff = functools.partial(f, b=2, c=3); ff(1) # (1)
a=1, b=2, c=3
>>> ff = functools.partial(f, 1, c=3); ff(2) # (2)
a=1, b=2, c=3
>>> ff = functools.partial(f, 1); ff(2, 3) # (2)
a=1, b=2, c=3
```



---
___
<h3 id="faq-class" style="color:#d35400;">类</h3>

> Python 2 中存在两种形式的类，1) New-Style Class，这种类需要显示的继承于object或设置文件的默认元类`__metaclass__=type`；2)Clasic Class，在 Python 3 中已经不存在了。

---
<h4 id="faq-class-namespace" style="color:#f39c12;">名称空间</h4>

 类型(class)存储了所有的静态字段和方法(包含实例方法)，而实例(instance)仅存储实例字段。

**字段 (Field) 和 属性 (Property) 是不同的。**
 - 实例字段存储在 `instance.__dict__`,代表单个对象实体的状态。
 - 静态字段存储在 `class.__dict__`,为所有同类型实例共享。
 - 必须通过类型和实例对象才能访问字段。
 - 以双下划线开头的 class/instance 成员视为私有,会被重命名为 `_<class>__<name>` 形式。(module 成员不变)

属性 (Property) 是由 getter、setter、deleter 几个方法构成的逻辑。属性可能直接返回字段值，也可能是动态逻辑运算的结果。

某些时候,既想使用私有字段,又不想放弃外部访问权限。
 - 用重命名后的格式访问。
 - 只用一个下划线,仅提醒,不重命名。

实例方法的特殊性: 当用实例调用时,它是个 bound method,动态绑定到对象实例。而当用类型调用时,是 unbound method,必须显式传递 self 参数。

---
<h4 id="faq-class-inheritance" style="color:#f39c12;">继承</h4>

 多继承，基类顺序影响成员搜索顺序。

 多重继承成员搜索顺序 mro(Method Resolution Order **旧式类是从左至右的深度优先搜索，新式类为C3 MRO算法**) 列表中的搜索起始位置,总是返回该参数后续类型的成员。单继承时总是搜索该参数的基类型。

 在多重继承初始化方法中使用 super 可能会引发一些奇怪的状况。

 => [Understanding Python MRO - Class search path](http://makina-corpus.com/blog/metier/2014/python-tutorial-understanding-python-mro-class-search-path)

---
<h4 id="faq-class-abclass" style="color:#f39c12;">抽象类</h4>

 `from abc import ABCMeta, abstractmethod, abstractproperty` # 创建抽象类的类型，抽象方法，抽象属性 ，`__metaclass__ = ABCMeta`标明此类为抽象类。

 抽象类 (Abstract Class) 无法实例化,且派生类必须 "完整" 实现所有抽象成员才可创建实例。

 如果派生类也是抽象类型,那么可以部分实现或完全不实现基类抽象成员。

---
<h4 id="faq-class-overwrite" style="color:#f39c12;">魔术方法(操作符重载)</h4>

操作时机：
- `__getattr__`: 访问不存在的成员
- `__setattr__`: 对任何成员的赋值操作
- `__delattr__`: 删除成员操作 
- `__getattribute__`: 访问任何存在或不存在的成员,包括 `__dict__`

不要在这几个方法里直接访问对象成员,也不要用 hasattr/getattr/setattr/delattr 函数,因为它们会被这些方法再次拦截,形成无限循环。正确的做法是直接操作 `__dict__`。而 `__getattribute__` 连 `__dict__` 都会拦截,只能用基类的 `__getattribute__` 返回结果。
```Python
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
以属性的方式访问字典的数据。
字典中还有一个特殊方法`__missing__`，找不到 key 时被调用。
```Python
class Dict(dict):

    def __init__(self, **kwargs):
        # super(Dict, self).__init__(**kwargs) 仅用于新式类
        dict.__init__(self, **kwargs)

    def __setattr__(self, key, value):
        self[key] = value

    def __getattr__(self, key):
        # If want to catch 'KeyError' raise 'AttributeError',  
        # '__missing__()' must raise 'KeyError' or remove `__missing__()`.
        return self[key]

    def __delattr__(self, key):
        self.pop(key, None)

    def __missing__(self, key):
        # Raise a error or
        return None

if __name__ == '__main__':
    d = Dict(a=1, b=2)
    print d             # {'a': 1, 'b': 2}
    print d['a']        # 1
    print d.a           # 1
    del d.a
    print d             # {'b': 2}
  　print d['c']　　　　　# None
    print d.c           # None
```
实现`__setitem__()/__getitem__()/__delitem__()`能像序列或字典类型那样操作对象。
```Python
class D(object):
    def __init__(self, **kwargs):
        self._data = kwargs
    def __getitem__(self, key):
        return self._data.get(key)
    def __setitem__(self, key, value):
        self._data[key] = value
    def __delitem__(self, key):
        self._data.pop(key, None)
    def __contains__(self, key):
        return key in self._data.keys()
    def __repr__(self):
        return '{0!r}'.format(self._data)
    __str__ = __repr__

if __name__ == '__main__':
    d = D(a=1, b=2)
    print d          # {'a': 1, 'b': 2}
    print d['a']     # 1
    d['a'] = 10
    print d['a']     # 10
    del d['a']
    print d          # {'b': 2}
```

比较`__cmp__`(Python 3被移除)，`__eq__`==，`__lt__`<，`__le__`<=，`__ne__`!=，`__ge__`>=，`__gt__`>。

=> [A Guide to Python's Magic Methods](http://www.rafekettler.com/magicmethods.html) & [译文](http://pyzh.readthedocs.org/en/latest/python-magic-methods-guide.html)

---
<h4 id="faq-class-descriptor" style="color:#f39c12;">描述器</h4>

一个描述器是一个有“绑定行为”的对象属性(object attribute)，它的访问控制被描述器协议方法重写。实现**描述器协议**的方法（实现任意一个即可）：
 - `descr.__get__(self, obj, type=None) --> value`
 - `descr.__set__(self, obj, value) --> None`
 - `descr.__delete__(self, obj) --> None`

如果一个对象同时定义了`__get__()`和`__set__()`，叫做 **data descriptor**；仅仅定义了`__get__()`叫做 **non-data descriptor**。区别在于：**相对于实例的字典的优先级**。在与实例字典中有同名的情况下，`data desriptor > instance.__dict__ > non-data descriptor`。

描述器是在 object, type, 和 super 的 `__getattribute__()` 方法中实现的。
 - 描述器的调用是因为`__getattribute__()`
 - 重写`__getattribute__()`会阻止正常的描述器调用

**属性(property), 方法(bound/unbound method), staticmethod 和 classmethod 都是基于描述器协议的。**
```Python
>>> class Mm(object):
...      def __init__(self):
...          self.same = '__dict__'
...      def same(self):
...          print 'non-data'
... 
>>> m = Mm()
>>> m.__dict__
{'same': '__dict__'}
>>> m.same
'__dict__'
>>> m.same() # 实例函数是 non-data descripter，优先级不如实例字典
Traceback (most recent call last):
  ...
TypeError: 'str' object is not callable
```

=> [Descriptor HowTo Guide](https://docs.python.org/2/howto/descriptor.html) & [翻译](http://pyzh.readthedocs.org/en/latest/Descriptor-HOW-TO-Guide.html)

=> [Class method differences in Python: bound, unbound and static](http://stackoverflow.com/a/114289/2996656) & [译文](http://pyzh.readthedocs.org/en/latest/python-questions-on-stackoverflow.html#unbound-methodbound-method)

---
<h4 id="faq-class-property" style="color:#f39c12;">属性 @property</h4>

`property([fget[, fset[, fdel[, doc]]]])` **将方法当成属性用**

可以通过函数的形式使用，也可以通过装饰器的形式来使用
```Python
>>> class Name(object):
...     @property
...     def name(self):
...         print 'Get:'
...         return self._name
...     @name.setter
...     def name(self, value):
...         print 'Set: ', value
...         self._name = value
...     @name.deleter
...     def name(self):
...         print 'Del: name'
...         del self._name
... 
>>> n = Name()
>>> n.name = 'Damnever'
Set: Damnever
>>> n.name
Get:
'Damnever'
>>> del n.name
Del: name
>>> n.name
Get:
Traceback (most recent call last):
  ...
AttributeError: 'Name' object has no attribute '_name'
```

---
<h4 id="faq-class-func" style="color:#f39c12;">@classmethod & @staticmethod</h4>

都与实例无关。classmethod 至少需要一个类名作为参数；staticmethod 相当与一个普通函数。因为这两个方法一般不会其它代码用到，通过 decorator 的方式放在类里可以**代码的可读性**。

classmethod 和 staticmethod 都可以通过实例和类名来调用。classmethod　只能访问类属性，staticmethod 即不能访问类属性也不能访问实例属性。

```Python
class MyClass(object):

    class_field = 'class field'

    def __init__(self):
        self.instance_field = 'instance_field'

    def instance_method(*args):
        print 'bound method args:', args
        print 'I can get:', args[0].instance_field

    @staticmethod
    def static_method(*args):
        print 'staticmethod args:', args

    @classmethod
    def class_method(*args):
        print 'classmethod args:', args
        print 'I can get:', args[0].class_field
        # print 'cm call static method:', args[0].static_method('sm')
        # print 'cm call bound method:', args[0]().instance_method()

if __name__ == '__main__':
    obj = MyClass()
    print '** Call classmethod:'
    obj.class_method()
    MyClass.class_method()
    print '** call staticmethod:'
    obj.static_method()
    MyClass.static_method()
    print '** call boundmethod:'
    obj.instance_method()
```
输出
```
** Call classmethod:
classmethod args: (<class '__main__.MyClass'>,)
I can get: class field
classmethod args: (<class '__main__.MyClass'>,)
I can get: class field
** call staticmethod:
staticmethod args: ()
staticmethod args: ()
** call boundmethod:
bound method args: (<__main__.MyClass object at 0x7f7adbc89a90>,)
I can get: instance_field
```

=> [PYTHON中STATICMETHOD和CLASSMETHOD的差异](http://www.wklken.me/posts/2013/12/22/difference-between-staticmethod-and-classmethod-in-python.html)

---
___
<h3 id="faq-metaclass" style="color:#d35400;">元类 (metaclass)</h3>

**类型对象,负责创建对象实例,控制对象行为 (方法)。而创建类型对象的是元类 (metaclass),也就是类型的类型。**

当解释器创建类型对象时,会按以下顺序查找` __metaclass__` 属性。
**`class.__metaclass__ -> bases.__metaclass__ -> module.__metaclass__ -> type`**(这也是为什么在模块中可以用 `__metaclass__` 为所有类型指定默认元类的缘故。)
```Python
>>> ## 使用 type() 动态创建类
>>> def fn(self):
...     print 'dynamic'
...
>>> Foo = type('Foo', (object,), dict(foo_say=fn))
>>> Foo().foo_say()
dynamic
>>> type(Foo); type(Foo())
<type 'type'>
<class '__main__.Foo'>
>>> ## 使用元类来定制类
>>> class MyMetaclass(type):
...     def __new__(cls, name, bases, attrs):
...         # do sth.
...         return type.__new__(cls, name, bases, attrs)
... 
>>> class MyClass(object):
...     __metaclass__ = MyMetaclass # 指定元类
... 
>>> type(MyClass); type(MyClass())
<class '__main__.MyMetaclass'>
<class '__main__.MyClass'>
```

=> [深刻理解 Python**2** 中的元类](http://blog.jobbole.com/21351/) & [原文](http://stackoverflow.com/questions/100003/what-is-a-metaclass-in-python/6581949#6581949)

=> [Python**3** 初探](https://www.ibm.com/developerworks/cn/linux/l-python3-2/)

=> [编写一个 ORM 框架](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/001386820064557c69858840b4c48d2b8411bc2ea9099ba**000)

---
___
<h3 id="faq-mixin" style="color:#d35400;">MixIn</h3>

一种特殊的多继承，在不改变原对象的情况下对其进行扩展。
 1. You want to provide a lot of optional features for a class.
 2. You want to use one particular feature in a lot of different classes.

=> [Mixin 扫盲班](http://wiki.woodpecker.org.cn/moin/FlyintoMixin)

=> [Mix-in 技术介绍](http://wiki.woodpecker.org.cn/moin/IntroMixin)

=> [Mixins considered harmful/1](http://www.artima.com/weblogs/viewpost.jsp?thread=246341)

=> [Mixins considered harmful/2](http://www.artima.com/weblogs/viewpost.jsp?thread=246483)


---
___
<h3 id="faq-introspection" style="color:#d35400;">自省</h3>

自省（introspection）是一种自我检查行为。

**Python 里面一切皆对象，函数，方法，类，实例，代码块等都有自己的内置属性。**

 => [Python自省（反射）指南](http://www.cnblogs.com/huxi/archive/2011/01/02/1924317.html)

---
___
<h3 id="faq-with" style="color:#d35400;">上下文与 with</h3>

**上下文管理协议 (Context Management Protocol) 为代码块提供了包含初始化和清理操作的安全上下文环境。即便代码块发生异常,清理操作也会被执行。**
 + `__enter__()`: 进入 Runtime 上下文,返回上下文对象；该方法返回值会被绑定到使用这种上下文管理器的 with 语句 as 子句下的标示符。
 + `__exit__(exc_type, exc_val, exc_tb)`: 退出 Runtime 上下文并返回 bool 指示标识，返回 True 会导致 with 语句抑制异常，并继续执行 with 语句后紧跟的语句；否则，执行完该方法后异常会继续传播。若 with 语句本体执行期间发生异常的话，自变量会包含异常类型、值、回溯信息。否则，三个自变量全为 None。

```Python
>>> class MyContext(object):
...     def __init__(self, text):
...         self._text = text
...     def __enter__(self):
...         print 'ENTER:', self.__class__.__name__
...         return self
...     def __exit__(self, exc_type, exc_val, exc_tb):
...         print 'EXIT:', self.__class__.__name__
...     def say(self):
...         print '%s say: %s' % (self.__class__.__name__, self._text)
... 
>>> with MyContext('Hello!') as mc:
...     mc.say()
... 
ENTER: MyContext
MyContext say: Hello!
EXIT: MyContext
```
可以在一个 with 语句中使用多个上下文对象,依次按照 *FILO* 顺序调用。
```Python
>>> import contextlib
>>> with open('readfile', 'r') as reader,\
...         open('writefile', 'w') as writer:
...     writer.write(reader.read())
... 
>>> with contextlib.nested(open('readfile', 'r'), open('writefile', 'r'))\
...         as (reader, writer):
...     print writer.read(), reader.read()
... 
contextlib.nested
contextlib.nested
```
另: threading 中的 Lock/RLock/Condition 实现了 Context Management Protocol。

=> [Python 中的上下文管理器](http://blog.jobbole.com/64175/)

=> [理解 Python 的 with 语句](http://python.42qu.com/11155501)

---
___
<h3 id="faq-closure" style="color:#d35400;">闭包 (closure)</h3>

**当函数离开创建环境后，依然持有其上下文状态。**

一个函数闭包是一个函数和一个引用集合的组合，这个引用集合指向这个函数被gund定义的作用域的变量。后者通常指向一个引用环境 (referencing environment)，这使得函数能够在它被定义的区域之外执行。在 Python 中，这个引用环境被存储在一个 cell 的 tuple 中。你能够通过 `func_closure` 或 `__closure__` 属性访问它。要铭记的一点是**引用及是引用，而不是对象的深度拷贝**。当然了，对于不可变对象而言，这并不是问题，然而对可变对象(list)这点就必须注意。
```Python
>>> def print_list(lst):
...     def func():
...         print lst
...     return func
...
>>> lst = [1, 2]
>>> g = print_list(lst)
>>> g()　　##　已经离开创建环境
[1, 2]
>>> ## lst.append(3)时，g()内部的引用和z仍然指向一个变量，而lst=[1]之后，两者就不再指向一个变量了。
>>> lst.append(3)
>>> g()
[1, 2, 3]
>>> lst = [1]  ## lst 已经是一个新的对象了
>>> g()
[1, 2, 3]
>>> g.__closure__ ;  g.func_closure
(<cell at 0x7ffd5fda7248: list object at 0x7ffd5fdaa680>,)
(<cell at 0x7ffd5fda7248: list object at 0x7ffd5fdaa680>,)
>>> print [str(c.cell_contents) for c in g.__closure__]
['[1, 2, 3]']
>>> def dump_closure(f):
...     if hasattr(f, '__closure__') and f.__closure__ is not None:
...         print '- Dumping function closure for %s:' % f.__name__
...         for i, c in enumerate(f.__closure__):
...             print '-- cell %d = %s' % (i, c.cell_contents)
...     else:
...         print '- %s has no closure!' % f.__name__
...
>>> dump_closure(g)
- Dumping function closure for func:
-- cell 0 = [1, 2, 3]
```
**后期绑定机制**（late binding）

这是指在闭包中使用的变量的值，是在内层函数被调用的时候查找的。
```Python
>>> def create_multipliers():
...     return [lambda x: i*x for i in range(5)] # 列表解析
... 
>>> for multiplier in create_multipliers():
...     print multiplier(2)
... 
8
8
8
8
8
>>> ## 在上面的代码中，当任一返回函数被调用的时候，i的值是在它被调用时的周围作用域中查找（到那时，循环已经结束了，所以i已经被赋予了它最终的值4）。
>>> def create_multipliers():
...     return [lambda x, i=i: i*x for i in range(5)]
... 
>>> for multiplier in create_multipliers():
...     print multiplier(2)
... 
0
2
4
6
8
```

=> [有趣的 Python 闭包](http://feilong.me/2012/06/interesting-python-closures)

=> [闭包](http://www.cnblogs.com/vamei/archive/2012/12/15/2772451.html)

=> [Python 闭包详解](http://www.cnblogs.com/ChrisChen3121/p/3208119.html)

=> [Closures、Decorators 和 functools](http://blog.jobbole.com/66895/)

=> [Python 2 nonlocal](http://code.activestate.com/recipes/578965-python-2-nonlocal/)

---
___
<h3 id="faq-decorator" style="color:#d35400;">装饰器"@" (decorator)</h3>

**若需要增强某函数的功能，但又不希望修改该函数的定义，这种在代码运行期间动态增加功能的方式，称之为“装饰器”（Decorator）。**

装饰器不一定非得是个函数返回包装对象,也可以是个类,通过 `__call__` 完成目标调用；当给某个方法`@class_decorator`时，类调用`__init__()`，`__call__()`在调用目标方法时被调用。如果 decorator 有参数的话，`__init__()` 成员就不能传入 func 了，而 func 是在 `__call__()`的时候传入的。
```Python
@dec2
@dec1(arg)
def func(*args, **kwargs):
    pass
# 等价于
def func(*args, **kwargs):
    pass
func = dec2( dec1(arg)(func) )
```
利用缓存提高斐波拉契数例的递归算法的效率
```Python
>>> import functools
>>> def memo(func):
...     cache = {}
...     miss = object()
...     @functools.wraps(func)
...     def wrapper(*args):
...         result = cache.get(args, miss)
...         if result is miss:
...             result = func(*args)
...             cache[args] = result
...         return result
...     return wrapper
... 
>>> @memo
... def fib(n):
...     if n < 2: return n
...     return fib(n - 1) + fib(n - 2)
... 
>>> fib(2);  fib(5)
1
5
```

=> [Python 的闭包和装饰器](http://book42qu.readthedocs.org/en/latest/python/python-closures-and-decorators.html)

=> **[Python 修饰器的函数式编程](http://coolshell.cn/articles/11265.html)**

=> [Python Decorator Library](https://wiki.python.org/moin/PythonDecoratorLibrary)

---
___
<h3 id="faq-yield" style="color:#d35400;">yield & generator</h3>

**生成器**是可以迭代的，读取它的时候只可以读取一次，因为它并不把所有的值放在内存中，它是实时地生成数据。

**yield** 是一个类似 return 的关键字，只是这个函数返回的是个生成器。使用空的 return 语句可以终止迭代，否则出现异常(非StopIteration)。

If the yield-expression is a yield-statement, this returned value is ignored, similar to ignoring the value returned by a function call used as a statement.
```Python
>>> g1 = [x*x for x in range(3)]
>>> g1
[0, 1, 4]
>>> g2 = (x*x for x in range(3)) # 这里变成了一个生成器
>>> print g2
<generator object <genexpr> at 0x7f45d219cd20>
>>> ########## 一个比较常见的用途是读取文件 ##########
>>> def read_file(fpath, block_size=1024):
...     with open(fpath, 'rb') as f:
...         while 1:
...             block = f.read(block_size)
...             if block:
...                 yield block
...             else:
...                 return
...
>>> for block in read_file('apt-get'):
...     print len(block)
... 
1024
397
```
支持自定义的生成器需要实现`__iter__()`(返回迭代器对象本身)和`next()`(从容器返回下一项，没有下一项了的话需要引发StopIteration异常)。
```Python
>>> class MyIteration(object):
...      def __init__(self, sequence):
...          self._seq = sequence
...          self._count = len(sequence)
...      def __iter__(self):
...          return self
...      def next(self):
...          if self._count:
...             self._count -= 1
...             return self._seq[-self._count-1]
...          raise StopIteration
... 
>>> mi = MyIteration(range(4))
>>> for each in mi:
...     print each
... 
0
1
2
3
```

=> [(译)Python关键字yield的解释(stackoverflow)](http://pyzh.readthedocs.org/en/latest/the-python-yield-keyword-explained.html)

=> [Iterators、Generators 和 itertools](http://blog.jobbole.com/66097/)

---
___
<h3 id="faq-coroutine" style="color:#d35400;">协程</h3>

**协程(Coroutine)，协同程序，又称微线程。**
本质上讲还是单线程的程序。只不过将每个任务封装成一个子程序(函数)，然后通过调度程序按照一定的算法轮流调用这种子程序(将未完成的函数挂起，去执行另一个函数)，从而推进任务的进展。

Python 使用 yield expression 来实现简单的协程。yield 表达式可以看做是一个函数调用，send()的参数作为表达式的返回值；每次 yield 产生数据给另一个子程序后，yield 表达式就变成一个函数一样等待 send()/next()/throw()/close() 对它的下一次调用。

+ 必须发送一个 None 来开启一个生成器，`send(None)`或`next()`。
+ 无论生成器什么时候被一个 next() 唤醒，`yield` 表达式的值都为 None。
+ `send(value)`唤醒一个生成器并且向其发送一个值，这个值被作为 yield 表达式的返回值。`send()`同时获取生成器产生的下一个值作为返回值，否则引发 StopItration　异常(当生成器不生产值退出了)。
+ `throw(type, value=None, traceback=None)`可以给生成器发送一个异常，从生成器的内部引发异常从而控制生成器的执行。
+ `close()`正常的（通过throw(GeneratorExit)并忽略GeneratorExit, StopIteration）关闭生成器。若生成器仍然返回了值，引发 RuntimeError。其它异常由解释器去处理。

```Python
>>> def gen():
...     r = ''
...     for n in range(5):
...         print 'GEN:', r
...         try:  # 可以使用 try/finally
...             r = yield n
...         finally:
...             print '** generator exit'
... 
>>> g = gen()
>>> g.send('') # 开启生成器必须发送 None，其余都不行
Traceback (most recent call last):
  ...
TypeError: can't send non-None value to a just-started generator
>>> g.next() # 或 next(g) 或 g.send(None)
GEN: 
0
>>> g.send('hi, gen')
GEN: hi, gen
1
>>> g.throw(GeneratorExit) # g.close()也会执行finally块，不报异常(被pass)
** generator exit
Traceback (most recent call last):
  ...
GeneratorExit
>>> g.send('Hello, gen?') # 生成器已经被异常终止
Traceback (most recent call last):
  ...
StopIteration
```

=> [PEP 342 -- Coroutines via Enhanced Generators](https://www.python.org/dev/peps/pep-0342/)

=> [yield 之学习心得](http://wiki.woodpecker.org.cn/moin/Py25yieldNote)

=> [A Curious Course on Coroutines and Concurrency](http://www.dabeaz.com/coroutines/index.html)

---
___
<h3 id="faq-algorithm" style="color:#d35400;">数据结构和算法</h3>

**bisect** 使用二分法在一个 "已排序 (sorted) 序列" 中查找合适的插入位置。
 - 只查找可插入位置，不插入
  + `bisect(l, a)` # 查找 a 在序列 l 中的合适插入位置,默认插入以存在元素右侧。
  + `bisect_left(l, a)` # 如果待查找元素在列表中存在,则返回左侧插入位置。
  + `bisect_right(l, a)` # 如果待查找元素在列表中存在,则返回右侧插入位置。
 - 直接插入
  + `insort(l, a)` # 同理，但直接插入
  + `insort_left(l, a)` # 同理，但直接插入
  + `insort_right(l, a)` # 同理，但直接插入


**heapq** 最小堆 (完全平衡二叉树，每个父节点小于等于其左右子节点)
 - `heappush(heap, item)` # 将 item 压入堆中
 - `heappop(heap)` # 总是弹出最小 item（堆顶）
 - `heappushpop(heap, item)` # 先push , 再pop, 弹出值小于等于 item
 - `heapreplace(heap, item)` # 先pop, 再push, 弹出值可能大于 item
 - `heapify(list)` # 将序列转换成堆
 - `nlargest/nsmallest(n, l)` # 从列表(不一定是堆)有序返回最大(最小)的 n 个元素

**Queue** 队列（在 Python3 里为 queue）
Queue： FIFO 队列 / LifoQueue： LIFO 队列（似栈）/ PriorityQueue： 优先级队列，级别低先出
 - `put(item, [, block[, timeout]]) / get([, block[, timeout]])` # 压入/取出元素。**put**：如果 block 为 True，timeout 不为 None，在等待时间 timeout 内队列一直为满，引发 Queue.Full 异常；如果 block 为 False，则timeout被忽略，只要入队的时候队列为满，立即引发 Queue.Full 异常。**get**： 同理引发 Queue.Empty 异常。
 - `put_nowait(item) / get_nowait()` # 相当于 `put(item, False) / get(False)`
 - `empty() / full()` # 返回 bool 型
 - `task_done()` # 在完成一项任务后，向任务已完成的队列发送一个信号
 - `join()` # 等待直到队列为空(阻塞直到任务完成)， 再执行别的操作

=> [Recursion(How to Think Like a Computer Scientist: Learning with Python 3)](http://openbookproject.net/thinkcs/python/english3e/recursion.html)

=> [算法 @老齐](https://github.com/qiwsir/algorithm/blob/master/README.md)

=> [Python @hujiaweibujidao](http://hujiaweibujidao.github.io/python/)

=> [Python 中的高级数据结构](http://blog.jobbole.com/65218/)

=> [whoosh 索引查找](https://pythonhosted.org/Whoosh/quickstart.html#a-quick-introduction)

---
___
<h3 id="faq-performance" style="color:#d35400;">性能和内存管理</h3>

 + 大量字符串拼接，使用 `''.join(list)` 而不是 `str + str`
 + 对于频繁增删元素的大大型列表,应该考虑用用链表等数据结构代替。
 + 如果需要创建 "海量" 对象实例,优先考虑 `__slots__`(**`__slots__` 属性会阻止虚拟机创建实例 `__dict__`,仅为名单中的指定成员分配内存空间。这有助于减少内存占用,提升执行行性能,尤其是在需要大量此类对象的时候。**) 。其派生类同样必须用` __slots__` 为新增字段分配存储空间 (即便是空 `__slots__ = []`),否则依然会创建 __dict__,反而导致更慢的执行行效率。

=> [Python 内置数据结构各种操作效率](http://hujiaweibujidao.github.io/blog/2014/05/08/python-algorithms-datastructures/)

=> [18 条 Python 代码性能优化小贴士](http://infiniteloop.in/blog/quick-python-performance-optimization-part-i/)

=> [Python 代码优化指南](http://www.ibm.com/developerworks/cn/linux/l-cn-python-optim/)

=> [Python 性能分析指南](http://www.oschina.net/translate/python-performance-analysis)

---

___

***
<h2 id="standard-library" style="color:#c0392b;">标准库</h2>

```
  如果一定要推荐一些 python 的源码去读，我的建议是标准库里关于网络的代码。从 SocketServer 开始，补上 socket 模块的知识，熟悉 TCP/UDP 编程，然后了解 Mixin 机制的最佳示例 SocketServer.{ForkingMixIn|ThreadingMixIn}，借这个机会了解 thread/threading 模块，这时会对并发量提出新的要求，就可以读 select 模块，开始对 select/{epoll|kqueue} 有深刻理解，搞懂以后就可以接触一下异步框架 asyncore 和 asynchat。这时开始出现分岔。如果是做 game 等以 TCP/UDP 协议为基础的peakhell应用，可以去读 greenlet 和 gevent，如果是做 web，则走下一条路。
  做 web，读 BaseHTTPServer、SimpleHTTPServer 和 CGIHTTPServer，读 cgi/cgitb，自己随意写框架，读cookielib，读 wsgiref，这时候自己写一个简便的 web framework 就 so easy 了，老板再也不担心你写 web 了，选择 flask/web.py/django/pyramid 都心中有数了。因为走的是 web 的路，所以难免要调用一下别人的 api，搞懂一下 httplib/urllib/urllib/urlparse。
   引自：赖勇浩[http://laiyonghao.com/]
```

* [Python(2.0) Standard Library](http://wiki.woodpecker.org.cn/moin/PythonStandardLib/)
* [不完全译版](https://python-documentation-cn.readthedocs.org/en/latest/library/index.html)
* [德云社区不完全译版](http://digitser.net/python/2.7.8/zh-CN/library/index.html)
* [又一刚开始译版](http://python.usyiyi.cn/python_278/library/index.html)
* [一些模块](http://automationtesting.sinaapp.com/blog/category/python_module)
* [官方文档 2.78](https://docs.python.org/2/library/) 硬伤
* [The Standard Python Library](http://effbot.org/librarybook/) 又是En

---
<h3 id="lib-test" style="color:#d35400;">unittest & doctest</h3>

**++unittest++**
 - TestCase (以test开头的方法就是测试方法)常用方法(help(unittest.TestCase)):
  - `assertEqual(first, second[, msg]) == assertEquals` # 判断两个对象是否相同
  - `assertTrue(expr[, msg]) / assertFalse` # 验证条件是否为 True/False
  - `assertRaises(excClass[[[, callableObj], *args], **kwargs])` # 返回一个上下文对象，验证异常的抛出。*args,**kwargs 是 callableObj 的参数。
  - `setUp()/tearDown()` # 在每调用一个测试方法的前后分别被执行。
  - `unittest.main()` # 启动测试，可以用命令行参数代替。
  - ```suite = unittest.TestLoader().loadTestsFromTestCase(TestObj)
  unittest.TextTestRunner(verbosity=2).run(suite)``` # 可用来代替main()。

 => [单元测试](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/00140137128705556022982cfd844b38d050add8565dcb9000)

**++doctest++** 直接提取注释中的代码并执行测试
 - `doctest.testmod()` # 开始文档测试
 - `python doc_test.py -v` # 如果没有错误什么都不会输出，加上参数 'v' 可以得到更详细的信息。
 - `python -m doctest -v example.py` # 导入标准库中的 example 模块并进行测试。
 - `doctest.testfile("example.txt")` # 将文档放于 example.txt 中，进行测试。
 - 文档中注释代码的异常必须和自定义异常一样。

---
<h3 id="lib-collections" style="color:#d35400;">collections [Counter, deque, namedtuple, defaultdict, OrderedDict]</h3>

- `Counter([iterable-or-mapping])` # 简单的计数器，dict 的一个子类，Key 不存在用返回0来代替 KeyError。并且支持集合形式的运算。
```Python
>>> cnt = collections.Counter()
>>> for word in ['red', 'blue', 'red', 'green', 'blue', 'blue']:
...     cnt[word] += 1
...
>>> cnt
Counter({'blue': 3, 'red': 2, 'green': 1})
>>> dict(cnt)
{'blue': 3, 'green': 1, 'red': 2}
>>> list(collections.Counter(a=4, b=2, c=3, d=0).elements()) # element 将其展开
['a', 'a', 'a', 'a', 'c', 'c', 'c', 'b', 'b']
>>> collections.Counter('aaabbbbcccccdddddd').most_common(2) # most_common 返回出现最多的 n 个元素及其个数
[('d', 6), ('c', 5)]
```

- **`namedtuple(typename, field_names[, verbose=False][, rename=False])`** # 具备tuple的不变性，又可以根据属性来引用。用来表示数据表也很合适。
```Python
>>> Point = collections.namedtuple('Point', ['x', 'y'])
>>> p = Point(1, 2)
>>> p.x
1
>>> p.y
2
>>> p.x, p.y
(1, 2)
>>> isinstance(p, Point)
True
>>> isinstance(p, tuple)
True
>>> t = [11, 22]
>>> Point._make(t)
Point(x=11, y=22)
```

- **`deque([iterable[, maxlen]])`** # 高效实现插入和删除操作的双向列表，适合用于队列和栈。
```Python
>>> q = collections.deque(range(5))
>>> q.append(5)  # deque([0, 1, 2, 3, 4, 5])
>>> q.appendleft(-1)  # deque([-1, 0, 1, 2, 3, 4, 5])
>>> q.extend(range(2))  # deque([-1, 0, 1, 2, 3, 4, 5, 0, 1])
>>> q.count(1)
2
>>> q.extendleft(range(2,4))  # deque([3, 2, -1, 0, 1, 2, 3, 4, 5, 0, 1])
>>> q.pop(); q
1 deque([3, 2, -1, 0, 1, 2, 3, 4, 5, 0])
>>> q.popleft(); q
3 deque([2, -1, 0, 1, 2, 3, 4, 5, 0])
>>> q.remove(-1)  # deque([2, 0, 1, 2, 3, 4, 5, 0])
>>> q.reverse()  # deque([0, 5, 4, 3, 2, 1, 0, 2])
>>> q.rotate(1)  # deque([2, 0, 5, 4, 3, 2, 1, 0])
```

- `defaultdict([default_factory[, ...]])` # 当 dict 的 key 不存在时，返回一个默认值。
```Python
>>> s = [('yellow', 1), ('blue', 2), ('yellow', 3), ('blue', 4), ('red', 1)]
>>> d = collections.defaultdict(list)  # 传入的参数为 dict 值的缺省类型，可以是函数
>>> for k, v in s:
...     d[k].append(v) # == d.setdefault(k, []).append(v) 前提 d = {}
...
>>> d.items()
[('blue', [2, 4]), ('red', [1]), ('yellow', [1, 3])]
>>> d['black']
[]
```

- `OrderedDict([items])` # 保持 dict 元素的添加顺序。
```Python
>>> od = collections.OrderedDict()
>>> od['a'] = 1; od['b'] = 2; od['c'] = 3; od
OrderedDict([('a', 1), ('b', 2), ('c', 3)])
>>> collections.OrderedDict(sorted({'banana': 3, 'apple':4, 'pear': 1, 'orange': 2}.items(), key=lambda t: t[1]))
OrderedDict([('pear', 1), ('orange', 2), ('banana', 3), ('apple', 4)])
>>> od.popitem(); od.popitem(); od.popitem() # LIFO
('c', 3) ('b', 2) ('a', 1)
```

---
<h3 id="lib-itertools" style="color:#d35400;">itertools</h3>

**提供了一系列迭代器能够帮助用户轻松地使用排列、组合、笛卡尔积或其他组合结构。**

=> [Iterators、Generators 和 itertools](http://blog.jobbole.com/66097/)

=> [官方文档 Functions creating iterators for efficient looping](https://docs.python.org/2/library/itertools.html)

---
<h3 id="lib-struct" style="color:#d35400;">struct & array</h3>

struct： 解决 str 和其他二进制数据类型的转换，特别是在在网络传输中。
 - `pack(fmt, v1, v2)` # 转换成 fmt 中描述的 struct类型的二进制形式
 - `unpack(fmt, v1, v2)` # 将二进制形式的 struct 类型通过 fmt 格式转换成 Python 类型

array： 将 Python 类型的数据（二进制、序列、文件内容）转换成给定类型的 C 数组

---
<h3 id="lib-datetime" style="color:#d35400;">time & datetime</h3>

 - **时间戳（timestamp）**的方式：通常来说，时间戳表示的是从 1970 年 1 月 1 日 00:00:00 开始按秒计算的偏移量（time.gmtime(0)）此模块中的函数无法处理 1970 纪元年以前的日期和时间或太遥远的未来（处理极限取决于 C 函数库，对于 32 位系统来说，是 2038 年）。
 - **UTC**（Coordinated Universal Time，世界协调时）也叫格林威治天文时间（Greenwich Astronomical Time，格林威治标准时间: Greenwich Mean Time），是世界标准时间。在中国为 UTC+8。
 - **DST**（Daylight Saving Time）即夏令时的意思。
 - [time模块详解](http://bbs.fishc.com/thread-51326-1-1.html)
 - [Python 时间和日期](http://www.yiibai.com/python/python_date_time.html#python_date_time)
```Python
# clock: 返回当前进程消耗的CPU时间 (秒)。
# sleep: 暂停进程 (秒,可以是小小数,以便设置毫秒、微秒级暂停)。
>>> time.clock()
0.027975
>>> time.sleep(1)
# strftime: 将 struct_time 格式化为字符串。
# strptime: 将字符串格式化为 struct_time。
# %H 24小时制, %l 12小时制, %a/%A 简化（完整星期名称）, %b/%B 简peakhell化（完整本地月份名称）
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
<h3 id="lib-serializable" style="color:#d35400;">anydbm & shelve & pickle(cPickle)</h3>

**`anydbm.open(filename[, flag[, mode]])`** # 将一个磁盘上的文件与一个“dict-like”对象关联起来，像操作字典一样。flag 参数设置对文件的操作方式 [rwc(没有则创建)n(每次都建空文件)]， mode 是 *unix 上对文件的访问权限 [0777]。

**`shelve.open(filename, flag='c', protocol=None, writeback=False)`** # 高级版 anydbm，支持在"dict-like"对象中存储任何可以被pickle序列化的对象。wirteback 参数表示将数据存储与缓存中，调用 close(其调用sync) 后才写入硬盘。

**`pickle/cPickle`** # 在一个文件中储存任何Python对象。后者为 C 语言实现。
 - `dump(obj, file[, protocol])` # 将序列化的对象写入文件。
 - `load(file)` # 读取文件中的数据并反序列化。
 - `dumps(obj[, protocol])` # 返回序列化的数据流。
 - `load(obj)` # 反序列化数据流。
 - `Pickler(file[, protocol])` # cPickle中为方法，拥有写入`dump(obj)`/ 清除pickler的记忆`clear_memo()`
 - `Unpickler(file)` #cPickle中为方法，拥有读取`load()`/ `noload()`

---
<h3 id="lib-encryption" style="color:#d35400;">hashlib & hmac & md5 & sha</h3>

- **hashlib** 散列算法(支持md5 sha1 sha224 sha256 sha384 sha512)
```Python
# 创建 md5 加密对象
>>> m = hashlib.md5()
# 加密文本，可追加
>>> m.update("Nobody inspects")
>>> m.update(" the spammish repetition")
>>> print m.hexdigest()
bb649c83dd1ea5c9d9dec9a18df0ffe9
# new(name, string='') 第一个参数为OpenSSL库中存在的函数名
>>> hashlib.new("md5", "Nobody inspects the spammish repetition").hexdigest()
'bb649c83dd1ea5c9d9dec9a18df0ffe9'
# sha1 加密
>>> hashlib.sha1('Nobody inspects the spammish repetition').hexdigest()
'531b07a0f5b66477a21742d2827176264f4bbfe2'
```


- **hmac** 签名(认证)加密算法(需要秘钥)
```Python
# 创建一个新的 hmac 对象，new(key[, msg[, digestmod]])
>>> m1 = hmac.new("MyKey", "I'm young.")
# 输出被 hmac 加密后的十六进制数据。digest()非十六进制
>>> print m1.hexdigest()
c83ac1cac45ba92b2f6629bee67fb953peakhell
# 用新字符串来更新 hmac
>>> m1.update("I'm old.")
>>> print m1.hexdigest()
3ee16436c0621a5d46fc8f3a4eb1d27e
# update(a); update(b) == update(a + b)
>>> m2 = hmac.new("MyKey")
>>> m2.update("I'm young."); m.update("I'm old.")
>>> print m2.hexdigest()
3ee16436c0621a5d46fc8f3a4eb1d27e
# 拷贝一个 hmac 的副本
>>> m3 = m2.copy()
>>> print m3.hexdigest()
3ee16436c0621a5d46fc8f3a4eb1d27e
>>> print hmac.new("MyKey", "I'm young.I'mold.").hexdigest()
aa0fb38cbe017bdb388fbfb9f9da1645
```

- **md5**
```Python
>>> m = md5.new()
>>> m.update("Hello,")
>>> m.update(" world!")
>>> m.hexdigest()
'6cd3556deb0da54bca060b4c39479839'
>>> md5.new("Hello, world!").hexdigest()
'6cd3556deb0da54bca060b4c39479839'
>>> md5.md5("Hello, world!").hexdigest()
'6cd3556deb0da54bca060b4c39479839'
```

- **sha** sha1
```Python
>>> s = sha.new()
>>> s.update("Hello,")
>>> s.update(" world!")
>>> s.hexdigest()
'943a702d06f34599aee1f8da8ef9f7296031d699'
>>> sha.new("Hello, world!").hexdigest()
'943a702d06f34599aee1f8da8ef9f7296031d699'
```

---
<h3 id="lib-json" style="color:#d35400;">json & base64 & uuid</h3>

- **json** JavaScript Object Notation(JavaScript 对象表示法)，用于存储和交换文本信息。
JSON 值可以是：
 + 数字（整数或浮点数）
 + 字符串（在双引号中）
 + 逻辑值（true 或 false）
 + 数组（在方括号中）
 + 对象（在花括号中）
 + null

 ```Python
# Neither of these calls raises an exception, but the results are not valid JSON 【Infinity, -Infinity, NaN】
>>> json.dumps(float('-inf'))
'-Infinity'
>>> json.dumps(float('nan'))
'NaN'
# Same when deserializing
>>> json.loads('-Infinity')
-inf
>>> json.loads('NaN')
nan
# 一个 json 对象里定义的名字必须是无二的
>>> json.loads('{"x":1, "x":2, "x": 3}')
{u'x': 3}
 # dump()/load() 可传入文件对象
```

- **base64** Base64编码会把3字节的二进制数据编码为4字节的文本数据，长度增加33%
编码后的文本数据为 4 的倍数。若被编码的二进制数据不是 3 的倍数，会剩下 1～2个字节，base64用 \x00 字节在末尾补足后，再在编码的末尾加上 1~2 个 '='，表示补了多少字节，解码的时候自动去掉。
```Python
>>> base64.b64encode('Hello, world!')
'SGVsbG8sIHdvcmxkIQ=='
>>> base64.b64decode('SGVsbG8sIHdvcmxkIQ==')
'Hello, world!'
```
在 URL 中字符 ‘+/-’ 可能引起歧义，必须用 'url_safe' 的 base64 来编码
```Python
>>> base64.b64encode('i\xb7\x1d\xfb\xef\xff')
'abcd++//'
>>> base64.urlsafe_b64encode('i\xb7\x1d\xfb\xef\xff')
'abcd--__'
>>> base64.urlsafe_b64decode('abcd--__')
'i\xb7\x1d\xfb\xef\xff'
```

- **uuid** 一种唯一标识
 - `UUID([hex[, bytes[, bytes_le[, fields[, int[, version]]]]]])` # 得到原始的数据
 - `uuid1([node[, clock_seq]])` # 由 MAC 地址、当前时间戳、随机数生成。(有安全性问题)
 - `uuid3(namespace, name)` # 基于命名空间和名字的MD5散列值。namespace 是给定的(参见官方文档)。
 - `uuid4()` # 由伪随机数得到，有一定的重复概率。
 - `uuid5(namespace, name)` # 基于命名空间和名字的 SHA-1 hash。
 - `bytes/int/hex` # 把生成的 uuid 转化成相应的格式。

 ```Python
>>> x = uuid.UUID('{00010203-0405-0607-0809-0a0b0c0d0e0f}')
>>> str(x)
'00010203-0405-0607-0809-0a0b0c0d0e0f'
>>> x.bytes
'\x00\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f'
>>> print uuid.UUID(bytes=x.bytes)
00010203-0405-0607-0809-0a0b0c0d0e0f
>>> print uuid.uuid1()
292b1924-4c96-11e4-8413-000c298861ee
>>> print uuid.uuid3(uuid.NAMESPACE_DNS, 'python.org')
6fa459ea-ee8a-3ca4-894e-db77e160355e
>>> print uuid.uuid4()
1e31baf7-cb01-4e22-b18a-2f830ee6f4d8
>>> print uuid.uuid4().hex
e17366f236084bdc8ed46ee5cdaddbe4
>>> print uuid.uuid5(uuid.NAMESPACE_DNS, 'python.org')
886313e1-3b8a-5372-9b90-0c9aee199e5d
```

---
<h3 id="lib-thread" style="color:#d35400;">threading & Event & Timer</h3>

**Lock/RLock/Condition 实现了 Context Management Protocol 可以自动调用 acquire()/release()。[with]
threading.local() 创建的对象会利用 thread-local storage (TLS) 为每个线程保存不同的数据。**

Event（事件）是最简单的线程通信机制之一：一个线程通知事件，其他线程等待事件。Event内置了一个初始为False的标志，当调用`set()`时设为True，调用`clear()`时重置为 False。`wait()`如果标志为True将立即返回，否则阻塞线程至等待阻塞状态，等待其他线程调用set()。Event没有锁，无法使线程进入同步阻塞状态。

`Timer(interval, function, args=[], kwargs={})`（定时器）是Thread的派生类，用于在指定时间后调用一个方法。

=> [Python多线程相关方法详解](http://www.mjix.com/archives/228.html)

=> [Python线程指南](http://www.cnblogs.com/huxi/archive/2010/06/26/1765808.html)

---
<h3 id="lib-email" style="color:#d35400;">smtplib & email & poplib</h3>

email(mime,parser,header,utils...) 主要用于构造/解析邮件
```Python
Message          # 继承关系 #
    MIMEBase
        MIMEMultipart
        MIMENonMultipart
            MIMEMessage
            MIMEText
            MIMEImage
```

=> [SMTP发送邮件](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/001386832745198026a685614e7462fb57dbf733cc9f3ad000)

=> [POP3收取邮件](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/001408244819215430d726128bf4fa78afe2890bec57736000)

---
<h3 id="lib-cookie" style="color:#d35400;">Cookie & cookielib</h3>

- **Cookie**
 - `BaseCookie([input])` # 类 dict 对象，存储并管理着称为 Morsel 的 cookie 值集合。
 - `SimpleCookie([input])` # 继承于 BaseCookie (另外两个子类SerialCookie/SmartCookie因安全问题已不赞成使用)。

 ```Python
>>> c = Cookie.SimpleCookie()
>>> c['number'] = 80; c['number'].value
'80'
>>> c['string'] = 'eight'; c['string'].value
'eight'
>>> print c   #  print c.output() 与其一样
Set-Cookie: number=80
Set-Cookie: string=eight
>>> c = Cookie.SimpleCookie()
>>> c['rocky'] = 'road'
>>> c['rocky']['path'] = '/cookie'
>>> print c.output(attrs=[], header='Cookie:') # attrs 若设置为空，只显示第一个；header 设置开始字符
Cookie: rocky=road
>>> print c.output(attrs=['rocky', 'path'], header='Cookie:')
Cookie:  rocky=road; Path=/cookie
>>> c = Cookie.SimpleCookie()
>>> c.load("chips=ahoy; vienna=finger") # 将字符串转化成 Morsel 形式
>>> print c
Set-Cookie: chips=ahoy
Set-Cookie: vienna=finger
>>>c.lear() # 清除存储的 cookie 数据
```

- **cookielib** 为存储和管理cookie提供客户端支持
 - `CookieJar(policy=None)` # 将 cookie 存在内存中
 - `FileCookieJar(filename, delayload=None, policy=None)` # 将 cookie 存在本地文件中，没有实现save函数。其子类实现了： MozillaCookieJar是为了创建与Mozilla浏览器cookies.txt兼容的FileCookieJar实例，LWPCookieJar是为了创建与libwww-perl的Set-Cookie3文件格式兼容的FileCookieJar实例，用LWPCookieJar保存的cookie文件易于人类阅读。

---
<h3 id="lib-url" style="color:#d35400;">urlparse & urllib & urllib2</h3>

> **一个HTTP请求报文由请求行（request line）、请求头部（header）、空行和请求数据4个部分组成**。
 HTTP响应也由三个部分组成，分别是：状态行、消息报头、响应正文。

> => [爬虫教程](http://blog.csdn.net/column/details/why-bug.html)

- **urlparse** 解析 URL 并进行拆分或拼接
 - `urlparse(urlstring[, scheme[, allow_fragments]])` # 拆分成六元素元组
 - `urlunparse(parts)` # 拼接通过 urlparse 拆分 url 的返回对象
 - `urlsplit(urlstring[, scheme[, allow_fragments]])` # 拆分成五元素元组，空格/空参数/请求/片段标示符将被舍弃
 - `urlunsplit(parts)` # 拼接通过 urlsplit 拆分 url 的返回对象
 - `urljoin(base, url[, allow_fragments])` # 拼接相对的 url

- **urllib**
 - `urlopen(url[, data[, proxies]])` # 创建一个表示远程 url 的类文件对象，然后像本地文件一样操作这个类文件对象来获取远程数据。参数data表示以post方式提交到 url 的数据。
 ```Python
>>> doc = urllib.urlopen("http://www.baidu.com/")
>>> print doc.info()
...<消息报头>...
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
```Python
 >>> urllib.urlencode({"name": ["user", "user2"], "age": 20})
'age=20&name=%5B%27user%27%2C+%27user2%27%5D'
>>> urllib.urlencode({"name": ["user", "user2"], "age": 20}, False)
'age=20&name=%5B%27user%27%2C+%27user2%27%5D'
>>> urllib.urlencode({"name": ["user", "user2"], "age": 20}, True)
'age=20&name=user&name=user2'
```
 - `pathname2url(path)` # 将本地路径转换成url路径，返回值已用quote编码。
```Python
 >>> urllib.pathname2url("D:\home\lastd\Documents")
'D%3A%5Chome%5Clastd%5CDocuments' # 不再被解析成路径
```
 - `url2pathname(path)` # 将 url 路径转换成本地路径，并用 unquote 解码。
```Python
 >>> urllib.url2pathname("D%3A%5Chome%5Clastd%5CDocuments")
'D:\\home\\lastd\\Documents'   # \ 被转义, 同 /
```

- **urllib2**
 - `urlopen(url[, data][, timeout])` # url 可以是 Request 对象。如果 *_proxy 环境变量被检测到，将会默认使用代理。
 - `build_opener([handler, ...])` # 创建自定义 opener 对象，支持验证、cookie等HTTP高级功能。参数 handler 是 Handler 实例。返回对象(**OpenerDirector**其**addheaders[不能为 dict]**属性可以用来设置 header)具有 open() (类同urlopen())方法。
 - `install_opener(opener)` # 使用此方法仅当想要通过 urlopen() 来使用 opener 对象。
 - `Request(url[, data][, headers][, origin_req_host][, unverifiable])` # 使用 **headers(必须是一个 dict)** 参数伪装浏览器。传入给 urlopen 作为 url 参数。可以使用比较Hack的方式通过其 get_method 方法来设置 HTTP 方法。
 - `HTTPCookieProcessor([cookiejar])` # 传入 cookielib.CookieJar 对象。继承于 BaseHandler。
 - `ProxyHandler([proxies])` # 参数proxies是一个字典，将协议名称（http，ftp）等映射到相应代理服务器的URL。
 - `HTTPPasswordMgr()/HTTPPasswordMgrWithDefaultRealm(realm, uri, user, passwd)` # 使用一个密码管理的对象来处理 urls 和 realms 来映射用户名和密码。如果知道 realm (realm 是与验证相关联的名称或描述信息，取决于远程服务器)是什么,就能使用前者(通过add_password(realm, uri, user, passwd)设置密码)。后者(继承于前者)没有找到合适的，realm 为 None。
 - `ProxyBasicAuthHandler([password_mgr])` # 继承于(AbstractBasicAuthHandler, BaseHandler)，可选参数为一个 HTTPPasswordMgr 对象。可以用 add_password(realm,uri,user,passwd) 来代替设置密码。
 - `HTTPHandler /HTTPSHandler` # 可以打开 Debug Log，拥有对应的 *_open 方法。
```Python
>>> hh = urllib2.HTTPHandler(debuglevel = 1)
>>> opener = urllib2.build_opener(hh)
>>> opener.open("http://www.baidu.com/")
```

---
<h3 id="lib-os" style="color:#d35400;">os</h3>

---
<h3 id="lib-sys" style="color:#d35400;">sys</h3>

---
<h3 id="lib-socket" style="color:#d35400;">SocketServer & SimpleHTTPServer & etc.</h3>

`python -m SimpleHttpServer 8000` 可以在当前文件夹下创建一个HTTP Server，局域网内可以用来共享文件。

Python 3: `python(3) -m http.server`

=> [非常简单的Python HTTP服务](http://coolshell.cn/articles/1480.html)

=> [python 网络编程](http://www.cnblogs.com/cacique/tag/python%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/)

=> [Python socket 网络服务器](http://www.cnblogs.com/vamei/archive/2012/10/30/2744955.html)

=> [Python源码学习01.准备篇](http://defshine.github.io/python-source-learn01.html)

=> [Python源码学习02.SocketServer](http://defshine.github.io/python-source-learn02.html)

---
<h3 id="lib-async-1" style="color:#d35400;">select & epoll</h3>

**异步管理多个 socket 连接，提高并发量。**

select.EPOLLIN,select.EPOLLOUT,select.EPOLLHUP 对应 1,4,16。

当 event 可读时为奇数，可写时为偶数。边缘触发下被注册 socket 的 event 只被关注一次，需要一次完成 event 直到 socket.error 发生。

水平触发模式常被用在移植使用select或者poll机制的应用程序时，而边沿触发模式可以用在当程序员不需要或不想要操作系统协助管理event状态时。

=> [关于C10K、异步回调、协程、同步阻塞](http://rango.swoole.com/archives/381)

=> [select 和 poll I/O复用的简单使用](http://www.cnblogs.com/coser/archive/2012/01/06/2315216.html)

=> [Python中使用epoll开发服务端程序](http://www.oschina.net/question/54100_8940)

=> How To Use Linux epoll with Python [英文](http://scotdoyle.com/python-epoll-howto.html) & [译文](http://devres.zoomquiet.io/data/20100927213110/index.html)

---
<h3 id="lib-async-2" style="color:#d35400;">asyncore & asynchat</h3>

**异步 socket 服务客户端和服务器的基础架构。**

=> [asyncore 文档翻译](http://automationtesting.sinaapp.com/blog/m_asyncore)

=> [asynchat 文档翻译](http://automationtesting.sinaapp.com/blog/m_asynchat)

***
<h2 id="web-dev" style="color:#c0392b;">Web 开发</h2>

 - [RFC 2616 (HTTP协议)](http://www.faqs.org/rfcs/rfc2616.html)
 - [RFC 2109 (Cookie)](https://www.ietf.org/rfc/rfc2109.txt)
 - [Web Python (CGI&WSGI)](http://webpython.codepoint.net/) & [译文](http://www.xefan.com/archives/84004.html)
 -  [PEP333 (Python Web Server Gateway Interface v1.0)](http://www.python.org/dev/peps/pep-0333) & [译文](http://www.cnblogs.com/laozhbook/p/python_pep_333.html)
 - [Serving Static Content With WSGI](http://pwp.stevecassidy.net/wsgi/static.html)
 - [jinja2](http://docs.jinkan.org/docs/jinja2/)
 - [廖雪峰 Python 实战](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/001397616003925a3d157284cd24bc0952d6c4a7c9d8c55000)
 - [ PEP 249 (Python Database API Specification v2.0)](http://legacy.python.org/dev/peps/pep-0249/) & [译文](http://blog.csdn.net/dajianshi/article/details/7482201)
 - [MySQLdb操作](https://github.com/qiwsir/ITArticles/blob/master/BasicPython/304.md)
 - [Introduction to MySQL in Python](http://www.mikusa.com/python-mysql-docs/introduction.html)
 -  [The Django Book](http://www.djangobook.com/en/2.0/index.html) & [译文](http://djangobook.py3k.cn/2.0/)

---
***
<h2 id="flask" style="color:#c0392b;">Flask</h2>

<h3 id="flask-use" style="color:#d35400;">使用</h3>

 - [教程 En](http://blog.miguelgrinberg.com/post/the-flask-mega-tutorial-part-i-hello-world)
 - [Jinja2 官方文档 2.7](http://docs.jinkan.org/docs/jinja2)
 - [Flask 官方文档 0.10.1](https://dormousehole.readthedocs.org/en/latest/)

---
<h3 id="flask-plugin" style="color:#d35400;">插件扩展</h3>

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
<h2 id="tornado" style="color:#c0392b;">Tornado</h2>
<h3 id="tornado-use" style="color:#d35400;">使用</h3>

- Tornado 是一个 Web 框架和异步，无阻塞 I/O 的网络库。

- **UI模块**是封装模板中包含的标记、样式以及行为的可复用组件。它所定义的元素通常用于多个模板交叉复用或在同一个模板中重复使用。模块本身是一个继承自Tornado的UIModule类的简单Python类，并定义了一个render方法。当一个模板使用{% module Foo(...) %}标签引用一个模块时，Tornado的模板引擎调用模块的render方法，然后返回一个字符串来替换模板中的模块标签。UI模块也可以在渲染后的页面中嵌入自己的JavaScript和CSS文件，或指定额外包含的JavaScript或CSS文件。你可以定义可选的embedded_javascript、embedded_css、javascript_files和css_files方法来实现这一方法。

- **模板** (tornado.template)
```Python
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
```一杯
默认提供了一些方法: escape(), url_escape(), json_encode(), squeeze().
可以添加任意自命名的方法 (在 tornado.web.RquestHandler 里, 可重写 get_template_namespace):
```Python
# Python code
def add(x ,y):
       return x + y
tornado.template.execute(add = add)
# the template
{{ add(1, 2) }}
```

=> [Python 教程 @老齐](https://github.com/qiwsir/ITArticles/blob/master/BasicPython/index.md#%E7%AC%AC%E4%B8%89%E9%83%A8%E5%88%86-%E6%98%A8%E5%A4%9C%E8%A5%BF%E9%A3%8E%E4%BA%AD%E5%8F%B0%E8%B0%81%E7%99%BB)

=> [Introduction to Tornado](http://www.pythoner.com/tag/tornado)

=> [官方文档中译版](http://www.tornadoweb.cn/documentation#_13)

=> [官方文档4.0.1](http://www.tornadoweb.org/en/stable/)

---
<h3 id="tornado-source-code" style="color:#d35400;">源码剖析</h3>

=> [Tornado 源码分析系列](http://www.cnblogs.com/Bozh/archive/2012/07/22/2603976.html)

=> [Tornado 源码解析篇](http://www.nowamagic.net/librarys/veda/detail/2566)

---

<h2 id="" style="color:#c0392b;">H2</h2>
<h3 id="" style="color:#d35400;">H3</h3>
<h4 id="" style="color:#f39c12;">H4</h4>
