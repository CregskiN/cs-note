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





## 3. 齐次坐标 Homogeneous coordinates



## 4. 合成变换 Composing transforms 



## 5. 三维变换 3D transformations

