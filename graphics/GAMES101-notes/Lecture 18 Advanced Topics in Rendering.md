[TOC]

# 1. 高级光线传播 Advanced Light Transport

unbiased 和 biased 无偏的和有偏的估计



## 1.1 Bidirectional Path Tracing (BDPT) 双向路径追踪

从前的 Path Tracing：从摄像机打出，一条从摄像机到光源的路径

Bidirectional Path Tracing：





## 1.2 Metropolis Light Transport (MLT)

一些介绍

+ 一种 Markov Chain Monte Carlo (MCMC) 马尔可夫链的应用

  输入当前采样点，生成在 PDF 分布下的下一个采样点

+ 给出一条路径，MLT 可以生成类似的路径

  <img src="https://www.qiniu.cregskin.com/202202151636053.png" alt="image-20220215163629024" style="zoom:50%;" />

+ 也是无偏的

+ 在间接光数量非常多的情况下，很有效

  <img src="https://www.qiniu.cregskin.com/202202151636917.png" alt="image-20220215163658887" style="zoom:50%;" />

  > 右图 焦散效果路径：人眼 - specuar - diffuse - specular - 光源

不足

+ 很难估计收敛速度（渲染效果）
+ 不能保证每个 pixel 收敛速度相等（有的渲染很好，有的变成脏点）

<img src="https://www.qiniu.cregskin.com/202202151651852.png" alt="image-20220215165114824" style="zoom: 80%;" />



## 1.3 Photon Mapping 光子映射

+ 是一个 Biased 估计

+ 适合渲染 caustics（焦散）（实际上只有聚焦）

  <img src="https://www.qiniu.cregskin.com/202202151657470.png" alt="image-20220215165731434" style="zoom:67%;" />

+ 其中一种实现方法：

  1. 从光源打出 light-sub-path，经过折射/反射，停留到 diffuse 表面

  2. 从观测位置打出 camera-sub-path，经过折射/反射，同样停留到 diffuse 表面

  3. 1、2 两步重叠的点，视为光子
  4. 计算： 对 diffuse 局部表面的光子做密度估计density estimation

  通过找 Shading point 附近 N 个光子，及这些光子所处区域的面积，计算

+ 为什么 unbaised？

  估计局部光子密度的时候，使用的 <img src="https://www.qiniu.cregskin.com/202202151731066.png" alt="image-20220215173149031" style="zoom: 33%;" /> $\ne$ <img src="https://www.qiniu.cregskin.com/202202151732633.png" alt="image-20220215173203603" style="zoom: 33%;" /> 

<img src="https://www.qiniu.cregskin.com/202202151734964.png" alt="image-20220215173419924" style="zoom:33%;" />

> + 什么是 biased unbaised？
>
>   简单理解就是，无偏没有模糊点
>
> + 什么是 consistent？
>
>   随着采样规模的增加，不会出现模糊点
>
> + 为什么不能取固定区域的密度估计 density estimation？
>
>   固定 dA 就不是一种 consistent 的方法了



### Vertex Connection Merging (VCM)

+ 解决的问题：在 3. 步中，为减少前两步的浪费，两点相近即可视为光子

<img src="https://www.qiniu.cregskin.com/202202151722178.png" alt="image-20220215172248153" style="zoom:67%;" />



## 1.4 Instant Radiosity (IR) 实时辐射度

+ 又被称为 many-light approaches

+ 关键思想：

  1. 从光源处发射若干条 light sub-path 停留到物体表面，停留的点称为 Virtual Point Light (VPL)

  2. 再将 VPLs 当作新的光源，重复 1

<img src="https://www.qiniu.cregskin.com/202202151720054.png" alt="image-20220215172017028"  />

+ 在漫反射居多的场景中，有不错的表现

+ 不足：

  1. 有的地方会产生亮点（因为改良后的蒙特卡洛，用对光源积分代替对点积分中，除以两个点的距离的平方。当两个点很接近，这步除法的商会变的非常大）

  2. 不能处理 glossy 材质

<img src="https://www.qiniu.cregskin.com/202202161023111.png" alt="image-20220216102352076" style="zoom:50%;" />





# 2. 高级外观建模 Advanced Apperarance Modeling

## 2.1 非表面模型 Non-surface models 

### Participating Media 参与介质 / 散射介质

如下图：雾气 fog、云 cloud。不定义在物体表面，而是空间中

<img src="https://www.qiniu.cregskin.com/202202161053523.png" alt="image-20220216105355494" style="zoom: 25%;" /> <img src="https://www.qiniu.cregskin.com/202202161054479.png" alt="image-20220216105415445" style="zoom:25%;" /> 

微观上，光线穿过散射介质，可能被吸收、被散射

<img src="https://www.qiniu.cregskin.com/202202161056322.png" alt="image-20220216105625295" style="zoom:50%;" />

**Phase Function 相位函数**

定义了再那个位置，光线如何散射（类比 BSDF）

<img src="https://www.qiniu.cregskin.com/202202161107781.png" alt="image-20220216110741748" style="zoom:50%;" />



**Participating Media 渲染**

