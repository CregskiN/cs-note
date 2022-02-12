[TOC]

材质与外观

光照与材质的作用关系

材质在渲染器中的体现，就是 BRDF



# 1. Material == BRDF

漫反射材质

<img src="https://www.qiniu.cregskin.com/202202121042957.png" alt="image-20220212104040326" style="zoom:50%;" />



**Glossy material 近似镜面的材料** 

<img src="https://www.qiniu.cregskin.com/202202121103695.png" alt="image-20220212110319674" style="zoom:50%;" />





**Ideal reflective / refractive material (BSDF*) 一部分能量被吸收，半透明材质**

<img src="https://www.qiniu.cregskin.com/202202121102970.png" alt="image-20220212110244949" style="zoom:50%;" />

# 2. 折射 == BTDF 

折射定律

<img src="https://www.qiniu.cregskin.com/202202121105177.png" alt="image-20220212110545156" style="zoom:50%;" />



当入射介质折射率小于折射介质，则出现全反射现象

<img src="https://www.qiniu.cregskin.com/202202121109703.png" alt="image-20220212110930678" style="zoom:50%;" />



<img src="https://www.qiniu.cregskin.com/202202121111798.png" alt="image-20220212111151774" style="zoom:50%;" />



> BRDF + BTDF = BSDF
>
> BRDF 反射系数，BTDF 折射系数，统称散射系数 BSDF





菲涅尔项

Schilick's approximation



微表面模型 Microfacet Material

距离足够远，表面的细节看不到，只能看到光反射形成的整体情况

从远处看到的是材质，从近处看到的是几何

























