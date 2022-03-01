[TOC]

相机 Camera 、棱镜 Lenses 、光场 Light Fields



# 1. 成像

计算机有两种成像方法：光栅化成像，光线追踪成像，这两种算是合成方法，自然界中不存在。

自然界中存在的是 Capture ，即捕获拍照的方法



## 1.1 Pinhole/Lense Camera 针孔/透镜相机

**Pinhole Camera**

原理是小孔成像，RayTracing 用的是这种模型

<img src="https://www.qiniu.cregskin.com/202202171747675.png" alt="image-20220217174738643" style="zoom:50%;" />

**Lense Camera**

<img src="https://www.qiniu.cregskin.com/202202171748788.png" alt="image-20220217174838759" style="zoom:50%;" />

按下快门按键，依次发生：

1. **快门**打开

   + 光线从**快门**进入，经过**透镜**散射，打到**感光元件**上

   + **感光元件**的每个微小单元记录光线信息

2. **快门**关闭

如果没有透镜，会如何？

感光元件的每个微小单元，会接收来自所有方向的光线，最终记录的结果非常相似

> 实际上，感光元件记录的是 **irradiance**

<img src="https://www.qiniu.cregskin.com/202202171751540.png" alt="image-20220217175123515" style="zoom:50%;" /> 







## 1.2 Field of View (FOV) 视场

什么因素可以决定视场？

<img src="https://www.qiniu.cregskin.com/202202171121087.png" alt="image-20220217112117052" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202202171121549.png" alt="image-20220217112127521" style="zoom:50%;" />

依据上面的公式，对于固定大小的传感器 Sensor，减小焦距 Focal lenght 会增大视场



因为某些历史原因，提到某焦距下的视场，默认传感器大小为 35mm

<img src="https://www.qiniu.cregskin.com/202202171757316.png" alt="image-20220217175725289" style="zoom:50%;" />

> 手机相机的 FOV 与相机相同，实际上采用了等比例缩放
>
> <img src="https://www.qiniu.cregskin.com/202202171757581.png" alt="image-20220217175744546" style="zoom:40%;" />



## 1.3 Exposure 曝光度

**Exposure = time x irradiance**

+ **irrdiance**：受**单位区域 Sensor 记录信息**和**焦距**的影响
+ **time**：曝光时间。即**快门打开的时间** 

> Sensor 上每个小单元，记录的是来自所有方向的 Irrdiance，最终成像，是这些 Irrdiance 平均的结果

相关的几个概念：

+ **Aperture size 光圈大小**：Aperiture size = 1 / F-Number，F-Number 为通常使用的数值

+ **Shutter speed 快门速度**

+ **ISO（感光度）**

  算是一种后期对光强的处理，可以发生在传感器本身，也可以发生在传感器传入图像数据之后，显示之前

<img src="https://www.qiniu.cregskin.com/202202171701940.png" alt="image-20220217170148909" style="zoom:50%;" />

> ISO 是对所有 pixel 的亮度增强，同时也会对本身存在的 noise 增强。
>
> 一般情况下，不会用 ISO 得到一个更亮的图像



**Side Effect of Shutter Speed 快门速度的副作用——动态模糊**

<img src="https://www.qiniu.cregskin.com/202202172031859.png" alt="image-20220217203151824" style="zoom:50%;" />

> 动态模糊并不总是不好的，人视觉上，有运动模糊 = 速度快，而且动态模糊会让人眼自动补偿帧数

<img src="https://www.qiniu.cregskin.com/202202172033027.png" alt="image-20220217203312997" style="zoom:50%;" />

在快门打开的时间段内，Sensor 不同部分接收光线的时间点一定是不同的。如上图，来自轴的光线到达Sensor 的时间点，是在扇叶光之前到达的



### Shutter speed 在摄影中的运用

**高速摄影**

<img src="https://www.qiniu.cregskin.com/202202172034184.png" alt="image-20220217203458157" style="zoom:50%;" />

**延迟摄影**

<img src="https://www.qiniu.cregskin.com/202202172034510.png" alt="image-20220217203446479" style="zoom:50%;" />



## 1.4 Thin Lens Approximation 薄透镜近似

> 理想的、能把平行光线聚集、焦距可以改变的凸透镜

实际上，相机通过多组镜片，动态改变焦距

<img src="https://www.qiniu.cregskin.com/202202172037423.png" alt="image-20220217203728393" style="zoom:50%;" />

**Gaussian Thin Lens Equation**

<img src="https://www.qiniu.cregskin.com/202202172040863.png" alt="image-20220217204017833" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202202172041692.png" alt="image-20220217204159671" style="zoom:50%;" />

薄透镜可以解决很多的问题：

### Defocus Blur 散焦模糊

Circle of Confusion 弥散圈，可以表示成像模糊的程度（景深效果就是模糊效果）

<img src="https://www.qiniu.cregskin.com/202202181033202.png" alt="image-20220218103329166" style="zoom:50%;" />

透镜右侧，可以构成相似三角形，得出关系：

<img src="https://www.qiniu.cregskin.com/202202181034978.png" alt="image-20220218103420948" style="zoom:50%;" />

+ C：Circle of Confusion，弥散圈，在传感器上有一定程度模糊的像
+ A：Aperture size，凸透镜直径，光圈直径，光圈大小



> 所以 CoC 的大小，与光圈直径有有关

### 重新定义 F-Number (aka F-Stop)

定义：The f-number of a lens is defined as the focal length divided by the diameter of the aperture 焦距 / 透镜直径

**A = F / N**

+ A：absolute aperture diameter 即光圈直径
+ f：focal length 焦距
+ N：relative aperture 即 F-Numbe，是凸透镜自身的一种参数

代换之前的 C/A 公式，得到：

<img src="https://www.qiniu.cregskin.com/202202181049000.png" alt="image-20220218104907970" style="zoom:50%;" />

> 景深模糊程度 C，受光圈大小 A、焦距 f 和 f-Number 影响

### Depth of Field 景深

所谓景深，指的是当成像出现一定范围、可接受的模糊时，最远物距与最近物距的差。推导如下：

<img src="https://www.qiniu.cregskin.com/202202181657110.png" alt="image-20220218165706079" style="zoom:50%;" />



### Ray Tracing Ideal This Lenses

<img src="https://www.qiniu.cregskin.com/202202181101999.png" alt="image-20220218110105966" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202202181101751.png" alt="image-20220218110147720" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202202181101429.png" alt="image-20220218110117396" style="zoom:50%;" />











