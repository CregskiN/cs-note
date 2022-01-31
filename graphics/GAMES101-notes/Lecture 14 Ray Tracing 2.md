[TOC]



​                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           

# 0. 前情提要

+ DLSS：提高图片分辨率

+ RTXGI：实时光线渲染方面

+ 趋势：
  + 由于 RTX 的进步，离线渲染逐渐搬到实时渲染
  + 光栅化仍然有价值



+ 上节
  + 什么是 Ray tracing
  + Whitted-style ray tracing
  + 光线-物体求交
    + 隐式表面
    + 三角形
  + 加速结构
    + 包围盒：轴对齐包围盒
      + 三对对面，光线-AABB求交
+ 本节
  + 使用类似 AABB 的结构加速光线追踪
    + 均匀格子 Uniform grids
    + 空间划分 Spatial partitions
  + Basic radiometry



# 1. 加速光线-表面求交的加速结构



## 1.1 Uniform Spatial Partitions (Grids)

在做光线追踪之前，把空间划分成若干个小格子



<img src="https://www.qiniu.cregskin.com/202201261749212.png" alt="image-20220126174927182" style="zoom: 33%;" />

具体做光线追踪时：

<img src="https://www.qiniu.cregskin.com/202201261751773.png" alt="image-20220126175145742" style="zoom: 33%;" />

> 如何光栅化一条线？
>
> 这条光线往右上方打，下一个格子只可能在右侧或上侧

> 格子划分不能太稀疏，也不能太密集，一般认为 27 * 物体数



> Uniform Spatial Partitions 适用场景：物体分布均匀



## 1.2 空间划分 Spatial Partitions

<img src="https://www.qiniu.cregskin.com/202201261802255.png" alt="image-20220126180221218" style="zoom:40%;" />

+ Oct-Tree 八叉树：二维空间四叉树，三维空间八叉树。。。
+ KD-Tree：与八叉树几乎相同，水平一刀竖直一刀水平一刀.. 3D 下，沿着三个面划分
+ BSP-Tree：二分划分



### KD-Tree

在做光线追踪之前，

<img src="https://www.qiniu.cregskin.com/202201261815054.png" alt="image-20220126181547022" style="zoom:33%;" />

> 只在叶子节点，存储与几何形体相关的内容

+ 中间节点存储：
  + 划分的方向：沿着哪个轴
  + 划分的位置：中间？三分之二？
  + 孩子节点（两个）的指针
+ 叶子节点存储：
  + 与物体相关的数据



<img src="https://www.qiniu.cregskin.com/202201261819576.png" alt="image-20220126181955550" style="zoom: 25%;" /><img src="https://www.qiniu.cregskin.com/202201261821722.png" alt="image-20220126182141675" style="zoom:25%;" />



<img src="https://www.qiniu.cregskin.com/202201261822321.png" alt="image-20220126182220279" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/202201261822226.png" alt="image-20220126182235181" style="zoom:25%;" />

<img src="https://www.qiniu.cregskin.com/202201261831325.png" alt="image-20220126183133279" style="zoom:33%;" />

1. 预处理：进行 Spatial Partition，用 KD-Tree 记录
2. 对包围盒 A 进行递归操作
   1. 若 A 为叶子节点，则对 Ray-A内所有物体求交
   2. 若 Ray-左包围盒有交点，对左包围盒递归
   3. 若 Ray-有包围盒有交点，对右包围盒递归

> 存在的问题：
>
> 1. 若进行完美的包围盒划分，需要知道包围盒与三角形的位置关系：
>
>    + 三角形完全在盒子内，三角形一部分在盒子内，盒子内部有三角形
>
>    位置关系很难判断
>
> 2. 同一个物体，可能需要存储在多个叶子节点





## 1.3 Bounding Volume Hierarchy (BVH)

KD-Tree 按空间划分，而 BVH 按物体划分

<img src="https://www.qiniu.cregskin.com/202201261856126.png" alt="image-20220126185605095" style="zoom:46%;" />

