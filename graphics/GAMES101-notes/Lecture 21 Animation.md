[TOC]

# 1. History

科学研究产生第一部电影

# 2. KeyFrame animation

关键帧动画，技术角度讲，就是用插值**计算一个点向另一个点移动过程中的位置**

<img src="https://www.qiniu.cregskin.com/202203011633467.png" alt="image-20220301163319433" style="zoom:50%;" />





# 3. Physical simulation 物理仿真

衣物仿真

流体仿真



## Mass Spring System 质点弹簧系统

+ <img src="https://www.qiniu.cregskin.com/202203011650556.png" alt="image-20220301165045528" style="zoom:50%;" /> 

  + $f_{a \rarr b}$ 为质点 a 向质点 b 施加的弹力 

  + $k_s$ 为弹簧系数：刚度 stiffness

+ 添加拉伸距离项

  <img src="https://www.qiniu.cregskin.com/202203021651520.png" alt="image-20220302165143459" style="zoom:50%;" /> 

  + Rest length 弹簧静止长度
  + <img src="https://www.qiniu.cregskin.com/202203021655995.png" alt="image-20220302165507969" style="zoom:33%;" /> 为方向向量（已单位化）
  + **存在的问题：弹簧震动不会停止**

+ 对所有质点，引入摩擦力

  <img src="https://www.qiniu.cregskin.com/202203021658841.png" alt="image-20220302165803815" style="zoom:50%;" /> 

  + $k_d$ 为阻尼系数 damping coefficient

  + **存在的问题：所有质点以相同速度移动时，质点没有相对位移，弹簧的震荡也不会停止**

    这个摩擦力只能描述外部对弹簧整体的影响，而不能描述弹簧内部质点的相互作用

+ 改进摩擦力，引入两质点的相对速度

  <img src="https://www.qiniu.cregskin.com/202203021720903.png" alt="image-20220302172011876" style="zoom:50%;" /> 

  + <img src="https://www.qiniu.cregskin.com/202203021721220.png" alt="image-20220302172125190" style="zoom:40%;" /> 为 b 对 a 的相对运动速度，在 a 到 b 方向上的投影

    > 单位向量1 dot 向量2 等价于 向量2在向量1方向上的投影

  + **为什么需要投影？**

    答：不是所有力，都能使弹簧发生形变。如固定弹簧一点，另一点做匀速圆周运动



三种模型：

<img src="https://www.qiniu.cregskin.com/202203021726888.png" alt="image-20220302172604858" style="zoom:50%;" />

**模拟一块布**

假设用以下模型模拟一块布：



<img src="https://www.qiniu.cregskin.com/202203021730418.png" alt="image-20220302173009392" style="zoom:33%;" />

该模型存在两个问题：

+ 在 sheer 力下，无法保持形状
+ 在对折（out-of-plane bending 平面外弯曲）下，像一张很薄的纸，没有恢复原状的力



**方案1：添加斜对角线**

<img src="https://www.qiniu.cregskin.com/202203021733034.png" alt="image-20220302173317005" style="zoom:33%;" /> <img src="https://www.qiniu.cregskin.com/202203021735823.png" alt="image-20220302173534794" style="zoom:33%;" />

存在的问题：

左图：

1. 模型不对称，导致受力形变各向异性。布应该是对称的
2. 在对折时，没有维持原形状的力

 右图：

1. 无法应对对折

**方案2：隔点加线**

<img src="https://www.qiniu.cregskin.com/202203021738959.png" alt="image-20220302173816928" style="zoom:33%;" /> 

在对折时，红色的线会有少量形变，提供一种抵抗对折的力（符合布的特性）



**FEM (Finite Element Method) Instead of Springs 有限元方法，另一种对力传导的建模**



## Particle System 粒子系统

<img src="https://www.qiniu.cregskin.com/202203022131458.png" alt="image-20220302213148431" style="zoom: 25%;" />

粒子系统：将大量粒子的集合，建模为动力系统，每个粒子都受一组力

+ 理解起来很简单
+ 粒子越少，计算用时越少；粒子越多，复杂度越高

可能需要解决的问题：

+ 大量的粒子：流体 fluids 模拟
+ 加速结构：如寻找附近的粒子，以进行力的传导

