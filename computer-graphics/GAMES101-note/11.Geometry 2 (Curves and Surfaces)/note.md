# Curves and Surfaces

[TOC]



# Last Lecture

+ 初步介绍几何
  + 几何的例子
  + 几何的表示方法
    + 隐式几何
      + CSG
      + 距离函数 distance function
      + 水平集 level set
    + 显式几何





# 1. 显式几何 Explict Representations

## 1.1 点云 Point Cloud

+ 非常多、密集的点(x, y, z)
+ 很容易表示各种图形
+ 适用于大型数据集
+ 通常转换为多边形网格
+ 在采样不足的区域很难绘制

<img src="https://www.qiniu.cregskin.com/image-20201205093853455.png" alt="image-20201205093853455" style="zoom:25%;" />

+ 三维空间扫描，就是点云
+ 给出点云，如何描述出一个面？





## 1.2 多边形面 Polygon Mesh

+ 存储顶点多边形（通常是三角形或四边形）
+ 易于处理/模拟，自适应采样
+ 更复杂的数据结构
+ 图形学中，应用最广泛的显式表示

<img src="https://www.qiniu.cregskin.com/image-20201205094017450.png" alt="image-20201205094017450" style="zoom:25%;" />



## 1.3 顶点、纹理、法线的对应的文件格式

<img src="https://www.qiniu.cregskin.com/image-20201205094337547.png" alt="image-20201205094337547" style="zoom:35%;" />

+ vertex
+ vertex texture
+ vertex normal
+ face（图示为三角形）
  + 点1：v坐标 / vertex texture坐标 / vertex normal坐标
  + 点2：v坐标 / vertex texture坐标 / vertex normal坐标
  + 点3：v坐标 / vertex texture坐标 / vertex normal坐标





# 2. 曲线 Curves (Explict)

曲线的应用：

1. 相机的移动路径 https://youtu.be/rIJMuQPwr3E

2. 物体的移动路径 https://youtu.be/b-o5wtZlJPc

3. 字体的曲线。无限放大也是平滑的

   <img src="https://www.qiniu.cregskin.com/image-20201205094749651.png" alt="image-20201205094749651" style="zoom:25%;" />



## 2.1 贝塞尔曲线 bezier curves

用一系列控制点，定义一条曲线

如下图：

$定义一条曲线：起点p_0终点p_3，起点的切线方向沿p_0p_1，终点的切线方向沿p_2p_3$

<img src="https://www.qiniu.cregskin.com/image-20201205094851078.png" alt="image-20201205094851078" style="zoom:25%;" />





怎么画？

## 2.2 卡斯特尔焦算法 De Casteljau's algorithm

<img src="https://www.qiniu.cregskin.com/image-20201205095052755.png" alt="image-20201205095052755" style="zoom:50%;" /><img src="https://www.qiniu.cregskin.com/image-20201205095057918.png" alt="image-20201205095057918" style="zoom: 50%;" />



显式几何，要么直接给点，要么直接给参数。贝塞尔曲线给出的是参数t

给定两个点，一个控制点

<img src="https://www.qiniu.cregskin.com/image-20201205095352602.png" alt="image-20201205095352602" style="zoom:25%;" />



给定两个点，两个控制点

<img src="https://www.qiniu.cregskin.com/image-20201205095514086.png" alt="image-20201205095514086" style="zoom:25%;" />



递归过程：

<img src="https://www.qiniu.cregskin.com/image-20201205095925025.png" alt="image-20201205095925025" style="zoom:25%;" />

$$给出n+1个控制点（分别是b_0...b_n） \\$$

<img src="https://www.qiniu.cregskin.com/image-20201205100206445.png" alt="image-20201205100206445" style="zoom:25%;" />



直接写出伯恩斯坦多项式下贝塞尔曲线的定义式：

<img src="https://www.qiniu.cregskin.com/image-20201205100250971.png" alt="image-20201205100250971" style="zoom:25%;" />



伯恩斯坦多项式中的一项

<img src="https://www.qiniu.cregskin.com/image-20201205100321810.png" alt="image-20201205100321810" style="zoom:25%;" />

### 贝塞尔曲线性质

+ 插值端点

  + 规定必须过起点终点 b(0)  b(1)

+ 与末端线段相切 $b'(0) = 3 (b_1 - b_0) ; b'(1) = 3 (b_3 - b_2)$

+ 对已经绘制完成的贝塞尔曲线各点做仿射变换，得出的效果与先对控制点做仿射变换再进行绘制一样**（投影变换不可以！）**

  Affine Map = Linear map + Translate map

