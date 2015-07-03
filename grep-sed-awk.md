*   [grep](#grep)
*   [sed](#sed)
*   [awk](#awk)

***

<h2 id="grep">GREP</h2>

Global search Regular Expression and print out the line.

常用参数(grep --help)：
```
-i 忽略大小写
-v 选择不匹配的行
-c 匹配行数量
```

基本正则表达式：

| 符号 | 作用 |
|----|----|
| ^  | 匹配行首 |
| $  | 匹配行尾 |
| [] | 匹配多种可能，其中的^表示反选，-表示范围 |
| .  | 任意字符 |
| *  | 匹配零个或多个 |
| \<\\> | 精确匹配其中的字符串 |
| \\{m, n\\} | 匹配m至n次 |
| [:alnum:] | 数字字符 |
| [:alpha:] | 字母字符 |
| [:alnum:] | 字母数字字符 |
| [:digit:] | 数字字符 |
| [:graph:] | 非空格、控制字符 |
| [:lower:] | 小写字母 |
| [:uper:] | 大写字母 |
| [:cntrl:] | 控制字符 |
| [:print:] | 非空字符 |
| [:punct:] | 标点字符 |
| [:space:] | 空白字符（空格、新行、制表符） |
| [:xdigit:] | 十六进制数字 |

扩展正则表达式：

| 符号 | 作用 |
|----|----|
| +  | 匹配一次以上 |
| ?  | 匹配0~1次 |
| 单竖线  | 或，匹配左边或右边 |

<h2 id="sed">SED</h2>

Stream editor.

常用参数(sed --help)：
```
-i 直接修改源文件
-e 连接多个编辑命令
-n 不显示没关系的行
-f 指定命令脚本
```

**命令**和Vim很相似：
```
>>> cat test.txt
0 line zero.
1 line one.
2 line two.

4 line four, line three is empty line.
5 line five.
```
- **删除(d)**

```
### 删除第一行
>>> sed '1d' test.txt
1 line one.
2 line two.

4 line four, line three is empty line.
5 line five.
### 删除所有（第一行到最后一行）
>>> sed '1,$d' test.txt
### 仅保留第二行
>>> sed '2!d' test.txt
1 line one.
### 删除匹配行
>>>  sed '/four/d' test.txt
0 line zero.
1 line one.
2 line two.

5 line five.
```

- **替换（s/y）**

```
### 替换每行第一次出现的字符串
>>> sed 's/line/LINE/' test.txt
0 LINE zero.
1 LINE one.
2 LINE two.

4 LINE four, line three is empty line.
5 LINE five.
### 全部替换
>>> sed 's/line/LINE/g' test.txt
0 LINE zero.
1 LINE one.
2 LINE two.

4 LINE four, LINE three is empty LINE.
5 LINE five.
### 替换每行的第二次出现的
>>> sed 's/line/LINE/2' test.txt
0 line zero.
1 line one.
2 line two.

4 line four, LINE three is empty line.
5 line five.
### 替换匹配的
>>> sed 's/\bzero/0/' test.txt
0 line 0.
1 line one.
2 line two.

4 line four, line three is empty line.
5 line five.
### 字符转换
>>> sed 'y/01245/12456/' test.txt
1 line zero.
2 line one.
4 line two.

5 line four, line three is empty line.
6 line five.
### 替换匹配行的下一行，将空行的下一行里的line替换成LINE
>>> sed '/^$/{n; s/line/LINE/}' test.txt
0 line zero.
1 line one.
2 line two.

4 LINE four, line three is empty line.
5 line five.
```

- **插入(i/a)**

```
### 插入到指定行
>>> sed '1 i Insert to line 1' test.txt
Insert to line 1
0 line zero.
1 line one.
2 line two.

4 line four, line three is empty line.
5 line five.
### 插入到指定行后面
>>> sed '1 a Insert to line 2' test.txt
0 line zero.
Insert to line 2
1 line one.
2 line two.

4 line four, line three is empty line.
5 line five.
### 插入到匹配行后面
>>> sed '/1/a Insert to line 3' test.txt
0 line zero.
1 line one.
Insert to line 3
2 line two.

4 line four, line three is empty line.
5 line five.
### 插入到匹配行前面
>>> sed '/1/i Insert to line 2' test.txt
0 line zero.
Insert to line 2
1 line one.
2 line two.

4 line four, line three is empty line.
5 line five.
```

- **读取/写入/打印**

```
>>> echo "HELLO WORLD" > hello.txt; cat hello.txt
HELLO WORLD
### 读取文件内容到空行所在处
>>> sed '/^$/r hello.txt' test.txt
0 line zero.
1 line one.
2 line two.

HELLO WORLD
4 line four, line three is empty line.
5 line five.
### 只显示相关的行
>>> sed -n 's/line/LINE/p' test.txt
0 LINE zero.
1 LINE one.
2 LINE two.
4 LINE four, line three is empty line.
5 LINE five.
### 写入指定内容到文件
>>> sed -n '1,2 w test2.txt' test.txt; cat test2.txt
0 line zero.
1 line one.
```

- **批量执行脚本**

```
>>> cat sed.rules
s/line/LINE/g
y/01245/12456/
>>> sed -f sed.rules test.txt
1 LINE zero.
2 LINE one.
4 LINE two.

5 LINE four, LINE three is empty LINE.
6 LINE five.
```

- **模式空间/保留空间**

```
### H h G g 待……
>>> sed '/0/{h;d};/1/G' test.txt
1 line one.
0 line zero.
2 line two.

4 line four, line three is empty line.
5 line five.
```

<h2 id="awk">AWK</h2>

不像`sed`是基于行的，`awk`是基于列的是一种**语言**...参考：http://coolshell.cn/articles/9070.html。

打印指定域：
```
>>> ls -al --color=never | awk '{print $1, $6, $7, $8}'
total
drwxrwxrwx Jul 3 14:10
drwxr-xr-x Jul 3 11:54
-rwxrwxrwx Apr 24 21:04
-rwxrwxrwx Apr 30 11:12
-rwxrwxrwx Jun 30 15:50
drwxrwxrwx Jul 2 17:43
...
```
截取字符串：
```
>>> ls -al | awk '{print substr($1, 0, 4)}'
tota
drwx
drwx
-rwx
-rwx
-rwx
drwx
...
```
过滤：
```
>>> ls -al | awk '$5 > 62442704 {print $NF}'
bt.json
```
计算当前目录大小：
```
>>> ls -al | awk 'BEGIN{total=0}{total+=$5}END{print total}'
916276395
```
