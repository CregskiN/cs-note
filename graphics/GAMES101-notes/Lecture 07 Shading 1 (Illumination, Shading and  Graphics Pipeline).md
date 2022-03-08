[TOC]



## 0. 前置内容

+ Rasterization
  + Rasterizing one triangle
  + Sampling theory
  + Antialiasing 先模糊，再采样
+ Visiblity / occusion
  + Z-buffering
+ Shading
  + Illumination & Shading
  + Graphics Pipeline



## 1. 可见性 Visiblity

画家画法：先画远处内容



### 1.1 Z-buffer

+ 存储每个采样点的最小深度 z 值
+ 在实现上，需要为所有深度值配备额外的缓冲区
  + FrameBuffer 存储每个采样点的颜色
  + DepthBuffer （Z-Buffer）存储每个采样点的深度

> 在 GAMES101 中，朝向为 -Z，故 z 越小，离观测点越远

<img src="https://www.qiniu.cregskin.com/202201081736523.png" alt="image-20220108173658489" style="zoom: 50%;" />

```c++
for (each triangle T) // 遍历所有三角形
	for (each sample (x,y,z) in T) // 遍历三角形内所有采样点
		if (z < zbuffer[x,y]) // closest sample so far
			framebuffer[x,y] = rgb; // update color
			zbuffer[x,y] = z; // update depth
		else
; // do nothing, this sample is occluded
```



> 遍历三角形的顺序对结果的影响

> Z-buffer 处理不了透明物体



## 2. Shading

目前为止的内容：

<img src="https://www.qiniu.cregskin.com/202201081752712.png" alt="image-20220108175238684" style="zoom:50%;" />

1. 摆好相机和物体
2. 计算物体与相机相对位置
3. 将物体取到屏幕上
4. 用三角形覆盖并渲染





### 2.1 一种简单的着色模型 Blinn-Phong Reflectance Model

<img src="https://www.qiniu.cregskin.com/202201081800940.png" alt="image-20220108180026900" style="zoom: 33%;" />

+ 镜面反射高光 Specular highlights（光源在物体表面镜面反射到人眼）
+ 漫反射 Diffuse reflection（光源在物体表面，往对称方向附近散射到人眼）
+ 环境光 Ambient lighting（接受来自其他物体的反射光，经过镜面反射到人眼）



#### 反射点 Shading point



<img src="https://www.qiniu.cregskin.com/202201081805032.png" alt="image-20220108180520001" style="zoom:50%;" />

+ Shading point：反射点（平面）
+ n：法线方向
+ l：光源相对 Shading point 方向
+ v：光测点相对 Shading point 方向
+ 物体表面材质（颜色、光反射系数）

<img src="https://www.qiniu.cregskin.com/202201081808728.png" alt="image-20220108180843699" style="zoom: 33%;" />

> 暂时不考虑有其他物体遮挡光线



#### 漫反射 DIffuse Reflection

漫反射示意图：

<img src="https://www.qiniu.cregskin.com/202201081844693.png" alt="image-20220108184441662" style="zoom:33%;" />

**光源相对方向、法线角度与反射的关系**：

<img src="https://www.qiniu.cregskin.com/202201081845062.png" alt="image-20220108184500035" style="zoom: 47%;" />

+ n、l、v 重合，反射点接收所有的光线
+ l、n 成 60 度角
+ l、n 夹角 $\theta$ 的余弦值有关系



**到光源距离，与光强的关系**：

<img src="https://www.qiniu.cregskin.com/202201081849128.png" alt="image-20220108184901100" style="zoom:33%;" />

某时某刻，光线的能量 I 均匀分布在一个球壳上。球壳上某一点接收到的能量，与其到电光源的距离 r。有线性函数关系。



最终得出漫反射公式：

<img src="https://www.qiniu.cregskin.com/202201081854679.png" alt="image-20220108185441653" style="zoom:50%;" />

+ $L_d$
+ $k_d$：材料表面光线反射系数，1 为全反射，0 为不反射
+ $\vec{n} \dp \vec{l}$：光源相对方向与法线夹角v

> 漫反射与观测方向无关
>
>  

> 若采用纹理贴图，用 uv 对应的纹理颜色，代替 $k_d$











