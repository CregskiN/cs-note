# A Swift and Brutal Introduction to Linear Algrbra!

[TOC]



## 1. 图形学的前置学科

+ 基础数学
  + 线性代数 Linear Algebra
  + 微积分 Calculus
  + 统计学 Statistics
+ 基础物理
  + 视觉 Optics
  + 机械 Mechanics
+ 其他 Misc
  + 信号处理 Signal Processing
  + 数字分析 Numberical Analysis



## 2. 向量

## 3. 向量计算

### 3.1 向量与标量运算

### 3.2 向量取反

### 3.3 向量加减

### 3.4 向量相乘

#### 点乘/内积

![image-20201120180102009](https://www.qiniu.cregskin.com/image-20201120180102009.png)



![image-20201120180134304](https://www.qiniu.cregskin.com/image-20201120180134304.png)

应用：

1. 计算两个向量夹角

   <img src="https://www.qiniu.cregskin.com/image-20201120180305837.png" alt="image-20201120180305837" style="zoom:50%;" />

2. 判断两个向量是否垂直

   $cos(\theta) = 0 , \theta = \pi / 2$

3. 得出 $\vec{a}$ 到 $\vec{b}$ 的投影

   <img src="https://www.qiniu.cregskin.com/image-20201120181100098.png" alt="image-20201120181100098" style="zoom:50%;" />

4. 两个方向接近的程度？

5. 前与后的方向判断？

   <img src="https://www.qiniu.cregskin.com/image-20201120181248242.png" alt="image-20201120181248242" style="zoom:50%;" />

   若 a、b 方向相同，$\vec{a} \cdot \vec{b} > 0$ 

   若 a、b 方向垂直，$\vec{a} \cdot \vec{b} = 0$

   若 a、c 方向大于 90度，$\vec{a} \cdot \vec{b} < 0$

   a、b 越接近，$\vec{a} \cdot \vec{b} \rightarrow 1$

   





#### 叉乘/外积/向量积

<img src="https://www.qiniu.cregskin.com/image-20201120180342591.png" alt="image-20201120180342591" style="zoom:50%;" />

![image-20201120180404663](https://www.qiniu.cregskin.com/image-20201120180404663.png)

![image-20201120182240943](https://www.qiniu.cregskin.com/image-20201120182240943.png)

应用：

1. 得到与A、B向量垂直的第三条向量，方向遵循右手定则（提升维度）

   <img src="https://www.qiniu.cregskin.com/image-20201120182434023.png" alt="image-20201120182434023" style="zoom:50%;" />

2. 判断左和右

   <img src="https://www.qiniu.cregskin.com/image-20201120183450171.png" alt="image-20201120183450171" style="zoom:50%;" />

   **向量b 在 向量a 的左侧还是右侧？**

   $\vec{a} \times \vec{b} = \vec{c} = (c_x, c_y, c_z)$  检查 $c_z$ 的符号

   + 为正，则说明 向量a 逆时针旋转可到达 向量b，b 在 a 的左侧
   + 为负，说明 向量a 顺时针旋转到达 向量b，b 在 a 的右侧

3. 判断点在图形的内还是外

   <img src="https://www.qiniu.cregskin.com/20201120184158.png" alt="image-20201120184128857" style="zoom:50%;" />

   **点p 在三角形内还是外？**

   **AP 在 AB 的左侧** && BP **在 BC 的左侧** && **CP 在 CA 的左侧**，即满足同时满足

   $(\vec{AB} \times \vec{AP})_z > 0$

   $(\vec{BC} \times \vec{BP})_z > 0$

   $(\vec{CA} \times \vec{CP})_z > 0$





## 4. 矩阵

### 4.1 矩阵加减

<img src="https://www.qiniu.cregskin.com/image-20201120190436675.png" alt="image-20201120190436675" style="zoom:70%;" />

<img src="https://www.qiniu.cregskin.com/image-20201120190445759.png" alt="image-20201120190445759" style="zoom:67%;" />



### 4.2 矩阵乘数

<img src="https://www.qiniu.cregskin.com/image-20201120190458227.png" alt="image-20201120190458227" style="zoom:67%;" />

### 4.3 矩阵乘向量

<img src="https://www.qiniu.cregskin.com/image-20201120191400943.png" alt="image-20201120191400943" style="zoom:50%;" />

应用：

1. 将向量按某轴做镜像

   

### 4.4 矩阵乘矩阵

#### 点乘

前提：前列数 = 后行数

前列数表示 变换后基向量的数量

后行数表示 即将进行矩阵变换的向量的维度

![image-20201120190919563](https://www.qiniu.cregskin.com/image-20201120190919563.png)

**i行j列元素 = 前矩阵的i行向量 点乘 后矩阵的 j列向量**

NOTE：

1. 无交换律
2. 有结合律、分配律

##### 转置矩阵 

<img src="../../../../../../Library/Application Support/typora-user-images/image-20201120191608178.png" alt="image-20201120191608178" style="zoom:50%;" />

性质

<img src="../../../../../../Library/Application Support/typora-user-images/image-20201120191638042.png" alt="image-20201120191638042" style="zoom:50%;" />

##### 单位矩阵

<img src="https://www.qiniu.cregskin.com/image-20201120191828278.png" alt="image-20201120191828278" style="zoom:50%;" />

性质

<img src="https://www.qiniu.cregskin.com/image-20201120191837479.png" alt="image-20201120191837479" style="zoom:50%;" />

#### 叉乘





### 4.5 向量点乘、叉乘与矩阵

向量点乘 -> 矩阵点乘

<img src="https://www.qiniu.cregskin.com/image-20201120211653437.png" alt="image-20201120211653437" style="zoom: 50%;" />

向量叉乘 -> 矩阵与向量点乘

<img src="https://www.qiniu.cregskin.com/image-20201120211935113.png" alt="image-20201120211935113" style="zoom:50%;" />





## References

https://learnopengl-cn.github.io/01%20Getting%20started/07%20Transformations/#_6