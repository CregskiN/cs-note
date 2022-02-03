[TOC]



# 0. 前情提要

+ hw6 加速结构
+ hw7 路径追踪 path tracing



**上节**

+ 基础光线追踪
  + 光线生成
  + 光线-物体求交
+ 加速
  + Ray AABB intersection 
  + Spatial partitions vs object partitions 
  + BVH traversal
+ Radiometry

**本节**

+ Radiometry cont.
+ Light transport 
  + The reflection equation 
  + The rendering equation 
+ Global illumination 
+ Probability review





# 1. Radiometry

+ Radiant energy：辐射能量，单位焦耳<img src="https://www.qiniu.cregskin.com/202201311657090.png" alt="image-20220131165700060" style="zoom: 33%;" />

+ Radiant flux (power)：辐射通量，单位时间内的能量，单位瓦特、流明<img src="https://www.qiniu.cregskin.com/202201311657751.png" alt="image-20220131165709730" style="zoom: 33%;" />

+ Radiant intensity：辐射强度，（单位时间内）从一个点朝某立体角发出的能量 <img src="https://www.qiniu.cregskin.com/202201311657909.png" alt="image-20220131165716882" style="zoom: 33%;" />

+ Solid Angle：立体角 <img src="https://www.qiniu.cregskin.com/202201311657950.png" alt="image-20220131165726915" style="zoom: 33%;" /> <img src="https://www.qiniu.cregskin.com/202201311658437.png" alt="image-20220131165813407" style="zoom:50%;" />

+ Differential Solid Angles：微分立体角

  <img src="https://www.qiniu.cregskin.com/202201311700187.png" alt="image-20220127175746309" style="zoom: 33%;" />



## 1.2 Irradiance

<img src="https://www.qiniu.cregskin.com/202201311705282.png" alt="image-20220131170543256" style="zoom:33%;" />

Irradiance：单位投影区域上入射的功率（光线可以来自四面八方，垂直的光线直接吸收，不垂直的光线按如下处理）<img src="https://www.qiniu.cregskin.com/202201311719834.png" alt="image-20220131171905798" style="zoom:33%;" /> <img src="https://www.qiniu.cregskin.com/202201311719283.png" alt="image-20220131171918256" style="zoom:33%;" />



**Lambert’s Cosine Law**

<img src="https://www.qiniu.cregskin.com/202201311713707.png" alt="image-20220131171317673" style="zoom: 40%;" />

+ 如果入射光线与物体表面垂直，则照射区域为整个表面，吸收所有能量
+ 如果入射光线与物体表面成60度角，则 cos60 的光线照射到物体表面，被吸收

物体表面接收来自光源的能量，与**光线和物体表面的角度**有关：例如四季

<img src="https://www.qiniu.cregskin.com/202201311714280.png" alt="image-20220131171431250" style="zoom:33%;" />





## 1.3 Radiance

<img src="https://www.qiniu.cregskin.com/202201311719602.png" alt="image-20220131171953564" style="zoom:50%;" />

Radiance：辐射度（亮度）是指在一个表面上，单位投影面积在单位立体角，发射/接收辐射的功率（分为 Exiting Radiance 和 Incident Radiance）

<img src="https://www.qiniu.cregskin.com/202201311720428.png" alt="image-20220131172020391" style="zoom: 33%;" /> <img src="https://www.qiniu.cregskin.com/202201311720259.png" alt="image-20220131172031232" style="zoom: 33%;" />

+ 回想：
  + Irrdiance：单位投影面积入射的功率（从四面八方入射的能量）
  + Radiant intensity：单位立体角射出的功率
+ 可以理解成：
  + Radiance：限制单位立体角的 Irrdiance
  + Radiance：限制单位投影区域（projected unit area）的 Intensity



**Incident Radiance**：单位投影面积，接收来自某一个方向角入射的光线的功率（Irrdiance 是从四面八方入射的光线的功率）

<img src="https://www.qiniu.cregskin.com/202202011028652.png" alt="image-20220201102821622" style="zoom:50%;" />



<img src="https://www.qiniu.cregskin.com/202202011028139.png" alt="image-20220201102832115" style="zoom: 33%;" />

**Exiting Radiance**：从一个单位投影面积开始，朝着某一个方向角发出的光线的功率（Radiant Intensity 是从一个点开始，朝某个方向角发出的光线的功率）

<img src="https://www.qiniu.cregskin.com/202202011042645.png" alt="image-20220201104233603" style="zoom:50%;" />



<img src="https://www.qiniu.cregskin.com/202202011042997.png" alt="image-20220201104243956" style="zoom:33%;" />

**Irradiance 和 Radiance**

+ Irradiance：通过单位投影面积，接收来自**四面八方**的辐射功率的总和
+ Radiance：通过单位投影面积，接收来自**指定方向**的辐射功率

Radiance 无非就是在 Irradiance 基础上，增加一个方向性

<img src="https://www.qiniu.cregskin.com/202202011627081.png" alt="image-20220201162732053" style="zoom: 33%;" />

