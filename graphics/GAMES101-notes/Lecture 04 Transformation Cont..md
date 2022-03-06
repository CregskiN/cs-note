[TOC]



## 0. 前情提要

+ 变换
  + 为什么学习、几种2D变换、齐次坐标、复合变换、3D变换

+ 本节
  + 3D 变换
  + 观测变换 **Viewing Transformation**
    + 视图变换 View Transformation / Camera
    + 投影变换 Projection Transformation
      + 正交投影 Orthographic Porjection
      + 透视投影 Perspective Projection



## 1. 3D Transformtions

### 1.1 3D 齐次坐标与仿射变换

<img src="https://www.qiniu.cregskin.com/202201051050759.png" alt="image-20220105105026710" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202201051051302.png" alt="image-20220105105115278" style="zoom:50%;" />

> 先应用的线性变换，还是先应用平移变换？
>
> 答：先线性，后平移



### 1.2 几种 3D 变换

<img src="https://www.qiniu.cregskin.com/202201051052064.png" alt="image-20220105105242041" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202201051052159.png" alt="image-20220105105259133" style="zoom:50%;" />



 ### 1.3 3D 旋转

#### 欧拉角

用简单的 x、y、z 轴旋转组合成综合的旋转

<img src="https://www.qiniu.cregskin.com/202201051057626.png" alt="image-20220105105702600" style="zoom:50%;" />

+ Pitch 抬头低头
+ Yaw 左转右转
+ Roll 歪头旋转



#### 罗德里格斯旋转公式 Rodrigues' Rotation Formula

沿着 n轴 旋转 \alpha 度

<img src="https://www.qiniu.cregskin.com/202201051059625.png" alt="image-20220105105937600" style="zoom:50%;" />

> 注意，这里用的不是齐次坐标，而 model 变换矩阵，需要用齐次坐标



可以分解为：

+ 将 n轴 平移到坐标轴
+ 沿坐标轴旋转
+ 平移回原位置

> 四元数
>
> 两个旋转一定角度的矩阵做差，结果并不等同角度直接做差得到的矩阵





## 2. Viewing Transf ormation

3D物体 ➡️ 2D图片

+ Model变换 Find a good place and arrange people 
+ View变换 Find a good "angle" to put the camera
+ Projection 变换 Cheese!

### 2.1 View Transformation

如何定义一个相机？

+ 定义相机位置 $\vec{e}$
+ 定义相机朝向 $\vec{g}$
+ 定义上方向 $\vec{t}$

<img src="https://www.qiniu.cregskin.com/202201051118312.png" alt="image-20220105111831269" style="zoom:50%;" />

> 只要相机、物体相对位置不变，观测内容也不变
>

约定俗成，把相机固定在原点，以 Y轴 为上方向 $\vec{t}$，以 -Z轴 为朝向 $\vec{g}$，仅仅对物体移动

数学上，用 $M_{view}$ 完成：

1. $T_{view}$ 把 $\vec{e}$ 移动到 (0, 0)
2. $R_{view}$ 把 $\vec{g}$ 旋转到 -Z、把 $\vec{t}$ 旋转到 Y、把 $\vec{g} \cp \vec{t}$ 旋转到 X

<img src="https://www.qiniu.cregskin.com/202201051133039.png" alt="image-20220105113346013" style="zoom:50%;" />

> 旋转矩阵属于正交矩阵

> 因先平移，后旋转，不能直接用齐次坐标下的复合公式







### 2.2 Projection Transformation



#### 正交投影 Orthographic Projection

一种简单的理解：

+ 相机固定在原点，朝向 -Z，上方向 Y
+ 移除 Z 坐标（直接拍扁）
+ 把坐标缩放到 $[-1, 1]^2$

<img src="https://www.qiniu.cregskin.com/202201051555639.png" alt="image-20220105155532609" style="zoom:50%;" />

推广理解：

把一个 $[l, r] \cp [b, t] \cp [f, n]$ 的长方体，映射到 $[-1, 1]^3$ 的立方体（正则立方体 Canonical cube）

> 注意朝向是 -Z 方向

<img src="https://www.qiniu.cregskin.com/202201051604192.png" alt="image-20220105160425140" style="zoom: 33%;" />

最终得出正交投影的变换矩阵 $M_{ortho}$ 

> 先平移，再缩放。缩放之后，图像会有拉伸的现象，在**视口变换**中会解决

<img src="https://www.qiniu.cregskin.com/202201051607859.png" alt="image-20220105160729830" style="zoom: 33%;" />





#### 投影矩阵 Perspective Projection

*投影现象*：近大远小

在开始之前，回顾 3D 齐次坐标中点的定义：

<img src="https://www.qiniu.cregskin.com/202201051615810.png" alt="image-20220105161508782" style="zoom: 33%;" />

透视投影基本思路：

1. 把 Frustum 压扁成一个立方体（Z 轴不变） $M_{persp \rarr ortho}$
2. 对立方体做正交投影 $M_{ortho}$

<img src="https://www.qiniu.cregskin.com/202201051617818.png" alt="image-20220105161719791" style="zoom: 33%;" />

> **near面 任意点 x y z 不变**
>
> **far面 任意点 x y z 的 z 不变，中心点 x y z 不变**

<img src="https://www.qiniu.cregskin.com/202201051627631.png" alt="image-20220105162750600" style="zoom:33%;" />

变换前后 x、y 关系如下：

<img src="https://www.qiniu.cregskin.com/202201051629531.png" alt="image-20220105162946502" style="zoom: 67%;" />



即，Frustum 内任意一点的变化如下：

<img src="https://www.qiniu.cregskin.com/202201051630109.png" alt="image-20220105163016082" style="zoom:67%;" />

用变换矩阵表示：

<img src="https://www.qiniu.cregskin.com/202201051631522.png" alt="image-20220105163130492" style="zoom:50%;" />

$M_{perspective \rarr ortho}$ 可以确定一部分：

<img src="https://www.qiniu.cregskin.com/202201051631609.png" alt="image-20220105163140584" style="zoom:50%;" />

对于 near面 的任意点：

<img src="https://www.qiniu.cregskin.com/202201051634207.png" alt="image-20220105163430176" style="zoom:50%;" />

确定（1）式：

<img src="https://www.qiniu.cregskin.com/202201051645743.png" alt="image-20220105164558713" style="zoom:50%;" />

对于 far面 的中心点，其 x y z 坐标均不变，得到（2）式

<img src="https://www.qiniu.cregskin.com/202201051645488.png" alt="image-20220105164548459" style="zoom:50%;" />

（1）、（2）式联立：

<img src="https://www.qiniu.cregskin.com/202201051648123.png" alt="image-20220105164818095" style="zoom:50%;" />



>问：n、f中间的面，压缩成立方体后，z 坐标是近了还是远了？
>
>答：远了
>
><img src="https://www.qiniu.cregskin.com/202201062239356.jpeg" alt="IMG_1138CE9705CE-1" style="zoom:50%;" />













