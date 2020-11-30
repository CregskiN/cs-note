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
> <img src="https://www.qiniu.cregskin.com/image-20201130124729555.png" alt="image-20201130124729555" style="zoom:63%;" />
> $$
> f(x, y) 的结果是四个点 u_{01}、u_{11}、u_{00}、u_{00}、u_{10} 纹理插值的结果 \\ 
> 也就是四个点纹理线性组合的结果 \\
> f(x, y) = u_{01}S_{rb} + u_{11}S_{lb} + u_{00}S_{rt} + u_{10}S_{lt} \\
> S_{rb} 意为 S of right-bottom，其他同理 \\
> $$
> 
>
> 



结果：平滑过渡

缺点：质量相对三次插值很差



#### Bicubic interpolation

更高的计算量

双向三次插值，取周围临近十六个方格，不是线性插值



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

    信号变化过快，采样速度较慢

    解决办法：采样更多的纹理点，生成一个像素

  + 在一个像素内频率很高

  + 需要更高频的采样方法



**如何使用更少的采样点？** 

**采样引起走样，如果不采样呢？如何立刻知道一个纹理区域的平均值？**



#### MipMap

点查询 point query 和 范围查询 range query。原始策略属于点查询。

范围查询有很多种，范围内最大值、最小值、平均值。图形学中，范围查询查的是平均值。

**Mipmap特性**：允许做范围查询。**范围查询快、查询结果是近似结果、仅仅做正方形范围查询**



<img src="https://www.qiniu.cregskin.com/image-20201130160440658.png" alt="image-20201130160440658" style="zoom:40%;" />



MipMap 每一层存储了缩略一倍的纹理

<img src="https://www.qiniu.cregskin.com/image-20201130160708961.png" alt="image-20201130160708961" style="zoom:25%;" />

<img src="https://www.qiniu.cregskin.com/image-20201130161109511.png" style="zoom:25%;" />



如何知道将要 Shading 的像素，对应纹理为 MipMap 中第几层的区域？

<img src="https://www.qiniu.cregskin.com/image-20201130161533703.png" alt="image-20201130161533703" style="zoom:30%;" />

1. 找到目标像素、临近像素在纹理图中的位置

2. 求出该像素在纹理图中占据的范围边长 L

3. 计算：同一个像素对应的纹理范围边长L，在哪一层 MipMap 中被缩略为 1

   在第 $D = log_2{L}$ 层上

4. 得出该像素对应的纹理

<img src="https://www.qiniu.cregskin.com/image-20201130162358591.png" alt="image-20201130162358591" style="zoom:33%;" />



问题：MipMap 的层数是不连续的，假设第 k 层，L 为3，k+1层，L为1，对于L=2的范围， 该如何取？

<img src="https://www.qiniu.cregskin.com/image-20201130162616856.png" alt="image-20201130162616856" style="zoom:25%;" />

可能形成如上图的割裂





解决办法：**插值**

#### 三线性插值 Trilinear interpolcation

1. 在第 D 层做双线性插值，在 D+1 层做双线性插值

2. 对以上两层结果再做一个线性插值

   $lerp(x, lerp(D), lerp(D+1)$

<img src="https://www.qiniu.cregskin.com/image-20201130162730003.png" alt="image-20201130162730003" style="zoom:37%;" />



三线性插值结果：

<img src="https://www.qiniu.cregskin.com/image-20201130162957842.png" alt="image-20201130162957842" style="zoom:35%;" />



#### MipMap 的不足

远处的细节被过分模糊了

<img src="https://www.qiniu.cregskin.com/image-20201130163119357.png" alt="image-20201130163119357" style="zoom:33%;" />

<img src="https://www.qiniu.cregskin.com/image-20201130163634745.png" alt="image-20201130163634745" style="zoom:34%;" />

MipMap 的问题：

1. 查找像素在纹理uv图中的范围，近似成正方形，再在MipMap中查询纹理结果，对于实际纹理是一个近似值
2. 如果一个像素在纹理图中对应的范围是长方形，被近似成正方形后查询的纹理结果，与实际纹理图中对应的结果差距是很大的





解决方法：各向异性过滤 Anisotropic Filtering

#### 各向异性过滤 Anisotropic Filtering

各向异性：在各个方向上长度不同

又称 Ripmap，总开销是原本的3倍。

与 MipMap 不同的是，其内存储压缩了长条形纹理范围

<img src="https://www.qiniu.cregskin.com/image-20201130101911374.png" alt="image-20201130101911374" style="zoom:50%;" />

2x，3x，占用空间为原来的三倍。显存足够就行，不会影响计算力，不会卡顿



+ 可以查找轴对齐的矩形区域
+ 对角线脚印还是个问题

问题：如果一个像素对应的纹理范围是一个斜长方形，MipMap和RipMap都没有拟合的斜长方形范围，如何处理？其他不规则的图形呢？

答：EWA filter

#### EWA filter

任意一个不规则图形，被划分为多个圆形覆盖不规则图形

多次查询多个圆形，得出纹理结果

<img src="https://www.qiniu.cregskin.com/image-20201130164126633.png" alt="image-20201130164126633" style="zoom:30%;" />

+ 使用多个查找
+ 加权平均数
+ Mipmap层次结构仍然有用
+ 能处理不规则的脚印





# 3. Applications of texture

















