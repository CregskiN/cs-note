# Ray Tracing 1 (White-Style Ray Tracing)

[TOC]





**光线追踪**和**光栅化**是两个不同的成像方式



# 1. 为什么使用光线追踪 Ray Tracing ?

## 1.1 光栅化 Rasterization 的不足

+ 光栅化不能很好的表示全局效果 global effects，如：
  + 软阴影 soft shadows
  + 经过多次反射的光线 light bounces more than once

  <img src="https://www.qiniu.cregskin.com/image-20210108213006641.png" alt="image-20210108213006641" style="zoom:50%;" />



+ 光栅化很快，但是质量堪忧

  <img src="https://www.qiniu.cregskin.com/image-20210108213335853.png" alt="image-20210108213335853" style="zoom: 50%;" />



## 1.2 光线追踪 & 光栅化

+ 光线追踪的渲染结果很精准，但很慢

  + 光栅化做实时渲染 real-time，光线追踪做离线渲染 offline

    Ray Tracing 有多慢？1帧至少需要10K个CPU小时





# 2. 基础的光线追踪算法 Basic Ray-Tracing Algorithm

## 2.1 一些定义

1. 光线 Light Rays：

   + 光线沿直线传播
   + 光线之间不能发生碰撞 collide
   + 光线从光源发出，经过反射，被眼睛接收（光路可逆）

   **光线追踪利用的是：光路的可逆性**，起点是光源，终点是相机/眼睛

2. 光线投射 Ray Casting

   + 第一步：从摄像机位置到适口平面中每个像素做投射，检查是否投射到物体某点（是否被摄像机可见），最终生成一张图
   + 第二步：假设投射到物体上某点，检查该光源是否可以投射到该点（是否被光源可见）

   <img src="https://www.qiniu.cregskin.com/image-20210108215915429.png" alt="image-20210108215915429" style="zoom:50%;" />

   

## 2.2 针孔相机模型 Pihole Camera Model

此处基于 Pinhole Camera Model

假设：摄像机是点、光源是点、光线打到物体上会完美反射/折射

### Ray Casting - Generating Eye Rays



<img src="https://www.qiniu.cregskin.com/image-20210108221052498.png" alt="image-20210108221052498" style="zoom:50%;" />

上图所示为一条 Eye Ray 的生成流程中的第一步：

沿 Eye point 到 image plane 做一条直线，记录该直线与最近物体的交点（图示中有两个物体与该条 Eye Ray 有交点：球、三角，仅记录球的交点）



### Ray Casting - Shading Pixles ( Local Only )

<img src="https://www.qiniu.cregskin.com/image-20210108221707250.png" alt="image-20210108221707250" style="zoom:50%;" />

+ 作交点 Shading point 与光源的连线 Shadow Ray，判断光源与交点间是否有物体遮挡（即是否处于阴影中）
+ 求出 Shading point 的法线，做 Shading



**针孔相机模型 Pihole Camera Model 得到的结果与光栅化类似，但还未解决光线多次反射的问题**

# 3. Recursive (Whitted-Style) Ray Tracing

<img src="https://www.qiniu.cregskin.com/image-20210108222430442.png" alt="image-20210108222430442" style="zoom:40%;" />

## 3.1 主要流程

**第一步**：沿 eye point 到 image plane 某点方向做直线，记录该直线与所有物体的最近交点

<img src="https://www.qiniu.cregskin.com/image-20210108223226047.png" alt="image-20210108223226047" style="zoom:33%;" />

**第二步**：作出反射光 Reflected Ray、折射光 Refracted Ray，记录他们的 bounce 点

<img src="https://www.qiniu.cregskin.com/image-20210108223236661.png" alt="image-20210108223236661" style="zoom:33%;" />

<img src="https://www.qiniu.cregskin.com/image-20210108223244782.png" alt="image-20210108223244782" style="zoom:33%;" />

**第三步**：将第一步第二步记录的交点，结合 light source point 作 Shadow Rays

<img src="https://www.qiniu.cregskin.com/image-20210108223256507.png" alt="image-20210108223256507" style="zoom:33%;" />

**第四步**：将所有点，作为 Shading point 着色之后的结果，顺着光路累加到 image plane

（计算中需要考虑光线 bounce 的能量损失）



