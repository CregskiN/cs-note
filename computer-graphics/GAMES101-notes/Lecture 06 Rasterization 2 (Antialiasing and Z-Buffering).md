[TOC]

## 0. 前情提要

+ Viewing
  + MVP
+ Rasterizing triangles
  + Point-in-triangle test
  + Aliasing 反走样



+ Antialiasing
  + Sampling throty
  + Antialiasing in practice
+ Visibility / occlusion
  + Z-buffering



> 采样会产生问题：锯齿

> Sampling **Artifacts** (Errors / Mistakes / Inaccuracies) 



<img src="http://www.qiniu.cregskin.com/202201081117269.png" alt="image-20220108111746236" style="zoom:33%;" />



## 1. 抗锯齿/反走样 Antialiasing

+ 锯齿 Jaggies —— 在空间中采样
+ 摩尔纹 Moire —— 欠采样图片
+ 车轮效应 Wagon wheel effect —— 在时间中采样

本质：信号变化太快，但采样速度跟不上



### 1.1 模糊 Blurring /滤波 Pre-Filter

采样的过程：滤波➡️采样

<img src="http://www.qiniu.cregskin.com/202201081123565.png" alt="image-20220108112325538" style="zoom:50%;" />

> 先采样，发现走样，再 Blurring 可以吗？
>
> 答：不可以



### 1.2 走样的原因

<img src="http://www.qiniu.cregskin.com/202201081128244.png" alt="image-20220108112816216" style="zoom:33%;" />

#### 傅立叶级数展开

任何一个函数，可以展开为常数+包含三角函数的多项式

<img src="http://www.qiniu.cregskin.com/202201081130148.png" alt="image-20220108113006117" style="zoom: 50%;" />

#### 傅立叶变换

一个函数 f，可以通过傅立叶变换可以换成另一个函数 F

而 F 也可以通过逆傅立叶变换成 f

<img src="http://www.qiniu.cregskin.com/202201081131928.png" alt="image-20220108113157901" style="zoom:50%;" />



#### 采样的频率需要与原函数的频率匹配

<img src="http://www.qiniu.cregskin.com/202201081137373.png" alt="image-20220108113711345" style="zoom:50%;" />



<img src="http://www.qiniu.cregskin.com/202201081251545.png" alt="image-20220108125157508" style="zoom:50%;" />

高频信号没有被充分采样，导致采样结果显示：原信号为一个低频信号

> 走样 Aliases：以一种方式对两个不同的高频信号采样，获得两个无法区分的采样结果，这种现象称为走样。





### 1.3 滤波 Filter

> 滤波：丢弃特定频率的内容

+ （原图像、频域图像）

​	<img src="http://www.qiniu.cregskin.com/202201081304061.png" alt="image-20220108130410032" style="zoom:50%;" />

+ （过滤低频信号的图像、频域图像）高通滤波器

​	<img src="http://www.qiniu.cregskin.com/202201081304826.png" alt="image-20220108130455797" style="zoom:50%;" />

>图像有明显变化的地方，经傅立叶变换频率较高，可以通过高通滤波器

+ （过滤高频信号的图像、频域信号）低通滤波器 / Blur

​	<img src="http://www.qiniu.cregskin.com/202201081306247.png" alt="image-20220108130651217" style="zoom:50%;" />

+ (过滤高频、低频信号的图像、频域信号)

​	<img src="http://www.qiniu.cregskin.com/202201081308401.png" alt="image-20220108130846374" style="zoom:50%;" />



#### 滤波 卷积 平均 / Filtering = Convolution = Averaging

卷积

<img src="http://www.qiniu.cregskin.com/202201081313870.png" alt="image-20220108131329842" style="zoom:33%;" />



`卷积定理`：**时域上对两个信号卷积，对应频域上两个信号乘积**

故卷积有两种操作：

+ 直接用一个滤波器 Filter / Convolution kernel，对图像做卷积操作

+ 对图像傅立叶变换，变到频域 frequency domain 上

  1. 频域相乘

  2. 逆傅立叶变换回时域 spatial domain 上



实例：

<img src="http://www.qiniu.cregskin.com/202201081511876.png" alt="image-20220108151110842" style="zoom:50%;" />

> 九分之一是归一化操作，避免卷积之后提亮





### 1.4 频率角度的采样

重复频域上的内容

<img src="http://www.qiniu.cregskin.com/202201081520984.png" alt="image-20220108152002952" style="zoom:50%;" />

+ e = a * c（时域上的乘积）
  + a 为给出的时域信号
  + c 为采样（此处为冲激函数）
  + e 为采样结果
+  f = b convolute d（在频率图像上显示为**搬移**）
  + b 为 a 对应的频域信号
  + d 为 c 对应的频域信号
  + f 为 a c 卷积结果

> 采样，在频率角度，就是重复频谱



<img src="http://www.qiniu.cregskin.com/202201081525700.png" alt="image-20220108152520657" style="zoom:50%;" />

> 当采样频率低时，频域上，频谱搬移的间隔小，甚至混合，导致**走样**







### 1.5 反走样的实现

方法一：增加采样频率

方法二：反走样 Antialiasing

i. 模糊 用低通滤波器卷积，去除高频分量<img src="http://www.qiniu.cregskin.com/202201081534990.png" alt="image-20220108153448959" style="zoom:33%;" />

ii. 像素卷积后，对九宫格采样，再平均

<img src="http://www.qiniu.cregskin.com/202201081538906.png" alt="image-20220108153855875" style="zoom:50%;" />

#### MSAA

对应 Antialiasing 的第一步：**模糊**

<img src="http://www.qiniu.cregskin.com/202201081540723.png" alt="image-20220108154049691" style="zoom: 33%;" />



<img src="http://www.qiniu.cregskin.com/202201081541340.png" alt="image-20220108154143305" style="zoom:33%;" />

<img src="http://www.qiniu.cregskin.com/202201081543576.png" alt="image-20220108154319545" style="zoom:33%;" />



> MSAA 并不是提高分辨率，而是用一种近似的方法，得到三角形的覆盖情况



#### 其他抗锯齿的方案

+ FXAA - Fast Approximate AA

  对有锯齿图像的后期处理。把有锯齿的边界，替换成没有锯齿的图形

+ TAA - Temporal AA

  找上一帧的信息，复用。应用于静态物体

+ 超分辨率 Super resolution / super sampling
  + 把低分辨率图像，变成高分辨率图像，而没有锯齿
  + 解决样本不足的问题（类似MSAA中把单个像素点分割）
  + DLSS（Deep Learning Super Sampling）





























