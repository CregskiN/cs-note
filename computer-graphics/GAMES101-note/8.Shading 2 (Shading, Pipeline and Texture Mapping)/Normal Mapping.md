# 法线映射 Normal Mapping

[TOC]



## 1. 普通图片、法线贴图、凹凸贴图

普通图片存储这样的信息：

+ 像素点1
  + R（red）三原色中的红
  + G（green）三原色中的绿
  + B（blue）三原色中的蓝
+ 像素点2
+ 像素点3
+ 若干像素点....



凹凸贴图可以视作一种特殊的图片，存储的信息包括：

+ 像素点1
  + Nomal-x 法线的x分量
  + Normal_y 法线的y分量
  + Normal_z 法线的z分量
+ 像素点2
+ 像素点3
+ 若干像素点....



可以看到，二者唯一的区别是：普通图片中的rgb，被替换为法线矢量xyz

这也是为什么，凹凸贴图/法线贴图可以以图片的形式显示出来，只是“颜色”不那么正常

图示：法线贴图

<img src="https://www.qiniu.cregskin.com/image-20201221225501604.png" alt="image-20201221225501604" style="zoom:25%;" />





> 问：为什么法线贴图的显示，看起来不太正常？
>
> 答：正常图片存储颜色的rgb，被替换为法向量的xyz。所以法线贴图能像普通图片显示到屏幕上，但“颜色RGB”被替换成法线xyz，所以颜色显示上不太正常



法线贴图的rgb被替换为当前像素的法线xyz，那么是否可以替换其他 同样具有三个分量的矢量呢？

答案是可以的。



凹凸贴图存储的是shading point的相对高度，shading阶段，使用相对高度结合原法线，计算扰动后法线，用于shading。因此，凹凸贴图存储的相对高度可以通过扰动法线，影响shading结果



凹凸贴图效果：

<img src="https://www.qiniu.cregskin.com/image-20201221231829707.png" alt="image-20201221231829707" style="zoom:33%;" />



**shading point 的法线，可以影响shading结果。所以法线贴图存储的法线、凹凸贴图存储的相对高度，都可以影响shading结果**



## 2. 三种着色频率 Shading frequencies

shading 阶段，目的是给各个 fragment 上色



模型文件（obj等）存储的信息包括：顶点位置xyz，纹理坐标uv，顶点法线。shading阶段需要每个像素的法线，对于小三角形（fragment）中的单个像素，其法线可以通过三种方式得到：

1. flat shading - shading each triangle
   + 对 fragment 的顶点的法线取平均值，进行一次 shading
   + 将 shading 结果作为整个 fragment 的 shading 结果
2. gouraud shading - shading each vertex
   + 对 fragment 的顶点 shading
   + fragment 内像素的颜色，则通过顶点插值得到
3. phone shading - shading each pixel
   + 对顶点法线插值，得到 fragement 内各像素的法线
   + 对 fragment 内各个像素 shading（已知法线，通过TBN矩阵，获取uv）



所以，Normal Mapping 在 shading 发挥的作用，体现在 shading 中的法线，从法线贴图中获取



## 3. 法线贴图的使用

### 已有条件

顶点数据 vertex 中包括：顶点局部空间xyz坐标、uv坐标 texture coordinate、顶点法线 normal、顶点切线 tangent



### 获取切线空间

（以 flat shading 三角形 为例）

已知 fragement 的顶点位置坐标 $V_0、V_1、V_2$，



### TBN矩阵

作用：将法线贴图中存储的切线空间中的法线，转化为世界坐标下的法线







最终目的：使物体表面有沟壑，在shading过程中有所体现



策略1：定义大量顶点

​	缺陷：模型极复杂

策略2：使用法线贴图 normal mapping

​	优点：只需改变纹理，而不是改变模型。低耦合

​	缺点：只是扰动fragment的法线，从而改变shading结果，实际上顶点位置并未改变，在其他针对顶点的操作（如阴影）会呈现没有沟壑的阴影

策略3：使用位移贴图 displacement mapping

​	优点：改变了真实的顶点位置



为了更好完成法线映射 Normal Mapping，







## Reference

[【D3D11游戏编程】学习笔记二十四：切线空间（Tangent Space）](https://blog.csdn.net/BonChoix/article/details/8619624)