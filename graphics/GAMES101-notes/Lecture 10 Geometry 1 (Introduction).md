[TOC]



## 0. 前情提要

+ Shading 1 & 2 
  + Blinn-Phong reflectance model
  + Shading models / frequencies
  + Graphics Pipeline
  + Texture mapping



+ Shading 3
  + Barycentric coordinates
  + Texture antialiasing（Mipmap）
  + Applications of textures



+ Geometry 1

  + Examples of geometry 

  + Various representations of geometry



## 1. 纹理的应用

### 1.1 环境贴图 Environment Map

Light from the environment：环境光（此处用贴图记录）

<img src="https://www.qiniu.cregskin.com/202201151742337.png" alt="image-20220115174221305" style="zoom:50%;" />



环境光的贴图形式：球壳展开

<img src="https://www.qiniu.cregskin.com/202201211513241.png" alt="image-20220121151336187" style="zoom:50%;" />



涉及曲度问题，所以靠近极点的地方有扭曲

<img src="https://www.qiniu.cregskin.com/202201211515251.png" alt="image-20220121151534219" style="zoom:50%;" />



+ 不同于球壳的（环境光）记录方式：Cube Map

<img src="https://www.qiniu.cregskin.com/202201211516040.png" alt="image-20220121151647012" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202201211517276.png" alt="image-20220121151725223" style="zoom: 33%;" />





### 1.2 纹理的应用

> Blinn-Phone 模型中，一个 Shading Point 包含三部分：
>
> <img src="https://www.qiniu.cregskin.com/202201131144780.png" alt="image-20220113114424753" style="zoom: 33%;" />
>
> + Ambient：环境光项
> + Diffust：漫反射项（$k_d$ 为漫反射项系数，即颜色，**可用纹理代替**）
> + Specular：高光项



#### 凹凸贴图 Bump Mapping / 法线贴图

定义每个 Shading Point 的相对高度，由此：**法线发生变化**，最终会有明暗效果

<img src="https://www.qiniu.cregskin.com/202201211524725.png" alt="image-20220121152404684" style="zoom: 50%;" />



#### 位移贴图 Displacement Mapping

<img src="https://www.qiniu.cregskin.com/202201211534075.png" alt="image-20220121153451045" style="zoom:50%;" />



> 凹凸贴图实际上没有改变定点的位置，只是扰动法线
>
> 而位移贴图实际上**改变了各个三角形顶点的位置**，不只是扰动法线（模型的 Frequencies 必须要契合纹理的高度变化）



#### 3D 噪声

<img src="https://www.qiniu.cregskin.com/202201211540046.png" alt="image-20220121154010014" style="zoom:50%;" />





#### 预计算

提前计算环境光遮蔽效果

<img src="https://www.qiniu.cregskin.com/202201211542080.png" alt="image-20220121154219048" style="zoom:50%;" />



#### 3D 纹理和体渲染

<img src="https://www.qiniu.cregskin.com/202201211543989.png" alt="image-20220121154335956" style="zoom:50%;" />





## 2. 几何 Geometry

### 2.1 各式的几何

<img src="https://www.qiniu.cregskin.com/202201211555818.png" alt="image-20220121155539783" style="zoom:30%;" /><img src="https://www.qiniu.cregskin.com/202201211558783.png" alt="image-20220121155815749" style="zoom:32%;" /><img src="https://www.qiniu.cregskin.com/202201211559136.png" alt="image-20220121155939105" style="zoom:33%;" />

复杂的几何，如何表示？如何存储？宏观视角、围观视角分别如何表示？如何过渡



### 2.2 表示几何的方式

+ 分类：

  + 隐式几何 Implicit

  + 显示几何 explicit



#### 隐式几何 Implicit

不给出点具体在那哪个坐标，而是给出各个点之间的关系（函数关系）

<img src="https://www.qiniu.cregskin.com/202201211614436.png" alt="image-20220121161453405" style="zoom:50%;" />

具体标示出这种隐式的相对关系，很难

<img src="https://www.qiniu.cregskin.com/202201211605009.png" alt="image-20220121160535975" style="zoom: 33%;" />

例如：

+ 判断某个点是否在几何内？



#### 显示几何 explicit

两种显示几何表示方法：

+ 直接给出各个点的三维坐标

+ 给出 uv 到 三维坐标的映射关系

<img src="https://www.qiniu.cregskin.com/202201211607995.png" alt="image-20220121160746959" style="zoom:50%;" />

> 判断某个点是否在几何内，对于 implicit 很简单（看是否符合表达式即可），但对于 explicit 很难



根据需要，选择 显示/隐式 表示方法即可



#### 其他表示方法

**构造立体几何** Constructive Solid Geometry（Implict）

> 其实就是几何图形的布尔运算

<img src="https://www.qiniu.cregskin.com/202201211616659.png" alt="image-20220121161651614" style="zoom:50%;" />

**距离函数** Distance Functions（Implicit）

例如：逐渐靠近的两个球，会发生形状上的变化

<img src="https://www.qiniu.cregskin.com/202201211618092.png" alt="image-20220121161813047" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202201211626549.png" alt="image-20220121162643517" style="zoom:50%;" />

> 距离函数可以表示两个几何的过渡



**水平集** Level Set Methods (Also implicit)

在 2D 几何中，存储一组网格式的函数值（近似），所有函数值接近 0 的网格组合到一起，就是几何的边界

<img src="https://www.qiniu.cregskin.com/202201211639076.png" alt="image-20220121163936046" style="zoom:80%;" />

类似三维中的 CT

<img src="https://www.qiniu.cregskin.com/202201211641272.png" alt="image-20220121164130239" style="zoom:50%;" />



<img src="https://www.qiniu.cregskin.com/202201211630189.png" alt="image-20220121163012138" style="zoom:50%;" />



**分型** Fractals（implicit）

<img src="https://www.qiniu.cregskin.com/202201211630190.png" alt="image-20220121163056141" style="zoom:50%;" />



隐式表示：

+ 优点：
  1. 描述简单（即：一个函数）
  2. 容易解决某些特定问题（如：判断某点在几何内外、某点几何表面的距离）
  3. 适合光线与面求交
  4. 对于简单的图形，描述精准，没有采样问题
  5. 易于处理拓扑的更改（如：流体）

+ 缺点：
  + 很难描述复杂模型（一头牛）







