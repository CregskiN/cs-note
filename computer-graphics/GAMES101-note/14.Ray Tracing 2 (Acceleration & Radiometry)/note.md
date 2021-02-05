# Ray Tracing 2 (Acceleration & Radiometry)

[TOC]



+ GTC 新闻：DLSS 2.0
  + 把 720p 的图片拉伸到 4k 不失真
+ GTC 新闻：RTXGI
+ 个人感受
  + 离线渲染技术很快就会变成实时的
  + 当前的实时渲染技术仍然是有用的









# Last Lecture

+ 为什么使用光线追踪 Ray Tracing ？

+ Witted-style Ray Tracing

  计算光线（包括反射后、折射后的光线）与物体的交点，作为 shading point 着色之后，将着色结果顺着光路累加到像素点

+ 光线-物体 求交 Ray-Object intersections

  + 隐式表面 Implicit surfaces
  + 三角形（显式表面）Triangles 

+ 轴线包围盒 Axis-Aligned Bouding Boxes (AABBs)

  + Bounding Volumes 三对平行于 xoy xoz yoz 的面
  + 将 光线-物体求交 改为 光线-AABB求交



本节内容：

+ 如何使用 AABB 加速光线追踪？
  + 均匀网格 Uniform Grids
  + 空间划分 Spatial Partitions
+ 辐射度量学 Basic Radiometry



# 1. 均匀空间分区（网格） Uniform Spatial Partitions ( Grids )

## 1.1 处理过程

1. 找到包围盒 Bounding Box

   <img src="https://www.qiniu.cregskin.com/image-20210112203809736.png" alt="image-20210112203809736" style="zoom: 25%;" />

2. 预处理：添加网格

   <img src="https://www.qiniu.cregskin.com/image-20210112203859113.png" alt="image-20210112203859113" style="zoom:25%;" />

3. 标记包含物体表面的格子

   <img src="https://www.qiniu.cregskin.com/image-20210112204022736.png" alt="image-20210112204022736" style="zoom:25%;" />

4.  求交

   + 光线与划分的网格A 求交
     + 如果与光线相交的网格中没有物体，结束该网格的处理
     + 如果与光线相交的网格中有物体
       + 光线与物体求交
   + 光线与划分的网格B 求交
     + ..
       + ..

   > 如何找到应该与光线求交的“网格”？
   >
   > 答：画直线算法。bresenham算法

   <img src="https://www.qiniu.cregskin.com/image-20210112204106576.png" alt="image-20210112204106576" style="zoom:25%;" />

## 1.2 影响加速效果的因素

### 将空间划分成网格的数量

<img src="https://www.qiniu.cregskin.com/image-20210112204832770.png" alt="image-20210112204832770" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20210112204849226.png" alt="image-20210112204849226" style="zoom:25%;" />

格子太稀疏太密集都不好，光线与“不包含物体的格子”求交也有算力消耗

最合适的格子数量 = $C$ \* $objs$ 即 一个常数 乘 物体的数量

3D 情况下常用的 C 为 27

<img src="https://www.qiniu.cregskin.com/image-20210112205002493.png" alt="image-20210112205002493" style="zoom:25%;" />

### 应用场景

光线与无关的网格求交，还是有一定的计算消耗。是否采用均分网格 Uniform Spatial Partitions ( Grids ) 的策略，由场景决定，如：

+ 空间中的物体分布均匀 - 较少的“不包含物体的网格” - 较少的算力消耗

  <img src="https://www.qiniu.cregskin.com/image-20210112205353844.png" alt="image-20210112205353844" style="zoom:25%;" />

+ 空间中物体分布不均匀 - 存在较大的空旷区域 - 意味着“不包含物体的网格”会非常多，求交消耗算力

  <img src="https://www.qiniu.cregskin.com/image-20210112205424510.png" alt="image-20210112205424510" style="zoom:25%;" />







# 2. 空间划分 Spatial Partitions

网格均分 Uniform Spatial Partitions ( Grid ) 策略的缺点：

+ 当遇到空旷区域非常多，有不必要的计算消耗（光线与“不包含物体的网格”求交）



空间划分 Spatial Partitions 的思想是：

+ 空旷区域划分成一个大网格
+ 存在物体的区域划分成数量多的小网格



## 2.1 空间划分的例子 examples

### 八叉树 Oct-Tree 

<img src="https://www.qiniu.cregskin.com/image-20210112210835002.png" alt="image-20210112210835002" style="zoom:33%;" />

1. 将空间均匀划分成 8 份
2. 筛选出 8 份子空间中存在物体的子空间，对其再次划分 8 份
3. 直到 8 份空间中，不存在物体的子空间比例，达到预设比例为止（如预设存在物体的子空间占到 1/4 ）



