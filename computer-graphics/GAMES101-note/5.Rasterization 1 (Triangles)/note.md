# Rasterization 1 (Triangles)

[TOC]



> 昨晚观测矩阵后，下一步做什么？
>
> 答：画在屏幕上



## 1. 完成视图变换 Finishing up Viewing

经如下变换，

<img src="https://www.qiniu.cregskin.com/image-20201123190018637.png" alt="image-20201123190018637"  />

平截头体的**近平面不变，远平面变得和近平面一样大**

<img src="https://www.qiniu.cregskin.com/image-20201123190220615.png" alt="image-20201123190220615" style="zoom:50%;" />

> 立方体用 \[l, r] x \[b, t] x [n, f] 表示（分别对应x、y、z轴坐标）
>
> <img src="https://www.qiniu.cregskin.com/image-20201123190404256.png" alt="image-20201123190404256" style="zoom:25%;" />

<img src="https://www.qiniu.cregskin.com/image-20201123191143511.png" alt="image-20201123191143511" style="zoom:25%;" />;l

如何定义平截头体（视锥）？

1. 给近平面定义 **宽高比 Aspect radio**
2. **定义视角fovY field-of-view**（垂直可视角度）



<img src="https://www.qiniu.cregskin.com/image-20201123191107065.png" alt="image-20201123191107065" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/image-20201123191637232.png" alt="image-20201123191637232" style="zoom: 30%;" />

> 通过控制fov，可以实现视觉上的缩放效果
>
> fov增大，压缩到cube中的图像变小
>
> fov缩小，压缩到cube中的图像变大
>
> 当视野变小时，场景投影出来的空间就会减小，产生放大(Zoom In)了的感觉



> + **M**odel 变换，摆放物体位置
> + **V**iew 变换，摆放相机位置、方向
> + **P**rojection 变换
>   + Orthographic 正交投影，将空间压缩为**小立方体 cube[-1,1]^3**
>   + Perspective 透视投影，将平截头体 frustum 压缩为**小立方体 cube[-1,1]^3**
> + 获得**小立方体**，之后呢？处理 cube，把 cube 画到屏幕上



### 1.1 视口变换 Viewport transformation

#### 前置定义

+ 什么是屏幕？

  + 二维数组，每个元素都是一个像素点 **pixels**
  + 数组大小为分辨率 **Resolution**
  + 一种光栅成像设备 raster display

+ Raster 指的是德语中的相机

  + 把东西画在屏幕上，就是光栅化

+ 像素 Pixel （Picture Element 缩写）

  + 抽象理解，像素是一个颜色均匀的正方形
  + 红黄蓝混合物

+ 定义屏幕空间（不同于虎书）

  + 像素坐标 (x, y) {x [0, width-1] y[0, height-1]}
  + 屏幕空间的中心 (x+0.5, y+0.5) 下图为 (2.5, 1.5)

  <img src="https://www.qiniu.cregskin.com/image-20201123192827493.png" alt="image-20201123192827493" style="zoom: 25%;" />



#### 视口变换

+ 暂时不管 z
+ 把 cube[-1,1]^3 宽高拉伸到 width height，并移动左下角到 (0, 0)

几何上，**立方体近平面贴上了 xOy 面**

<img src="https://www.qiniu.cregskin.com/image-20201123194226934.png" alt="image-20201123194226934" style="zoom: 25%;" />

<img src="https://www.qiniu.cregskin.com/image-20201123194531698.png" alt="image-20201123194531698" style="zoom:40%;" />





## 2. 光栅化 Rasterization

> 把多边形打散成像素，画在屏幕上

### 2.1 不同的光栅显示设备 Different raster displays

示波器

<img src="../../../../../Library/Application Support/typora-user-images/image-20201123194911865.png" alt="image-20201123194911865" style="zoom:15%;" />

原理：阴极射线管 CRT

