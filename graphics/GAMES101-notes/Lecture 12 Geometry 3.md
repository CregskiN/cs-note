[TOC]



## 0. 前情提要



## 1. 网格操作 Mesh Operations

+ 网格细分 Mesh Subdivision（upsampling）

  <img src="https://www.qiniu.cregskin.com/202201222140743.png" alt="image-20220122214030719" style="zoom: 33%;" />

+ 网格简化 Mesh simplification（downsampling）

  <img src="https://www.qiniu.cregskin.com/202201222142129.png" alt="image-20220122214231100" style="zoom:33%;" />

  + 减少运算量

+ 网格正则化 Mesh regularizationÏ（same）

  <img src="https://www.qiniu.cregskin.com/202201222141068.png" alt="image-20220122214156041" style="zoom:33%;" />





### 1.1 Loop Subdivision

> Loop 这个人发明的，不是“循环”

目的：1. 分出更多的三角形 2. 让表面更圆润

逻辑概述：

1. 将每个三角形分解为四个小三角形

   <img src="https://www.qiniu.cregskin.com/202201222202382.png" alt="image-20220122220212356" style="zoom:50%;" />

2. 区分出新顶点和旧顶点，做不同处理

   <img src="https://www.qiniu.cregskin.com/202201222202181.png" alt="image-20220122220240153" style="zoom:50%;" />

具体实现：

1. 分解

2. **对于新顶点**：

   <img src="https://www.qiniu.cregskin.com/202201222203201.png" alt="image-20220122220342177" style="zoom: 33%;" />

   **对于旧顶点**：

   <img src="https://www.qiniu.cregskin.com/202201222204736.png" alt="image-20220122220405710" style="zoom: 45%;" />

   + n：旧顶点的度数
   + u：受周围顶点影响的影响因子

   最终，旧顶点的变化受 1. 旧顶点本身 2. 周围顶点 的影响



Loop 细分的结果：

<img src="https://www.qiniu.cregskin.com/202201222208722.png" alt="image-20220122220854693" style="zoom:50%;" />



### 1.2 Catmull-Clark Subdivision (General Mesh)

几个定义：

<img src="https://www.qiniu.cregskin.com/202201222212812.png" alt="image-20220122221222788" style="zoom: 50%;" />

+ Non-quad face：非四边形面
+ Extraordinary vetex：奇异点（度不为4）



**具体实现**：

<img src="https://www.qiniu.cregskin.com/202201222228894.png" alt="image-20220122222800866" style="zoom:33%;" />

第一次：Catmull-Clark Subdivision

<img src="https://www.qiniu.cregskin.com/202201222214500.png" alt="image-20220122221429471" style="zoom: 33%;" />

1. 连接四边形的一个对角边，形成两个三角形

2. 对每个三角形：

   + 取边的中点，取三角形的重心，连接中点与重心

   > 经过一次细分：
   >
   > + 有多少个奇异点？
   >
   >   原 2 个，新引入 2 个，共 4 个（在非四边形内点的点，需要连接每条边上的中点，这个点一定是新奇异点）
   >
   > + 有多少个非四边形面？
   >
   >   原 2 个，经过 Catmull-Clark Subdivision，剩 0 个



第二次：Catmull-Clark Subdivision

<img src="https://www.qiniu.cregskin.com/202201222228864.png" alt="image-20220122222829838" style="zoom:33%;" />



**数学表示形式**：

<img src="https://www.qiniu.cregskin.com/202201222231670.png" alt="image-20220122223141643" style="zoom:40%;" />

将顶点分为三类：

+ f：四边形的中心
+ e：边的中心
+ v：四边形的顶点





> Loop Subdivision 和 Catmull-Clark Subdivision 区别
>
> <img src="https://www.qiniu.cregskin.com/202201222229680.png" alt="image-20220122222940650" style="zoom:33%;" />
>
> + Loop：只能用于三角形的细分
> + Catmull-Clark Subdivision：可用于四边形的细分



### 1.3 Edge Collapse: Quadric Error Metrics

> 边坍缩，一种 Mesh Simplification

<img src="https://www.qiniu.cregskin.com/202201222248142.png" alt="image-20220122224831112" style="zoom: 33%;" />

需要的效果：坍缩前后的轮廓大致一样



**二次误差度量 Quadric Error Metrics**

二次误差：新顶点到原相邻面的距离的平方和最小

<img src="https://www.qiniu.cregskin.com/202201222257419.png" alt="image-20220122225739389" style="zoom:50%;" />

核心算法：

1. 取最小二次度量误差
2. 动态更新任何一个点的值

> 寻找最小二次度量误差，是在一个局部范围内进行的，实际上是一种`贪心算法`



坍缩结果：

<img src="https://www.qiniu.cregskin.com/202201222303338.png" alt="image-20220122230350305" style="zoom:50%;" />





## 2. Shadow mapping

在光栅化情况下，如何展示阴影？在之前的 Blinn-Phong 模型中，无法展示阴影，为此出现了 Shadow Mapping 技术。

几点了解：

+ 是一种 图像-空间 算法
  + 在阴影计算中，不需要清楚场景下的几何信息
  + 必须克服走样的问题
+ 关键点
  + 不在阴影中的 Shading point 可以**同时被光源和相机看到**



实际操作有两步：

假设一个场景

<img src="https://www.qiniu.cregskin.com/202201222321686.png" alt="image-20220122232107655" style="zoom:33%;" />

+ 光源：虚拟摄像机
+ 物体
+ 观测点



1. Render from Light

    在`光源`处摆放`虚拟摄像机`，看向场景，记录深度到 `Shadow Map`

   <img src="https://www.qiniu.cregskin.com/202201222321534.png" alt="image-20220122232124505" style="zoom:33%;" />

2. Render from Eye

   ​	从`观测点`看向场景，对于能看到的 Shading point 做 3. 操作

   <img src="https://www.qiniu.cregskin.com/202201222322528.png" alt="image-20220122232209487" style="zoom:33%;" />

3. Project to light

   ​	将可视像素投影到虚拟摄像机的成像图上，比较该点与虚拟成像图上记录的深度，判断该点是否“可被光源看到”

   <img src="https://www.qiniu.cregskin.com/202201222322803.png" alt="image-20220122232255760" style="zoom:33%;" />

   ​	

> 存在的问题：
>
> 1. 存在数值精度问题。在 3 中，深度的大小可以比较出来，但如果两个点非常接近，以浮点数存储的深度很难比较是否相等
> 2. Shadow Map 的分辨率很难把控
> 3. Shadow Map 只能做硬阴影

> 硬阴影、软阴影：区别是轮廓是否锐利



<img src="https://www.qiniu.cregskin.com/202201222333991.png" alt="image-20220122233346949" style="zoom:50%;" />

+ Umbra：本影区域，月亮完全挡住了来自太阳的光
+ Pernumbra：半影区域，月亮挡住一部分来自太阳的光

> 软硬阴影的产生，取决于光源本身的大小，而 Rasterization 的光源是点光源，做不到产生软阴影

