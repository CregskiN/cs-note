# Geometry 3

[TOC]





# Last Lecture

在三角形面上有更多细分

+ Mesh Subdivision

  <img src="https://www.qiniu.cregskin.com/image-20201205172636132.png" alt="image-20201205172636132" style="zoom:25%;" />

+ Mesh Simplification

  **可能导致牛角丢失**

  <img src="https://www.qiniu.cregskin.com/image-20201205172629335.png" alt="image-20201205172629335" style="zoom:25%;" />

+ Mesh Regularization

  **耳朵角丢失**

  <img src="https://www.qiniu.cregskin.com/image-20201205172648171.png" alt="image-20201205172648171" style="zoom:25%;" />



# 1. 对平面的处理

## 1.1 细分平面 Mesh Subdivision

1. 用更多的三角形细分原平面
2. 让细分出的三角形位置发生一点变化以让模型表面更圆滑

<img src="https://www.qiniu.cregskin.com/image-20201205174000461.png" alt="image-20201205174000461" style="zoom:20%;" />

### Loop Subdivision

1. 细分：产生很多新的三角形

   <img src="https://www.qiniu.cregskin.com/image-20201205173102764.png" alt="image-20201205173102764" style="zoom:25%;" />

2. **调整新的三角形顶点位置**，显示出凹凸

   <img src="https://www.qiniu.cregskin.com/image-20201205173227487.png" alt="image-20201205173227487" style="zoom:25%;" />

   + 新的顶点（三条边的终点）

     找到新的四个顶点，分别作以下**加权平均**操作：

     <img src="https://www.qiniu.cregskin.com/image-20201205174335425.png" alt="image-20201205174335425" style="zoom:20%;" />

   + 旧的顶点（大三角形三顶点）

     借助周围三角形顶点加权更新

     <img src="https://www.qiniu.cregskin.com/image-20201205174500796.png" alt="image-20201205174500796" style="zoom:20%;" />

     
     $$
     n：顶点的度（连接边的数量） \\
     u：顶点的值 \left\{ \begin{matrix} \frac{3}{16} & n = 3 \\ \frac{3}{8n} & n \ne 3  \end{matrix} \right.
     $$

   Loop Subdivision 结果

   总结起来：先细分，再调整，就是 Loop Subdivision

   ![image-20201205175150169](https://www.qiniu.cregskin.com/image-20201205175150169.png)



### Catmull-Clark Subdivision (General Mesh)

对于非三角形的细分，即普遍情况下的细分

有两个定义：

1. **非四边形面** Non-quad face

2. **奇异点** Extraordinary Vertex，即度不为4的顶点

   <img src="https://www.qiniu.cregskin.com/image-20201205175438402.png" alt="image-20201205175438402" style="zoom:25%;" />

   <img src="https://www.qiniu.cregskin.com/image-20201205175644316.png" style="zoom: 25%;" />

   经过一次 Catmull-Clack Subdivision

   + 现在有四个奇异点
   + 原两个三角形重心，度为3，原奇异点度为4
   + 四边形面全部消失了（性质）

   再多次 Catmull-Clack

   <img src="https://www.qiniu.cregskin.com/image-20201205221312518.png" alt="image-20201205221312518" style="zoom:25%;" />

   <img src="https://www.qiniu.cregskin.com/image-20201205221321222.png" alt="image-20201205221321222" style="zoom:25%;" />

   <img src="https://www.qiniu.cregskin.com/image-20201205221456999.png" alt="image-20201205221456999" style="zoom:25%;" />

   <img src="https://www.qiniu.cregskin.com/image-20201205221512225.png" alt="image-20201205221512225" style="zoom:24%;" />

   

   第一个使用细分完成的动画作品

   <img src="https://www.qiniu.cregskin.com/image-20201205221708190.png" alt="image-20201205221708190" style="zoom:25%;" />

   







## 1.2 平面简化 Mesh Simplification

<img src="https://www.qiniu.cregskin.com/image-20201205221849972.png" alt="image-20201205221849972" style="zoom:25%;" />

不同场景下使用合适的简化模型

如，距离很远，300个三角形表示的骷髅就可以

问题：在一定距离，使用3000和300个三角形表示骷髅，如何有一个平滑过度的切换效果？





如何做几何的简化？

### 边坍缩 edge collapsing

<img src="https://www.qiniu.cregskin.com/image-20201205222159787.png" alt="image-20201205222159787" style="zoom:25%;" />

### 二次误差度量 Quadric Error Metrics

<img src="https://www.qiniu.cregskin.com/image-20201205222356683.png" alt="image-20201205222356683" style="zoom:25%;" />

点到周围各个面的距离的平方和最小



<img src="https://www.qiniu.cregskin.com/image-20201205222448786.png" alt="image-20201205222448786" style="zoom:25%;" />





# 2. 阴影

Shadow Mapping

点光源

有明显的边界，称为硬阴影

点不在阴影里：摄像机可以看到点，但是光源看不到































