[TOC]

材质与外观

光照与材质的作用关系

材质在渲染器中的体现，就是 BRDF



# 1. 材质的反射与BRDF

## 全反射材质

**漫反射 - 全反射材质**

<img src="https://www.qiniu.cregskin.com/202202121042957.png" alt="image-20220212104040326" style="zoom:50%;" />

即，计算漫反射时，入射光不会被吸收，全部反射出去

假设入射光均匀进入：

<img src="https://www.qiniu.cregskin.com/202202132128471.png" alt="image-20220213212859425" style="zoom:50%;" />



## 金属光泽材质

**Glossy material 近似镜面的材料材质**

如下图，入射光进入后，在一定角度范围内射出

<img src="https://www.qiniu.cregskin.com/202202140946266.png" alt="image-20220214094609236" style="zoom:50%;" />

## 半透明材质

**Ideal reflective / refractive material (BSDF*) 理想的反射/折射材质**

入射光在材质表面，一部分折射进入材质内，一部分反射出去

<img src="https://www.qiniu.cregskin.com/202202121102970.png" alt="image-20220212110244949" style="zoom:50%;" />

+ BSDF：散射系数。 BSDF = BRDF + BTDF



# 2. 折射定律与反射定律

## 反射定律

理想的高光反射

<img src="https://www.qiniu.cregskin.com/202202141002962.png" alt="image-20220214100231936" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202202141002063.png" alt="image-20220214100254038" style="zoom:50%;" />

+ $\omega_i / \omega_o$ ：入射光 / 出射光

镜面反射 BRDF

<img src="https://www.qiniu.cregskin.com/202202141013876.png" alt="image-20220214101326849" style="zoom:50%;" />



## 折射定律

**折射率**

<img src="https://www.qiniu.cregskin.com/202202121105177.png" alt="image-20220212110545156" style="zoom:50%;" />



**全反射**

当入射介质折射率 $n_i >$ 折射介质折射率 $n_t$ ，出现全反射现象

<img src="https://www.qiniu.cregskin.com/202202121109703.png" alt="image-20220212110930678" style="zoom:50%;" />





<img src="https://www.qiniu.cregskin.com/202202121111798.png" alt="image-20220212111151774" style="zoom:50%;" />



> BRDF + BTDF = BSDF
>
> BRDF 反射系数，BTDF 折射系数，统称散射系数 BSDF





## Fresnel Reflection / Term 菲涅尔项 

光线的反射程度，会随着入射角（以及光的偏振 polarization of light）的变化而变化

<img src="https://www.qiniu.cregskin.com/202202141034112.png" alt="image-20220214103446083" style="zoom:50%;" />

菲涅尔项反映的是材质对光线的反射程度，与入射角（=反射角）的关系（x - 与法线的角度 ｜y - 反射占入射光百分比）：

<img src="https://www.qiniu.cregskin.com/202202141043693.png" alt="image-20220214104302664" style="zoom:33%;" /><img src="https://www.qiniu.cregskin.com/202202141043117.png" alt="image-20220214104313074" style="zoom:33%;" /> 

> 导体的折射率是负数

菲涅尔项的计算：

<img src="https://www.qiniu.cregskin.com/202202141048560.png" alt="image-20220214104851532" style="zoom: 67%;" />

Schilick's approximation 史密克斯近似：

<img src="https://www.qiniu.cregskin.com/202202141049974.png" alt="image-20220214104947945" style="zoom:50%;" />



# 3. 微表面模型 Microfacet Material

距离足够远，表面的细节看不到，只能看到光反射形成的“整体情况”，看不到微小的细节，如几何

<img src="https://www.qiniu.cregskin.com/202202150910684.png" alt="image-20220215091017643" style="zoom: 50%;" />

**近处能看到的几何，随着观测距离的增加，会慢慢“近似”成材质**

> 此处“材质”体现为 BRDF，“近似”即推导 BRDF 的过程

如何近似？

<img src="https://www.qiniu.cregskin.com/202202150912164.png" alt="image-20220215091205131" style="zoom:50%;" />