<img src="https://www.qiniu.cregskin.com/image-20201123195026851.png" alt="image-20201123195026851" style="zoom: 15%;" />

流程：扫描：一行一行打出电子

<img src="https://www.qiniu.cregskin.com/image-20201123195203680.png" alt="image-20201123195203680" style="zoom: 40%;" />

优化：隔行扫描，隔一行画一行。人眼有画面暂留现象。在视频压缩用到



通用显示设备：LCD 平板显示设备、电子计算器，分辨率大于视网膜，称视网膜屏。

LCD 通过液晶的扭曲，光通过光栅限制，波动被限制和扭转

<img src="https://www.qiniu.cregskin.com/image-20201123195708807.png" alt="image-20201123195708807" style="zoom:50%;" />

+ LED 发光二极管

+ 电子墨水屏。有黑白色墨水，通电控制墨水朝向。但刷新特别慢



### 2.2 光栅化三角形 Rasterizing a triangle

+ 三角形可以表示多边形
+ 独特性质
  + 给定三个点，就能连一个面
  + 内外部定义清晰，还可以用叉积判断点是否在三角形内
  + 三角形内部任意点，相对三个点的插值可以任意变化

<img src="https://www.qiniu.cregskin.com/image-20201123200231746.png" alt="image-20201123200231746" style="zoom:25%;" />

如何判断，像素是否被点亮？



> 采样：已知一个函数 f(x)，给出一个离散的 x 几何，得出函数值



已知如下空间：

<img src="https://www.qiniu.cregskin.com/image-20201123200436343.png" alt="image-20201123200436343" style="zoom:33%;" />

使用 inside(int x, int y): enum(1, 0) 确定是否应该点亮像素点

```c++
for(int x = 0; x < xmax; x++){
  for(int y = 0; y < ymax; y++){
    image[x][y] = inside(tri, x + 0.5, y + 0.5);
  }
}
```



inside 根据什么原理？

答：使用叉积，判断点是否在三角形内



<img src="https://www.qiniu.cregskin.com/image-20201123200838625.png" alt="image-20201123200838625" style="zoom:33%;" />



如果点Q正好在三角形的边上，如何处理？

答：可以自己定义。本课程不做处理（不算在三角形内）



#### Bouding Box 稍微优化一下

三角形不一定占据所有的屏幕空间。蓝色表示占有区域 Bounding Box 包围盒 / 轴向包围盒。AABB

<img src="https://www.qiniu.cregskin.com/image-20201123201150374.png" alt="image-20201123201150374" style="zoom:50%;" />



#### Bounding Box 失效

仅找每一行最左的像素点和最右的像素点。适用于Bounding Box很大，但实际上三角形很小的情景

<img src="https://www.qiniu.cregskin.com/image-20201123201418693.png" alt="image-20201123201418693" style="zoom:50%;" />



#### 真实的光栅

<img src="https://www.qiniu.cregskin.com/image-20201123201614004.png" alt="image-20201123201614004" style="zoom:25%;" />

> 绿色像素点更多，因为人眼对绿色更敏感，更舒服



<img src="https://www.qiniu.cregskin.com/image-20201123201805944.png" alt="image-20201123201805944" style="zoom:25%;" />





采样后的点阵

<img src="https://www.qiniu.cregskin.com/image-20201123201846148.png" alt="image-20201123201846148" style="zoom:50%;" />

期待的效果

<img src="https://www.qiniu.cregskin.com/image-20201123202021892.png" alt="image-20201123202021892" style="zoom:33%;" />



实际的效果

<img src="https://www.qiniu.cregskin.com/image-20201123201917560.png" alt="image-20201123201917560" style="zoom:50%;" />

锯齿！Jaggies

原因：像素本身是有大小的。采样率对于信号来说不够高，产生走样



<img src="https://www.qiniu.cregskin.com/image-20201123202042894.png" alt="image-20201123202042894" style="zoom:25%;" />



## 3. 闭塞和可见度 Occlusions and Visibility