# Some toys

## [ddht](./ddht)

A powerful DHT crawler.
![email bomber](./ddht/example.png)
Please read **[README.md](./ddht/README.md).**

---
## [cmd_tree.py](./cmd_tree.py)
A command line program, which imitate 'tree' on *unix.

![cmd_tree](./cmd_tree.png)
```
usage: cmd_tree.py [-h] [-P path] [-L level]

List directory as a tree.

optional arguments:
    -h, --help : show this help message and exit
    -P path :    Given a path to show, default is current directory.
    -L level :   Directories' recursion depth.
```
---
## [toc_gen.py](./toc_gen.py)
Generates table of content for markdown.
```
Your title style must be like this:
    <h1 id="h1">H1 title</h1>
    <h2 id="h2">H2 title</h2>
    ...
Generated TOC like this:
    *   [H1 title](#h1)
        *    [H2 title](#h2)
    ...


usage: toc_gen.py [-h] [-S src] [-D des]

Generates TOC from markdown text.

optional arguments:
      -h, --help  show this help message and exit
      -S src      A path of source file.
      -D des      A file path to store TOC.
```

---
## [luoo_download.py](./luoo_download.py)
```
Download music from luoo.net

Usage: luoo_download.py <journal_num> <music_num>
```

---
## [proxy.py](./proxy.py)
A simple proxy by Tornado.

---
## [win_wifi_auto_reconnect.py](./win_wifi_auto_reconnect.py)
Windows WIFI auto reconnect script.

---
## [Algorithms](./algorithm)
Some algorithms write in C, Python and a little Golang.

---
## [pythonchanllenge](./pythonchanllenge)
Some solutions to problems in pythonchanllenge.com.