可以观察到，microsurface 的法线分布在一个范围内

<img src="https://www.qiniu.cregskin.com/202202150916044.png" alt="image-20220215091603013" style="zoom:50%;" />

+ $F(i, h)$ 菲涅尔项 
+ $G(i, o, h)$ 阴影遮挡项
+ $D(h)$ 法线分布项

有多少光线，经过材质的反射，能进入人眼？

wi、wo 的半程向量在材质法线范围 D 内

<img src="https://www.qiniu.cregskin.com/202202151028799.png" alt="image-20220215102845743" style="zoom:50%;" />



# 4. 微表面的方向性（区分材质的方式）

以金属表面为例，分为两种：各向同性表面 Isotropic，各向异性表面 Anisotropic

<img src="https://www.qiniu.cregskin.com/202202151029565.png" alt="image-20220215102935532" style="zoom:50%;" />

上图中，通过观察金属光泽可知，金属表面是沿着竖直方向打磨的

原因如下图所示：

<img src="https://www.qiniu.cregskin.com/202202151033444.png" alt="image-20220215103313413" style="zoom:50%;" />

在方位角上旋转物体，观察入射光和出射光的相对方向：

+ 相对方向基本没有变化的是 Isotropic。微表面法线分布非常均匀

+ 相对方向发生变化的是 Aniostropic。微表面法线分布有明确的方向性

<img src="https://www.qiniu.cregskin.com/202202151110486.png" alt="image-20220215111014454" style="zoom:50%;" />

Anisotropic 的 BRDF 与绝对方位角有关

> ????

<img src="https://www.qiniu.cregskin.com/202202151110904.png" alt="image-20220215111050873" style="zoom:37%;" /> <img src="https://www.qiniu.cregskin.com/202202151111585.png" alt="image-20220215111107557" style="zoom:33%;" /> <img src="https://www.qiniu.cregskin.com/202202151111244.png" alt="image-20220215111120205" style="zoom:33%;" />





# 5. BRDF 深入

**BRDF 的性质**

+ 非负 <img src="https://www.qiniu.cregskin.com/202202151113226.png" alt="image-20220215111330200" style="zoom:50%;" /> 
+ 线性 <img src="https://www.qiniu.cregskin.com/202202151114583.png" alt="image-20220215111415552" style="zoom:50%;" />
+ 可逆 <img src="https://www.qiniu.cregskin.com/202202151115567.png" alt="image-20220215111511540" style="zoom:33%;" /> 
+ 能量守恒（BRDF 不大于 1，能量不会增加） <img src="https://www.qiniu.cregskin.com/202202151115113.png" alt="image-20220215111533087" style="zoom:50%;" /> 
+ BRDF 分两种
  + 对于 Isotropic，只与相对方位角有关 <img src="https://www.qiniu.cregskin.com/202202151530520.png" alt="image-20220215153045490" style="zoom:50%;" /> 
  + 对于 Anisotropic，<img src="https://www.qiniu.cregskin.com/202202151530442.png" alt="image-20220215153058415" style="zoom:50%;" /> 



## BRDF 的测量

为什么要测量 BRDF？

如下图：

<img src="https://www.qiniu.cregskin.com/202202151532766.png" alt="image-20220215153259715" style="zoom: 67%;" />

**史密克斯近似得到的菲涅尔项，与真实材料的菲涅尔项差距较大**

### 基于图像的测量

$f(w_i, w_o)$

如下图：

<img src="https://www.qiniu.cregskin.com/202202151535812.png" alt="image-20220215153505761" style="zoom:50%;" />

枚举所有的入射方向，放置一个光源。枚举所有出射方向，放置一个摄像机。在四个维度上测量 BRDF：光源任意位置、物体任意位置、相机任意位置、相机任意朝向

数据量是四维的！

可以改进效率的思路：

+ Isotropic surfaces reduce dimensionality from 4D to 3D 
+ Reciprocity reduces # of measurements by half
+ ...