+ 能弹射多少次，取决于散射介质
+ 能传播多远，也取决于散射介质
+ 连接每个 Shading point，生成一条从观测点到光源的 Path，做路径追踪

<img src="https://www.qiniu.cregskin.com/202202161110597.png" alt="image-20220216111037568" style="zoom:50%;" />



**应用**

<img src="https://www.qiniu.cregskin.com/202202161110874.png" alt="image-20220216111055838" style="zoom: 27%;" /> <img src="https://www.qiniu.cregskin.com/202202161111371.png" alt="image-20220216111111335" style="zoom:27%;" /> 





### Hair / fur / fiber (BCSDF)

**kajiya-Key Model**

把头发视为能产生反射的圆柱，反射方向在一定范围内

<img src="https://www.qiniu.cregskin.com/202202161115774.png" alt="image-20220216111548725" style="zoom: 37%;" /> <img src="https://www.qiniu.cregskin.com/202202161042644.png" alt="image-20220216104218614" style="zoom: 30%;" />



**Marschner Model**

Marschner Model 将头发建模为 Glass-like cylinder：

<img src="https://www.qiniu.cregskin.com/202202161120171.png" alt="image-20220216112030141" style="zoom: 50%;" />

考虑 反射 R、折射再折射 TT、折射 内部反射 再折射 TRT

<img src="https://www.qiniu.cregskin.com/202202161117830.png" alt="image-20220216111733801" style="zoom:40%;" />  <img src="https://www.qiniu.cregskin.com/202202161042766.png" alt="image-20220216104201732" style="zoom:30%;" />



> 头发计算量太大了



人的头发模型，能否应用到动物身上呢？

答案：不能。如图

<img src="https://www.qiniu.cregskin.com/202202161044861.png" alt="image-20220216104434828" style="zoom:50%;" />



从实际上动物毛发，与人毛发的材质分析：

<img src="https://www.qiniu.cregskin.com/202202161122941.png" alt="image-20220216112217911" style="zoom:50%;" />

实际上无论人、动物，毛发的结构从外到内都是：

+ Culticle 角质
+ Cortex 表皮，折射、反射光线
+ Medulla 髓质，散射光线



引入后的渲染结果：

<img src="https://www.qiniu.cregskin.com/202202161126074.png" alt="image-20220216112624042" style="zoom:50%;" />





**Double Cylinder Model 双层圆柱模型 —— by 闫令琪**

+ R、TT、TRT 未穿过髓质的 path

+ TTs、TRTs 穿过髓质的 path

<img src="https://www.qiniu.cregskin.com/202202161127776.png" alt="image-20220216112712745" style="zoom: 33%;" /> <img src="https://www.qiniu.cregskin.com/202202161406561.png" alt="image-20220216140622529" style="zoom: 33%;" /> 

最终的结果，是这几类 path 叠加的结果

<img src="https://www.qiniu.cregskin.com/202202161406645.png" alt="image-20220216140651614" style="zoom:50%;" />



### Granular material 颗粒材质

<img src="https://www.qiniu.cregskin.com/202202170924938.png" alt="image-20220217092430897" style="zoom:50%;" />



## 2.2 Surface models 表面模型

### Translucent material (BSSRDF)

以玉石为例，光线在 Translucent （半透明） 材质一点进入，在另一点出去

**Subsurface Scattering 次表面反射（类似 BRDF）**

比 BRDF 多考虑光线射入位置、射出位置

<img src="https://www.qiniu.cregskin.com/202202170945107.png" alt="image-20220217094545071" style="zoom:50%;" />

**Dipole Approximation 偶极子近似**

近似的思路：光源发出光线打到半透明材质上，经过散射进入人眼，就好像半透明材质内部，有一个光源（为了物理上近似，假象有两个光源）

<img src="https://www.qiniu.cregskin.com/202202170949039.png" alt="image-20220217094953009" style="zoom:50%;" />

结果：

<img src="https://www.qiniu.cregskin.com/202202170952631.png" alt="image-20220217095242593" style="zoom:25%;" /> <img src="https://www.qiniu.cregskin.com/202202170952950.png" alt="image-20220217095254914" style="zoom:25%;" />



<img src="https://www.qiniu.cregskin.com/202202170954280.png" alt="image-20220217095431221" style="zoom:50%;" />



### Cloth 布料

<img src="https://www.qiniu.cregskin.com/202202170956176.png" alt="image-20220217095646138" style="zoom:40%;" />

不同的织法，有不同的外观效果

<img src="https://www.qiniu.cregskin.com/202202170957224.png" alt="image-20220217095742189" style="zoom:50%;" />

+ 一种改进的思路：把织物当作 Participating Media 渲染（不把织物当成一个面，而是一个“体积”）

  <img src="https://www.qiniu.cregskin.com/202202170959483.png" alt="image-20220217095907447" style="zoom:50%;" />

+ 另一种思路：把织物当作“头发”渲染

  <img src="https://www.qiniu.cregskin.com/202202171000296.png" alt="image-20220217100015261" style="zoom:50%;" />





### Detailed material (non-statistical BRDF)

## Procedural apperance 程序生成的外观

























