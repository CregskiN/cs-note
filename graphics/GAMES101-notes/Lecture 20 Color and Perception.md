[TOC]



Finishing up light field / lumigraph Color 

+ What is color 什么是颜色？
+ Color perception 颜色感知
+ Color reproduction / matching 颜色复制 / 匹配
+ Color space 色彩空间



# 1. Light Field / Lumigraph 光场

> light field == lumigraph 光场

VR 虚拟现实类比：

在自然场景中，观察一个屋子内的场景：

<img src="https://www.qiniu.cregskin.com/202202182017930.png" alt="image-20220218201737903" style="zoom:50%;" />

放一块幕布，将光线聚集在幕布上，人直接看向幕布。

严格意义上，人在幕布上看到的内容，与之前在自然场景中看到的内容是一致的，如下图：

<img src="https://www.qiniu.cregskin.com/202202182018406.png" alt="image-20220218201808379" style="zoom:50%;" />

把人看到的所有内容，用函数描述出来，就是**全光函数 The Plenoptic Function**



## 1.1 全光函数的定义

首先，全光函数应该能**描述三维空间内的观测方向**（by 极坐标参数）：

> 黑白胶片

<img src="https://www.qiniu.cregskin.com/202202182024372.png" alt="image-20220218202413346" style="zoom:50%;" />

观测内容还应该是有**颜色**的（by 波长参数 wavelength）：

> photograph

<img src="https://www.qiniu.cregskin.com/202202182026844.png" alt="image-20220218202612821" style="zoom:50%;" />

观测内容应该随着时间变化（by 时间参数）：

> Movie

<img src="https://www.qiniu.cregskin.com/202202182028147.png" alt="image-20220218202854119" style="zoom:50%;" />

最后，观测内容应该随所处位置变化（by 位置参数 $V_X、V_Y、V_Z$）：

> Holofraphic movie 全息电影

<img src="https://www.qiniu.cregskin.com/202202182030526.png" alt="image-20220218203000499" style="zoom:50%;" />

如上，通过这七个参数，就能描述所有能观测到的内容。



## 1.2 光场的定义

何为光场，光场与全光函数有什么联系？

答：从定义看，全光函数记录的是任意位置、朝任意方向、任意时间点，观测到的任意颜色的光。光场，实际上就是在一定空间内，对全光函数的采样

<img src="https://www.qiniu.cregskin.com/202202182040512.png" alt="image-20220218204046486" style="zoom: 33%;" />

在定义光场之前，需要几个额外的定义：

+ 光线：

  + $V_X、V_Y、V_Z$ ：起点
  + $\theta、\phi$ ：极坐标方向

  <img src="https://www.qiniu.cregskin.com/202202182056069.png" alt="image-20220218205648045" style="zoom:50%;" />   

+ 全光面 Plenoptic surface

  封闭物体表面任意位置（$V_X、V_Y、V_Z$）、朝任意方向（$\theta、\phi$）的光强，都可以记录在一个包围盒上，这就是 **光场**，可以看做在位置和方向上采样的全光函数

  <img src="https://www.qiniu.cregskin.com/202202182101776.png" alt="image-20220218210104743" style="zoom:50%;" />
  
  
  
  <img src="https://www.qiniu.cregskin.com/202202211029645.png" alt="image-20220221102930601" style="zoom:50%;" />
  
   对于观测者，只需关注物体所处的光场（包围盒），而无需知道光线在凹凸不平的物体表面是如何反射的
  
  <img src="https://www.qiniu.cregskin.com/202202190945595.png" alt="image-20220219094558558" style="zoom: 33%;" />
  
  

​	

