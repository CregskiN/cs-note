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

### Artifact 走样 宏观原因

信号变化的速度太快，以至于采样的速度跟不上



## 1.2 走样的解决策略

###  模糊处理 + 对像素采样

滤波

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





### 1.3 傅立叶级数展开

任何一个周期函数，都可视为多个正弦波、余弦波的组合

<img src="https://www.qiniu.cregskin.com/image-20201125084621546.png" alt="image-20201125084621546" style="zoom: 50%;" />

上图拟合目标为 $$\left \{ \right.$$ 的函数

![image-20201125084711711](https://www.qiniu.cregskin.com/image-20201125084711711.png)

**欧拉公式**：

<img src="https://www.qiniu.cregskin.com/image-20201125084718283.png" alt="image-20201125084718283" style="zoom:50%;" />



**等间隔采样的问题：当被采样频率高，采样频率低，拟合度非常低**。如图：

<img src="https://www.qiniu.cregskin.com/image-20201125084936941.png" alt="image-20201125084936941" style="zoom:33%;" />



### 1.4 从采样的角度分析，走样的原因

对不同频率的波采样，得出了一样的结果，导致无法区分采样出的信号与原信号是否一致

**高频信号采样不足：错误地显示样本来自低频信号**
**在给定采样率下无法区分的两个频率称为“别名”**

<img src="https://www.qiniu.cregskin.com/image-20201125085225629.png" alt="image-20201125085225629" style="zoom:67%;" />



> 过滤去除，一定频率内容
>
> Filtering Getting rid of certain frequency contents



### 1.5 傅立叶变换 Fourier Transform

时域信号 -> 频域信号

![image-20201125085652116](https://www.qiniu.cregskin.com/image-20201125085652116.png)

中心低频，四周高频，亮度表示信息量。

> 水平和竖直为什么是两条线？ 
>
> ?????



滤波，滤除低频波，得出单纯的高频波。

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



### 1.6 滤波时域卷积 = 平均

Filtering Convolution  ( = Averaging )

用滤波器做卷积操作

<img src="https://www.qiniu.cregskin.com/image-20201125090559498.png" alt="image-20201125090544825" style="zoom: 50%;" />

移动滤波器，继续卷积

<img src="https://www.qiniu.cregskin.com/image-20201125090556611.png" alt="image-20201125090556611" style="zoom:50%;" />



### 1.7 时域卷积与频域乘积

> 时域上的卷积，对应到频域上的乘积

<img src="https://www.qiniu.cregskin.com/image-20201125091441852.png" alt="image-20201125091441852" style="zoom:50%;" />



**低通滤波器**

<img src="https://www.qiniu.cregskin.com/image-20201125091935312.png" alt="image-20201125091935312" style="zoom:25%;" />



### 1.8 从时域频域分析采样是什么

连续的模拟信号，在时域上的图像。其傅立叶变换后，在频谱上的图像

![image-20201125092525571](https://www.qiniu.cregskin.com/image-20201125092525571.png)

冲击函数在时域上的图像。冲击函数对应傅立叶变换在频谱上的图像

![image-20201125092603512](https://www.qiniu.cregskin.com/image-20201125092603512.png)

使用冲击函数，对时域信号采样。在频谱上，对应的采样

![image-20201125092640697](https://www.qiniu.cregskin.com/image-20201125092640697.png)

**从图像上看，采样=重复频率内容**





从频谱上，对走样进行解释：

时域信号采样越稀疏，频谱上信号间越密集，直到发生混合

<img src="https://www.qiniu.cregskin.com/image-20201125093004620.png" alt="image-20201125093004620" style="zoom:50%;" />



### 1.4 抗锯齿的实际使用

#### 增加采样率

+ 本质上增加了频谱中，两个信号的距离
+ 高分辨率

#### 反走样

+ 在频谱上做重复之前，让频谱“变窄”

+ 采样前，滤除高频分量（模糊处理）

  ![image-20201125093538685](https://www.qiniu.cregskin.com/image-20201125093538685.png)

  频谱不再发生混叠



### 如何对图片模糊处理？

+ 用足够大的低通滤波器，对图片卷积，获得平均值
+ 再对平均值采样



### Antialiasing By Supersampling （MSAA）

通过更多的样本，做模糊

<img src="https://www.qiniu.cregskin.com/image-20201125094103608.png" alt="image-20201125094103608" style="zoom:50%;" />

MSAA牺牲了什么？

答：增加采样点 = 增加计算量。如果用2*2采样，增加四倍

如何用很少采样点，获得好的效果？

答：不一定用方块，可能是多种图形，可复用



### 更多抗锯齿方案

FXAA Fast Approximate AA

快速近似抗锯齿

TAA Temporal AA

复用上一帧的采样结果（将MSAA结果分布在时间上）

**对于运动的物体怎么办？**



### 抗锯齿相关概念

+ Super resolution / super sampling 超分辨率

  放大图像，但不想看到锯齿

  + 类似MSAA，解决样本不足的问题

  + 应用技术：DLSS（Deep Learing Super Sampling）

    猜测细节







## 2. 可见性遮挡 Visiblity occlusion

### 2.1 Z缓冲















