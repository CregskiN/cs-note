# Transformation 变换

[TOC]



## 1. 为什么学习变换

## 2. 二维变换 2D transformations

### 2.1 用矩阵表示变换

### 2.2 缩放 scale

#### x、y轴 缩放0.5倍

<img src="https://www.qiniu.cregskin.com/image-20201120225507510.png" alt="image-20201120225507510" style="zoom:67%;" />



<img src="https://www.qiniu.cregskin.com/image-20201120225544807.png" alt="image-20201120225544807" style="zoom:50%;" />

#### x轴缩放0.5倍，y轴缩放1.0倍

![image-20201120225733955](https://www.qiniu.cregskin.com/image-20201120225733955.png)

![image-20201120225738910](https://www.qiniu.cregskin.com/image-20201120225738910.png)

#### 沿y轴镜像翻转

![image-20201120225909526](https://www.qiniu.cregskin.com/image-20201120225909526.png)

<img src="https://www.qiniu.cregskin.com/image-20201120225917143.png" alt="image-20201120225917143" style="zoom:50%;" />



### 2.3 剪切 shear

#### 剪切

<img src="https://www.qiniu.cregskin.com/image-20201120225932096.png" alt="image-20201120225932096" style="zoom:50%;" />



$x' = x + ay$

$y' = y$

<img src="https://www.qiniu.cregskin.com/image-20201120230604885.png" alt="image-20201120230604885" style="zoom:50%;" />

理解为基向量的变换



### 2.4 旋转 rotation

#### 绕原点旋转，默认逆时针旋转45度

<img src="https://www.qiniu.cregskin.com/image-20201120231004220.png" alt="image-20201120231004220" style="zoom:50%;" />

![image-20201120231330879](https://www.qiniu.cregskin.com/image-20201120231330879.png)

![image-20201120231337569](https://www.qiniu.cregskin.com/image-20201120231330879.png)

取两个点(0, 1)(1, 0)以及变化后的$(cos{\theta},sin{\theta})(-sin{\theta},cos{\theta})$列出等式

$$ \begin{pmatrix} cos{\theta} \\ sin{\theta} \end{pmatrix} = \begin{bmatrix} A & B \\ C & D \end{bmatrix} \begin{pmatrix} 1 \\ 0 \end{pmatrix}$$

得 $A = cos(\theta), C = sin{\theta}$



$$\begin{pmatrix} -sin{\theta} \\ cos{\theta} \end{pmatrix} = \begin{bmatrix} A & B \\ C & D \end{bmatrix} \begin{pmatrix} 0 \\ 1 \end{pmatrix}$$

得 $B = -sin(\theta), D = cos(\theta)$



<img src="https://www.qiniu.cregskin.com/image-20201121161356753.png" alt="image-20201121161356753" style="zoom:50%;" />

**Linear Transform = Matrix**



## 3. 齐次坐标 Homogeneous coordinates

### 3.1 遇到问题

**平移变换**

<img src="https://www.qiniu.cregskin.com/image-20201121163321960.png" alt="image-20201121163321960" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/image-20201121163337891.png" alt="image-20201121163337891" style="zoom:50%;" />

问题：不能再写成 $$\vec{v'} = \begin{bmatrix} A & B \\ C & D \end{bmatrix} \begin{pmatrix} x \\ y \end{pmatrix}$$

只能写成：

<img src="https://www.qiniu.cregskin.com/image-20201121163619190.png" alt="image-20201121163619190" style="zoom:50%;" />

所以，**平移变换不是线性变换**



### 3.2 引入齐次坐标

> 如何把所有变换包括：缩放、剪切、旋转、平移用一种方法表示？

> 答：**引入齐次坐标**

> trade off：空间和时间复杂度、引入齐次坐标前后，便利伴随着牺牲，此消彼长



给点、向量添加一个坐标$w$

<img src="https://www.qiniu.cregskin.com/image-20201121163931313.png" alt="image-20201121163931313" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/image-20201121163914532.png" alt="image-20201121163914532" style="zoom:50%;" />





### 3.3 引入齐次坐标后，点和向量的意义

引入齐次坐标后，点与点、向量与向量、点与向量有何意义？

<img src="https://www.qiniu.cregskin.com/image-20201121164705666.png" alt="image-20201121164705666" style="zoom:50%;" />

**点与点相加？**

<img src="https://www.qiniu.cregskin.com/image-20201121164743405.png" alt="image-20201121164743405" style="zoom:50%;" />

**表示两个点的中点**



### 3.3 仿射变换 Affine Map 

包含线性变换和平移变换

<img src="https://www.qiniu.cregskin.com/image-20201121165320459.png" alt="image-20201121165320459" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/image-20201121165314096.png" alt="image-20201121165314096" style="zoom:50%;" />



使用齐次坐标表示

<img src="https://www.qiniu.cregskin.com/image-20201121165400097.png" alt="image-20201121165400097" style="zoom:50%;" />



### 3.4 验证引入齐次坐标是否合理

<img src="https://www.qiniu.cregskin.com/image-20201121165507979.png" alt="image-20201121165507979" style="zoom: 50%;" />

<img src="https://www.qiniu.cregskin.com/image-20201121165513707.png" alt="image-20201121165513707" style="zoom:46%;" />

<img src="https://www.qiniu.cregskin.com/image-20201121165528121.png" alt="image-20201121165528121" style="zoom:50%;" />

### 3.5 其他变换

#### 逆变换 Inverse Transform

<img src="https://www.qiniu.cregskin.com/image-20201121165826631.png" alt="image-20201121165826631" style="zoom: 50%;" />





## 4. 合成变换 Composing transforms 

<img src="https://www.qiniu.cregskin.com/image-20201121165849599.png" alt="image-20201121165849599" style="zoom:50%;" />

如何实现？

**先平移，后旋转？**

<img src="https://www.qiniu.cregskin.com/image-20201121165905378.png" alt="image-20201121165905378" style="zoom:50%;" />

1. 平移：x轴正向1，y轴0
2. 旋转：以原点为中心，逆时针旋转45度

**失败了**



**先旋转，后平移？**

<img src="https://www.qiniu.cregskin.com/image-20201121170131505.png" alt="image-20201121170131505" style="zoom:50%;" />

1. 旋转：以原点为中心，逆时针旋转45度
2. 平移：x轴正向1，y轴0

**成功**



> 矩阵乘法不满足交换律，对应到几何意义——变换顺序不能交换

<img src="https://www.qiniu.cregskin.com/image-20201121170252659.png" alt="image-20201121170252659" style="zoom:50%;" />



### 4.1 以任意点为中心旋转

1. 把旋转点移到原点
2. 旋转
3. 再把旋转点移回

<img src="https://www.qiniu.cregskin.com/image-20201121171546858.png" alt="image-20201121171546858" style="zoom:50%;" />



<img src="https://www.qiniu.cregskin.com/image-20201121171608982.png" alt="image-20201121171608982" style="zoom:50%;" />



## 5. 三维变换 3D transformations

参考二维变换的表示，仿射变换加入齐次坐标$w$表示

<img src="https://www.qiniu.cregskin.com/image-20201121171715545.png" alt="image-20201121171715545" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/image-20201121164705666.png" alt="image-20201121164705666" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/image-20201121171917415.png" alt="image-20201121171917415" style="zoom:50%;" />



> 已知**齐次坐标表示**的**合成矩阵**M，在变换中，是先线性变换再平移，还是先平移再线性变换？

<img src="https://www.qiniu.cregskin.com/image-20201121165320459.png" alt="image-20201121165320459" style="zoom:50%;" />

> 先线性变换，再平移



![image-20201121172322208](https://www.qiniu.cregskin.com/image-20201121172322208.png)





