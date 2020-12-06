# Geometry

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



## 1.1 光线 lighting

### Environment Map

Environment Map

yota 茶壶

![image-20201130172005549](https://www.qiniu.cregskin.com/image-20201130172005549.png)





环境光

记录在球面上

<img src="https://www.qiniu.cregskin.com/image-20201130172155821.png" alt="image-20201130172155821" style="zoom:35%;" />





### Spherical Environment Map

把环境光存储在球面

<img src="https://www.qiniu.cregskin.com/image-20201130172222267.png" alt="image-20201130172222267" style="zoom:25%;" />



展开

<img src="https://www.qiniu.cregskin.com/image-20201130172243192.png" alt="image-20201130172243192" style="zoom:25%;" />

靠近球面极点的位置，展开后发生扭曲



解决办法：把环境光记录在球所处的立方体表面

### Cube Map

<img src="https://www.qiniu.cregskin.com/image-20201130172433817.png" alt="image-20201130172433817" style="zoom:33%;" />

问题：来自某一个方向的光照，可以在球面方便的获知，但在立方体中需要额外计算才能获知



## 1.2 凹凸贴图

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





### 细节

凹凸贴图定义了纹理点法线高度的相对移动

<img src="https://www.qiniu.cregskin.com/image-20201130173824347.png" alt="image-20201130173824347" style="zoom: 40%;" />



### flatland case

假设一个平面上，点P的法线 n(p) = (0, 1)

<img src="https://www.qiniu.cregskin.com/image-20201130174440940.png" alt="image-20201130174440940" style="zoom:33%;" />



切线逆时针旋转90度，就是法线



### 3D

如果是3D立体bi表面？

<img src="https://www.qiniu.cregskin.com/image-20201130174616698.png" alt="image-20201130174616698" style="zoom:33%;" />



## 1.3 位移贴图 Displacement Mapping

真的对顶点做移动

![image-20201130174902733](https://www.qiniu.cregskin.com/image-20201130174902733.png)



上图可见，

**凹凸贴图**的阴影没有改变几何形体，在阴影时会露馅

**位移贴图**是真实地改变三角形顶点位置



Dynamic Tesselation 动态曲面细分，细分小的三角形，使用位移贴图，减少计算量。DirectX 使用



## 1.4 三维程序噪波 + 实体建模

<img src="https://www.qiniu.cregskin.com/image-20201130175343974.png" alt="image-20201130175343974" style="zoom:33%;" />



## 1.5 提供预计算着色

处理阴影等

<img src="https://www.qiniu.cregskin.com/image-20201130175541944.png" alt="image-20201130175541944" style="zoom: 33%;" />



## 1.6 三维纹理与体绘制

<img src="https://www.qiniu.cregskin.com/image-20201130175537043.png" alt="image-20201130175537043" style="zoom:33%;" />





---



# 2. Introduction to geometry

## 2.1 Examples of Geometry

<img src="../../../../../Library/Application Support/typora-user-images/image-20201205084231032.png" alt="image-20201205084231032" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084240501.png" alt="image-20201205084240501" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084255356.png" alt="image-20201205084255356" style="zoom:25%;" /><img src="../../../../../Library/Application Support/typora-user-images/image-20201205084334828.png" alt="image-20201205084334828" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084345599.png" alt="image-20201205084345599" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084429463.png" alt="image-20201205084429463" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084605276.png" alt="image-20201205084605276" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084701737.png" alt="image-20201205084701737" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201205084737148.png" alt="image-20201205084737148" style="zoom:25%;" />





+ 复杂几何的描述
+ 存储



## 2.2 几何分类

### 隐式几何 Implicit

不告诉点具体位置，告诉点的函数关系，如<img src="https://www.qiniu.cregskin.com/image-20201205085201718.png" alt="image-20201205085201718" style="zoom: 25%;" />，

<img src="https://www.qiniu.cregskin.com/image-20201205085338923.png" alt="image-20201205085338923" style="zoom:25%;" />



**缺点**：

很难描述出这个面是什么形状

<img src="https://www.qiniu.cregskin.com/image-20201205090540591.png" alt="image-20201205090540591" style="zoom:25%;" />



**优点**：

很容易判断点面内、外、面上

<img src="https://www.qiniu.cregskin.com/image-20201205090020526.png" alt="image-20201205090020526" style="zoom:25%;" />





### 显式几何 Explicit

显式：通过参数映射，定义的表面



下图，马鞍面

<img src="https://www.qiniu.cregskin.com/image-20201205090128158.png" alt="image-20201205090128158" style="zoom:25%;" />



<img src="https://www.qiniu.cregskin.com/image-20201205090249148.png" alt="image-20201205090249148" style="zoom:25%;" />





显式很难判断点在面内外：

<img src="https://www.qiniu.cregskin.com/image-20201205090330417.png" alt="image-20201205090330417" style="zoom: 25%;" />





### 小结

根据需要，选择显式几何、隐式几何



## 2.3 Constructive Solid Geometry (CSG)

使用已知的基本几何，布尔运算，形成新的几何。应用非常广泛！



<img src="https://www.qiniu.cregskin.com/image-20201205090805769.png" alt="image-20201205090805769" style="zoom:25%;" />



## 2.4 距离函数 Distance Functions (Implict)

距离函数：空间中任意一点，到将要表述的物体表面的最小距离。点在物体内部，值为负，反之为正

<img src="https://www.qiniu.cregskin.com/image-20201205091408293.png" alt="image-20201205091408293" style="zoom:23%;" />





<img src="https://www.qiniu.cregskin.com/image-20201205091650667.png" alt="image-20201205091650667" style="zoom:25%;" />



<img src="https://www.qiniu.cregskin.com/image-20201205091708735.png" alt="image-20201205091708735" style="zoom:25%;" />









## 2.5 水平集 Level Set Methods (Implicit)

类似地理的等高线

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