### 三类光线 Ray 的正式叫法

+ primary ray
+ secondary ray
+ shadow ray

<img src="https://www.qiniu.cregskin.com/image-20210108223304704.png" alt="image-20210108223304704" style="zoom:33%;" />

## 3.2 线面求交  Ray-Surface Intersection

### 数学中的光线

<img src="https://www.qiniu.cregskin.com/image-20210108225208177.png" alt="image-20210108225208177" style="zoom:33%;" />



### 线球相交 Ray Intersection With Sphere

光线、球面 定义式如下：

<img src="https://www.qiniu.cregskin.com/image-20210108230234397.png" alt="image-20210108230234397" style="zoom:33%;" />

光线、球面 示意图如下：

<img src="https://www.qiniu.cregskin.com/image-20210108230300250.png" alt="image-20210108230300250" style="zoom:50%;" />

如何保证光线与球面相交于点p？

<img src="https://www.qiniu.cregskin.com/image-20210108230421595.png" alt="image-20210108230421595" style="zoom: 50%;" />

得到下面形式的表达式

<img src="https://www.qiniu.cregskin.com/image-20210108230807791.png" alt="image-20210108230807791" style="zoom:50%;" />

这三项的求法：



<img src="https://www.qiniu.cregskin.com/image-20210108230818341.png" alt="image-20210108230818341" style="zoom: 50%;" />

t的求法：

<img src="https://www.qiniu.cregskin.com/image-20210108230826156.png" alt="image-20210108230826156" style="zoom:50%;" />

t可以有0个、1个、2个，分别对应下面相离、相切、相交

<img src="https://www.qiniu.cregskin.com/image-20210110201255659.png" alt="image-20210110201255659" style="zoom:50%;" />





### 光线与隐式表面的相交 Ray Intersection With Implict Surface

光线表达式：<img src="https://www.qiniu.cregskin.com/image-20210110201431744.png" alt="image-20210110201431744" style="zoom:50%;" />

隐式表面表达式：<img src="https://www.qiniu.cregskin.com/image-20210110201457886.png" alt="image-20210110201457886" style="zoom:50%;" />



将光线带入为p：<img src="https://www.qiniu.cregskin.com/image-20210110201521980.png" alt="image-20210110201521980" style="zoom:50%;" />



就可以求出光线与复杂的隐式表面的交点

<img src="https://www.qiniu.cregskin.com/image-20210110201548765.png" alt="image-20210110201548765" style="zoom:50%;" />



### 光线与显式表面求交 Ray Intersection With Explicit Surface

在显式表面中，三角形非常重要

+ 在渲染上 Rendering：可见性、阴影、光线

+ 在几何上 Geometry：判断点在封闭物体内还是外

  某条光线上，在物体中的部分任意一点往外做射线，都只有奇数个交点（直线与物体表面相切不算）



<img src="https://www.qiniu.cregskin.com/image-20210110202610710.png" alt="image-20210110202610710" style="zoom:50%;" />

如何计算光线与三角形的交点？

+ 最简单的策略：光线与每个三角形求交
+ 是否有策略加速运算？可以

计算结果，无非是光线与三角形有 0 个交点，或 1 个交点



**如何求光线与三角形交点？**拆分成以下两步：