+ 凸壳特性 Convex Hull

  贝塞尔曲线一定在控制点内  

  包围所有已知点的最小凸多边形

  <img src="https://www.qiniu.cregskin.com/image-20201230210748869.png" alt="image-20201230210748869" style="zoom:25%;" />



问题：

控制点多，不易控制

<img src="https://www.qiniu.cregskin.com/image-20201205101445006.png" alt="image-20201205101445006" style="zoom:15%;" />

此时绘制的曲线，受控制点影响较小，不容易使用单个控制点控制曲线



如何解决？

## 2.3 分段贝塞尔曲线 Piecewise bezier curvesl

每四个控制点控制一段贝塞尔曲线

<img src="https://www.qiniu.cregskin.com/image-20201230211401711.png" alt="image-20201230211401711" style="zoom: 50%;" />



问题：如何确保分段贝塞尔曲线是光滑的？

答：两段贝塞尔曲线的控制点共线 （C1连续）

<img src="https://www.qiniu.cregskin.com/image-20201205101812594.png" alt="image-20201205101812594" style="zoom:25%;" />



### 分段贝塞尔曲线的连续性 continuity

#### $C^0$ 连续

在几何上，前一段贝塞尔曲线的末端，与后一段贝塞尔曲线的起始端在同一个点

<img src="https://www.qiniu.cregskin.com/image-20201205103423409.png" alt="image-20201205103423409" style="zoom:25%;" />

#### C1连续

满足C0连续的前提下，前一段曲线后两个控制点$$a_{n-1}、a_{n}$$、后一段曲线前两个控制点$$b_0、b_1$$。有如下关系：
$$
a_{n-1}到a_n的距离l_{a_{n-1}a_{n}}=b_{0}到b_{1}的距离l_{b_{0}b_{1}} \\ 
a_{n-1}、a_{n}、b_{0}、b_{1} 共线 \\ 
a_{n}、b_{0}重合，且与a_{n-1}、b_{1}中点重合
$$


<img src="https://www.qiniu.cregskin.com/image-20201205103735950.png" alt="image-20201205103735950" style="zoom:25%;" />







## 2.3 样条 splines, etc

贝塞尔曲线的弊端：

拖动控制点，整条曲线都会改变，尤其是控制点很多的时候。这样的性质使贝塞尔曲线缺乏**局部性**

解决办法：分段贝塞尔曲线，为贝塞尔曲线整体增加**局部性 **

另一种解决办法：B样条，贝塞尔曲线的扩展，在一定范围内保持**局部性**



B样条：通过一组给定点并具有一定数量连续导数的连续曲线。

+ 满足一定连续性
+ 一条使用控制点控制的曲线
+ 具有贝塞尔曲线的性质





# 3. Surfaces 表面

曲面如何得到？

<img src="https://www.qiniu.cregskin.com/image-20201205105028073.png" alt="image-20201205105028073" style="zoom:25%;" />



## 3.1 贝塞尔曲面 Bezier surfaces

<img src="https://www.qiniu.cregskin.com/image-20201205105125376.png" alt="image-20201205105125376" style="zoom:25%;" />

如何从贝塞尔曲线到贝塞尔曲面？

总体：在两个方向上应用贝塞尔曲线，即二次插值

1. 定义 4 ✖️ 4个控制点

   <img src="https://www.qiniu.cregskin.com/image-20201230213411436.png" alt="image-20201230213411436" style="zoom: 33%;" />

2. 在四个行上，用各自四个控制点定义四条贝塞尔曲线

   <img src="https://www.qiniu.cregskin.com/image-20201230213505647.png" alt="image-20201230213505647" style="zoom:33%;" />

3. 以不同的 t 下，行贝塞尔曲线的四个点为控制点，再做一条贝塞尔曲线

   <img src="https://www.qiniu.cregskin.com/image-20201230213616541.png" alt="image-20201230213616541" style="zoom:33%;" />

4. 最终，蓝色的贝塞尔曲线绘制成曲面

   <img src="https://www.qiniu.cregskin.com/image-20201230213703505.png" alt="image-20201230213703505" style="zoom:33%;" />





<img src="https://www.qiniu.cregskin.com/image-20201230213738857.png" alt="image-20201230213738857" style="zoom:33%;" />



问题：如何保证不同的曲面不留缝隙？



## 3.2 Triangles & quads

### 网格细分 Mesh Subdivision

### 网格简化 Mesh simplification

### 网格正规化 Mesh regularization

