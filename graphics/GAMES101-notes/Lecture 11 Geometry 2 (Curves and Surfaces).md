[TOC]





## 0. 前情提要

 Explicit Representations

+ Curves 
  + Bezier curves 
  + De Casteljau’s algorithm
  + B-splines, etc. 
+ Surfaces
  + Bezier surfaces
  + Triangles & quads
    + Subdivision, simplification, regularization



## 1. 显式表示 Explicit

点云 Point Cloud

<img src="https://www.qiniu.cregskin.com/202201221642447.png" alt="image-20220122164204416" style="zoom:33%;" />

+ 容易表示 (x, y, z)
+ 容易表示各种各样的几何
+ 对于大批量数据集很有用（点数/像素数 >> 1）
+ 经常转成多边形面
+ 容易因采样不足，导致难以绘制（走样）



**多边形面 Polygon Mesh (Explicit)**

<img src="https://www.qiniu.cregskin.com/202201221644584.png" alt="image-20220122164402559" style="zoom:50%;" />



+ 存储顶点、多边形面（经常用三角形、四边形）
+ 容易处理、仿真、自适应采样
+ 很难的数据结构
+ 也许是图形学中，最常见的表示形式





## 2. 曲线 Curves

**应用场景**

+ 摄像机移动路径
+ 动画运动曲线
+ 矢量字体



### 2.1 贝塞尔曲线 Bézier Curves

<img src="https://www.qiniu.cregskin.com/202201221955747.png" alt="image-20220122195548668" style="zoom:50%;" />

+ 起始点、截止点固定 p0 p3
+ 起始方向、截止方向固定



#### de Casteljau Algorithm####

**三个控制点**

<img src="https://www.qiniu.cregskin.com/202201221958157.png" alt="image-20220122195815130" style="zoom:60%;" />

初始：三个点，两条线段

1. 在 $b_0-b_1$ 上找到参数 t 对应的点 $b_{0}^{1}$ ,在 $b_1-b_2$ 上找到参数 t 对应的点 $b_{1}^{1}$

   （两个点，一条线段）

2. 在 $b_{0}^{1} - b_{1}^{1}$ 上找到参数 t 对应的点 $b_{0}^{2}$

确定贝塞尔曲线上一个点 $b_{0}^{2}$



**四个控制点**

<img src="https://www.qiniu.cregskin.com/202201221959285.png" alt="image-20220122195949257" style="zoom:50%;" />

初始：四个点，三条线段

1.  
2.  
3. 



流程如下：

<img src="https://www.qiniu.cregskin.com/202201222006277.png" alt="image-20220122200623240" style="zoom:50%;" />

遍历线段，做线性插值



用数学线性插值描述三个控制点的贝塞尔曲线绘制：

<img src="https://www.qiniu.cregskin.com/202201222007416.png" alt="image-20220122200738379" style="zoom:70%;" />

归纳如下：

<img src="https://www.qiniu.cregskin.com/202201222016767.png" alt="image-20220122201600740" style="zoom:50%;" />



例子（扩展到三维）：

<img src="https://www.qiniu.cregskin.com/202201222017497.png" alt="image-20220122201748470" style="zoom:50%;" />





<img src="https://www.qiniu.cregskin.com/202201222034202.png" alt="image-20220122203454179" style="zoom: 67%;" />



#### 贝塞尔曲线的性质

+ 必须过起点、终点 <img src="https://www.qiniu.cregskin.com/202201222045376.png" alt="image-20220122204508347" style="zoom: 50%;" />

+ 起始点、终点的斜率：<img src="https://www.qiniu.cregskin.com/202201222041255.png" alt="image-20220122204113212" style="zoom:50%;" />

+ 仿射变换前后，形状不变（不包括投影）

+ 凸包性：贝塞尔曲线在控制点形成的凸包之内

  <img src="https://www.qiniu.cregskin.com/202201222044828.png" alt="image-20220122204441797" style="zoom:33%;" />

  > 如果控制点排在一条直线上，贝塞尔曲线什么样？
  >
  > 答：因凸包性，一定是一条直线



### 2.2 逐段贝塞尔曲线 Piecewise Bézier Curves

`矛盾`：当控制点多的时候，不便于用控制点控制贝塞尔曲线形状

<img src="https://www.qiniu.cregskin.com/202201222048274.png" alt="image-20220122204804244" style="zoom:50%;" />

`解决办法`：Piecewise 通过**每四个控制点，控制一段曲线**，解决控制问题

<img src="https://www.qiniu.cregskin.com/202201222051196.png" alt="image-20220122205139136" style="zoom: 25%;" />



`矛盾`：如何保证两段曲线衔接部分是光滑的？

`解决办法`：连续性

+ $C^0$ 连续：仅仅函数值是连续的
+ $C^1$ 连续：分割点处一阶导数连续
+ ...



### 2.3 其他曲线

#### 样条 splines

给出一系列锚点，按顺序连接

<img src="https://www.qiniu.cregskin.com/202201222057156.png" alt="image-20220122205749123" style="zoom: 33%;" />

#### B样条 basis splines

+ 需要输入比贝塞尔曲线更多的内容
+ 适用于局部修改（动一两个控制点，不至于影响整个曲线，这点性质贝塞尔曲线不具备）







## 3. 曲面 curved surface

### 3.1 贝塞尔曲线 to 曲面

图示：用 4 * 4 个控制点得出的曲面

<img src="https://www.qiniu.cregskin.com/202201222104689.png" alt="image-20220122210425657" style="zoom:50%;" />



<img src="https://www.qiniu.cregskin.com/202201222125978.png" alt="image-20220122212507939" style="zoom:50%;" />

1. 取四个点为一组，共取四组。每组内以 $u \in [0, 1]$ 绘制一条贝塞尔曲线，共绘制四条
2. 当 $u = u $ 时，在每条贝塞尔曲线上获取一个控制点，共四个控制点，以 $v \in [0, 1]$ 绘制一条贝塞尔曲线。
3. 在 $u \in [0, 1]$ 内重复 2，得到贝塞尔曲面





## 4. 网格操作：几何体处理 Mesh Operations

+ 网格细分 Mesh Subdivision
+ 网格简化 Mesh simplification
+ 网格正则化 Mesh regularization



