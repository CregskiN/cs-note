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



## 2. 凹凸贴图

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



## 3. 位移贴图 Displacement Mapping

真的对顶点做移动

![image-20201130174902733](https://www.qiniu.cregskin.com/image-20201130174902733.png)



上图可见，

**凹凸贴图**的阴影没有改变几何形体，在阴影时会露馅

**位移贴图**是真实地改变三角形顶点位置



Dynamic Tesselation 动态曲面细分，细分小的三角形，使用位移贴图，减少计算量。DirectX 使用



## 4. 三维程序噪波 + 实体建模

<img src="https://www.qiniu.cregskin.com/image-20201130175343974.png" alt="image-20201130175343974" style="zoom:33%;" />

## 提供预计算着色

处理阴影等

<img src="https://www.qiniu.cregskin.com/image-20201130175541944.png" alt="image-20201130175541944" style="zoom: 33%;" />



## 三维纹理与体绘制

<img src="https://www.qiniu.cregskin.com/image-20201130175537043.png" alt="image-20201130175537043" style="zoom:33%;" />