### KD-Tree

<img src="https://www.qiniu.cregskin.com/image-20210112211714313.png" alt="image-20210112211714313" style="zoom: 33%;" />

1. 沿着某条轴将空间划分成两份（上图所示，先按x轴划分一次）
2. 对上一步得出的子空间，分别沿另一条轴（上图所示y轴）再划分一次，得到分别得到两个子空间
3. 对上一步得出的子空间，分别沿另一条轴（上图所示x轴）再划分一次，得到分别得到两个子空间
4. ...交替用平行于坐标轴的直线划分



推广到3D空间，就是沿xoy面划分、沿xoz面划分、沿yoz面划分。。。。。



### BSP-Tree

<img src="https://www.qiniu.cregskin.com/image-20210112212048680.png" alt="image-20210112212048680" style="zoom:33%;" />



## 2.2 KD-Tree

时刻：在开始做光线求交之前

### KD-Tree 的数据结构

<img src="https://www.qiniu.cregskin.com/image-20210112212753118.png" alt="image-20210112212753118" style="zoom:33%;" />

+ 每个非叶子节点记录：
  + 划分轴：当前沿哪个轴划分？
  + 划分位置：划分轴沿上一层划分轴的哪个位置开始划分？
  + 子节点：两个指向字节点的指针
  + 内部节点不存储物体 No object atr stored in internal nodes
+ 每个叶子结点存储
  + 物体列表 list of object



### KD-Tree 的使用

<img src="https://www.qiniu.cregskin.com/image-20210112213911701.png" alt="image-20210112213911701" style="zoom: 33%;" />

KD-Tree 使用过程

1. 光线与大包围盒A求交，相交。*遍历其子节点*

   1. 光线与包围盒1**（叶子结点）**求交，相交

      + 光线与包围盒1内所有物体求交

   2. 光线与包围盒B求交，相交。*遍历其子节点*

      1. 光线与包围盒2**（叶子结点）**求交，相交

         + 光线与包围盒2内所有物体求交

      2. 光线与包围盒C求交，相交。*遍历其子节点*

         1. 光线与包围盒3**（叶子结点）**求交，相交
            + 光线与包围盒3内所有物体求交
         2. 光线与包围盒D求交，相交。*遍历其子节点*
            1. 光线与包围盒4**（叶子结点）**求交，相交
               + 光线与包围盒4内所有物体求交
            2. 光线与包围盒5**（叶子结点）**求交，不相交

         

### KD-Tree 的问题

+ 很难判断物体是否与包围盒有交集（我暂时不知道判断这个有啥用）
+ 一个物体可能存储到多个叶子结点中

近十年，开始抛弃这种方法





# 3. 物体划分 Object Partitions & Bounding Volume Hierarchy ( BVH )

从空间的角度进行划分有各种问题，如 KD-Tree 中列出的

+ 很难判断物体是否与包围盒有交集（我暂时不知道判断这个有啥用）
+ 一个物体可能存储到多个叶子结点中



## 2.1 BVH 处理过程

<img src="https://www.qiniu.cregskin.com/image-20210112220521623.png" alt="image-20210112220521623" style="zoom:33%;" />

+ 找到位置相近、一定数量的物体，用包围盒A包裹。空间划分为A内和**A外**
  + 针对A外，找到位置相近、一定数量的物体，用包围盒B包裹。A外空间划分为**B外**和B内
    + 针对B外，找到位置相近、一定数量的物体，用包围盒C包裹。B外空间划分为**C外**和C内
      + C外剩余物体不满“一定数量”，直接划分包围盒D



+ 如何划分节点？
  + 寻找一个维度划分，如参考KD-Tree，交替沿x轴y轴划分
  + idea 1：只沿着最长的轴划分，最后得到宽高差不多的包围盒
  + idea 2：尽量把物体分为两半，保证这两半物体数量差不多（减少树的深度）



BVH 的数据结构

+ 中间节点
  + 包围盒
  + 叶子结点指针
+ 叶子结点
  + 包围盒
  + 物体列表



## 2.2 BVH 的遍历 BVH Traversal

<img src="https://www.qiniu.cregskin.com/image-20210112221909874.png" alt="image-20210112221909874" style="zoom:33%;" />

```c++
对光线ray和BVH节点求交：
  如果光线与BVH节点所在包围盒不相交
  	返回
  如果该BVH节点是叶子结点
  	光线与该节点存储的所有物体求交
  	返回交点
  光线与该BVH左节点求交
  光线与该BVH右节点求交
  
  返回交点
```



## 2.3 空间划分与物体划分 Spatial vs Object Partitions

