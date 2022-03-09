[TOC]



## 0. 前情提要

<img src="https://www.qiniu.cregskin.com/202201131107921.png" alt="image-20220113110750860" style="zoom:50%;" />



+ Shading 2
  + Bling-Phong reflectance model
    + Specular and ambient terms
  + Shading frequencies
  + Graphics pipeline
  + Texture mapping
  + Barycentric coordinates



+ 漫反射项 Diffuse Term

<img src="https://www.qiniu.cregskin.com/202201131109039.png" alt="image-20220113110933002" style="zoom:50%;" />

+ kd：漫反射系数（颜色）
+ I：光源强度、r：距离
+ n：法线、l：光源方向、v：观测方向



## 1. Blinn-Phone part 2

### 1.1 高光项 Specular Term

> 当观察角度接近镜面反射方向足够接近，可以观察到高光

<img src="https://www.qiniu.cregskin.com/202201131114395.png" alt="image-20220113111444365" style="zoom:50%;" />

不同于上面提到的经验，Blinn-Phong 模型引入半程向量，考虑半程向量与法线方向接近程度

+ h：半程向量
+ ks：镜面反射系数

+ p：控制 cos 的容忍度（高光应该在很小的角度才能观测到）

  <img src="https://www.qiniu.cregskin.com/202201131123556.png" alt="image-20220113112318525" style="zoom:33%;" />

> 考虑观测方向和反射向量夹角的模型，叫 Phone 模型。因不好算，Blinn-Phone 模型改进

单纯展示高光项：

<img src="https://www.qiniu.cregskin.com/202201131141255.png" alt="image-20220113114112221" style="zoom:33%;" />



### 1.2 环境光项 Ambient Term

> 经过无数次反射，照到物体表面的光

Blinn-Phone 模型假设，所有 Shading point 接收的环境光是一定的

<img src="https://www.qiniu.cregskin.com/202201131142052.png" alt="image-20220113114245016" style="zoom:50%;" />

就为了保证，所有表面都不是黑的。实质上这个很不真实



### 1.3 最终的着色结果：

<img src="https://www.qiniu.cregskin.com/202201131144780.png" alt="image-20220113114424753" style="zoom:50%;" />



## 2. 着色频率 Shading Frequencies

> 频率实际上指分成的小三角形的密度，视觉上是物体表面的“圆滑程度”

<img src="https://www.qiniu.cregskin.com/202201131719015.png" alt="image-20220113171943983" style="zoom: 33%;" />

+ 从边界情况，可以看出用的着色单元是一样的

+ 着色应该用在哪？
  
  

### 2.1 三种 Shading 方案

+ Flat Shading：四边形平面

  <img src="https://www.qiniu.cregskin.com/202201131819010.png" alt="image-20220113181908959" style="zoom: 50%;" />

+ Gouraud Shading：已知顶点法线，直接对四边形每个顶点着色，其内插值
  
  <img src="https://www.qiniu.cregskin.com/202201131819326.png" alt="image-20220113181922302" style="zoom:50%;" />
  
+ Phone shading：已知顶点法线 ，然后对四边形内各像素做插值求法线，最后再 Shading 结果

  <img src="https://www.qiniu.cregskin.com/202201131819941.png" alt="image-20220113181934920" style="zoom:50%;" />

着色结果对比：

<img src="https://www.qiniu.cregskin.com/202201141927283.png" alt="image-20220114192540512" style="zoom:50%;" />



### 2.2 法线的计算

一个顶点，与多个三角形关联

+ 如何定义顶点法线？一个顶点法线，为相邻面法线的加权平均（按面积、斜度等）

  <img src="https://www.qiniu.cregskin.com/202201150932739.png" alt="image-20220115093258698" style="zoom:25%;" />

+ 如何定义逐像素的法线？由顶点法线，插值出其内每个像素的法线

  <img src="https://www.qiniu.cregskin.com/202201150932605.png" alt="image-20220115093209578" style="zoom: 33%;" />





## 3. 图形渲染管线 / 实时渲染管线

> Graphics Pipeline / real-time rendering

### 3.1 Graphics Pipeline

<img src="https://www.qiniu.cregskin.com/202201150934817.png" alt="image-20220115093425791" style="zoom:50%;" />

输入 3D 顶点坐标

1. **Vertex Processing**：MVP变换（将 3D 顶点投影到屏幕上）

   生成 Vertex Stream

2. **Triangle Processing**：连接顶点，划定若干个三角形

   生成 Triangle Stream

3. **Raserization**：对三角形内部的像素进行采样

   生成 Fragment Stream

4. **Fragment Processing**：处理采样的像素（Z-Buffer）

   生成 Shaded Fragment

5. **Framebuffer Operations**：Fragment 着色

   最终 Disply

<img src="https://www.qiniu.cregskin.com/202201151020069.png" alt="image-20220115102057037" style="zoom: 25%;" /><img src="https://www.qiniu.cregskin.com/202201151021446.png" alt="image-20220115102112409" style="zoom: 25%;" /><img src="https://www.qiniu.cregskin.com/202201151021051.png" alt="image-20220115102125014" style="zoom: 25%;" /><img src="https://www.qiniu.cregskin.com/202201151021981.png" alt="image-20220115102135946" style="zoom:25%;" />





### 3.2 Shader

> 现代 GPU 允许用户编程如何对顶点与像素着色

```glsl
/* Fragment Shader */
uniform sampler2D myTexture;
uniform vec3 lightDir; // 像素固定光照方向
varying vec2 uv;
varying vec3 norm; // 法线（OpenGL 自动对顶点插值得出）

void diffuseShader()
{
   vec3 kd;
   kd = texture2d(myTexture, uv);
   kd *= clamp(dot(–lightDir, norm), 0.0, 1.0);
   gl_FragColor = vec4(kd, 1.0);
}
```

+ Fragment Shader：对像素处理的着色器（OpenGL 会对每个像素执行）
+ Vertex Shader：对顶点处理的着色器

> shadertoy.com







## 4. 纹理映射 Texture Mapping

> 物体不同位置有特定材质，在光线照射下可以有不同表现

三维物体的表面，展开后是二维图像

<img src="https://www.qiniu.cregskin.com/202201151041796.png" alt="image-20220115104130769" style="zoom:50%;" />

### 4.1 uv 坐标

texture 上有特定纹理坐标（用u v表示）

<img src="https://www.qiniu.cregskin.com/202201151045966.png" alt="image-20220115104551937" style="zoom:50%;" />

> u、v 大小在 [0, 1]



### 4.2 纹理 to 物体表面的应用

同一张纹理，可以重复应用到整个场景

<img src="https://www.qiniu.cregskin.com/202201151048040.png" alt="image-20220115104838013" style="zoom:33%;" />



> 知道三角形顶点的 u v 坐标，如何得到三角形内部像素的 u v？
>
> 答：插值















