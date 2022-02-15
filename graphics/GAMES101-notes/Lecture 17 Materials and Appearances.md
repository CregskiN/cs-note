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



























