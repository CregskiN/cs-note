

​	 

# Transformation cont

[TOC]



## 1. 三维变换 3D transformations

<img src="https://www.qiniu.cregskin.com/image-20201121222911603.png" alt="image-20201121222911603" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/image-20201121222938669.png" alt="image-20201121222938669" style="zoom:50%;" />

仿射变换 = 线性变换 + 平移



### 1.1 缩放

<img src="https://www.qiniu.cregskin.com/image-20201121223108336.png" alt="image-20201121223108336" style="zoom:67%;" />



### 1.2 平移

<img src="https://www.qiniu.cregskin.com/image-20201121223113493.png" alt="image-20201121223113493" style="zoom: 67%;" />

### 1.3 旋转

<img src="https://www.qiniu.cregskin.com/image-20201121223953335.png" alt="image-20201121223953335" style="zoom:50%;" />

#### 绕x轴旋转$\alpha$度<img src="https://www.qiniu.cregskin.com/image-20201121223850138.png" alt="image-20201121223850138" style="zoom: 50%;" />



#### 绕y轴旋转$\alpha$度<img src="https://www.qiniu.cregskin.com/image-20201121223857509.png" alt="image-20201121223857509" style="zoom: 50%;" />



#### 绕z轴旋转$\alpha$度<img src="https://www.qiniu.cregskin.com/image-20201121223912315.png" alt="image-20201121223912315" style="zoom: 50%;" />

### 任意轴的旋转

首先明确：

<img src="https://www.qiniu.cregskin.com/image-20201121225735095.png" alt="image-20201121225735095" style="zoom:50%;" />

即：某轴的旋转，可视为分别绕x、y、z轴逆时针旋转$\alpha$ $\beta$ $\gamma$ 度的组合

这三个角，称为欧拉角

<img src="https://www.qiniu.cregskin.com/image-20201121230053545.png" alt="image-20201121230053545" style="zoom:50%;" />

Pitch：视角上下旋转

Yaw：视角左右旋转

Roll：以视角正前方为中心旋转



#### Rodrigues' Rotation Formula

罗德里格斯公式

绕轴 $\vec{n}$ 旋转 $\alpha$ 度

<img src="https://www.qiniu.cregskin.com/image-20201123184745890.png" alt="image-20201123184745890" style="zoom:50%;" />

注意：这里默认旋转轴 $\vec{n}$ 是过原点的



问题：沿任意轴怎么办？

1. 平移到原点
2. 绕过原点的轴旋转
3. 平移回原位置



> 四元数是什么？为什么引入？



## 2. 视图变换 Viewing transformation

场景：三维世界的一个模型，呈现到二维屏幕上

什么是观测变换 Viewing transformation ？

+ 拍摄一张照片需要步骤？
  + 找一块空间，把所有人集中到一起（model transformation 模型变换）
  + 选一个相机角度/位置（view transformation 视图变换）
  + 茄子！（projection transformation 投影变换）

简称 MVP 变换 - model view projection



### 2.1 视图 View / Camera transformation

#### 分析

视图变换用于确定相机的一些属性

+ 位置 Position $\vec{e}$
+ 观看方向 Look-at / gaze direction $\vec{g}$
+ 上方向 Up direction $\vec{t}$

<img src="https://www.qiniu.cregskin.com/image-20201121233607078.png" alt="image-20201121233607078" style="zoom:50%;" />



物体和相机的移动，对成相有什么影响？

答：一起移动，相对不动，成像不会有变化。二者有相对移动，成像会变化

> 为同时兼具相对移动和编码方便，
>
> **令：相机位置 $\vec{e}$ 处于 (0, 0, 0)，观看方向 $\vec{g}$ 指向 -z 方向 (0, 0, -1)，上方向为 +y 方向**

<img src="https://www.qiniu.cregskin.com/image-20201122095342715.png" alt="image-20201122095342715" style="zoom:50%;" />

#### 实际操作

实际输入的相机位置 $\vec{e}$ 、观看方向 $\vec{g}$ 是在三维空间中的，需要把他们转换到 (0, 0, 0) 和 -z 方向

原相机位置 e、观看方向 g、上方向 t：<img src="https://www.qiniu.cregskin.com/image-20201122095908254.png" alt="image-20201122095908254" style="zoom:50%;" />

