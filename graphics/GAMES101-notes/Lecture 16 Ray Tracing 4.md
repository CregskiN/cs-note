[TOC]



# 0. 前情提要

上节

+ 辐射度量学深入 Radiometry cont.
+ 光线传播 Light transport 
  + 反射方程 The reflection equation 
  + 渲染方程 The rendering equation 
+ 全局光照 Global illumination 
+ 概率论复习 Probability review



本节

+ A Brief Review 
+ 蒙特卡洛积分 Monte Carlo Integration
+ 路径追踪 Path Tracing



# 1. A Brief Review

## 1.1 渲染方程

<img src="https://www.qiniu.cregskin.com/202202040926932.png" alt="image-20220204092632885" style="zoom:50%;" />

Shading point 半球范围内，来自光源的光、来自其他物体反射过来的光、自发光加到一起，就是最终光强度



## 1.2 连续型随机变量

<img src="https://www.qiniu.cregskin.com/202202040928269.png" alt="image-20220204092859241" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202202040929098.png" alt="image-20220204092907073" style="zoom:50%;" />

<img src="https://www.qiniu.cregskin.com/202202040929478.png" alt="image-20220204092915452" style="zoom:50%;" />



# 2. Monte Carlo Integration

> 黎曼积分：高等数学中的元素法

<img src="https://www.qiniu.cregskin.com/202202061757881.png" alt="image-20220206175740847" style="zoom:50%;" />

蒙特卡洛积分可以看做广义上的黎曼积分，即按**某种分布** $pdf(x)$ 对函数值采样，计算积分区域对应面积，最后求平均，作为最终积分值

定义如下：

<img src="https://www.qiniu.cregskin.com/202202081124584.png" alt="image-20220208112401557" style="zoom:50%;" />



> 对 $\frac{f(X_i)}{pdf(X_i)}$ 求均值，近似于求期望：
>
> <img src="https://www.qiniu.cregskin.com/202202081129733.png" alt="image-20220208112959699" style="zoom:50%;" />
>
> 由 $E(x) = \int_{a}^{b} f(x) \cdot pdf(x) \, {\rm d}x$ ，得：
>
> <img src="https://www.qiniu.cregskin.com/202202081131573.png" alt="image-20220208113103531" style="zoom:50%;" />
>
> 可知，对 $F_N$ 近似的期望，是对积分值的一个无偏估计量



蒙特卡洛积分比黎曼积分更广义之处，在于可以更改对函数值的采样（分布），以**均匀分布**为例，定义如下：

<img src="https://www.qiniu.cregskin.com/202202081138934.png" alt="image-20220208113801909" style="zoom:50%;" />

最终得出：

<img src="https://www.qiniu.cregskin.com/202202081138477.png" alt="image-20220208113822451" style="zoom:50%;" />

> 注意：
>
> 1. 样本越多，方差越小
>
>    <img src="https://www.qiniu.cregskin.com/202202081139931.png" alt="image-20220208113937905" style="zoom:50%;" />
>
>    可知：
>
>    <img src="https://www.qiniu.cregskin.com/202202081139120.png" alt="image-20220208113955094" style="zoom:50%;" />
>
> 2. 注意 x 代表什么（结合渲染方程）



# 3. Path Tracing

## 3.1 Whitted-Styled 的不足

Whitted-Styled Ray Tracing：

+ 光线在光滑物体表面发生反射、折射
+ 在漫反射表面停止

存在的不足：

1. 只能反映在镜面表面的反射，而磨砂表面无法表示

   <img src="https://www.qiniu.cregskin.com/202202071819999.png" alt="image-20220207181945970" style="zoom:50%;" />

2. 光线在物体表面一次漫反射后，不能继续漫反射 

   左图表示仅考虑直接光照（无漫反射在物体间进行），右图考虑全局光照

   > 直接光照：从光源出发，照射到物体表面，反射到人眼
   >
   > 全局光照：从光源出发，经过多次反射、折射，进入人眼

   <img src="https://www.qiniu.cregskin.com/202202071819653.png" alt="image-20220207181929623" style="zoom:50%;" />

> 由此得出结论，Whitted-Style 是错误的，而渲染方程是正确的



## 3.2 解渲染方程

回顾渲染方程（所有 $\omega$ 方向都是从 Shading point 向外）

