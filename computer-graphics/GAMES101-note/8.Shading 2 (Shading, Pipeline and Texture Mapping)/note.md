# Shading 2 (Shading, Pipeline and Texture Mapping)

[TOC]



# 回顾 Last Lecture

+ Blinn-Phone reflectance model

  + Diffuse 漫反射

    由反射点开始，向四面八方反射的光，强度是相等的。这个强度，与两个因素有关：Shading point 表面材质、入射光与 Shading point 法线夹角

    <img src="https://www.qiniu.cregskin.com/image-20201129163625780.png" alt="image-20201129163625780" style="zoom:50%;" />

    **接收多少能量，与光线和Shading point平面角度有关**

  + Specular 高光

  + Ambient 环境反射光照




> 已知 Shading point 面的法线，是得出 Shading 结果的前提！！

<img src="https://www.qiniu.cregskin.com/image-20201128181754201.png" alt="image-20201128181754201" style="zoom: 33%;" />



# 1. 布林-冯反射模型 Blinn-Phone reflectance model

<img src="https://www.qiniu.cregskin.com/image-20201129163625780.png" alt="image-20201129163625780" style="zoom:50%;" />
$$
\vec{l}：对ShadingPoint，光线入射方向 \\ 
\vec{v}：对ShadingPoint，观测方向 \\
\vec{R}：对ShadingPoint，光线反射方向
$$


## 1.1 高光 Speculat



### 观测高光的条件

<img src="https://www.qiniu.cregskin.com/image-20201129164233765.png" alt="image-20201129164233765" style="zoom:50%;" />
$$
\vec{l}：对ShadingPoint，光线入射方向 \\ 
\vec{v}：对ShadingPoint，观测方向 \\
\vec{R}：对ShadingPoint，光线反射方向
$$
答：向量v和向量R足够接近，就能观测到高光



### 半程向量 half vector

<img src="https://www.qiniu.cregskin.com/image-20201129164233765.png" alt="image-20201129164233765" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/image-20201129164624185.png" alt="image-20201129164624185" style="zoom:26%;" />
$$
\vec{l}：对ShadingPoint，光线入射方向 \\ 
\vec{R}：对ShadingPoint，光线反射方向 \\
\vec{n}：对ShadingPoint，法线方向 （l、R的角平分线）\\
\vec{v}：对ShadingPoint，观测方向 \\
\vec{h}：对SHadingPoint，半程向量方向 （l、v的角平分线）\\

\alpha：\vec{n}和\vec{h}成夹角 \\

K_s：镜面反射系数 \\
p：控制高光程度
$$
**h和n夹角越小（点乘），越能看到高光**



+ **为什么不考虑高光反射，能量被吸收的问题？**

  答：布林-冯模型简化忽略了

+ **为什么布林-冯用的是半程向量和法线夹角，而不是反射向量和观测方向的夹角？**

  <img src="https://www.qiniu.cregskin.com/20201129165459.png" alt="image-20201129165435313" style="zoom:50%;" />

  答：布林反射模型用就是反射向量和观测方向，布林-冯反射模型用的是半程向量和法线夹角，计算量更小

+ **指数p是什么意思？**

  如下图：

  <img src="https://www.qiniu.cregskin.com/image-20201129165602095.png" alt="image-20201129165602095" style="zoom:47%;" />

  高光对角度$\alpha$的容忍度很低，即角度很小的情况下才能看到高光。但cos对角度容忍度太高了。实际应用一般是100～200

  下图为p对实际高光表现的影响：

  <img src="https://www.qiniu.cregskin.com/image-20201129165856618.png" alt="image-20201129165856618" style="zoom:28%;" />







## 1.2 环境光照 ambient

<img src="https://www.qiniu.cregskin.com/image-20201128181754201.png" alt="image-20201128181754201" style="zoom: 33%;" />

Blinn-Phong 认为，每个 Shading point 接受的环境光照相同。环境光在这里是一个常数

