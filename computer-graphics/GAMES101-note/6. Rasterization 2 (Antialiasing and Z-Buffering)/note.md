# Resterization 2 (Antialiasing and Z-Buffering)

[TOC]

# 1. 抗锯齿 Antialiasing（反走样）

锯齿 = 走样

## 1.1 锯齿的产生

### 采样

离散成像素，进行采样，形成图片

<img src="https://www.qiniu.cregskin.com/image-20201125082335589.png" alt="image-20201125082335589" style="zoom: 33%;" />

在时间上对现实世界采样，获得动画

<img src="https://www.qiniu.cregskin.com/image-20201125082552227.png" alt="image-20201125082552227" style="zoom: 25%;" />



> **Artrifact**：看上去不太对的东西。瑕疵



### 因采样的产生的问题

锯齿 Jaggies

<img src="https://www.qiniu.cregskin.com/image-20201125083045495.png" alt="image-20201125083045495" style="zoom:25%;" />

摩尔纹：跳过奇数行、基数列

<img src="https://www.qiniu.cregskin.com/image-20201125082740704.png" alt="image-20201125082740704" style="zoom:33%;" />

顺时针旋转的轮子，某些部分看起来是逆时针旋转：人眼在时间上的采样，跟不上轮子转动速度

<img src="https://www.qiniu.cregskin.com/image-20201125082947104.png" alt="image-20201125082947104" style="zoom:25%;" />

### 直观上走样的原因 Artifact

信号变化的速度太快，以至于采样的速度跟不上



## 1.2 走样的解决策略

###  模糊处理 + 对像素采样

模糊处理：滤波（使用低通滤波器，滤除高频分量）

采样：像素点不再显示单纯的红色、白色，而是根据模糊处理后像素点的颜色百分比显示颜色

