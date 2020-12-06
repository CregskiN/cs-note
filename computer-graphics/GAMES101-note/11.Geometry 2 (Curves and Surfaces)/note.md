# Curves and Surfaces

[TOC]



# Last Lecture

+ 初步介绍几何
  + 几何的例子
  + 几何的表示方法
    + 隐式几何
    + 显式几何





# 1. 显式几何 Explict Representations

## 1.1 点云 Point Cloud

非常多、密集的点(x, y, z)

<img src="https://www.qiniu.cregskin.com/image-20201205093853455.png" alt="image-20201205093853455" style="zoom:25%;" />

+ 三维空间扫描，就是点云
+ 给出点云，如何描述出一个面？





## 1.2 多边形面 Polygon Mesh

应用最多的显式表示

<img src="https://www.qiniu.cregskin.com/image-20201205094017450.png" alt="image-20201205094017450" style="zoom:25%;" />



## 1.3 顶点、纹理、法线的对应的文件格式

<img src="https://www.qiniu.cregskin.com/image-20201205094337547.png" alt="image-20201205094337547" style="zoom:35%;" />





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



显式几何，要么直接给点，要么直接给参数

给定两个点，一个控制点

<img src="https://www.qiniu.cregskin.com/image-20201205095352602.png" alt="image-20201205095352602" style="zoom:25%;" />



给定两个点，两个控制点

<img src="https://www.qiniu.cregskin.com/image-20201205095514086.png" alt="image-20201205095514086" style="zoom:25%;" />



递归过程：

<img src="https://www.qiniu.cregskin.com/image-20201205095925025.png" alt="image-20201205095925025" style="zoom:25%;" />

给出 n+1 个控制点

<img src="https://www.qiniu.cregskin.com/image-20201205100206445.png" alt="image-20201205100206445" style="zoom:25%;" />

<img src="https://www.qiniu.cregskin.com/image-20201205100250971.png" alt="image-20201205100250971" style="zoom:25%;" />



伯恩斯坦多项式中的一项

<img src="https://www.qiniu.cregskin.com/image-20201205100321810.png" alt="image-20201205100321810" style="zoom:25%;" />

### 贝塞尔曲线性质

+ 规定必须过起点终点 b(0)  b(1)

+ 与末端线段相切 $b'(0) = 3 (b_1 - b_0) ; b'(1) = 3 (b_3 - b_2)$

+ 对控制点做仿射变换，由控制点得出的曲线也会有仿射变换。**投影变换除外！**

+ 凸壳特性：贝塞尔曲线一定在控制点内  

  包围所有已知点的最小凸多边形



问题：

控制点多，不易控制

<img src="https://www.qiniu.cregskin.com/image-20201205101445006.png" alt="image-20201205101445006" style="zoom:15%;" />

## 2.3 分段贝塞尔曲线 Piecewise bezier curvesl

<img src="https://www.qiniu.cregskin.com/image-20201205101539865.png" alt="image-20201205101539865" style="zoom:25%;" />



问题：如何确保分段贝塞尔曲线是光滑的？

答：两段贝塞尔曲线的控制点共线 （C1连续）

<img src="https://www.qiniu.cregskin.com/image-20201205101812594.png" alt="image-20201205101812594" style="zoom:25%;" />



### 分段贝塞尔曲线的连续性

#### C0连续

在几何上，前一段贝塞尔曲线的末端，与后一段贝塞尔曲线的起始端在同一个点

<img src="https://www.qiniu.cregskin.com/image-20201205103423409.png" alt="image-20201205103423409" style="zoom:25%;" />

#### C1连续

满足C0连续的前提下，前一段贝塞尔曲线末端切线、末端控制点、后一段贝塞尔曲线起始端、起始端控制点共线

也可以说前一段贝塞尔曲线末端一阶导数，与后一段贝塞尔曲线起始端一阶导数相等

<img src="https://www.qiniu.cregskin.com/image-20201205103735950.png" alt="image-20201205103735950" style="zoom:25%;" />







## 2.3 样条 B-splines, etc

贝塞尔曲线的弊端：

拖动控制点，整条曲线都会改变，尤其是控制点很多的时候

解决办法：分段贝塞尔曲线，为贝塞尔曲线整体增加**局部性**

另一种解决办法：B样条，贝塞尔曲线的扩展，在一定范围内保持**局部性**



B样条：通过一组给定点并具有一定数量连续导数的连续曲线。

+ 满足一定连续性
+ 一条使用控制点控制的曲线
+ 具有贝塞尔曲线的性质





















# 3. Surfaces 表面

<img src="https://www.qiniu.cregskin.com/image-20201205105028073.png" alt="image-20201205105028073" style="zoom:25%;" />



## 3.1 贝塞尔曲面 Bezier surfaces

如何从贝塞尔曲线到贝塞尔曲面

<img src="https://www.qiniu.cregskin.com/image-20201205105125376.png" alt="image-20201205105125376" style="zoom:25%;" />



## 3.2 Triangles & quads

### 网格细分 Mesh Subdivision

### 网格简化 Mesh simplification

### 网格正规化 Mesh regularization

