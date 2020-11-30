# Shading 1 (Illumination, Shading and Graphics Pipeline)

[TOC]

# 复习 Last Lectures

+ Rasterization
  + Rasterizing one Triangle 光栅化三角形
  + Sampling theory 采样原理
  + Antialiasing 反走样



# 1. 可见性 Visibility / 遮挡 occlusion

作画过程：<img src="https://www.qiniu.cregskin.com/image-20201128174357878.png" alt="image-20201128174357878" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201128174015361.png" alt="image-20201128174015361" style="zoom:25%;" />

画家算法：先整体画完远处物体，再画近处物体覆盖远处物体

<img src="https://www.qiniu.cregskin.com/image-20201128174131025.png" alt="image-20201128174131025" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201128174140814.png" alt="image-20201128174140814" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201128174151973.png" alt="image-20201128174151973" style="zoom:25%;" /><img src="https://www.qiniu.cregskin.com/image-20201128174207627.png" alt="image-20201128174207627" style="zoom:25%;" />

对立方体，画家算法是适用的



如何定义深度关系？

<img src="https://www.qiniu.cregskin.com/image-20201128174427650.png" alt="image-20201128174427650" style="zoom:25%;" />

在以上图形中，画家算法不适用



如何定义深度？

## 1.1 深度缓冲算法 Z-Buffering

+ 对每个像素来说，只存储当前像素最小深度（即最近）
+ 需要额外的缓冲池，存储每个像素的深度值
  + **frame buffer** 帧缓冲区存储颜色值
  + **depth buffer** (z-buffer) 深度缓冲区存储深度值
+ 重要提示：为了简单起见，我们假设 z 总是正的（z越小，表示越近）

<img src="https://www.qiniu.cregskin.com/image-20201128174900254.png" alt="image-20201128174900254" style="zoom:50%;" />

左图是渲染最终效果，右图深度记录图

```c++
for(each triangle T){
  for (each sample(x, y, z) in T){
    if(z < zbuffer[x, y]){ // 如果在当前三角形采样的像素点，深度大于当前z-buffer中缓存的深度
      framebuffer[x, y] = rgb; // 更新颜色缓冲区中，对应像素点[x, y]的颜色
      zbuffer[x, y] = z; // 更新深度缓冲区中，对应像素点[x, y]的深度
    }
  }
}
```

初始化 z-buffer 存储的深度是无限远。采样的三角三角形像素深度都是5，更小。更新frame buffer、z-buffer

<img src="https://www.qiniu.cregskin.com/image-20201128175408974.png" alt="image-20201128175408974" style="zoom:50%;" />

另外一个采样的三角形，一部分像素深度与已有的像素深度重叠，更新frame-buffer、z-buffer

<img src="https://www.qiniu.cregskin.com/20201128175508.png" alt="image-20201128175416287" style="zoom:50%;" />

相比于需要排序的画家算法O(logn)，深度缓冲算法与三角形绘画顺序无关，不需要排序，复杂度 O(n)



> 实际上，浮点数很难判断相等。导致无法精准区分深度



> 透明物体如何处理？Z-Buffer深度缓冲算法解决不了透明物体



# 2. 着色 Shading

不同光照下显示出不同的颜色

+ 定义：用平行线或一块颜色使插图或图表变暗或着色
+ 对不同物体，应用不同材质。不同的材质，针对光线有不同的表现。

## 2.1 基础的着色模型 - Blinn-Phong Reflectance Model

这不是一个真实准确、符合物理的模型！

<img src="https://www.qiniu.cregskin.com/image-20201128181754201.png" alt="image-20201128181754201" style="zoom:50%;" />

+ 镜面反射高光 Specular highlight

+ 漫反射 Diffuse reflection

+ 环境照明 Ambient lighting

  来自环境（桌子、墙等）的光照



### 着色点 Shading point

<img src="https://www.qiniu.cregskin.com/image-20201128182115971.png" alt="image-20201128182115971" style="zoom:60%;" />

考虑一个点的着色结果。在局部范围内，可以认为是平面

+ 光源
  + n 向量，法线

  + v 向量，观测方向 view direction

  + l 向量，光源方向 light direction

    > 表示方向的向量，都是单位向量，长度都是1

+ 物体表面相关属性

  + 颜色 color
  + 亮 shininess
  + 等 so on



> Shading is Local
>
> 不考虑其他物体存在，即是否被其他物体遮盖，显示阴影





## 2.2 照明 Illumination & 着色 Shading

### 漫反射 Diffuse Reflection

<img src="https://www.qiniu.cregskin.com/image-20201128182724228.png" alt="image-20201128182724228" style="zoom:50%;" />

#### 光线角度与Shading point

显示出不同的亮度。入射光携带能量，一部分被物体表面吸收，一部分被反射。

反射的能量大小，与 Shading point 和光线成的夹角有关

+ Lambert's consine law

<img src="https://www.qiniu.cregskin.com/image-20201128183617269.png" alt="image-20201128183617269" style="zoom:35%;" />



#### 光强、距离，与Shading point



<img src="https://www.qiniu.cregskin.com/image-20201128183750095.png" alt="image-20201128183750095" style="zoom:24%;" />
$$
取半径为1球壳的单位能量为I，半径为r的壳单位能量为\frac{I}{r^2} \\
能量守恒 \\
$$
结论：

1. ShadingPoint能量与距离成平方反比

2. <img src="https://www.qiniu.cregskin.com/image-20201128184754581.png" alt="image-20201128184754581" style="zoom:32%;" />
   $$
   \frac{I}{r^2}：到达 ShadingPoint的能量 \\
   \frac{I}{r^2}max(0, n \cdot l)：接收到的能量 \\
   K_d：漫反射系数，0，吸收所有能量；1，反射所有能量。可表示为RGB \\
   L_d：漫反射光
   $$
   



Shading point 接收了能量，发出符合自身材质的光（RGB）



漫反射往四面八方反射的光，在任何位置观测，是一样的

<img src="https://www.qiniu.cregskin.com/image-20201128185001416.png" alt="image-20201128185001416" style="zoom:35%;" />















## 2.3 管线渲染 Graphics Pipeline



