![image-20201125083354833](https://www.qiniu.cregskin.com/image-20201125083354833.png)

优化前

<img src="https://www.qiniu.cregskin.com/image-20201125083642617.png" alt="image-20201125083642617" style="zoom:50%;" />

优化后

<img src="https://www.qiniu.cregskin.com/image-20201125083631214.png" alt="image-20201125083631214" style="zoom: 50%;" />



> 可否先采样，后模糊处理？
>
> 答：不行



Antialiasing 反走样 = 模糊处理 + 采样

Blurred Aliasing = 采样 + 模糊处理

<img src="https://www.qiniu.cregskin.com/image-20201125083857912.png" alt="image-20201125083857912" style="zoom:67%;" />





## 1.3 模糊处理的原理

### 傅立叶级数展开

任何一个周期函数，都可视为多个正弦波、余弦波的组合

<img src="https://www.qiniu.cregskin.com/image-20201125084621546.png" alt="image-20201125084621546" style="zoom: 50%;" />

上图拟合目标为 $$\left \{ \right.$$ 的函数

![image-20201125084711711](https://www.qiniu.cregskin.com/image-20201125084711711.png)

**欧拉公式**：

<img src="https://www.qiniu.cregskin.com/image-20201125084718283.png" alt="image-20201125084718283" style="zoom:50%;" />



**等间隔采样的问题：当被信号频率f变高，采样频率低，拟合度非常低**。如图：

<img src="https://www.qiniu.cregskin.com/image-20201125084936941.png" alt="image-20201125084936941" style="zoom:33%;" />

得出一个结论：最终采样的拟合程度，与**函数频率**和**采样间隔**密切相关



### 走样问题 与 采样间隔

如下图，假设有两种函数，紫色函数为 f1，黑色函数为 f2，按图中所示采样，f1、f2 的采样结果显示与 f2 一模一样。**最终使用同样的采样方式，对不同的函数采样，得出相同的采样结果**



<img src="https://www.qiniu.cregskin.com/image-20201125085225629.png" alt="image-20201125085225629" style="zoom: 67%;" />

**走样**：对不同频率的波采样，得出了一样的结果，导致无法区分采样出的信号与原信号是否一致

**高频信号采样不足：错误地显示来自低频信号的样本**
**在给定采样率下无法区分的两个频率称为“别名”**

> 过滤去除，一定频率内容
>
> Filtering Getting rid of certain frequency contents



### 滤波与图像显示

滤波：过滤某些频率的波

时域信号 -> 频域信号

![image-20201125085652116](https://www.qiniu.cregskin.com/image-20201125085652116.png)

中心低频，四周高频，亮度表示信息量。

> 水平和竖直为什么是两条线？ 
>
> 答：非周期性变化的信号



滤波，滤除低频波，得出单纯的高频波

下图显示为高通滤波器：只让高频信号通过

<img src="https://www.qiniu.cregskin.com/image-20201125085911865.png" alt="image-20201125085911865" style="zoom:67%;" />

衣服边界与四周变化较大，信号变化也大



下图为剔除低频信息，细节丢失了

**低通滤波器：只让低频通过**

<img src="https://www.qiniu.cregskin.com/image-20201125090114924.png" alt="image-20201125090114924" style="zoom:67%;" />

同时剔除高频、低频信息

![image-20201125090222625](https://www.qiniu.cregskin.com/image-20201125090222625.png)

剔除更多低频信号

<img src="https://www.qiniu.cregskin.com/image-20201125090320193.png" alt="image-20201125090320193" style="zoom:67%;" />



### 时域卷积 = 平均 = 模糊处理 = 滤高频波

Filtering Convolution  ( = Averaging )

用滤波器做卷积操作

<img src="https://www.qiniu.cregskin.com/image-20201125090559498.png" alt="image-20201125090544825" style="zoom: 50%;" />

移动滤波器，继续卷积

<img src="https://www.qiniu.cregskin.com/image-20201125090556611.png" alt="image-20201125090556611" style="zoom:50%;" />



### 傅立叶变换 Fourier Transform、时域卷积、频域乘积

> 图像 * 滤波器 = 时域卷积 = 模糊图像
>
> 经傅立叶变换
>
> 频域图像 x 频域滤波器 = 频域乘积
>
> 频域乘积经逆傅立叶变换，得出模糊图像

<img src="https://www.qiniu.cregskin.com/image-20201125091441852.png" alt="image-20201125091441852" style="zoom:50%;" />



**低通滤波器**：图示在九个像素点内，做平均。

转换到频域图像，大部分是低频信息

越大的 box ，过滤后得出的图像越模糊，频域图像上，高频分量越少

<img src="https://www.qiniu.cregskin.com/image-20201125111109694.png" alt="image-20201125111109694" style="zoom: 25%;" />





### 采样就是频域的内容不断重复

连续的模拟信号，在时域上的图像。其傅立叶变换后，在频谱上的图像

![image-20201125092525571](https://www.qiniu.cregskin.com/image-20201125092525571.png)

冲击函数在时域上的图像。冲击函数对应傅立叶变换在频谱上的图像

![image-20201125092603512](https://www.qiniu.cregskin.com/image-20201125092603512.png)

使用冲击函数，对时域信号采样。在频谱上，对应的采样

![image-20201125092640697](https://www.qiniu.cregskin.com/image-20201125092640697.png)

**从图像上看，采样 = 时域乘积 = 频域卷积 = 重复频域内容**



**时域上的乘积  <img src="https://www.qiniu.cregskin.com/image-20201125111903479.png" alt="image-20201125111903479" style="zoom:25%;" />**

**对应 ** 

**频域上的卷积<img src="https://www.qiniu.cregskin.com/image-20201125111924371.png" alt="image-20201125111924371" style="zoom:25%;" />**  



### 走样 与 采样率、频率

采样率越低，采样稀疏，频谱上信号间越密集。采样率低到一定程度，频谱显示的信号发生混叠，导致走样

<img src="https://www.qiniu.cregskin.com/image-20201125093004620.png" alt="image-20201125093004620" style="zoom:40%;" />



### 抗锯齿的实践

#### 换设备

#### 增加采样率

+ 本质上增加了频谱中，两个信号的距离
+ 高分辨率

#### 反走样

+ 在频谱上做重复之前，让频谱“变窄”

+ 采样前，滤除高频分量（模糊处理）

  ![image-20201125093538685](https://www.qiniu.cregskin.com/image-20201125093538685.png)

  频谱不再发生混叠





![image-20201125113153712](https://www.qiniu.cregskin.com/image-20201125113153712.png)

注意栅格化三角形中的抗锯齿边，其中像素值取中间值



### 反走样具体操作

<img src="https://www.qiniu.cregskin.com/image-20201125113606062.png" alt="image-20201125113606062" style="zoom:50%;" />

1. 用足够大的低通滤波器，对图片中每个像素卷积，获得平均值

   <img src="https://www.qiniu.cregskin.com/image-20201125113331364.png" alt="image-20201125113331364" style="zoom:50%;" />

   <img src="https://www.qiniu.cregskin.com/image-20201125114050591.png" alt="image-20201125114050591" style="zoom:20%;" />

   **如何计算出三角形在某个区域覆盖的范围？MSAA近似反走样**

2. 再对像素卷积后，平均值（中心像素）采样



### Antialiasing By Supersampling （MSAA）

[求解反走样的近似方法](https://www.bilibili.com/video/BV1Zz4y1D7fM)，而不是精准解决反走样。通过更多的样本，做模糊

<img src="https://www.qiniu.cregskin.com/image-20201125094103608.png" alt="image-20201125094103608" style="zoom: 25%;" />

原图

![image-20201125114244888](https://www.qiniu.cregskin.com/image-20201125114244888.png)

在每一个像素位置划分出更多采样点，下图划分四个

<img src="https://www.qiniu.cregskin.com/image-20201125114310580.png" alt="image-20201125114310580" style="zoom: 65%;" />

覆盖了四个子采样点中的三个，那这个采样点覆盖率75%

<img src="https://www.qiniu.cregskin.com/image-20201125114405186.png" alt="image-20201125114405186" style="zoom:67%;" />

同样方法，判断其他点。最终模糊效果为：

<img src="../../../../../Library/Application Support/typora-user-images/image-20201125114415507.png" alt="image-20201125114415507" style="zoom: 67%;" />

采样结果：

<img src="https://www.qiniu.cregskin.com/image-20201125114522806.png" alt="image-20201125114522806" style="zoom:67%;" />



**MSAA牺牲了什么？**

答：增加采样点 = 增加计算量。如果用2*2采样，增加四倍



**如何用很少采样点，获得好的效果？**

答：不一定用方块，可能是多种图形。还存在样本复用



## 1.4 更多抗锯齿方案

+ FXAA Fast Approximate AA

  快速近似抗锯齿。增加图像的后期处理，不增加样本数，对样本后期处理，把带锯齿的部分，换成没有锯齿的部分

+ TAA Temporal AA

  复用上一帧的采样结果（将MSAA结果分布在时间上，如果两帧没有区别，直接复用）



**对于运动的物体怎么办？如何实现抗锯齿？**



## 1.5 抗锯齿相关概念

Super resolution / super sampling 超分辨率

+ 放大图像，但不想看到锯齿。512*512拉伸到4K，低采样率的图片拉伸到更高分辨率，样本不足，细节缺失

+ 需要解决样本不足的问题

+ 应用技术：DLSS（Deep Learing Super Sampling）

  猜测细节







## 2. 可见性遮挡 Visiblity occlusion

### 2.1 Z缓冲















