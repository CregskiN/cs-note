# Geometry 3

[TOC]





# Last Lecture

在三角形面上有更多细分

+ Mesh Subdivision 平面细化

  <img src="https://www.qiniu.cregskin.com/image-20201205172636132.png" alt="image-20201205172636132" style="zoom:25%;" />

+ Mesh Simplification 平面简化

  + 一定要保持不同三角形的连接关系
  + **可能导致牛角丢失**

  <img src="https://www.qiniu.cregskin.com/image-20201205172629335.png" alt="image-20201205172629335" style="zoom:25%;" />

+ Mesh Regularization 平面规格化

  **耳朵角丢失**

  <img src="https://www.qiniu.cregskin.com/image-20201205172648171.png" alt="image-20201205172648171" style="zoom:25%;" />



# 1. 对面的处理

## 1.1 网格细分 Mesh Subdivision

1. 用更多的三角形细分原平面
2. 让细分出的三角形位置发生一点变化以让模型表面更圆滑

<img src="https://www.qiniu.cregskin.com/image-20201205174000461.png" alt="image-20201205174000461" style="zoom:20%;" />

### 第一种细分：Loop Subdivision

1. 先细分：产生很多新的三角形

   <img src="https://www.qiniu.cregskin.com/image-20201205173102764.png" alt="image-20201205173102764" style="zoom:25%;" />

2. 再调整：**调整三角形顶点位置（新旧顶点分别处理）**，显示出凹凸

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



### 第二种细分：Catmull-Clark Subdivision (General Mesh)

Loop Subdivision 只能完成对于三角形的细分。

Catmull-Clark Subdivision 完成非三角形即普遍情况下的细分

有两个定义：

1. **非四边形面** Non-quad face

2. **奇异点** Extraordinary Vertex，即度不为4的顶点

   <img src="https://www.qiniu.cregskin.com/image-20201205175438402.png" alt="image-20201205175438402" style="zoom:25%;" />

   细分操作：

   + 取 Non-quad face 的中点
   + 取每条线的中点
   + 将以上中点连接

   <img src="https://www.qiniu.cregskin.com/image-20201205175644316.png" style="zoom: 25%;" />

   经过一次 Catmull-Clack Subdivision

   + 奇异点 extraordinary vertices 数量有何变化？

     奇异点 extraordinary vertices 由两个变成四个

   + 奇异点 extraordinary vertices 的度如何？

     + 两个旧的奇异点，度仍为 5
     + 两个新的奇异点，从非四边形衍生而出，度数为非四边形边数。此处为 3

   + 剩多少个非四边形面？

     所有的非四边形面都消失了。即非四边形面引入奇异点后，就消失了】

   <img src="https://www.qiniu.cregskin.com/image-20201205221312518.png" alt="image-20201205221312518" style="zoom:25%;" />

   <img src="https://www.qiniu.cregskin.com/image-20201205221321222.png" alt="image-20201205221321222" style="zoom:25%;" />

   <img src="https://www.qiniu.cregskin.com/image-20201205221456999.png" alt="image-20201205221456999" style="zoom:25%;" />

   点分三类：

   1. 在面中心的点

      处理方式：面对应各顶点的平均

   2. 在边中心的点

      处理方式：边的两端点和临面中心的点做平均

   3. 旧的点

   

   ### 两种细分的区别

   Loop Subdivision 只能应用于对三角形的细分

   Catmull-Clark Subdivision 能适用于所有多边形细分

   <img src="https://www.qiniu.cregskin.com/image-20201205221512225.png" alt="image-20201205221512225" style="zoom:24%;" />

   

   

   ### 第一个使用细分完成的动画作品

   皮克斯公司

   <img src="https://www.qiniu.cregskin.com/image-20201205221708190.png" alt="image-20201205221708190" style="zoom:25%;" />
   
   







## 1.2 网格简化 Mesh Simplification

<img src="https://www.qiniu.cregskin.com/image-20201205221849972.png" alt="image-20201205221849972" style="zoom:25%;" />

上图表示的shading：

1. 30000 个 flat shading
2. 3000 个
3. 300 个
4. 30 个

**三角形越多越好吗？**

答：不一定。不同场景下使用合适的简化模型

如，距离很远，300个三角形表示的骷髅就可以

问题：在一定距离，使用3000和300个三角形表示骷髅，如何有一个平滑过度的切换效果？



与 MipMap 的联系

原理上，观察位置与shading 像素对应的位置距离较远，用一个“范围”就可以表示



对于非整数分层的 Mipmap，可以用插值获取一个平滑过渡的结果（二次插值）

那对于不同距离（分层）的几何，如何得到一个平滑过渡？这是一个难题



如何做几何的简化？

### 边坍缩 edge collaps

<img src="https://www.qiniu.cregskin.com/image-20201205222159787.png" alt="image-20201205222159787" style="zoom:25%;" />



### 二次误差度量 Quadric Error Metrics

**二次误差：点到与其相关面的距离的平方和**

Edge Collaps 需要考虑的问题：

1. 在简化过程中，会引入多少几何误差 Geometric Error？
2. 简单地平均旧顶点，获取新顶点似乎不是一个好主意
3. 引入**二次误差度量**：新顶点的位置，应该保证到各旧边的距离的平方和最小

<img src="https://www.qiniu.cregskin.com/image-20201205222356683.png" alt="image-20201205222356683" style="zoom:25%;" />



边坍缩 edge collapse 过程中的思考

1. 边坍缩的花费如何？
2. 策略：
   + 计算每条边的中点，测量二次误差 quadric error