<img src="https://www.qiniu.cregskin.com/image-20210112222443766.png" alt="image-20210112222443766" style="zoom: 33%;" /><img src="https://www.qiniu.cregskin.com/image-20210112222643639.png" alt="image-20210112222643639" style="zoom:33%;" />

+ Spatial Partition
  + 将空间划分为不重叠的区域 Partition space into non-overlapping regions
  + 一个物体可能被划分到在多个空间中 An object can be contained in multiple regions
+ Object Partition
  + 将对象划分为不相交的子集 Partition set of objects into disjoint subsets
  + 包围盒可能有重叠 Bounding boxes for each set may overlap in space



> Whitted-Style 光线追踪到目前为止



> 下面开始现代光线追踪

# 3. 辐射度量学 Basic Radiometry

动机：

+ 在 Blinn-Phone Model 中
  + 光线强度 Light intensity 被预设为 10
  + 10 有什么意义？
+ Whitted style Ray Tracing 正确吗？
+ 辐射度量学给光线一个精确的度量，以得出一个更真实的结果



## 3.1 辐射度量学的内容 Radiometry 

+ Measurment system and units for illumination 针对光照的测量系统及单位
+ Accurately measure the spatial properties of light 准确的测量光线的空间特性
  + New terms: **Radiant flux** 辐射通量, **intensity** 强度, **irradiance** 辐照度, **radiance** 光照度
+ Perform lighting calculations in **a physically correct manner** 以遵循物理规律的方式进行光照展示的计算



---

+ Why 这是什么？
  + 辐射度量学 Basic Radiometry
+ What 这是干什么用的？
  + 用于解决 Blinn-Phone 模型中光照部分不符合物理规律，导致 shading 结果“塑料感”
  + 一套符合物理规律的光照系统
+ How 具体场景下如何使用？

---





## 3.2 Radiant Energy and Flux ( Power )

+ Why 是什么？

  + Definition: 

    + **Radiant energy** is the energy of **electromagnetic radiation**. It is measured in units of joules, and denoted by the symbol:  **辐射能**是**电磁辐射**的能量。它以焦耳为单位测量，并用符号表示：（能量）

      <img src="https://www.qiniu.cregskin.com/image-20210112224700218.png" alt="image-20210112224700218" style="zoom:60%;" />

    + **Radiant flux (power)** is the energy emitted, reflected, transmitted or received, per unit time. 单位时间内，能量的发射、反射、传输、接受（类似于功率，灯泡的流明/亮度）

      <img src="https://www.qiniu.cregskin.com/image-20210112224711263.png" alt="image-20210112224711263" style="zoom:57%;" />



## 3.3 一些重要的光线测量概念 Important Light Measurements of Interest

<img src="https://www.qiniu.cregskin.com/image-20210112225140890.png" alt="image-20210112225140890" style="zoom:40%;" />

+ Light Emitted From A Source 一个点光源发散出的光线中，具有的方向属性：**Radiant Intensity** 辐射强度
+ Light Falling On A Surface 一个物体表面接受的光的能量：**Irradiance** 辐照度
+ Light Traveling Along A Ray 光在传播中度量的能量：**Radiance** 光辉



### Radiant Intensity

+ Why？是什么

  + **Radiant intensity** is the power per unit **solid angle (立体角)** emitted by a point light source. 

    Radiant Intensity 是单位**立体角**对应的能量

    <img src="https://www.qiniu.cregskin.com/image-20210112231127814.png" alt="image-20210112231127814" style="zoom:50%;" />

    <img src="https://www.qiniu.cregskin.com/image-20210112232428575.png" alt="image-20210112232428575" style="zoom:33%;" />
    $$
    
    $$
    

### Angle and Solid Angle 角和立体角

2D 上理解角 **Angle**

<img src="https://www.qiniu.cregskin.com/image-20210112231344958.png" alt="image-20210112231344958" style="zoom:35%;" />

一个角对应一个弧长

<img src="https://www.qiniu.cregskin.com/image-20210112231423579.png" alt="image-20210112231423579" style="zoom:50%;" />



3D 空间中的立体角，是2D上的一个延伸 **Solid Angle**

<img src="https://www.qiniu.cregskin.com/image-20210112231509462.png" alt="image-20210112231509462" style="zoom:33%;" />

弧长引申为球上的单位面积

<img src="https://www.qiniu.cregskin.com/image-20210112231535085.png" alt="image-20210112231535085" style="zoom:50%;" />



立体角在球面上的定义 Solid Angle 

<img src="https://www.qiniu.cregskin.com/image-20210112231937421.png" alt="image-20210112231937421" style="zoom:35%;" />



> 一个球所有单位立体角积分起来，是 4 pi
>
> <img src="https://www.qiniu.cregskin.com/image-20210112232146490.png" alt="image-20210112232146490" style="zoom:30%;" />