<img src="https://www.qiniu.cregskin.com/202201261855923.png" alt="image-20220126185522879" style="zoom: 45%;" />

性质：一个物体只存储在一个叶子节点

引起的问题：BVH 对空间的划分存在交叉，即两个包围盒有交差的部分



**如何划分节点，保证物体尽量平均地分布在各个包围盒内？**

+ 选择分布最松散的一个维度，如x轴，沿维度方向给出三角形编号
+ 按三角形按一定顺序编号，从中位数序号的三角形开始划分，分成两部分三角形数量接近的包围盒（涉及寻找中位数的算法，类似快排）



**BVH 求交逻辑**：

 <img src="https://www.qiniu.cregskin.com/202201271557625.png" alt="image-20220127155722595" style="zoom:45%;" />

对跟节点递归，递归逻辑如下：

1. 若光线与当前节点的包围盒没有相交，则返回
2. 若当前节点为叶子节点，
   1. 光线与节点内所有物体求交
   2. 返回最近的交点
3. 对当前节点的左节点递归，对当前节点的右节点递归，返回递归结果





### Spatial vs Object Partitions

<img src="https://www.qiniu.cregskin.com/202201271559976.png" alt="image-20220127155935952" style="zoom: 45%;" />



# 2. 辐射度量学 Basic radiometry

一套相比 Blinn-Phong 更完整的，描述光传播方式的理论

光具有四个属性：辐射通量 Radiant flux，强度 intensity，辐照度 irradiance，光辉 radiance



## 2.1 Radiant Energy and Flux (Power)

Radiant energy：电磁波的能量，单位是焦耳，符号<img src="https://www.qiniu.cregskin.com/202201271623758.png" alt="image-20220127162354728" style="zoom:33%;" />

Radiant flux：单位时间内，释放、反射、传输或接受的能量，定义 <img src="https://www.qiniu.cregskin.com/202201271625471.png" alt="image-20220127162514451" style="zoom:33%;" />

> Radiant flux 类似于功率，单位是 瓦特 W = watt，或者流明 lm = lumen（灯泡的亮度）
>
> 另一个角度理解 flux 通量，是单位时间内发出的光线数量
>
> <img src="https://www.qiniu.cregskin.com/202201271630417.png" alt="image-20220127163009387" style="zoom:33%;" />



<img src="https://www.qiniu.cregskin.com/202201271714818.png" alt="image-20220127171425761" style="zoom:50%;" />

+ 光源往四面八方发射能量：方向性的属性 Radiant Intensity
+ 表面接受的光线的能量：光线的接收 Irradiance
+ 光线在传播中的度量：radiance



### 2.1 Radiant Intensity

Definition: The radiant (luminous) intensity is the power per unit solid angle (?) emitted by a point light source.

Radiant Intensity：单位时间内，点光源往单位角度（**立体角**）发射的能量 <img src="https://www.qiniu.cregskin.com/202201271722148.png" alt="image-20220127172200124" style="zoom: 50%;" />

> 单位是坎德拉 <img src="https://www.qiniu.cregskin.com/202201271722331.png" alt="image-20220127172229308" style="zoom: 50%;" />

**平面角与立体角**

<img src="https://www.qiniu.cregskin.com/202201271725779.png" alt="image-20220127172546757" style="zoom:50%;" />

+ 角度 = 弧长 / 半径（二维） 
+ 立体角 = 部分球壳面积 / 半径^2，整个球面立体角为 4π



**微分立体角**

<img src="https://www.qiniu.cregskin.com/202201271757332.png" alt="image-20220127175746309" style="zoom:40%;" />

<img src="https://www.qiniu.cregskin.com/202201271759600.png" alt="image-20220127175938576" style="zoom:40%;" />







<img src="https://www.qiniu.cregskin.com/202201310934437.png" alt="image-20220131093437378" style="zoom:67%;" />





<img src="https://www.qiniu.cregskin.com/202201310935708.png" alt="image-20220131093537662" style="zoom:50%;" />
