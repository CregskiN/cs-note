# vim

[TOC]



2020.11.02，在小米有品购买的米物键盘到了。键盘小巧，配合 MacBookPro 使用体验不错，但有一点不足：初次上手蓝牙键盘 + 触控板不是很舒服，故开始接触vim。以下为我接触 vim 的笔记



## 1. 安装

新手使用vscode商店的插件 vim ，体验还是可以的

### 1.1 下载

![image-20201102225956710](https://www.qiniu.cregskin.com/image-20201102225956710.png)



### 1.2 配置

复制商店页提供的默认配置到`setting.json`

```json
"vim.easymotion": true,
"vim.incsearch": true,
"vim.useSystemClipboard": true,
"vim.useCtrlKeys": true,
"vim.hlsearch": true,
"vim.insertModeKeyBindings": [
  {
    "before": ["j", "j"],
    "after": ["<Esc>"]
  }
],
"vim.normalModeKeyBindingsNonRecursive": [
  {
    "before": ["<leader>", "d"],
    "after": ["d", "d"]
  },
  {
    "before": ["<C-n>"],
    "commands": [":nohl"]
  }
],
"vim.leader": "<space>",
"vim.handleKeys": {
  "<C-a>": false,
  "<C-f>": false
}
```

### Reference

[在**VSCode**中使用**Vim**的正确方式](https://zhuanlan.zhihu.com/p/141248420)



## 2. 常用概念与按键

### 2.1 插入模式 / 输入模式

日常编辑文字的模式

| 按键 | 命令                           |
| ---- | ------------------------------ |
| ESC  | 退出`插入模式`，进入`命令模式` |



### 2.2 命令模式

1. **移动光标**

   | 按键            | 命令                           |
   | --------------- | ------------------------------ |
   | command + f / b | 上翻一页 / 下翻一页            |
   | command + u / d | 上翻半页 / 下翻半页            |
   | k、j、h、l      | 上、下、左、右                 |
   | `n`G / `n`gg    | 跳转到`第 n 行`                |
   | gg / G          | 跳转至`文首` / 跳转至`文尾`    |
   | gd              | 跳转至光标所在变量的`声明位置` |

   

2. **选择、复制、粘贴、删除**

   | 按键      | 命令                                                         |
   | --------- | ------------------------------------------------------------ |
   | shift + v | 选中光标所在行                                               |
   |           |                                                              |
   | yy        | 复制光标所在行                                               |
   |           |                                                              |
   | p \ P     | 粘贴到光标所在下一行 / 粘贴到光标所在上一行                  |
   |           |                                                              |
   | x / X     | 向后删除一个字符 = Delete / 向前删除一个字符 = Backspace     |
   | d0 / d$   | 删除行内，从光标位置到开头 / 删除行内，从光标位置到末尾      |
   | dd / dw   | 删除光标`所在行` / 删除光标`所在单词`                        |
   | `n`dd     | 从光标位置往下，删除`n`行                                    |
   | cc / cw   | 删除光标`所在行`并进入编辑模式 / 删除光标`所在单词`并进入编辑模式 |

   

3. **直接进入插入模式**

   | 按键  | 命令                                                         |
   | ----- | ------------------------------------------------------------ |
   | i / a | 在当前选中`字符前`进入 / 在当前选中`字符后`进入              |
   | O / o | 在当前**行前插入新行**，并将光标移至新行 <br />/ 在当前**行后插入新行**，并将光标移至新行 |

   

4. **多标签编辑**

   | 按键          | 命令                                |
   | ------------- | ----------------------------------- |
   | :tabn / :tabp | 跳转到下一个标签 / 跳转到上一个标签 |
   | gt / gT       | 跳转到下一个标签 / 跳转到上一个标签 |
   | `n`gt         | 跳转到第`n`个标签                   |
   | :tabc / :tabo | 关闭`当前`标签 / 关闭`其他`标签     |

   

5. **多文件编辑**

   | 按键        | 含义               |
   | ----------- | ------------------ |
   | :e filename | 打开 filename 文件 |

   



### 2.3. 编辑模式

在**命令模式**下输入`: + 如下字母`，可实现对文件的保存、查找、替换等

| 按键     | 命令                             |
| -------- | -------------------------------- |
| :w       | 将文件写入缓冲区                 |
| :q       | 退出，如缓冲区有修改，会提示     |
| :q!      | 不保存、强制退出。放弃缓冲区修改 |
| :wq / :x | 保存、退出                       |



### Reference

[Linux Vim三种工作模式（命令模式、输入模式和编辑模式）详解](http://c.biancheng.net/view/804.html)

[VIM常用快捷键](https://www.cnblogs.com/markleaf/p/7808817.html)

[VIM常用快捷键 - markleaf - 博客园](https://www.cnblogs.com/markleaf/p/7808817.html)





# Q & A

## Q：mac 端 vscode，按官方默认配置后，ctrl + f / b 失效

A：将 vim.handleKeys 中的 C-f 和 C-b 设置为 true，即取消**在vim中禁用如下快捷键**

```json
"vim.handleKeys": {
  "<C-a>": false,
  "<C-f>": true,
  "<C-b>": true
}
```