每一帧动画需要进行的操作：

+ 创建新的粒子
+ 计算每个粒子的受力
+ 更新每个粒子的位置和速度 velocity
+ 移除无效粒子
+ 渲染粒子

粒子系统受力分析：

+ 引力、斥力
  + 重力、电磁力... 弹力、推力
+ 阻力 Damping forces
  + 摩擦力、空气摩擦、粘滞力
+ 碰撞 Collisions
  + 墙体、容器、固定物体

> 粒子系统，本质上定义的是个体与群体的关系



模拟鸟群：

将鸟群建模为简单的粒子，进行受力分析

<img src="https://www.qiniu.cregskin.com/202203022141021.png" alt="image-20220302214118990" style="zoom:50%;" />

+ **attraction** 一定范围内的粒子，往一个中心聚集
+ **repulsion** 如果粒子靠的过于近，会产生斥力
+ **alignment** 每个个体朝向，为一定范围内其他粒子朝向的平均值





# 4. Kinematics 运动学

## Forward Kinematics 正运动学

关于骨架的一些定义：

+ 拓扑结构、关节几何联系、树形结构（无回路）

关节类型：

+ Pin 1D rotation <img src="https://www.qiniu.cregskin.com/202203022150320.png" alt="image-20220302215011293" style="zoom:25%;" /> 
+ Ball 2D rotation <img src="https://www.qiniu.cregskin.com/202203022151528.png" alt="image-20220302215133499" style="zoom:25%;" /> 
+ Prismatic joint 铰链 <img src="https://www.qiniu.cregskin.com/202203022152197.png" alt="image-20220302215221170" style="zoom:25%;" />

**举一个关于 Ball  的 Forward Kinematics 的例子**：

<img src="https://www.qiniu.cregskin.com/202203022156048.png" alt="image-20220302215613001" style="zoom:33%;" />

已知两个 segment 各自的角度，计算末端坐标

如要实现一个连贯的动作，只需要给出 $\theta$ 随时间的变化：

<img src="https://www.qiniu.cregskin.com/202203022157670.png" alt="image-20220302215746644" style="zoom:50%;" />

优点：

+ 直接控制非常方便
+ 实现起来简单直接

缺点：

+ 物理定律在动画中不一定适用 :-)
+ 对设计师来说，基于物理概念进行的操作，非常麻烦

所以催生了逆运动学



## Inverse Kinematics 逆运动学

<img src="https://www.qiniu.cregskin.com/202203022201042.png" alt="image-20220302220103014" style="zoom:50%;" />

动画师提供末端位置，计算机计算出合适的关节角度

<img src="https://www.qiniu.cregskin.com/202203022202250.png" alt="image-20220302220253223" style="zoom:50%;" />

存在的问题：

+ 逆运动学的解不唯一

<img src="https://www.qiniu.cregskin.com/202203022203069.png" alt="image-20220302220322041" style="zoom:50%;" />

+ 逆运动学的解集是有边界的

  <img src="https://www.qiniu.cregskin.com/202203022203786.png" alt="image-20220302220346759" style="zoom:50%;" />

解决方法：**梯度下降法**

<img src="https://www.qiniu.cregskin.com/202203022206323.png" alt="image-20220302220638294" style="zoom:50%;" />



# 5. Rigging 索具

<img src="https://www.qiniu.cregskin.com/202203022207265.png" alt="image-20220302220704234" style="zoom:50%;" />



# 6. Motion Capture 动作捕捉

给真人加一些控制点，通过控制点调整虚拟人物

需要建立 虚拟人物控制点-动捕演员 的映射

优点

+ 能迅速捕获大量真实数据
+ 真实数据的质量很高

缺点

+ 复杂、贵
+ 捕获到的动画，可能不符合动画师的要求，需要甄别修改





多种定义控制点的方法：

<img src="https://www.qiniu.cregskin.com/202203022213250.png" alt="image-20220302221335215" style="zoom:50%;" />



应用最广泛是光学方法

<img src="https://www.qiniu.cregskin.com/202203022213357.png" alt="image-20220302221313330" style="zoom:50%;" />



如何模拟真实的运动



















