[TOC]

# 0. 前情提要



# 1. Ray Tracing	

+ 为什么需要光线追踪？

  + 光栅化**不能很好地处理**全局效果

    + 软阴影、多次反射再到眼睛里的光线

    <img src="https://www.qiniu.cregskin.com/202201240950513.png" alt="image-20220124095049460" style="zoom:50%;" />

  + 光栅化很快，但只能获得一个近似效果（像塑料）

    <img src="https://www.qiniu.cregskin.com/202201240952534.png" alt="image-20220124095246504" style="zoom:50%;" />

  + 相比之下，光线追踪更精确，但会很慢

    + 光栅化：real-time，光线追踪：通常用于做 **offline**
    + 一帧 10k 个 CLOCK



## 1.1 基础的光线追踪算法

光线：

+ 沿直线传播
+ 光线交叉，不会发生碰撞
+ 光线一定是从光源发出，经过若干次反射，进入眼睛

> 反过来也可以理解成：眼睛发射出“感知光线”，到达光源，感知光线经过的路径，是一条光路\





### 1.1.1 Recursive (Whitted-Style) Ray Tracing

<img src="https://www.qiniu.cregskin.com/202201241016479.png" alt="image-20220124101654448" style="zoom:50%;" />

+ primary ray：沿观测点-像素方向的射线
+ seconday rays：primary ray 经反射、折射后的光线
+ shadow rays：从 primary ray、second rays 的反射点/折射点出发，到光源的射线

具体逻辑如下：

1. 沿 eye_point-pixel 发射 primary_ray，到达折射/反射点，经折射/反射，到达其他的折射/反射点
2. 分别从所有折射/反射点，往光源发射 shadow_rays ，若能到达光源，则该点视为 `可视点`
3. 将每条光路中所有 `可视点` 分别做 Shading，按权重加到最终该 pixel 的渲染结果

<img src="https://www.qiniu.cregskin.com/202201251114199.png" alt="image-20220125111401156" style="zoom:50%;" />



> 还需要解决的细节：
>
> 1. 如何判定光线被遮挡住？
> 2. 如何获得光线投射出去，与物体接触的位置？
> 3. 如何求反射光方向，折射光方向？
> 4. 光强衰减？





### 1.1.2 光线-表面交点

**对光线的定义**：

<img src="https://www.qiniu.cregskin.com/202201251142460.png" alt="image-20220125114253432" style="zoom:50%;" />

+ o：光源坐标
+ d：方向向量（单位化）



**光线与球求交**

<img src="https://www.qiniu.cregskin.com/202201251146574.png" alt="image-20220125114606545" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202201251146160.png" alt="image-20220125114621129" style="zoom:50%;" />

#### 光线-隐式表面求交：

<img src="https://www.qiniu.cregskin.com/202201261600383.png" alt="image-20220126160055340" style="zoom:50%;" />

#### 光线-三角形面求交（显示表面的代表）：

+ 渲染时需要考虑：

  + 可见性、阴影、光线

+ 判断点在几何内外

  + 在一个封闭图形/体内，往外发射一条射线，与该图形/体的交点个数一定是奇数
  + 在物体外，往封闭图形/体内发射射线，交点一定是偶数

  > 不考虑射线与三角形平行的情况

+ 如何计算，细分一下：

  + 最简单的思路：光线与每个三角形进行一次求交操作
  + 注意：只考虑 0/1 个交点，对应 交/不交



**光线-三角形求交**

问题分解成：

1. 光线与平面求交

2. 判定交点是否在三角形内

> 如何确定一个平面？法线 + 平面上一点

<img src="https://www.qiniu.cregskin.com/202201261634285.png" alt="image-20220126163433256" style="zoom:50%;" />



**Möller Trumbore Algorithm**

一次计算出**光线与三角形**交点

<img src="https://www.qiniu.cregskin.com/202201261648075.png" alt="image-20220126164823043" style="zoom:50%;" />





## 2. 加速光线-面求交

原思路：

1. 将每个三角形与光线求交

2. 找到最近的交点

存在的问题：

+ 极慢！



### 2.1 包围盒 Bounding Volumes

用一个包围盒，把需要求交的物体包起来，把步骤1分解：

1. 将每个三角形与光线求交
   1. 把物体用包围盒包裹
   2. 光线与包围盒求交，若光线与包围盒有交点，则与物体的每个三角形求交

2. 找到最近的交点



几种形状的包围盒：

<img src="https://www.qiniu.cregskin.com/202201261657601.png" alt="image-20220126165751567" style="zoom:50%;" />

**轴对齐包围盒 Axis-Aligned Bounding Box (AABB) **

<img src="https://www.qiniu.cregskin.com/202201261658879.png" alt="image-20220126165855845" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/202201261659692.png" alt="image-20220126165907660" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/202201261659073.png" alt="image-20220126165917014" style="zoom:25%;" />

+ 该包围盒视为：前后，上下，左右六个面围成的长方体
+ 这三组 六个面，分别与三个轴面平行



**在 2D 平面上，光线与一个轴对齐包围盒求交**

<img src="https://www.qiniu.cregskin.com/202201261704395.png" alt="image-20220126170448364" style="zoom:50%;" />

+ 什么情况下，可以认为光线进入了轴对齐包围盒？
  + 光线进入所有的对面，才算进入了包围盒
  + 光线退出任意一对对面，算退出了包围盒

+ 计算光线与对面交点的<img src="https://www.qiniu.cregskin.com/202201261711662.png" alt="image-20220126171122627" style="zoom: 50%;" />，负值也可以接受
+ <img src="https://www.qiniu.cregskin.com/202201261710203.png" alt="image-20220126171038152" style="zoom:50%;" />

+ 如果最终<img src="https://www.qiniu.cregskin.com/202201261712161.png" alt="image-20220126171204126" style="zoom:50%;" />，可以认为光线穿过了盒子

> 对于负值 t 如何考虑？
>
> 在满足 <img src="https://www.qiniu.cregskin.com/202201261715864.png" alt="image-20220126171204126" style="zoom:50%;" /> 的情况下（确定光线穿过盒子）
>
> + <img src="https://www.qiniu.cregskin.com/202201261716611.png" alt="image-20220126171617582" style="zoom:50%;" /> ：盒子位于光源的后面，没有交点
> + <img src="https://www.qiniu.cregskin.com/202201261717226.png" alt="image-20220126171711194" style="zoom:50%;" /> ：光源位于盒子内部，有交点
>
> 总的来说，光线与轴对齐包围盒相交的充要条件：<img src="https://www.qiniu.cregskin.com/202201261718259.png" alt="image-20220126171822228" style="zoom:50%;" />





**如何计算 t**

<img src="https://www.qiniu.cregskin.com/202201261736628.png" alt="image-20220126173627587" style="zoom:50%;" />

























