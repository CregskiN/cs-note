[TOC]



## 0. 前情提要

+ Shading 1 & 2
  + blinn-Phong reflectance model
  + Shading models / fraquencies
  + Graphics Ppeline
  + Texture mapping



+ Shading 3
  + Barycentric coordinates
  + Texture queries
  + Applications of textures





## 1. 重心坐标 Barycentric coordinates



### 1.1 中心坐标计算

+ 为什么要插值？

  得到一个过渡效果，如对三角形内部像素的三种 Shading

+ 对什么内容插值？

  纹理坐标 uv、颜色、法线

+ 如何插值？

  Barycentric coordinates



<img src="https://www.qiniu.cregskin.com/202201151100607.png" alt="image-20220115110040580" style="zoom:50%;" />

三角形内任意点 (x, y) 都可以用三个顶点坐标线性组合表示

+ 要求：三个系数非负且和为 1



重心坐标可以通过面积比求出：

<img src="https://www.qiniu.cregskin.com/202201151104600.png" alt="image-20220115110410568" style="zoom:50%;" />

计算公式如下：

<img src="https://www.qiniu.cregskin.com/202201151139705.png" alt="image-20220115113930675" style="zoom:50%;" />



> 投影前的重心坐标，与投影后在屏幕上像素的重心坐标，二者不相等。应该采用哪种重心坐标做插值？
>
> 答：应找到 2D 像素对应原三角形，在原三角形内做插值（逆变换）



### 1.2 应用到纹理坐标uv

用纹理上 uv 对应的颜色，代替 kd





### 1.3 存在的问题

#### 纹理放大 / 纹理太小 Texture Magnification

+ **pixel**：生成画面的像素
+ **texel**：纹理像素

物体分辨率 >> 纹理分辨率，同一个 texel，会应用到多个 pixel

<img src="https://www.qiniu.cregskin.com/202201151559418.png" alt="image-20220115155900388" style="zoom:50%;" />

解决办法：

+ Bilinear：双线性插值
+ Bicubic 



**Bilinear interpolation**

<img src="https://www.qiniu.cregskin.com/202201151607837.png" alt="image-20220115160746808" style="zoom:40%;" />

1. 找 texture 中 uv 临近的四个 texel
2. 两次横向差值，得 $u_0、u_1$
3. 一次纵向插值



**Bicubic interpolation**

与 Bilinear interpolation 不同是，先取 16 个临近 texel

+ more porformation
+ more compute





#### 纹理太小

效果：

<img src="https://www.qiniu.cregskin.com/202201151614156.png" alt="image-20220115161417121" style="zoom:33%;" />

+ 近处：出现锯齿（走样）
+ 远处：出现摩尔纹



原理：

<img src="https://www.qiniu.cregskin.com/202201151615167.png" alt="image-20220115161529125" style="zoom:33%;" />

+ 近处：一个 pixel 不足以覆盖一个 texel（采样频率 << 信号频率）

+ 远处：一个 pixel 覆盖超过一个 texel（采样频率 << 信号频率）



解决方法：

+ supersampling 超采样
+ 点查询
+ 范围查询 range query / average query
  + Mipmap



## 4. 纹理查询 Texture Mapping

### 4.1 Mipmap

> 仅仅可以快速、做**近似正方形**的、范围查询

<img src="https://www.qiniu.cregskin.com/202201151626497.png" alt="image-20220115162616463" style="zoom: 50%;" />

> 个人理解：提前得出插值结果

> 额外引入近 1/3 的存储



### 4.1 Mipmap 查询

+ 取 pixel 中心和临近 pixel 的中心，映射到 uv

  <img src="https://www.qiniu.cregskin.com/202201151634661.png" alt="image-20220115163405628" style="zoom: 33%;" />

+ 在 D 层查询到 pixel 唯一对应的 texel

  <img src="https://www.qiniu.cregskin.com/202201151638486.png" alt="image-20220115163836443" style="zoom:33%;" />

  + L：在某一层，pexel 对应的覆盖正方形的边长
  + 若 D 得不到整数，则用临近整数层插值

​	

**三线性插值 Trilinear interpolation**

<img src="https://www.qiniu.cregskin.com/202201151643915.png" alt="image-20220115164358876" style="zoom:50%;" />

1. 在 D 层插值得出 pixel 对应的 texel ‘
2. 在 D+1 层插值得出 pixel 对应的 texel ’‘
3. 将 1. 2. 结果再插值得出最终的 texel

> 如此，可以在层与层之间的出一个连续的 texel
>
> <img src="https://www.qiniu.cregskin.com/202201151646456.png" alt="image-20220115164618423" style="zoom:50%;" />



### 4.2 Mipmap 局限性

#### 过渡模糊 Overblur

<img src="https://www.qiniu.cregskin.com/202201151647625.png" alt="image-20220115164743590" style="zoom:33%;" />

**原理**：

Mipmap 是在正方形区域内做插值近似

但远处的 pixel 映射到 texture 应该是一个拉伸的区域（形状不规律的区域）

<img src="https://www.qiniu.cregskin.com/202201151650899.png" alt="image-20220115165051866" style="zoom:33%;" />

> 各向异性过滤仍没有彻底解决问题，对于斜着的 texel 区域无能为力

**解决办法**：

+ **各向异性过滤 Anisotropic Filtering**

  <img src="https://www.qiniu.cregskin.com/202201151653278.png" alt="image-20220115165322248" style="zoom: 33%;" />

  + 开销是原本 texture 的三倍

+ EWA filter

  把 texture 划分成多个不规则圆形

  <img src="https://www.qiniu.cregskin.com/202201151654025.png" alt="image-20220115165423988" style="zoom: 33%;" />

  + 多次查询 







