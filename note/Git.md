#Git&GitHub Learning

##参考
 - [Git入门](http://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/00137396287703354d8c6c01c904c7d9ff056ae23da865a000)
 - [git - 简明指南](http://rogerdudler.github.io/git-guide/index.zh.html)
 - [猴子都能懂的 GIT 入门](http://backlogtool.com/git-guide/cn/)
 - [Git Book v1.0](http://git-scm.com/book/zh/v1)
 - [GitHub 秘籍](http://snowdream86.gitbooks.io/github-cheat-sheet/content/zh/index.html)
 - [Git 参考手册](http://gitref.justjavac.com/)
 - [EMOJI CHEAT SHEET](http://www.emoji-cheat-sheet.com/)
 - [用对 gitignore](http://www.barretlee.com/blog/2015/09/06/set-gitignore-after-add-file/)
 
---

##开始
安装并设置身份信息
```
git config --global user.email "you@example.com"
git config --global user.name "Your Name"
```
创建 SSH Key, 将公钥 id_rsa.pub 添加进 GitHub
```
ssh-keygen -t rsa -C "youremail@example.com"
cat .ssh/id_rsa.pub
```
关联本地仓库
```
git init
git remote add origin git@github.com:Damnever/XXX.git
#另外一个版本库已向该引用进行了推送。再次推送前，先整合远程变更
git pull git@github.com:Damnever/XXX.git
```
推送
```
git add xxx
git commit -m "xxx"
git push -u origin master | git push origin master
```

---
##援疑质理
###修改远程仓库地址
```
git remote rm origin
git remote add origin git@github.com:Damnever/new.git
```

---
###合并两次提交：
```
git add xxx
git commit -m 'xxx'
git add xxxx        # 发现漏了一个 xxxx
git commit --amend  # 合并
```

---
###撤销 checkout
```
git reflog  # 查看日志，找到 checkout 前的一个点
git reset @{xx} --hard  # 重置到 xx 点
```

---
###撤销还未提交的文件
```
git reset HEAD filename
git checkout -- filename
```

---
###创建，合并分支
```
git branch dev       # 创建分支 dev
git checkout dev     # 切换分支到 dev
git checkout -b dev master  # 创建master下的分支dev并切换到分支 dev
git branch           # 查看分支
git checkout master  # 切换到 master 分支
git merge dev        # 将 dev 分支快速合并到 master
# 发生冲突时，需要重新编辑冲突的文件然后提交
# git log --graph --pretty=oneline --abbrev-commit # 查看分支合并情况
# git merge --no-ff -m "merge with no-ff" dev # 不使用 fast-forward 模式
git branch -d dev    # 删除 dev 分支，-D 强行删除
```

---
###暂存工作现场
```
git stash      # 把当前工作现场“储藏”起来
# 创建一个分支工作然后回到主分支合并分支...
git stash pop  # 恢复工作现场； git stash apply, git stash drop
git stash list # 查看工作现场
```