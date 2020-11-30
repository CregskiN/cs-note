# Texture Mapping Cont

[TOC]



# Last Lecture

Shading 1 & 2

+ 布林-冯反射模型 Blinn-Phone reflectance model
+ 渲染模式 / 渲染频率
  + flat shading 对平面 shading，代表整个图形的颜色
  + gourand shading 对顶点 shading，插值获取内部像素的颜色
  + phone shading 根据顶点，插值获取内部像素的法线，对像素 shading
+ 图形化管线 Graphics Pipeline
+ 纹理映射 Texture Mapping
  + UV



# 1. 重心坐标 Barycentric coordinates

如何在三角形内部，进行各种属性（UV、颜色、法线等）的插值

## 1.1 灵魂三问

1. **为什么**：为什么要在三角形内部做插值？

   指定顶点处的值
   通过三角形获得平滑变化的值

2. **是什么**：被插值的是什么内容？

   纹理UV坐标 Texture cooridinates、gourand shading 中插值颜色 colors、Phone Shading 中插值法线 normal vectors....

3. **怎么用**：如何做插值？

   + Barycentric coordinates



## 1.2 重心坐标

一个三角形，有一套重心坐标

定义：三角形内部任意一点 (x, y) 都可以用三个顶点的线性组合来表示，限制条件：线性变换的三个系数和为 1

<img src="https://www.qiniu.cregskin.com/image-20201130090758336.png" alt="image-20201130090758336" style="zoom:25%;" />



问：A点自己的重心坐标如何表示？

答：<img src="https://www.qiniu.cregskin.com/image-20201130091051396.png" alt="image-20201130091051396" style="zoom:25%;" />



定义的推导：

<img src="https://www.qiniu.cregskin.com/image-20201130091440911.png" alt="image-20201130091440911" style="zoom:25%;" />





### 用面积比求出重心坐标

<img src="https://www.qiniu.cregskin.com/20201130091240.png" alt="image-20201130091145431" style="zoom:25%;" />



三角形重心的重心坐标特性：

<img src="https://www.qiniu.cregskin.com/image-20201130091410014.png" alt="image-20201130091410014" style="zoom:25%;" />







# 2. 纹理查询 Texture queries

## 2.1 原始策略

<img src="https://www.qiniu.cregskin.com/image-20201130091606329.png" alt="image-20201130091606329" style="zoom:25%;" />

**问：重心坐标在投影下，不能保证重心坐标不变，如何处理？**

答：三维空间，使用三维的坐标做插值，再逆变换回二维，把插值结果对应到二维投影。相关：把已经投影到屏幕的三角形，逆变换回去，深度



```c++
for each rasterized screen sample(x, y) { // 屏幕上采样像素的位置（不论直接采样，还是MSAA采样）
  (u, v) = evalute texture coordinate at (x, y); // 根据顶点，插值出(x,y)对应的纹理坐标 uv
  texcolor = texture.sample(u, v); // 在纹理上查询uv坐标对应的值
  set samples's color to texcolor; // 代替Blinn-Phong反射模型的k_d
}
```



## 2.2 纹理的放大问题 Texture Maginication

像素和纹理的对应关系：<img src="https://www.qiniu.cregskin.com/image-20201130093127152.png" alt="image-20201130093127152" style="zoom:50%;" />

### 2.2.1 纹理小，屏幕分辨率大

**纹理小，屏幕分辨率大导致，通过像素取纹理，得出的uv坐标不是整数。**



#### 原始策略 Nearest

原始策略：对非整数的uv坐标取近似



假设：(x, y) 坐标映射到纹理的下图位置处：

<img src="https://www.qiniu.cregskin.com/image-20201130110359551.png" alt="image-20201130110359551" style="zoom:25%;" />

原始策略选择这个位置的纹理值为：

<img src="https://www.qiniu.cregskin.com/image-20201130110455105.png" alt="image-20201130110455105" style="zoom:25%;" />

于是结果：

<img src="https://www.qiniu.cregskin.com/image-20201130094230223.png" alt="image-20201130094230223" style="zoom:37%;" />



**矛盾点：当uv非整数，如何处理，以返回更符合预期结果的纹理？**



#### 双线性插值 Bilinear interpolation

<img src="https://www.qiniu.cregskin.com/image-20201130094230223.png" alt="image-20201130094230223" style="zoom:37%;" />

假设：(x, y) 坐标映射到纹理的下图位置处：

<img src="https://www.qiniu.cregskin.com/image-20201130110359551.png" alt="image-20201130110359551" style="zoom:25%;" />

找到临近四个点

<img src="https://www.qiniu.cregskin.com/image-20201130110554768.png" alt="image-20201130110554768" style="zoom:25%;" />

规定 t 和 s ：

<img src="https://www.qiniu.cregskin.com/image-20201130110626752.png" alt="image-20201130110626752" style="zoom:25%;" />

定义一个线性插值：

<img src="https://www.qiniu.cregskin.com/image-20201130110836544.png" alt="image-20201130110836544" style="zoom:25%;" />

水平方向上，分别对两对点做线性插值，得到两个点 u0 u1：

<img src="https://www.qiniu.cregskin.com/image-20201130113200411.png" alt="image-20201130113200411" style="zoom:25%;" />

竖直方向做一次线性插值，得到最终的点P：

<img src="https://www.qiniu.cregskin.com/image-20201130093753237.png" alt="image-20201130093753237" style="zoom:25%;" />

> 问：如何使用这三次插值的结果？
>
> <img src="https://www.qiniu.cregskin.com/image-20201130112708523.png" alt="image-20201130112708523" style="zoom: 50%;" />
> $$
> f(x, y) 的结果应当是四个点 u_{01}、u_{11}、u_{00}、u_{10}线性组合的结果，其中：\\
> 
> $$
> 
>
> 



结果：平滑过渡

缺点：质量相对三次插值很差



#### Bicubic interpolation

更高的计算量



### 2.2.2 纹理大，屏幕分辨率小

#### 原始策略

取像素对应纹理范围中，各个点的平均

左：原纹理图

![image-20201130094327355](https://www.qiniu.cregskin.com/image-20201130094327355.png)

近处锯齿，远处摩尔纹



原因：

<img src="https://www.qiniu.cregskin.com/image-20201130094551352.png" alt="image-20201130094551352" style="zoom:25%;" />

随着距离增加，屏幕一个像素，对应纹理中的范围越来越大



#### MSAA 增加采样点

解决办法：MSAA 增加采样点，解决锯齿问题。取 512 个点的平均

![image-20201130094747432](https://www.qiniu.cregskin.com/image-20201130094747432.png)

+ 问：采样原理在纹理过大的问题中，如何体现？
  + 高质量的采样结果，庞大的计算量
  + 一个像素内部，包含很大一块纹理
  + 在一个像素内频率很高
  + 需要更高频的采样方法

*？？？？？*



如何使用更少的采样点？ 

采样引起走样，如果不采样呢？如何立刻知道一个纹理区域的平均值？



#### MipMap

额外开销三分之一

点查询 point query 和 范围查询 range query

图形学中，范围查询查的是平均值

**Mipmap**：允许做范围查询。**范围查询快、查询结果是近似结果、仅仅做正方形范围查询**



#### 三线性插值 Trilinear interpolcation



#### 各向异性过滤 Anisotropic Filtering

又称 Ripmap

2x，3x，占用空间为原来的三倍。显存足够就行

<img src="https://www.qiniu.cregskin.com/image-20201130101911374.png" alt="image-20201130101911374" style="zoom:50%;" />



#### EWA filter









# 3. Applications of texture

















