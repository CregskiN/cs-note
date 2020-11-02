# vim

[TOC]



2020.11.02，在小米有品购买的米物键盘到了。键盘小巧，配合 MacBookPro 使用体验不错，但有一点不足：初次上手蓝牙键盘 + 触控板不是很舒服，故开始接触vim。以下为我接触 vim 的笔记



## 1. 安装

新手使用vscode商店的插件 vim ，体验还是可以的

1. 到商店查询 vim，安装

   ![image-20201102225956710](https://www.qiniu.cregskin.com/image-20201102225956710.png)

2. 复制商店页提供的默认配置到`setting.json`

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

### 1. 插入模式 / 输入模式

日常编辑文字的模式

| 按键 | 命令                           |
| ---- | ------------------------------ |
| ESC  | 退出`插入模式`，进入`命令模式` |



### 2. 命令模式

1. **移动光标**

   | 按键         | 命令                           |
   | ------------ | ------------------------------ |
   | k、j、h、l   | 上、下、左、右                 |
   | `n`G / `n`gg | 跳转到`第 n 行`                |
   | gg / G       | 跳转至`文首` / 跳转至`文尾`    |
   | gd           | 跳转至光标所在变量的`声明位置` |

   

2. **删除复制**

   | 按键 | 命令             |
   | ---- | ---------------- |
   | dd   | 删除光标所在行   |
   | dw   | 删除光标所在单词 |

   

3. **命令模式 -> 插入模式**

   | 按键 | 命令                       |
   | ---- | -------------------------- |
   | i    | 在当前光标位置进入插入模式 |

   



### 3. 编辑模式

在**命令模式**下输入`: + 如下字母`，可实现对文件的保存、查找、替换等

| 按键 | 命令         |
| ---- | ------------ |
| :wq  | 保存、退出   |
| :q   | 不保存、退出 |



### Reference

[Linux Vim三种工作模式（命令模式、输入模式和编辑模式）详解](http://c.biancheng.net/view/804.html)