<img src="https://www.qiniu.cregskin.com/202202011627176.png" alt="image-20220201162747151" style="zoom:33%;" />

> $E(p)$ 理解为在p点半球范围内的 Irrdiance 的总和，$dE(p, \omega)$ 理解为p点固定 $\omega$ 方向的 Irrdiance

<img src="https://www.qiniu.cregskin.com/202202011628722.png" alt="image-20220201162801697" style="zoom: 33%;" />



## 1.3 双向反射分布函数 Bidirectional Reflectance Distribution Function (BRDF)

<img src="https://www.qiniu.cregskin.com/202202011637367.png" alt="image-20220201163750337" style="zoom:50%;" />

反射：沿 $\omega_{i}$ 方向的 Radiance，打到单位区域 $dA$，被单位区域吸收，其中一部分转化成从 $dA$ 辐射到其他方向角的 Radiance

$dA$ 接收的来自某方向的能量：<img src="https://www.qiniu.cregskin.com/202202011700067.png" alt="image-20220201170046035" style="zoom:33%;" /> （加了方向的 Radiance）

$dA$ 发出到某方向的能量：<img src="https://www.qiniu.cregskin.com/202202011710245.png" alt="image-20220201171034214" style="zoom:33%;" /> （**BRDF 负责处理的内容**）

> irrdiance 为来自四面八方能量的总和，计作 $E$ ，而 $dE(\omega_{i})$ 则为来自指定方向 $\omega_{i}$ 的能量

`BRDF` 规定在某材质的表面，从方向 $\omega_{i}$ 传入光线的功率，与经过反射传出方向 $\omega_{r}$ 的光线功率的比值：

<img src="https://www.qiniu.cregskin.com/202202011716991.png" alt="image-20220201171653957" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202202011717928.png" alt="image-20220201171708900" style="zoom:50%;" />

通过 BRDF 定义了不同材质对入射光的处理：镜面反射、漫反射等等





# 2. Light transport

## 2.1 反射方程 Reflection Equation

固定 Shading point，固定观测方向，对 Shading point 接收的所有 Incident Radiance 做 BRDF，将每个 Incident Radiance 朝观测方向发出 Radiance 的结果加和，就是最终观测到的亮度结果

<img src="https://www.qiniu.cregskin.com/202202011722388.png" alt="image-20220201172253329" style="zoom: 33%;" />

<img src="https://www.qiniu.cregskin.com/202202011727965.png" alt="image-20220201172720934" style="zoom: 50%;" />



反射方程的问题：

+ Incident Radiance 来自光源和其他物体（光线多次弹射），是一个递归的定义



## 2.2 渲染方程 Rendering Equation

观测到的 Shding point 的亮度不止来自于反射，如果 Shading point 本身就是个发光物体，还需要加上本身发出的 Radiance，由此得到渲染方程：

<img src="https://www.qiniu.cregskin.com/202202011734721.png" alt="image-20220201173456683" style="zoom:50%;" />

+ $\ohm^{+}$ ：半球，因为反射只是在一个半球空间内发生的
+ $con\theta$ 用 $\vec{n} \cdot \omega_i$ 代替

> 渲染方程的求解，在下一课



## 2.3 对渲染方程的理解

**一个点光源的简单情况**

<img src="https://www.qiniu.cregskin.com/202202020943553.png" alt="Snipaste_2022-02-02_09-42-45" style="zoom:50%;" />

> 对于点光源而非面光源，只需考虑一个方向（而非方向角）



**多个点光源**

<img src="https://www.qiniu.cregskin.com/202202020943623.png" alt="image-20220202094339587" style="zoom:50%;" />



**一个面光源**

<img src="https://www.qiniu.cregskin.com/202202020948759.png" alt="image-20220202094827729" style="zoom:50%;" />

实质上就是对面光源对应的方向角做积分



实际场景，还需要考虑其他物体反射过来的光线，对 x 的影响

<img src="https://www.qiniu.cregskin.com/202202032153114.png" alt="image-20220203215316083" style="zoom:50%;" />

解决办法如上图：把其他能产生反射光并且对 Shading point 有影响的物体表面，也看作面光源



**简化渲染方程**

<img src="https://www.qiniu.cregskin.com/202202032154976.png" alt="image-20220203215445947" style="zoom:50%;" />

首先按上图把渲染方程

<img src="https://www.qiniu.cregskin.com/202202032200312.png" alt="image-20220203220056282" style="zoom:40%;" />

<img src="https://www.qiniu.cregskin.com/202202032210943.png" alt="image-20220203221030910" style="zoom:50%;" />



<img src="https://www.qiniu.cregskin.com/202202032210542.png" alt="image-20220203221048496" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202202032211296.png" alt="image-20220203221103248" style="zoom:50%;" />

> 在之前学过的光栅化模型——Blinn-Phong 中，只计算了来自光源的反射光、漫反射光（环境光采用的常数）



# 3. Probability Review

分布

概率密度函数、概率密度图像

期望、概率密度积分求期望





