<img src="https://www.qiniu.cregskin.com/202202080940570.png" alt="image-20220208094011533" style="zoom:50%;" />



因自发光项直接计算得出，故对渲染方程简化如下：

<img src="https://www.qiniu.cregskin.com/202202081148745.png" alt="image-20220208114840717" style="zoom:50%;" />

> L 的物理意义是 Shading point 发射到观测点的 Radiance 值，而 Radiance 值到具体的亮度，还有一层转换



### 3.2.1 直接光照

蒙特卡洛积分公式：

<img src="https://www.qiniu.cregskin.com/202202081155602.png" alt="image-20220208115504575" style="zoom:50%;" />

+ 变量 $x$ 对应半球范围内的单位角 $\omega_i$

+ 被积函数 $x$ 对应<img src="https://www.qiniu.cregskin.com/202202081156276.png" alt="image-20220208115608248" style="zoom: 40%;" />

+ pdf 对应 <img src="https://www.qiniu.cregskin.com/202202081156444.png" alt="image-20220208115631418" style="zoom:40%;" />

> 整球角 $4\pi$ ，半球 $2\pi$，均匀分布，则 $pdf = \frac{1}{2\pi}$

代入，得：

<img src="https://www.qiniu.cregskin.com/202202081200150.png" alt="image-20220208120016120" style="zoom:50%;" />

**逻辑**：

1. 从 Shading point 向半球范围内，按 pdf 分布选定方向 wi

2. 遍历每个方向 wi，发射射线 r

   若 r 与光源有交叉，则计算 Lo

   若无交叉，则该 Shading point 对像素着色结果无贡献

**伪代码如下**：

```c++
shade(p, wo){
	Randomly choose N directions wi~pdf
	Lo = 0.0
	For each wi
	Trace a ray r(p, wi)
	If ray r hit the light
		Lo += (1 / N) * L_i * f_r * cosine / pdf(wi)
	Return Lo
}
```



> 不足：仅考虑直接光照，不考虑从其他物体反射过来的光线是不真实的



### 3.2.2 引入间接光照

<img src="https://www.qiniu.cregskin.com/202202081006907.png" alt="image-20220208100641874" style="zoom:67%;" />

由上图可知，本用于求 Shading point - 光源 相交的射线 PQ 交物体于 Q，可以把 Q 当作面光源，做 shade 处理。

**逻辑如下**：

1. 从 Shading point 向半球范围内，按 pdf 分布选定方向 wi

2. 遍历每个方向 wi，发射射线 r

   若 r 与光源有交叉，则计算 Lo

   若 r 与物体 q 有交叉，则先在 q 点做 shade(q, -wi)，将结果作为 p 点做 shade 时的一个参数，计算 Lo

   若无交叉，则该 Shading point 对像素着色结果无贡献

**伪代码如下**：

```c++
shade(p, wo){
  Randomly choose N directions wi~pdf
  Lo = 0.0
  For each wi
  Trace a ray r(p, wi)
  If ray r hit the light
  	Lo += (1 / N) * L_i * f_r * cosine / pdf(wi)
  Else If ray r hit an object at q
  	Lo += (1 / N) * shade(q, -wi) * f_r * cosine
  / pdf(wi)
  Return Lo
}

```





## 3.3 存在的问题

### 不足1: 光线的数量会随光线的弹射呈爆炸式增加

<img src="https://www.qiniu.cregskin.com/202202081008837.png" alt="image-20220208100829809" style="zoom:50%;" />

N = 1 时，光线不会爆炸（N 表示在半球范围内采样的数量）

> $N = 1$，就叫路径追踪 Path Ray Tracing
>
> $N \ne 1$，叫分布追踪 Distributed Ray Tracing

解决方法是，每个 Path 用一条光线，但一个像素采用多个 Path 求平均

<img src="https://www.qiniu.cregskin.com/202202081013310.png" alt="image-20220208101312273" style="zoom:50%;" />

```c++
shade(p, wo){
  Randomly choose `ONE` direction wi~pdf(w)
  Trace a ray r(p, wi)
  If ray r hit the light
  	Return L_i * f_r * cosine / pdf(wi)
  Else If ray r hit an object at q
  	Return shade(q, -wi) * f_r * cosine / pdf(wi)
}
```

最终，改良后的 Path Tracing **逻辑如下**：

