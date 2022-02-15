[TOC]

# 1. 高级光线传播 Advanced Light Transport

unbiased 和 biased 无偏的和有偏的估计



## 1.1 Bidirectional Path Tracing (BDPT) 双向路径追踪

从前的 Path Tracing：从摄像机打出，一条从摄像机到光源的路径

Bidirectional Path Tracing：





## 1.2 Metropolis Light Transport (MLT)

一些介绍

+ 一种 Markov Chain Monte Carlo (MCMC) 马尔可夫链的应用

  输入当前采样点，生成在 PDF 分布下的下一个采样点

+ 给出一条路径，MLT 可以生成类似的路径

  <img src="https://www.qiniu.cregskin.com/202202151636053.png" alt="image-20220215163629024" style="zoom:50%;" />

+ 也是无偏的

+ 在间接光数量非常多的情况下，很有效

  <img src="https://www.qiniu.cregskin.com/202202151636917.png" alt="image-20220215163658887" style="zoom:50%;" />

  > 右图 焦散效果路径：人眼 - specuar - diffuse - specular - 光源

不足

+ 很难估计收敛速度（渲染效果）
+ 不能保证每个 pixel 收敛速度相等（有的渲染很好，有的变成脏点）

<img src="https://www.qiniu.cregskin.com/202202151651852.png" alt="image-20220215165114824" style="zoom: 80%;" />



## 1.3 Photon Mapping 光子映射

+ 是一个 Biased 估计

+ 适合渲染 caustics（焦散）（实际上只有聚焦）

  <img src="https://www.qiniu.cregskin.com/202202151657470.png" alt="image-20220215165731434" style="zoom:67%;" />

+ 其中一种实现方法：

  1. 从光源打出 light-sub-path，经过折射/反射，停留到 diffuse 表面

  2. 从观测位置打出 camera-sub-path，经过折射/反射，同样停留到 diffuse 表面

  3. 计算： 对 diffuse 局部表面的光子做密度估计density estimation

  通过找 Shading point 附近 N 个光子，及这些光子所处区域的面积，计算

+ 为什么有偏？

  估计局部光子密度的时候，使用的 <img src="https://www.qiniu.cregskin.com/202202151731066.png" alt="image-20220215173149031" style="zoom: 33%;" /> $\ne$ <img src="https://www.qiniu.cregskin.com/202202151732633.png" alt="image-20220215173203603" style="zoom: 33%;" /> 

<img src="https://www.qiniu.cregskin.com/202202151734964.png" alt="image-20220215173419924" style="zoom:33%;" />

> + 什么是 biased unbaised？
>
>   简单理解就是，无偏没有模糊点
>
> + 什么是 consistent？
>
>   随着采样规模的增加，不会出现模糊点
>
> + 为什么不能取固定区域的密度估计 density estimation？
>
>   固定 dA 就不是一种 consistent 的方法了



### Vertex Connection Merging (VCM)

+ 解决的问题：

<img src="https://www.qiniu.cregskin.com/202202151722178.png" alt="image-20220215172248153" style="zoom:67%;" />



## 1.4 Instant Radiosity (IR) 实时辐射度

+ 又被称为 many-light approaches

+ 关键思想：

  1. 从光源处发射若干条 light sub-path 停留到物体表面，停留的点称为 Virtual Point Light (VPL)

  2. 再将 VPLs 当作新的光源，重复 1

+ 在漫反射居多的场景中，有不错的表现

+ 不足：
  1. 有的地方会产生亮点（因为改良后的蒙特卡洛，用对光源积分代替对点积分中，除以两个点的距离的平方。当两个点很接近，这步除法的商会变的非常大）
  2. 不能处理 glossy 材质

<img src="https://www.qiniu.cregskin.com/202202151720054.png" alt="image-20220215172017028"  />





















