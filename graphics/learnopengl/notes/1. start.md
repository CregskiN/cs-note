[TOC]

# 1. 一些基础概念

**核心模式与立即渲染模式**

+ Immediate mode
+ Core-profile



**状态机**

我们通常使用如下途径去更改OpenGL状态：设置选项，操作缓冲

+ 上下文 OpenGL Context
+ 状态设置函数 State-changing Function
+ 状态使用函数 State-using Function



**对象**

+ 可以把对象看做一个C风格的结构体 Struct

```c
struct object_name {
    float  option1;
    int    option2;
    char[] name;
};
```



# 2. 需要的库与实现的功能

+ 一个窗口、一个 OpenGL 上下文

  GLUT，SDL，SFML 和 **GLFW**

  > GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口。它允许用户创建OpenGL上下文、定义窗口参数以及处理用户输入

+ 获取当前平台 OpenGL 驱动

  GLAD

  > [https://glad.dav1d.de](https://glad.dav1d.de/)
  
  
  
  <img src="https://www.qiniu.cregskin.com/202203031648499.png" alt="image-20220303164824463" style="zoom:50%;" />





