+ **另一种光线（射线）定义方式**：

  + 定义一个平面，通过 2D平面给出位置、2D方位角给出方向

    <img src="https://www.qiniu.cregskin.com/202202211054346.png" alt="image-20220221105411321" style="zoom:40%;" />

  + 定义两个平行的平面，各给出一个位置，这两个面，可以用 uv、st 表示

    <img src="https://www.qiniu.cregskin.com/202202211055585.png" alt="image-20220221105505556" style="zoom: 33%;" /> <img src="https://www.qiniu.cregskin.com/202202211109302.png" alt="image-20220221110920276" style="zoom: 33%;" /> 




## 1.3 Light Field Camera 光场摄像机

### The Lytro Light Field Camera

 功能类似先拍照，后调整光圈、聚焦

<img src="https://www.qiniu.cregskin.com/202202230955131.png" alt="image-20220223095521072" style="zoom:50%;" />

传统摄像机，一个像素记录来自各个方向的 Irrdiance，经过平均，得到成像

而光场摄像机中，各个方向的光线射入微透镜，经过散射，打到一个像素上，相当于一个像素记录了各个方向的 Irrdiance

<img src="https://www.qiniu.cregskin.com/202202231001619.png" alt="image-20220223100151575" style="zoom:33%;" /> <img src="https://www.qiniu.cregskin.com/202202231001877.png" alt="image-20220223095842876" style="zoom: 33%;" /> 

通过光场摄像机的记录结果（**光场**），能得到什么呢？

+ **得到常规照片**。从所有像素记录的 Irrdiance 中选定单一方向的 Rdiance
+ **变换相机方向**。通过变换选定的 Radiance 方向
+ **可变焦效果**。光场记录了所有方向的入射光， 通过上一节的方式可实现变焦

存在的问题：

+ **分辨率不足**。传统摄像机，一个像素只需要记录多个光聚焦后的结果，而光场摄像机，需要用更多像素，记录光聚焦又散射的结果
+ **高成本**
+ **分辨率和单个像素需要的胶片像素数量，trade-off**









# 2. Physical Basis of Color 颜色的物理基础

牛顿分光实验表明，光是合成的结果



## 2.1 The Visible Spectrum of Light 光谱

图形学仅关注可见光光谱



**Spectral Power Distribution (SPD) 谱功率密度**

 描述光在每个波长的分布是多少

<img src="https://www.qiniu.cregskin.com/202202231156820.png" alt="image-20220223115624787" style="zoom: 45%;" />



<img src="https://www.qiniu.cregskin.com/202202231156752.png" alt="image-20220223115643724" style="zoom:45%;" />

**线性性质**

<img src="https://www.qiniu.cregskin.com/202202231157925.png" alt="image-20220223115740894" style="zoom: 33%;" />



**`颜色`是人类的感知，与人有关**



## 2.2 Biological Basis of Color

<img src="https://www.qiniu.cregskin.com/202202231200912.png" alt="image-20220223120009881" style="zoom:33%;" /> <img src="https://www.qiniu.cregskin.com/202202231203346.png" alt="image-20220223120315315" style="zoom:33%;" /> 

晶状体相当于透镜，对颜色的感知，要用到视网膜上的视杆细胞 Rod cells 和视锥细胞 Cone cells

而对于视锥细胞，根据对不同波长光的感知能力，又分为三类：

<img src="https://www.qiniu.cregskin.com/202202231203481.png" alt="image-20220223120349451" style="zoom:40%;" />

在每个人眼睛中，这三类颜色感知细胞的分布有很大差距：

<img src="https://www.qiniu.cregskin.com/202202231516298.png" alt="image-20220223151624668" style="zoom:40%;" />

> 即，颜色是人 “感知” 的结果



**如何用数学描述人感知的结果？**

## 2.3 Tristimulus Theory of Color 颜色的三刺激理论

<img src="https://www.qiniu.cregskin.com/202202231522164.png" alt="image-20220223152212136" style="zoom:50%;" />

+ $r_S、r_M、r_L$ 为某类细胞对不同波长光的响应函数
+ $s(\lambda)$ 为 Spectral Power Distribution (SPD) 谱功率密度



人眼感知颜色的过程如下：

