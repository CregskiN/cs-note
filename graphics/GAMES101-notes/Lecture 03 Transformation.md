

[TOC]

## 0. 前堂回顾

+ 向量
  + 加减、数乘
+ 点乘
  + 向量前后
+ 叉乘
  + 向量左右
+ 矩阵



## 1. 变换矩阵 Transform

### 1.1 缩放矩阵 Scale Martix

<img src="https://www.qiniu.cregskin.com/20211230211747.png" alt="image-20211230211747578" style="zoom:50%;" />



### 1.2 对称矩阵 Reflection Matrix

<img src="https://www.qiniu.cregskin.com/20211230212126.png" alt="image-20211230212126879" style="zoom:50%;" />



### 1.3 切变矩阵 Shear Matrix

<img src="https://www.qiniu.cregskin.com/20211230213413.png" alt="image-20211230213413118" style="zoom:50%;" />



### 1.4 旋转矩阵 Rotate

+ 以 (0, 0) 为旋转中心

  <img src="https://www.qiniu.cregskin.com/20211230213525.png" alt="image-20211230213525727" style="zoom:50%;" />



$\begin{bmatrix} 1 \\ 0 \end{bmatrix}$, $\begin{bmatrix} 0 \\ 1 \end{bmatrix}$, $\begin{bmatrix} cos\theta \\ sin\theta \end{bmatrix}$, $\begin{bmatrix} -sin\theta \\ cos\theta \end{bmatrix}$









<img src="https://www.qiniu.cregskin.com/20220104131824.JPG" alt="IMG_0154(20220104-131754)" style="zoom:50%;" />

### 1.5 线性变换 Linear Transforms = Martix

如上形式，统一归类为线性变换

<img src="https://www.qiniu.cregskin.com/20211230214247.png" alt="image-20211230214247491" style="zoom:50%;" />



### 1.6 平移变换（非线性变换的一种）

<img src="https://www.qiniu.cregskin.com/20211230214521.png" alt="image-20211230214521076" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/20211230214812.png" alt="image-20211230214812176" style="zoom:50%;" />

> Q：这并不满足线性变换的定义，如何统一表示线性变换、非线性变换？
>
> A：齐次坐标



## 2. 齐次坐标

+ 重新定义 2D point、2D vector

  <img src="https://www.qiniu.cregskin.com/20211230215227.png" alt="image-20211230215227139" style="zoom:50%;" />

  > 把点、向量区别对待，为保证平移不变性、满足如下运算规律
  >
  > <img src="https://www.qiniu.cregskin.com/20211230215426.png" alt="image-20211230215426383" style="zoom:50%;" />
  >
  > 点 + 点 = 两点中点（点经齐次化 w = 1）
  >
  > <img src="https://www.qiniu.cregskin.com/20211230215659.png" alt="image-20211230215659187" style="zoom:50%;" />

  

+ 最终可以表示线性变换、非线性变换

  <img src="https://www.qiniu.cregskin.com/20211230215928.png" alt="image-20211230215927970" style="zoom:50%;" />

+ <img src="https://www.qiniu.cregskin.com/20211230215954.png" alt="image-20211230215954821" style="zoom:50%;" />





## 3. 其他的变换

### 3.1 逆变换

### 3.2 混合变换 Composite Transform

+ 向量左乘顺序对应变换顺序 / 不满足交换律

<img src="https://www.qiniu.cregskin.com/20220104102000.png" alt="image-20220104102000416" style="zoom:50%;" />

+ 复杂变换可转换为：平移到原点➡️旋转➡️平移回原位置





## 4. 三维变换 3D Transforms

### 4.1 齐次坐标

<img src="https://www.qiniu.cregskin.com/20220104125041.png" alt="image-20220104125041864" style="zoom:50%;" />

+ 4 x 4 矩阵描绘仿射变换 affine transformation

  <img src="https://www.qiniu.cregskin.com/20220104125252.png" alt="image-20220104125252161" style="zoom:50%;" />



## Reference

[1. GAMES101-现代计算机图形学入门-闫令琪-P3Lecture 03 Transformation](https://www.bilibili.com/video/BV1X7411F744?p=3)

[2. P504 - 矩阵乘法与线性变换复合](https://www.bilibili.com/video/BV1ys411472E?p=5)











