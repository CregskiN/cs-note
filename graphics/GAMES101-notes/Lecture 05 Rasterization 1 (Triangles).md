[TOC] 

## 0. 前情提要

+ Viewing transformation
  + View transformation
  + Peojection transformation
    + Orthographic projection 忽略深度 Z
    + Perspective projection 先压缩，再正交



+ 本节
  + Viewport transformation
  + Rasterization
    + Different raster displays
    + Rasterizing a triangle



## 1. 视口变换 Viewport transformation

### 1.1 定义一个 Frustum



<img src="https://www.qiniu.cregskin.com/202201051727797.png" alt="image-20220105172748772" style="zoom: 33%;" />

<img src="https://www.qiniu.cregskin.com/202201051728924.png" alt="image-20220105172805898" style="zoom:50%;" />

+ fov：field-of-view 
+ fovY：垂直可视角度
+ aspect ratio：宽高比

如何将 fovY、aspect 转换到 l r b t



<img src="https://www.qiniu.cregskin.com/202201051734102.png" alt="image-20220105173430077" style="zoom:50%;" />

### 1.2 定义一个屏幕

+ 把一个像素，视为二维数组的一个元素，用 (x, y) 表示
  + <img src="https://www.qiniu.cregskin.com/202201051750277.png" alt="image-20220105175003251" style="zoom:50%;" />
  + 像素 (x, y) 的中心，是 (x+0.5, y+0.5)



### 1.3 视口变换

+ 先不管 z

+ 将 $[-1, 1]^2$ 变换到 $[0, width] \cp [0, height]$

  <img src="https://www.qiniu.cregskin.com/202201051754494.png" alt="image-20220105175441469" style="zoom:50%;" />

> 先缩放，再平移



### 像素到屏幕空间的映射

<img src="https://www.qiniu.cregskin.com/202201310852661.png" alt="image-20220131085220586" style="zoom: 67%;" />





## 2. Rasterization

把坐标打散成像素，在屏幕上显示出来 。类似阴极射线管CRT，以按行扫描的形式，隔行扫描



三角形表示能力强

+ 是最基础的多边形
+ 任何多边形都可分解为多个三角形
+ 三角形一定是一个平面
+ 三角形内外的点，定义清晰（没有凸三角形、凹三角形）
+ 根据内部点与三个顶点的位置关系，可以差值得到内部点的值



### 2.1 采样 Sampling

采样：把函数离散化

<img src="https://www.qiniu.cregskin.com/202201060920379.png" alt="image-20220106092032349" style="zoom:50%;" />



```c++
// 判断像素(x, y)的中心，是否在三角形内
void Sampling(){
	for(int x = 0; x < xmax; ++x){
  	for(int y = 0; y < ymax; ++y){
    	image[x][y] = inside(tri, x+0.5, y+0.5);
	  }  
  }
}
```



### 2.2 inside 函数

<img src="https://www.qiniu.cregskin.com/202201061135291.png" alt="image-20220106113529264" style="zoom:50%;" />

```c++
bool inside(float *tri, float x, float y){
  // 三条边分别与Q做叉积
}
```

> 边界情况：
>
> <img src="https://www.qiniu.cregskin.com/202201061139014.png" alt="image-20220106113926985" style="zoom:33%;" />
>
> 是否算在三角形内？是在1内，还是在2内？需要在inside里规定



### 2.3 Bounding Box

是否需要遍历所有点，判断是否在三角形内？

答：不需要，用 Bounding Box （轴向）包围盒

<img src="https://www.qiniu.cregskin.com/202201061141924.png" alt="image-20220106114120897" style="zoom:50%;" />

> 这属于一种加速光栅化的方法

### 2.4 其他光栅化加速方法

+ 每一行都做一个 Bouding Box
  + <img src="https://www.qiniu.cregskin.com/202201061143096.png" alt="image-20220106114302068" style="zoom:50%;" />
  + 适用于狭长的三角形





## 问题

1. 锯齿 Jaggies，走样问题 Aliasing

   <img src="https://www.qiniu.cregskin.com/202201061149833.png" alt="image-20220106114902803" style="zoom: 33%;" /><img src="https://www.qiniu.cregskin.com/202201061149926.png" alt="image-20220106114915897" style="zoom:33%;" />

   

   

   

   

   

   

 