![image-20201129170126416](https://www.qiniu.cregskin.com/image-20201129170126416.png)

所有环境光加起来，就是该点 Shading point 接收的环境光总量



> 实际上，这样的模型！是！不符合实际的！是假的！



<img src="https://www.qiniu.cregskin.com/image-20201129170629553.png" alt="image-20201129170629553" style="zoom:25%;" />



> 物体到观察点的距离，对观测结果是否有影响？目前认为没有影响



# 2. 着色频率 Shading frequencies

<img src="https://www.qiniu.cregskin.com/image-20201129171323544.png" alt="image-20201129171323544" style="zoom:28%;" />

**着色频率：把 Shading 用在哪些点上？**



三个球用的一个模型：

+ **flat Shading：Shading 用在面上**

  1. 算出每个面的法线
  2. 每个平面只需一次 Shading
  3. 用 2 的 Shading 结果表示整个面的着色结果

+ **Gouraud shading：Shading 用在顶点上**

  以图为例

  1. 算出每个四边形中，四个顶点的法线
  2. 对四个顶点做 Shading
  3. 四边形内部，根据 2 中四个顶点 Shading 结果做**插值**

+ **Phong shading：Shading 用在像素上**

  1. 算出每个四边形中，四个顶点的法线。

     根据四边形四个顶点的法线方向做**插值**，得出四边形内部各个顶点的法线方向

  2. 对四边形内部各个点做 Shading



<img src="https://www.qiniu.cregskin.com/image-20201129170629553.png" alt="image-20201129170629553" style="zoom:20%;" />



## 2.1 Shade each triangle (flat Shading)

**在每个平面上做一次 Shading**

1. 三角形两边做叉积，得出三角形平面的法线

2. Shading

   ![image-20201129231216787](https://www.qiniu.cregskin.com/image-20201129231216787.png)

+ 在每个平面上做一次 Shading
+ 对于平滑物体表面不太友好

<img src="https://www.qiniu.cregskin.com/image-20201129174626856.png" alt="image-20201129174626856" style="zoom:25%;" />



## 2.2 Shade each vertex (Gouraud shading)

1. **求出顶点的法线**
2. 对顶点做 Shading
3. 三角形内部的颜色，用**插值**计算

+ 在三角形每一个顶点上 Shading
+ 内部：从三角形顶点插值 Interpolate 颜色
+ 每个顶点都有一个法向量 normal vector（如何？）



## 2.3 Shade each pixel (Phong shading) 

1. 求出顶点法线
2. 在三角形内部，**插值出各个像素的法线方向**
3. 对各个像素做 Shading

+ 在三角形每一个顶点上 Shading
+ 内部：根据顶点法向量，在内部插值得出新的法向量。计算每个像素的完全着色模型

> 不是 Blinn-Phong 反射模型



> 这三种 Shading，首先把模型划分出多个面



## 2.4 区别

<img src="https://www.qiniu.cregskin.com/image-20201129175417576.png" alt="image-20201129175417576" style="zoom:30%;" />



## Q & A

+ 在 Gouraud Shading、Phone Shading 中，如何获得任意顶点的法线？

  一个顶点的法线，等于与相邻面法线的平均

  <img src="https://www.qiniu.cregskin.com/image-20201129222057898.png" alt="image-20201129222057898" style="zoom:33%;" />

  <img src="https://www.qiniu.cregskin.com/image-20201129221944181.png" alt="image-20201129221944181" style="zoom:50%;" />

+ 求出图形顶点的法线方向，如何插值得出图形中各个像素的法线？

  **重心坐标**

<img src="https://www.qiniu.cregskin.com/image-20201129221803038.png" alt="image-20201129221803038" style="zoom:23%;" />

​	



> 目前已知：着色模型、着色模型如何使用



# 3. 图形化管线 Graphics Pipeline

也称实时渲染管线



<img src="https://www.qiniu.cregskin.com/image-20201129222718517.png" alt="image-20201129222718517" style="zoom:30%;" />

+ 输入：三维空间中的点
+ Vertex Processing：把点投影到屏幕上
  + Vertex Stream
+ Triangle Processing：顶点以预设的方式组合成三角形
  + Triangle Stream
+ Rasterization：光栅化。采样、深度测试，把能呈现的像素找到。把三角形打散成 Fragment，离散的像素，片元
  + Fragment Stream
+ Fragement Processing：对像素着色
  + Shaded Fragment
+ Framebuffer Operations：把最终像素呈现。如MSAA，多个 Fragment 呈现一个像素

> 问：为什么说把点投影到屏幕上，再连成三角形？
>
> 答：实际上只操作顶点，就能按连接顺序形成图形



## Vertex Processing

MVP 变换所在步骤。对每一个顶点进行变换

<img src="https://www.qiniu.cregskin.com/image-20201129223142987.png" alt="image-20201129223142987" style="zoom:30%;" />



## Rasterization

### 采样

<img src="https://www.qiniu.cregskin.com/image-20201129223158490.png" alt="image-20201129223158490" style="zoom:30%;" />



## Fragment Processing

### Z-Buffer 深度测试

深度测试，决定这个 Fragement 是否可见。严格来说可以算作光栅化阶段的一部分

<img src="https://www.qiniu.cregskin.com/image-20201129223210334.png" alt="image-20201129223210334" style="zoom:30%;" />

### Shading

需要考虑不同的着色频率 Shading  Frequencies

+ 如果是 Gouraud shading，对每个顶点着色，只发生在 Vertex Processing
+ 如果是 Phone shading，需要等像素产生再 Shading，即 Fragment Processing 做 Shading

重点：顶点如何着色？像素如何着色？

<img src="https://www.qiniu.cregskin.com/image-20201129223514337.png" alt="image-20201129223514337" style="zoom:30%;" />

<img src="https://www.qiniu.cregskin.com/image-20201129223524929.png" alt="image-20201129223524929" style="zoom:30%;" />





<img src="https://www.qiniu.cregskin.com/image-20201128181754201.png" alt="image-20201128181754201" style="zoom: 33%;" />

三角形内部的点，都有图中对应点的属性

<img src="https://www.qiniu.cregskin.com/image-20201130082334990.png" alt="image-20201130082334990" style="zoom:40%;" />
$$
vec3::lightDir：光照方向，此处认为入射方向指向ShadingPoint，而不是本课程认为的从ShadingPoint出发 \\
vec3::norm：法线
$$
<img src="https://www.qiniu.cregskin.com/image-20201130082759303.png" alt="image-20201130082759303" style="zoom:30%;" />





> https://www.shadertoy.com/view/Id3Gz2



## 着色器的软硬件

> Unreal Engine 虚幻引擎
>
> 关注游戏开发，不需要很多图形学理论知识、人工智能知识
>
> ![image-20201130083153111](https://www.qiniu.cregskin.com/image-20201130083153111.png)



<img src="https://www.qiniu.cregskin.com/image-20201130083251480.png" alt="image-20201130083251480" style="zoom:25%;" />



核心数 = 并行计算数，比 CPU 更多

<img src="https://www.qiniu.cregskin.com/image-20201130083414757.png" alt="image-20201130083414757" style="zoom:25%;" />





# 4. Texture Mapping

## 4.1 纹理与漫反射

<img src="https://www.qiniu.cregskin.com/image-20201130083605886.png" alt="image-20201130083605886" style="zoom:25%;" />

纹理实际上是改变漫反射时的漫反射系数 $k_d$



## 4.2 物体的表面是二维的

任何三维物体表面，都可以看作二维

<img src="https://www.qiniu.cregskin.com/image-20201130083837848.png" alt="image-20201130083837848" style="zoom:29%;" />

纹理映射，就是纹理贴到三维图形上

<img src="https://www.qiniu.cregskin.com/image-20201130084007006.png" alt="image-20201130084007006" style="zoom:28%;" />

让纹理映射到空间三维物体上而不扭曲，是一个研究方向



## 4.3 纹理 UV 坐标

**通常认为uv范围都是[0,1]**

<img src="https://www.qiniu.cregskin.com/image-20201130084212045.png" alt="image-20201130084212045" style="zoom:27%;" />



<img src="https://www.qiniu.cregskin.com/image-20201130084835665.png" alt="image-20201130084835665" style="zoom:25%;" />



## 4.4 可无缝衔接的纹理 Tiled texture

![image-20201130085056190](https://www.qiniu.cregskin.com/image-20201130085056190.png)





# 5. Barycentric Coordinates

已知三角形三个顶点对应的纹理坐标UV，如何知道内部任意一点对应的纹理坐标UV。

答：**插值**