<img src="https://www.qiniu.cregskin.com/202202231524834.png" alt="image-20220223152449802" style="zoom:50%;" />



有没有一种可能：两种光线的光谱不同，但被感知的结果相同？

## 2.4 Metamerism 同色异谱

我们要模拟一种颜色的光，无需按照原光谱将不同波长的光精准调和

只需要用其他颜色的光，按照一定配比，调和出相同 SML 积分结果的复合光即可，人类感知到的颜色是一样的。

例如，用不同的光谱模拟太阳光：

<img src="https://www.qiniu.cregskin.com/202202231536227.png" alt="image-20220223153618194" style="zoom: 33%;" />



### Color Reproduction / Matching

> 加色系统

**CIE RGB**

右侧图像描述，要调和出 x轴 波长的光，需要三原色光的比例

<img src="https://www.qiniu.cregskin.com/202202231542348.png" alt="image-20220223154248313" style="zoom:50%;" />

> $r(\lambda)$ 出现负值的原因？
>
> 答：如左图，有时候单纯的加法思路很难拟合出确切的颜色。解决办法是右图，给目标颜色增加一部分主色，尽力拟合新主色，最后减去新主色增加的那部分，就会出现负值
>
> <img src="https://www.qiniu.cregskin.com/202202232059484.png" alt="image-20220223205920449" style="zoom:40%;" /> <img src="https://www.qiniu.cregskin.com/202202232048611.png" alt="image-20220223204858578" style="zoom: 35%;" />



## 2.6 Color Spaces 颜色空间

> sRGB 的色域空间 gamut 是有限的

色域：一个颜色空间所有能表示的颜色（不同颜色空间表示的色域是不同的）

**CIE XYZ**

图示为 Maching Functions，即合成 x轴 波长的光，所需三原色的“光强”

<img src="https://www.qiniu.cregskin.com/202202232118113.png" alt="image-20220223211811079" style="zoom:50%;" />

+ 这三原色是现实世界不存在的
+ Y 一定程度上可以表示合成光的亮度



**色域图**

<img src="https://www.qiniu.cregskin.com/202202232125970.png" alt="image-20220223212510935" style="zoom:50%;" />

+ <img src="https://www.qiniu.cregskin.com/202202232125297.png" alt="image-20220223212527264" style="zoom:50%;" /> 
+ 一般作出的色域图，是固定亮度 Y，改变 X、Y，作出的 (x, y) 图（z 由上一条得出）







### 2.7 Perceptually Organized ColorSpaces 其他常规颜色空间

**HSV**

常用于颜色拾取器 color picker

<img src="https://www.qiniu.cregskin.com/202203011048423.png" alt="image-20220301104818348" style="zoom: 33%;" />

+ Hue 色调：主要选定颜色（波长）
+ Saturation 饱和度：灰度（偏灰）
+ Lightness 亮度



**CIELAB**

<img src="https://www.qiniu.cregskin.com/202203011052582.png" alt="image-20220301105239549" style="zoom:50%;" />

+ L：亮度
+ A：红-绿
+ B：黄-蓝

> 人视觉感知上，这些颜色是互补色（差的太多）

<img src="https://www.qiniu.cregskin.com/202203011054951.png" alt="image-20220301105435918" style="zoom:50%;" />

> `画面暂留现象` 上图盯着十秒，切换成白色，视觉上会出现其互补色（五星红旗）



**颜色是人的感知**

<img src="https://www.qiniu.cregskin.com/202203011057419.png" alt="image-20220301105757386" style="zoom: 25%;" /> <img src="https://www.qiniu.cregskin.com/202203011058941.png" alt="image-20220301105816909" style="zoom:33%;" /> 



**CMYK: A Subtractive Color Space**

一种减色系统

<img src="https://www.qiniu.cregskin.com/202203011102393.png" alt="image-20220301110238361" style="zoom:33%;" /> 







gammer 矫正：radiance 到颜色的转换





