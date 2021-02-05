官网中对应的页面如下

https://code.visualstudio.com/docs/cpp/config-clang-mac#_prerequisites



### 1 准备

+ vscode 软件

+ C/C++ Extension Pack 插件

  <img src="https://www.qiniu.cregskin.com/image-20210130111245269.png" alt="image-20210130111245269" style="zoom: 33%;" />

+ clang/clang++ 编译器

  + 检查已安装clang++

    > clang++ -v

  + 如果未安装，请前往 app store 下载 xcode



### 2  .vscode配置

在当前工作区准备以下文件（夹）

+ .vscode

  + tasks.json # 用于编译c++文件
  + launch.json # 用于使用vscode自带的debug工具（左侧的小虫图标）
  + c_cpp_properties.json # 用于使用vscode自带的代码提示工具如 IntelliSense

+ main.cpp

  ```c++
  #include <iostream>
  #include <vector>
  #include <string>
  
  using namespace std;
  
  int main()
  {
      vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
  
      for (const string& word : msg)
      {
          cout << word << " ";
      }
      cout << endl;
  }
  ```

  

<img src="https://www.qiniu.cregskin.com/image-20210130112825799.png" alt="image-20210130112825799" style="zoom:50%;" />



### 配置tasks.json

command + shift + b，vscode会执行tasks.json中的任务。

本文配置的是c++编译，替换tasks.json的内容如下：

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build with Clang", //这个任务的名字在launch.json最后一项配置
      "type": "shell",
      "command": "clang++",
      "args": [
        "-std=c++17",
        "-stdlib=libc++",
        "-g",
        // 生成调试信息，GUN可使用该参数
        "${file}",
        // file指正在打开的文件
        "-o",
        // 生成可执行文件
        "${fileDirname}/${fileBasenameNoExtension}"
        // fileDirname指正在打开的文件所在的文件夹
        // fileBasenammeNoExtension指没有扩展名的文件，unix中可执行文件属于此类
      ],
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "problemMatcher": ["$gcc"],
      "group": {
        "kind": "build",
        "isDefault": true
      }
    }
  ]
}

```

打开main.cpp，按**command + shift + b**（注意，按这组快捷键时main.cpp文件在vscode中是正在打开的），如下图

<img src="https://www.qiniu.cregskin.com/image-20210130113056137.png" alt="image-20210130113056137" style="zoom:33%;" />



工作区中没有扩展名的main就是在mac os下生成的可执行文件（同理，如果是windows，有扩展名.exe）

在vscode内置的终端中，可以运行main，如下图：

<img src="https://www.qiniu.cregskin.com/image-20210130113224570.png" alt="image-20210130113224570" style="zoom:33%;" />







### 配置 c_cpp_properties.json

c_cpp_properties.json 的作用是：代码提示、代码跳转等

```json
{
  "configurations": [
    {
      "name": "Mac",
      "includePath": [
        "${workspaceFolder}/**",
        "/Library/Developer/CommandLineTools/usr/include",
        "/Library/Developer/CommandLineTools/usr/lib/clang/11.0.3/include",
        // 请根据你的clang版本修改，我这里是11.0.3
        "/usr/local/include"
      ],
      "defines": [],
      "macFrameworkPath": [
        "/System/Library/Frameworks",
        "/Library/Frameworks"
      ],
      "compilerPath": "/usr/bin/clang++",
      "cStandard": "c11",
      "cppStandard": "c++17",
      "intelliSenseMode": "clang-x64"
      // "compileCommands": "${workspaceFolder}/build/compile_commands.json"
    }
  ],
  "version": 4
}
```



### 配置launch.json

launch.json是调用vscode debug功能的配置文件

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "type": "lldb",
      "request": "launch",
      "name": "Debug",
      "program": "${workspaceFolder}/${fileBasenameNoExtension}",
      "args": [],
      "cwd": "${workspaceFolder}",
      "preLaunchTask": "Build with Clang"
    }
  ]
}
```



打开debug窗口，打好断点，按下图操作

<img src="https://www.qiniu.cregskin.com/image-20210130113807581.png" alt="image-20210130113807581" style="zoom:33%;" />



<img src="https://www.qiniu.cregskin.com/image-20210130113823247.png" alt="0130113823247" style="zoom:33%;" />





这三个配置文件中的参数说明，在官网都有，我把一部分写在了注释里



---

References：

https://code.visualstudio.com/docs/cpp/config-clang-mac#_prerequisites