1. 计算光线与三角形所在面的交点

   + 定义一个平面：法线 $\vec{N}$ + 平面上任意一点 $\vec{p^{'}}$

     <img src="https://www.qiniu.cregskin.com/image-20210110203031239.png" alt="image-20210110203031239" style="zoom:40%;" />

     该平面上任意点 $\vec{p}$ 满足：<img src="https://www.qiniu.cregskin.com/image-20210110203102288.png" alt="image-20210110203102288" style="zoom:33%;" />

   + 将光线公式带入到平面表达式中的 $\vec{p}$

     光线：<img src="https://www.qiniu.cregskin.com/image-20210110201431744.png" alt="image-20210110201431744" style="zoom:30%;" />

     平面：<img src="https://www.qiniu.cregskin.com/image-20210110203102288.png" alt="image-20210110203102288" style="zoom:30%;" />

     代入后：<img src="https://www.qiniu.cregskin.com/image-20210110203355378.png" alt="image-20210110203355378" style="zoom:30%;" />

     

     计算结果：<img src="https://www.qiniu.cregskin.com/image-20210110203414910.png" alt="image-20210110203414910" style="zoom:33%;" />

     

2. 判断该交点是否在三角形内

   （三步叉乘）

   

   

**是否有方法直接计算出光线与三角形的交点？** 

有，用重心坐标的方法列出等式：<img src="https://www.qiniu.cregskin.com/image-20210110203951199.png" alt="image-20210110203951199" style="zoom:33%;" />

写成的矩阵：<img src="https://www.qiniu.cregskin.com/image-20210110212245067.png" alt="image-20210110212245067" style="zoom:33%;" />

各个参数的说明：<img src="https://www.qiniu.cregskin.com/image-20210110212308959.png" alt="image-20210110212308959" style="zoom:33%;" />

求出三个未知数：$t$、$b_1$、$b_2$ 后，进行判断：$\left \{ \begin{matrix} b_1 \in [0, 1] \\ b_2 \in [0, 1] \end{matrix} \right.$





### 求交加速策略：包围盒 Bounding Volumes

+ 光线与物体表面每个三角形求交，原始策略：
  + 每个物体表面都有**大量的三角形需要求交**
  + 而需要的只是**距离光源最近的交点**
+ 问题
  + 原始策略的算法复杂度 = 像素 ✖️ 物体数 ✖️ 物体表面三角形数
  + 非常慢！

<img src="https://www.qiniu.cregskin.com/image-20210110221000321.png" alt="image-20210110221000321" style="zoom:16%;" /><img src="https://www.qiniu.cregskin.com/image-20210110221029653.png" alt="image-20210110221029653" style="zoom:16%;" />



包围盒 Bounding Volumes ：使用一块规则体积把物体包裹起来，包围盒具有三个特点

+ 物体“装满”包围盒的体积
+ 如果光线与包围盒不相交，则一定与物体不相交
+ 所以先测试光线与包围盒是否相交，如果相交，再测试光线与物体是否相交

<img src="https://www.qiniu.cregskin.com/image-20210110221919291.png" alt="image-20210110221919291" style="zoom:30%;" />

长方体包围盒由三对面构成：三对面分别平行于xoy面、xoz面、yoz面

<img src="https://www.qiniu.cregskin.com/image-20210110222412883.png" alt="image-20210110222412883" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20210110222422878.png" alt="image-20210110222422878" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20210110222432492.png" alt="image-20210110222432492" style="zoom:25%;" />

**二维的包围盒：轴对齐包围盒 Axis-Aligned Bounding Box ( AABB )**





**如何判定光线与包围盒的交点？**以2D为例

<img src="https://www.qiniu.cregskin.com/image-20210110223321457.png" alt="image-20210110223321457" style="zoom:35%;" />

左图：光线与平行于x轴的一对直线，相交于 $t_{min}$、$t_{max}$ 时刻

中图：光线与平行于y轴的一对直线，相交于$t_{min}、t_{max}$ 时刻

右图：**前两个图获得的直线相交的部分**，就是 Bounding Box 所截取的部分光线

> 如果左图、中图获得的直线不相交，则说明光线与 Bound Box 不相交



推广到3D情况：

+ 关键思想

  + t 时刻，光线在三个对面内（三个对面共有区域），才算光线与 Bounding Volume 相交
  + t 时刻，光线此时不在 Bouding Volume（光线离开任何一个对面），说明此时光线与 Bounding Volume 不相交

+ 算法思想：

  + 三组 $t_{min}$、$t_{max}$ 含义：光线进入该对面的时刻、光线离开该对面的时刻

  + $t_{enter}$ = max{$t_{min1}$, $t_{min2}$, $t_{min3}$}、$t_{exit}$ = min{$t_{max1}$, $t_{max2}$, $t_{max3}$}

  + 出现的问题

    + $t_{exit} \lt 0 $  ?

      盒子在光线反方向

    + $t_{exit} \ge 0 $ && $t_{enter} \lt 0$ ?

      光源在盒子内

  + 万全的条件：当且仅当 $t_{enter} \lt t_{exit}$ && $t_{exit} \gt 0$



> 为什么 AABB 和 Bounding Volume 都是 平行于轴 / 平行于面 构成的 box
>
> 方便计算



















