变换后相机位置 O、观看方向 -Z、上方向 Y：<img src="https://www.qiniu.cregskin.com/image-20201122101148650.png" alt="image-20201122101148650" style="zoom:50%;" />

+ **by $M_{view}$**
  + 把 $\vec{e}$ 平移到原点
  + 把 $\vec{g}$ 旋转到 $-\vec{Z}$
  + 把 $\vec{t}$ 旋转到 $+\vec{Y}$
  + 自然而然 $-\vec{z} \times \vec{y} = +\vec{X}$



#### 观察矩阵 view matrix

$M_{view} = R_{view}T_{view}$

+ 平移到原点 $$T_{view} = \begin{bmatrix} 1 & 0 & 0 & -x_e \\ 0 & 1 & 0 & -y_e \\ 0 & 0 & 1 & -z_e \\ 0 & 0 & 0 & 1 \end{bmatrix}$$

+ 旋转 $$\left\{ \begin{matrix} \vec{g} \rightarrow -\vec{Z} \\ \vec{t} \rightarrow \vec{Y} \end{matrix} \right.$$ 

  直接写旋转回Z Y 的 $R_{view}$ 不太好写。

  旋转矩阵是**正交矩阵**，其转置等于其逆 $R_{view}^{T} = R_{view}^{-1}$，可以先写 $R_{view}^{-1}$ 即，旋转 $$\left\{ \begin{matrix} -\vec{Z} \rightarrow \vec{g} \\ \vec{Y} \rightarrow \vec{t} \end{matrix} \right.$$

  $$R_{view}^{-1} = \begin{bmatrix} x_{\vec{g} \times x_{\vec{t}}} & x_{t} & x_{-g} & 0 \\ y_{\vec{g} \times \vec{t}} & z_t & z_{-g} & 0 \\ z_{\vec{g} \times \vec{t}} & z_t & z_{-g} & 0 \\ 0 & 0 & 0& 1 \end{bmatrix} = R_{view}^{T}$$

  把你旋转矩阵转置，得到旋转矩阵

  $$R_{view} = \begin{bmatrix} x_{\vec{g} \times \vec{t}} & y_{\vec{g} \times \vec{t}} & z_{\vec{g} \times \vec{t}} & 0 \\ x_{t} & y_{t} & z_{t} & 0 \\ x_{-g} & y_{-g} & z_{-g} & 0 \\ 0 & 0 & 0 & 1\end{bmatrix}$$

最后，所有物体都需要经过 view transformation，因为根据无相对运动成像不变，其他物体也需要与相机做同样的运动



> 至此：
>
> model martix 完成物品摆放
>
> view matrix 完成相机的摆放
>
> 还需要通过投影，在二维屏幕成像





### 2.2 投影 Projection transformation

<img src="https://www.qiniu.cregskin.com/image-20201122103909908.png" alt="image-20201122103909908" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/image-20201122104132096.png" alt="image-20201122104132096" style="zoom:50%;" />

正交投影：距离物体无限远观测

#### (i) 正交投影 Orthographic projection

<img src="https://www.qiniu.cregskin.com/image-20201122104334913.png" alt="image-20201122104334913" style="zoom: 80%;" />

+ 一个简单的理解方式
  + 把相机设置在原点，观测方向 -Z，上方向 Y
  + 把物体中心平移到原点，缩放长宽高到 **cuboid** [-1, 1]^3



举例：

已知立方体 [l, r] x [b, t] x [f, n]

![image-20201122110605464](https://www.qiniu.cregskin.com/image-20201122110605464.png)

先移动，再缩放：

<img src="https://www.qiniu.cregskin.com/image-20201122105358851.png" alt="image-20201122105358851" style="zoom:50%;" />

> 此处使用右手坐标系，表示远近的 [f, n] 其中 n > f

> OpenGL 在投影中的 API 使用的左手坐标系

> 正交投影的作用：把立方体中心移动到原点，缩放到 cube [-1, 1]^3

#### (ii) 透视投影 Prespective projection

近大远小，平行线不再平行

<img src="https://www.qiniu.cregskin.com/image-20201122110806065.png" alt="image-20201122110806065" style="zoom:33%;" />

**前置知识**

1. (x, y, z, 1)、(kx, ky, kz, k) {k != 0}、(xz, yz, z^2, z) {z != 0} 表示的是同一个三维点！

   如：(1, 0, 0, 1) (2, 0, 0, 2) 表示的同一个点 (1, 0, 0)

2. 透视投影大概是先把一个平截头体 Frustum 空间挤压到一个立方体 cuboid 中，再做一次正交投影

   规定：

   + 近平面不变
   + 远平面是在平面内向里收缩
   + 近平面中心到远平面中心的连线，不会发生变化

   <img src="https://www.qiniu.cregskin.com/image-20201122111300534.png" alt="image-20201122111300534" style="zoom: 33%;" />



**如何挤压？**即如何得出 $M_{persp \rightarrow ortho}$

以侧面图为例：

对于任意点(x, y, z )

<img src="https://www.qiniu.cregskin.com/image-20201122112743888.png" alt="image-20201122112743888" style="zoom: 33%;" />

x同理

<img src="https://www.qiniu.cregskin.com/image-20201122112848656.png" alt="image-20201122112848656" style="zoom: 33%;" />

代入 y' x'，化简

<img src="https://www.qiniu.cregskin.com/image-20201122113041605.png" alt="image-20201122113041605" style="zoom:33%;" />



**小结：**

<img src="https://www.qiniu.cregskin.com/image-20201122115441021.png" alt="image-20201122115441021" style="zoom: 33%;" />

<img src="https://www.qiniu.cregskin.com/image-20201122115500468.png" alt="image-20201122115500468" style="zoom:33%;" />

下面填充 $M_{presp \rightarrow ortho}$ 矩阵第三行。在挤压过程中;l：

+ 近平面上，所有坐标 x、y、z 不变，z 为 n  $$M_{persp \rightarrow ortho} \left( \begin{matrix} x \\ y \\ n \\ 1 \end{matrix} \right) = \left( \begin{matrix} x \\ y \\ n \\ 1 \end{matrix} \right)$$

  

  根据齐次坐标的定义，有  $$\left( \begin{matrix} x \\ y \\ n \\ 1 \end{matrix} \right) == \left( \begin{matrix} nx \\ ny \\ n^2 \\ n \end{matrix} \right) $$

  

  

  写作矩阵与点形式  $$\begin{bmatrix} n & 0 & 0 & 0  \\ 0 & n & 0 & 0 \\ C & D & A & B \\ 0 & 0 & 1 & 0 \end{bmatrix} \left( \begin{matrix} x \\ y \\ n \\ 1 \end{matrix} \right) = n^2$$

  

  

   抽出第三行与点形式：<img src="https://www.qiniu.cregskin.com/image-20201122164221104.png" alt="image-20201122164221104" style="zoom:25%;" />

  

  得出  $$\left \{ \begin{matrix} C = 0 \\ D = 0 \\ An + B = n^2 \end{matrix} \right.$$

  

+ 远平面上，所有坐标 z 不变，为 f

  选取远平面的中心点$$\left( \begin{matrix} 0 \\ 0 \\ f \\ 1 \end{matrix} \right) = \left( \begin{matrix} 0 \\ 0 \\ f^2 \\ f \end{matrix} \right)$$

  过程同近平面，抽出M第三行与点相乘  $$\left( \begin{matrix} 0 & 0 & A & B \end{matrix} \right) \left( \begin{matrix} 0 \\ 0 \\ f \\ 1 \end{matrix} \right) = \left( \begin{matrix} 0 \\ 0 \\ f^2 \\ f \end{matrix} \right)$$

  得出  $$\left \{ \begin{matrix} Af + B = f^2 \end{matrix} \right.$$

   

  联立  $$\left \{ \begin{matrix} An + B = n^2 \\ Af + B = f^2 \end{matrix} \right.$$

  

  得 $$\left \{ \begin{matrix} A = n + f \\ B = -nf \end{matrix} \right.$$

   最终代入回 M，得 $$M_{presp \rightarrow ortho} = \begin{bmatrix} n & 0 & 0 & 0  \\ 0 & n & 0 & 0 \\ 0 & 0 & n+f & -nf \\ 0 & 0 & 1 & 0 \end{bmatrix} $$