3. 更优的策略
   + 假设出每个点坍缩后的二次度量误差，并放入**优先队列**
   + 选择二次度量误差 quadric error 最小的点，坍缩。并**更新优先队列**

<img src="https://www.qiniu.cregskin.com/image-20201205222448786.png" alt="image-20201205222448786" style="zoom:25%;" />

**边坍缩的方法就是通过取局部最优解，试图获取一个全局最优解。实际上这种贪心算法并不一定获取全局最优解**



![image-20210103215128350](https://www.qiniu.cregskin.com/image-20210103215128350.png)



shading 阶段是如何得到阴影效果的？

# 2. 阴影

之前光栅化阶段，尤其是着色 shading 过程，只考虑了局部因素，

即影响 shading 的因素：shading point、摄像机位置、光源。

而不考虑：此物体其他部分与 shading point 相对位置（物体其他部分挡在了光源和 shading point 之间）等等。



解决阴影的方法：Shadow Mapping，对应的结构 Shadow Map



## 2.1 Shadow Mapping

+ 是什么？

  是一种图像空间 Image-space 的算法

  + 阴影计算过程中不知道场景的几何结构
  + 需要解决阴影的走样问题 Aliasing Artifacts

+ 关键思想：

  + 不在阴影中的点：光源可以看到、摄像机也可以看到
  + 在阴影中点：光源看不到，摄像机可以看到

+ Shadow Mapping 的缺陷

  + 只能处理点光源下阴影

    这种阴影通常有明显的阴影边界（**硬阴影**）



### Pass 1: Render from Light

从光源看向整个场景。记录下从光源观测各个点的**深度**（Z-Buffer）。由此，获取一张从光源处观测的深度图

<img src="https://www.qiniu.cregskin.com/image-20210103220735828.png" alt="image-20210103220735828" style="zoom:35%;" />

<img src="https://www.qiniu.cregskin.com/image-20210103221215076.png" alt="image-20210103221215076" style="zoom:33%;" />

### Pass 2A: Render from Eye

<img src="https://www.qiniu.cregskin.com/image-20210103221417800.png" alt="image-20210103221417800" style="zoom:33%;" />

从真正的摄像机位置，观测到上图示两个黑色点



<img src="https://www.qiniu.cregskin.com/image-20210103221428130.png" alt="image-20210103221428130" style="zoom:33%;" />

将这黑色点（图示橙色线连接的点）投影回光源位置的成像平面上（即寻找这个点在深度图中对应的像素）

+ 在深度图上找到了黑色点对应的像素！
  + 计算黑色点到光源位置的深度，与深度图中的深度对比
    + 相等：该点同时被摄像机和光源看到。**没有处在阴影中**

<img src="https://www.qiniu.cregskin.com/image-20210103221540371.png" alt="image-20210103221540371" style="zoom:33%;" />

将红色线连接的点投影回光源成像平面上，寻找其在深度图中对应的像素

+ 在深度图上找到了黑色点对应的像素！
  + 计算该点到光源位置的深度，与深度图中的深度对比 
    + 不相等：说明该点被摄像机看到，但没有被光源看到。**处在阴影中**





## 2.2 可视化阴影贴图 Visualizing Shadow Mapping

场景：

<img src="https://www.qiniu.cregskin.com/image-20210103222610898.png" alt="image-20210103222610898" style="zoom:33%;" />

加阴影和不加阴影的 shading 结果：

<img src="https://www.qiniu.cregskin.com/image-20210103222625599.png" alt="image-20210103222625599" style="zoom:33%;" />



从光源位置观测（大图）、从相机位置观测（小图）：

![image-20210103222720558](https://www.qiniu.cregskin.com/image-20210103222720558.png)



从光源位置观测的深度图（大图）、从光源位置观测的实际图像（小图）：

<img src="https://www.qiniu.cregskin.com/image-20210103222814614.png" alt="image-20210103222814614" style="zoom:33%;" />





从相机位置观测深度对比结果：

<img src="https://www.qiniu.cregskin.com/image-20210103223004217.png" alt="image-20210103223004217" style="zoom:33%;" />





### Shadow Mapping 在工业界的使用

<img src="https://www.qiniu.cregskin.com/image-20210103223614120.png" alt="image-20210103223614120" style="zoom:33%;" />

**存在一种阴影质量的选项**



### Shadow Mapping 存在的问题：

1. 数值精度。在对比点到光源的深度，与深度图中记录深度的大小时，使用的是浮点数

2. 光源深度图的分辨率（游戏中阴影质量选项）

   + 分辨率很大

     开销大

   + 分辨率很小

     产生有锯齿的阴影

3. 受点光源局限只能作出硬阴影效果（左图），而不能做出更符合真实情况的软阴影（右图）

   <img src="https://www.qiniu.cregskin.com/image-20210103223848437.png" alt="image-20210103223848437" style="zoom: 50%;" /><img src="https://www.qiniu.cregskin.com/image-20210103223902352.png" alt="image-20210103223902352" style="zoom: 50%;" />

   软阴影原理：

   <img src="https://www.qiniu.cregskin.com/image-20210103224132101.png" alt="image-20210103224132101" style="zoom:50%;" />

   在光源有大小时，出现本影 Umbra 和半阴影区域 Penumbra。以上图月食现象为例，在成像面（地球）上，有三个区域本影区域、半影区域、无阴影区域，对应三种现象：

   + 本影区域：全黑
   + 半影区域：从靠近本影到靠近无阴影区域呈现由暗到亮的过渡
   + 无阴影区域：顾名思义



