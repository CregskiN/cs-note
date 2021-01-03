# Geometry1



[TOC]



# Last Lectures

+ Shading 1 & 2
  + Blinn-Phone reflectance model 布林-冯模型
  + Shading models / grequencies 着色频率
  + Graphics Pipeline 实时渲染管线 / 图形化管线
  + Texture Mapping 纹理映射
+ Shading 3
  + Barycentric coordinates 重心坐标
  + Texture Antialiasing (MipMap、RipMap) 纹理反走样
  + Applications of texture



# 1. 纹理应用 Applications of Texture

![image-20201130170140591](https://www.qiniu.cregskin.com/image-20201130170140591.png)

给一个网格

+ flat shading
+ phone shading 

<img src="https://www.qiniu.cregskin.com/image-20201215094731023.png" alt="image-20201215094731023" style="zoom:25%;" />



什么是纹理？

是一块区域，可以范围查询、点查询





## 1.1 光线 lighting

### 环境贴图 Environment Map

Environment Map

yota 茶壶 犹他大学做的

<img src="https://www.qiniu.cregskin.com/image-20201130172005549.png" alt="image-20201130172005549" style="zoom: 50%;" />

认为光源无限远





环境光

记录在球面上

<img src="https://www.qiniu.cregskin.com/image-20201130172155821.png" alt="image-20201130172155821" style="zoom:35%;" />





### Spherical Environment Map

把环境光存储在球面

<img src="https://www.qiniu.cregskin.com/image-20201130172222267.png" alt="image-20201130172222267" style="zoom:25%;" />



展开

<img src="https://www.qiniu.cregskin.com/image-20201130172243192.png" alt="image-20201130172243192" style="zoom:25%;" />

问题：靠近球面极点的位置，展开后发生扭曲



解决办法：把环境光记录在球所处的立方体表面

### Cube Map

<img src="https://www.qiniu.cregskin.com/image-20201130172433817.png" alt="image-20201130172433817" style="zoom:33%;" />

<img src="https://www.qiniu.cregskin.com/image-20201215095446972.png" alt="image-20201215095446972" style="zoom:25%;" />

问题：来自某一个方向的光照，可以在球面方便的获知，但在立方体中需要额外计算才能获知

lint：天空盒 sky box



## 1.2 凹凸贴图 bump mapping / normal mapping

定义一个shading point的相对高度，扰动法线，从而改变渲染表面。但实际上，顶点位置没变。



需求：绘制一个表面凹凸的球

<img src="https://www.qiniu.cregskin.com/image-20201130172702445.png" alt="image-20201130172702445" style="zoom:33%;" />

原始策略：使用巨量的三角形，表示出一个凹凸的球。相比光滑的球，使用三角形多得多得多



通常，一个纹理贴图存储的只是颜色

+ 如果它存储了高度/正常值呢？
+ 凹凸 / 法线贴图
+ 伪造详细的几何图形

如果使用凹凸贴图，可以设定三角形的纹理坐标的相对高度

如此，在不把几何形体变复杂的前提下，使用一个复杂的纹理，定义该纹理点的相对高度

Shading 过程中，查询到纹理贴图上不同高度的法线，影响最终 Shading

实际上真实世界的法线，是光滑球的法线，贴图提供了一个虚拟法线





### 实现细节

凹凸贴图定义了：

+ 每个 shading point 的相对高度，并通过相对高度扰动法线

+ 如何实现？

  下图：黑色箭头是原法线，红色箭头是扰动后的法线

<img src="https://www.qiniu.cregskin.com/image-20201130173824347.png" alt="image-20201130173824347" style="zoom: 40%;" />





### 一个变化的二维函数 flatland case

下图中：蓝色曲线为凹凸贴图定义的平面

假设一个平面上：

+ 点P原法线 n(p) = (0, 1)
+ 点p处的导数 dp
+ 将倒数dp逆时针旋转90度，再单位化，就是扰动后的法线

<img src="https://www.qiniu.cregskin.com/image-20201130174440940.png" alt="image-20201130174440940" style="zoom:33%;" />
$$
dp：位移贴图中定义p点的导数 \\
c：控制位移贴图影响程度的参数 \\
\vec{n}：位移贴图定义的法线
$$






切线逆时针旋转90度，就是法线



### 3D

如果是3D立体bi表面？

+ 原三维空间中，点p坐标(0, 0, 1)
+ 点p每移动单位距离，u移动单位距离
+ 最终扰动后的法线n为

<img src="https://www.qiniu.cregskin.com/image-20201130174616698.png" alt="image-20201130174616698" style="zoom:33%;" />





## 1.3 位移贴图 Displacement Mapping

真的对顶点做移动

要求：需要模型足够细，细到顶点定义频率，要高于纹理频率

<img src="https://www.qiniu.cregskin.com/image-20201130174902733.png" alt="image-20201130174902733" style="zoom:50%;" />



上图可见，

**凹凸贴图**的阴影没有改变几何形体，在阴影时会露馅

**位移贴图**是真实地改变三角形顶点位置



Dynamic Tesselation 动态曲面细分，细分成更小的三角形，使用位移贴图，减少计算量。DirectX 使用



## 1.4 三维程序噪波 + 实体建模

<img src="https://www.qiniu.cregskin.com/image-20201130175343974.png" alt="image-20201130175343974" style="zoom:33%;" />



## 1.5 提供预计算着色

处理阴影等

<img src="https://www.qiniu.cregskin.com/image-20201130175541944.png" alt="image-20201130175541944" style="zoom: 33%;" />



## 1.6 三维纹理与体绘制

<img src="https://www.qiniu.cregskin.com/image-20201130175537043.png" alt="image-20201130175537043" style="zoom:33%;" />





---



# 2. 几何的介绍 Introduction to geometry

## 2.1 Examples of Geometry

<img src="https://www.qiniu.cregskin.com/image-20201205084231032.png" alt="image-20201205084231032" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084240501.png" alt="image-20201205084240501" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084255356.png" alt="image-20201205084255356" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084334828.png" alt="image-20201205084334828" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084345599.png" alt="image-20201205084345599" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084429463.png" alt="image-20201205084429463" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084605276.png" alt="image-20201205084605276" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084701737.png" alt="image-20201205084701737" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084737148.png" alt="image-20201205084737148" style="zoom:25%;" />



+ 复杂几何的描述
+ 存储



## 2.2 几何分类

### 隐式几何 Implicit

不告诉点具体位置，告诉点的函数关系，如<img src="https://www.qiniu.cregskin.com/image-20201205085201718.png" alt="image-20201205085201718" style="zoom: 25%;" />，

<img src="https://www.qiniu.cregskin.com/image-20201205085338923.png" alt="image-20201205085338923" style="zoom:25%;" />



**缺点**：

很难描述出这个面是什么形状（平面、曲面）

<img src="https://www.qiniu.cregskin.com/image-20201205090540591.png" alt="image-20201205090540591" style="zoom:25%;" />



**优点**：

很容易判断点面内、外、面上

<img src="https://www.qiniu.cregskin.com/image-20201205090020526.png" alt="image-20201205090020526" style="zoom:25%;" />





### 显式几何 Explicit

显式有两种：

1. 直接定义三角形三个顶点
2. 通过参数映射，定义的表面

下图，马鞍面

<img src="https://www.qiniu.cregskin.com/image-20201205090128158.png" alt="image-20201205090128158" style="zoom:25%;" />

把所有uv对应的xyz对应（obj文件中给出了对应关系），得出马鞍面



再举例 uv 和 三维坐标 映射：

<img src="https://www.qiniu.cregskin.com/image-20201205090249148.png" alt="image-20201205090249148" style="zoom:25%;" />



**显示几何 explicit 的优点：**

+ 显式很难判断点在面内外

<img src="https://www.qiniu.cregskin.com/image-20201205090330417.png" alt="image-20201205090330417" style="zoom: 25%;" />





### 小结

1. 隐式几何 implicit 

   <img src="https://www.qiniu.cregskin.com/image-20201225113338576.png" alt="image-20201225113338576" style="zoom:50%;" />

   🌰：

   <img src="https://www.qiniu.cregskin.com/image-20201225113518721.png" alt="image-20201225113518721" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201225113532434.png" alt="image-20201225113532434" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201225113544885.png" alt="image-20201225113544885" style="zoom:25%;" />

2. 显示几何 explicit 

   1. 直接给出顶点，组成平面

   2. 给出映射关系，如uv和xyz

      <img src="https://www.qiniu.cregskin.com/image-20201225113415924.png" alt="image-20201225113415924" style="zoom:50%;" />





**更复杂的模型如何构建？用函数？**

## 2.3 构造立体几何 Constructive Solid Geometry (CSG) ( Implicit )

使用已知的基本几何，布尔运算，形成新的几何。应用非常广泛！



<img src="https://www.qiniu.cregskin.com/image-20201205090805769.png" alt="image-20201205090805769" style="zoom:25%;" />



## 2.4 距离函数 Distance Functions (Implict)

距离函数：空间中任意一点，到将要表述的物体表面的最小距离。距离有正负，点在物体内部，值为负，反之为正

<img src="https://www.qiniu.cregskin.com/image-20201205091408293.png" alt="image-20201205091408293" style="zoom:23%;" />



blending 融合

<img src="https://www.qiniu.cregskin.com/image-20201205091650667.png" alt="image-20201205091650667" style="zoom:25%;" />



<img src="https://www.qiniu.cregskin.com/image-20201205091708735.png" alt="image-20201205091708735" style="zoom:25%;" />







**距离函数 blend 之后，如何恢复成原来的函数？**

## 2.5 水平集 Level Set Methods (Implicit)

函数表述写在格子上，类似地理的等高线

<img src="https://www.qiniu.cregskin.com/image-20201205092013464.png" alt="image-20201205092013464" style="zoom:25%;" />



水平集在**纹理**中的应用

<img src="https://www.qiniu.cregskin.com/image-20201205092057185.png" alt="image-20201205092057185" style="zoom:25%;" />



<img src="https://www.qiniu.cregskin.com/image-20201205092130923.png" alt="image-20201205092130923" style="zoom: 25%;" />





## 2.6 分型 Fractal (Implicit)

<img src="https://www.qiniu.cregskin.com/image-20201205092200000.png" alt="image-20201205092200000" style="zoom: 25%;" />





## 2.7 小结

+ 隐式几何
  + 优点
    + 抽象描述。节省存储
    + 精准的位置查询。查询出点在物体表面、物体内、物体外、到物体表面的最小距离（距离函数）
    + 方便对光线和物体表面求交
    + 对于简单的形状，准确描述，如弧度
    + 易于处理拓扑变化
  + 缺点
    + 无法直观得出隐函数表示的物体形状













