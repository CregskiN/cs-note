[TOC]





# 1. Single particle simulation 简单的粒子仿真

**速度场**：

<img src="https://www.qiniu.cregskin.com/202203030957790.png" alt="image-20220303095737737" style="zoom:33%;" />

<img src="https://www.qiniu.cregskin.com/202203030958732.png" alt="image-20220303095800703" style="zoom:80%;" />



## Explicit Euler method 显式欧拉法

**用当前的位置、速度，计算 $\triangle t$ 之后的位置、速度**

<img src="https://www.qiniu.cregskin.com/202203030958064.png" alt="image-20220303095821033" style="zoom:50%;" /> 





## Instability and improvements 

### 存在的问题：

+ 有误差

  <img src="https://www.qiniu.cregskin.com/202203031000108.png" alt="image-20220303100021083" style="zoom:50%;" /> 

  步长 $\triangle t$ 对最终拟合的效果影响非常大。可以通过减小步长，获得更好的模拟结果

+ **不稳定**

  <img src="https://www.qiniu.cregskin.com/202203031002859.png" alt="image-20220303100259835" style="zoom:50%;" /> <img src="https://www.qiniu.cregskin.com/202203031003577.png" alt="image-20220303100308552" style="zoom:50%;" /> 

  这种瑕疵被放大的现象，在数字信号处理中被称为正反馈。不会随着 $\triangle t$ 减小而消失

  > PUBG 车辆无限翻滚的问题，就是不稳定被放大的结果



### 解决 Instability

**Midpoint Method 中点法**

<img src="https://www.qiniu.cregskin.com/202203031007627.png" alt="image-20220303100736598" style="zoom: 67%;" /> 

稍微修正，得到一个二次的模型



**Adaptive Step Size 自适应步长**

<img src="https://www.qiniu.cregskin.com/202203031019806.png" alt="image-20220303101928763" style="zoom:50%;" /> <img src="https://www.qiniu.cregskin.com/202203031019550.png" alt="image-20220303101937506" style="zoom:50%;" /> 



**Implicit Euler Method 隐式欧拉法**

用当前的位置、$\triangle t$ 之后的位置、速度，计算 $\triangle t$ 之后的位置、速度

<img src="https://www.qiniu.cregskin.com/202203031016819.png" alt="image-20220303101649793" style="zoom:80%;" /> 

存在的问题：

+ 如果速度不是按线性变化，这个式子计算结果误差就比较大

好处：稳定



如何衡量何为“稳定”？

+ $\frac{局部误差（每一步的误差）}{全剧误差（所有误差之和）}$ 

+  Implicit Euler 方法是一阶的

  + 局部截断误差 O(h^2)
  + 全局截断误差 O(h)

  > h 指步长

  



**Runge-Kutta Families 隆格-库塔方法**

这是一系列解常微分方程的方法

+ 适用于非线性问题
+ 一种四价方法广泛应用，RK4（误差非常小）

<img src="https://www.qiniu.cregskin.com/202203031032077.png" alt="image-20220303103229045" style="zoom:50%;" />

> from **数值分析 numerical analysis**





**Positiion-Based / Verlet Intergration**

不是基于物理的方法

优缺点：

+ 快、简单
+ 不是基于物理，不遵循能量守恒



# 2. Rigid body simulation 刚体模拟

让内部所有点，按照相同的方式运动

<img src="https://www.qiniu.cregskin.com/202203031104189.png" alt="image-20220303110443157" style="zoom:50%;" />

使用 Position-Based 方法

+ 水体是由若干刚体小球壳组成的
+ 水体在任何情况下不可压缩
+ 如果水体某部分密度改变，通过移动小球，修正这种变化
+ 你需要知道密度的梯度，每个粒子的位置

> 梯度下降法 gradient descent：通过调整输入，让结果与预期接近





# 3. Fluid simulation

模拟大规模物质的两个基本思路：

+ 拉格朗日方法 Lagrangian approach，俗称**质点法**

  通过模拟每个小水滴，模拟水

  <img src="https://www.qiniu.cregskin.com/202203031118178.png" alt="image-20220303111823148" style="zoom:50%;" />

+ 欧拉方法 Eulerian approach

  把空间划分成若干个网格，分析网格内密度随时间变化

  <img src="https://www.qiniu.cregskin.com/202203031124116.png" alt="image-20220303112402090" style="zoom:50%;" />

+ Material Point Method (MPM)

  Hybrid 结合这两种的方法

  













































