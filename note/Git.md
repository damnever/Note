# Simple Git&GitHub Guide for Beginners

-> https://github.com/0o200/guides

## 参考
 - [Git入门](http://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/00137396287703354d8c6c01c904c7d9ff056ae23da865a000)
 - [git - 简明指南](http://rogerdudler.github.io/git-guide/index.zh.html)
 - [猴子都能懂的 GIT 入门](http://backlogtool.com/git-guide/cn/)
 - [Git Book v1.0](http://git-scm.com/book/zh/v1)
 - [GitHub 秘籍](http://snowdream86.gitbooks.io/github-cheat-sheet/content/zh/index.html)
 - [Git 参考手册](http://gitref.justjavac.com/)
 - [EMOJI CHEAT SHEET](http://www.emoji-cheat-sheet.com/)
 - [用对 gitignore](http://www.barretlee.com/blog/2015/09/06/set-gitignore-after-add-file/)

---

## 开始

安装并设置身份信息
```
> git config --global user.email "you@example.com"
> git config --global user.name "Your Name"
```

创建 SSH Key, 将公钥 id_rsa.pub 添加进 GitHub
```
> ssh-keygen -t rsa -C "youremail@example.com"
> cat .ssh/id_rsa.pub
```

## GitHub `pull request` 工作流

关联本地仓库
```
> git init
> git remote add origin git@github.com:me/repo.git
```

如果是公有项目
```
> git remote add upstream git@github.com:other/repo.git  # 添加其它仓库
```

更新本地代码
```
> git checkout master  # 一般都是 master 分支，自行应变
> git pull upstream master   # 如果是自己的项目直接 git pull origin master
```

切换分支
```
> git checkout -b patch-1  # 慎用 git checkout -B patch-1 会覆盖掉已存在的分支
> git branch  # 查看分支
```

修改查看变动
```
> git diff    # 可以先在本地 review 一遍
> git status  # 查看文件状态
```

添加并提交
```
> git add xxx.txt
> git commit -m "xxx"
> git push origin patch-1
```

最后在 GitHub 上面提交 `pull request`，自己 review 一遍，然后在右侧栏里面指定对应的人

---

## 援疑质理

建议修改成自己顺手的编辑器

```
> git config --global core.editor vim
> # vim 很简单，按 i 进行编辑，编辑完按 Esc 退出到 normal 模式，然后输入 :wq 保存并退出
> # 高阶使用姿势自行查阅
```

### 修改最近一次的 commit 信息

```
> git rebase -i HEAD~1
# 进入编辑器界面有一行：
# pick 4297720 commit msg
# 将 pick 替换成 r，也就是 reword，下面的以 # 口头文本注释是有提示的，保存并退出
# 此时会再次打开编辑窗口，编辑 commit 信息保存退出即可
> git log --pretty=online  # 查看 commit 信息
```

### 合并两次 commit：

```
> git rebase -i HEAD~2
# 进入编辑器界面有两行：
# pick 4297720 commit msg 1
# pick 4ec7f20 commit msg 2
# 将第二个 pick 替换成 s，也就是 squash，以 # 口头文本注释是有提示的，保存并退出
# 此时会再次打开编辑窗口，合并两次 commit 信息保存退出即可
```

### 暂存工作现场

```
> git stash      # 把当前工作现场“储藏”起来
> git stash apply # 恢复
```

### 其它使用姿势自行查阅