1. 在每个 pexel 中选择 N 个样本点（N 条单根的光线）

2. 遍历每个样本点，发射一条射线 $r(camera, sample)$

   若 r 能反射/折射出一条从观测点到光源的路径，则累加到该 pixel 的渲染结果

   若无法找到这条路径，则该样本无贡献

**伪代码如下**：

```c++
ray_generation(camPos, pixel){
  Uniformly choose N sample positions within the pixel
  pixel_radiance = 0.0
  For each sample in the pixel
  	Shoot a ray r(camPos, cam_to_sample)
  	If ray r hit the scene at p
  		pixel_radiance += 1 / N * shade(p, sample_to_cam)
  Return pixel_radiance
}
```



### 不足2: shade 递归截止条件不好规定

俄罗斯轮盘赌 Russian Roulette

+ 在某次弹射进行前，先进行概率 P 判断是否应该继续弹射

  + 若继续弹射，则返回值为 $L_0 / P$

  + 若停止弹射，则返回值为 0（作为递归截止条件）

> 为什么返回值是 $L_0 / P$ ，而不是 $L_0 \cdot P$？
>
> <img src="https://www.qiniu.cregskin.com/202202081546932.png" alt="image-20220208154608855" style="zoom:40%;" /> 不会改变该 Shading point 的 Radiance 的期望 「？？？？？」

伪代码如下：

```c++
shade(p, wo){
  // Manually specify a probability P_RR
	// Randomly select ksi in a uniform dist. in [0, 1]
  If (ksi > P_RR) return 0.0;
  
  Randomly choose ONE direction wi~pdf(w)
  Trace a ray r(p, wi)
  If ray r hit the light
  	Return L_i * f_r * cosine / pdf(wi) / P_RR
  Else If ray r hit an object at q
  	Return shade(q, -wi) * f_r * cosine / pdf(wi) / P_RR
}
```



### 不足3: 效率很低

**每个 Path 能打到光源的概率是非常低的！**

<img src="https://www.qiniu.cregskin.com/202202081551161.png" alt="image-20220208155117129" style="zoom:50%;" />

反射光方向 wi 是否能打到光源，对渲染结果有决定性影响，受 Path 数量、光源大小影响。

原渲染方程，是对方向角 wi 积分，由 $d\omega = \frac{dA}{r^2}$ 知 <img src="https://www.qiniu.cregskin.com/202202081720812.png" alt="image-20220208172038774" style="zoom: 35%;" /> 代入改写成：

<img src="https://www.qiniu.cregskin.com/202202081037829.png" alt="image-20220208103722799" style="zoom:50%;" />



> 对于直接光照采用换元后的积分，间接光照还是采用原积分

> 对于直接光照，无需采用 RR

```c++
shade(p, wo){
  # Contribution from the light source.
  Uniformly sample the light at x’ (pdf_light = 1 / A)
  L_dir = L_i * f_r * cos θ * cos θ’ / |x’ - p|^2 / pdf_light
    
  # Contribution from other reflectors.
  L_indir = 0.0
  Test Russian Roulette with probability P_RR
  Uniformly sample the hemisphere toward wi (pdf_hemi = 1 / 2pi)
  Trace a ray r(p, wi)
  If ray r hit a non-emitting object at q
  	L_indir = shade(q, -wi) * f_r * cos θ / pdf_hemi / P_RR
  
  Return L_dir + L_indir
}
```

还差最后一步，增加对于 Shading point 到光源的遮挡检测：

```c++
shade(p, wo){
  # Contribution from the light source.
  Uniformly sample the light at x’ (pdf_light = 1 / A)
  L_dir = 0.0
  Shoot a ray from p to x’
	If the ray is not blocked in the middle
  	L_dir = L_i * f_r * cos θ * cos θ’ / |x’ - p|^2 / pdf_light

    
  # Contribution from other reflectors.
  L_indir = 0.0
  Test Russian Roulette with probability P_RR
  Uniformly sample the hemisphere toward wi (pdf_hemi = 1 / 2pi)
  Trace a ray r(p, wi)
  If ray r hit a non-emitting object at q
  	L_indir = shade(q, -wi) * f_r * cos θ / pdf_hemi / P_RR
  
  Return L_dir + L_indir
}
```



> 点光源怎么处理？一般处理成很小的面光源





