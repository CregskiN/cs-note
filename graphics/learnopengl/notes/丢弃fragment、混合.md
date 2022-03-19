# GLSL discard



# 混合

<img src="https://www.qiniu.cregskin.com/202203182020083.png" alt="image-20220318202002056" style="zoom: 67%;" /> 

<img src="https://www.qiniu.cregskin.com/202203182020627.png" alt="image-20220318202029603" style="zoom:50%;" /> 



```c++
glEnable(GL_BLEND);
```

```c++
// 设置 F_source、F_destination
glBlendFunc(GLenum sfactor, GLenum dfactor)
// 设置常数颜色向量
glBlendColor(C_constant)
```

+ `sfactor` 源因子，即 $F_{source}$ alpha 因子对纹理颜色的影响
+ `dfactor` 目标因子，即 $F_{destination}$ alpha 对纹理下层颜色的影响

也可以使用glBlendFuncSeparate为RGB和alpha通道分别设置不同的选项：

```c++
glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
```

| 选项                          | 值                                                      |
| ----------------------------- | ------------------------------------------------------- |
| `GL_ZERO`                     | 因子等于00                                              |
| `GL_ONE`                      | 因子等于11                                              |
| `GL_SRC_COLOR`                | 因子等于源颜色向量C¯sourceC¯source                      |
| `GL_ONE_MINUS_SRC_COLOR`      | 因子等于1−C¯source1−C¯source                            |
| `GL_DST_COLOR`                | 因子等于目标颜色向量C¯destinationC¯destination          |
| `GL_ONE_MINUS_DST_COLOR`      | 因子等于1−C¯destination1−C¯destination                  |
| `GL_SRC_ALPHA`                | 因子等于C¯sourceC¯source的alphaalpha分量                |
| `GL_ONE_MINUS_SRC_ALPHA`      | 因子等于1−1− C¯sourceC¯source的alphaalpha分量           |
| `GL_DST_ALPHA`                | 因子等于C¯destinationC¯destination的alphaalpha分量      |
| `GL_ONE_MINUS_DST_ALPHA`      | 因子等于1−1− C¯destinationC¯destination的alphaalpha分量 |
| `GL_CONSTANT_COLOR`           | 因子等于常数颜色向量C¯constantC¯constant                |
| `GL_ONE_MINUS_CONSTANT_COLOR` | 因子等于1−C¯constant1−C¯constant                        |
| `GL_CONSTANT_ALPHA`           | 因子等于C¯constantC¯constant的alphaalpha分量            |
| `GL_ONE_MINUS_CONSTANT_ALPHA` | 因子等于1−1− C¯constantC¯constant的alphaalpha分量       |

更多的灵活性：允许我们设置运算符，它提供了三个选项：

```c++
glBlendEquation(GLenum mode)
```

<img src="https://www.qiniu.cregskin.com/202203191938526.png" alt="image-20220319193810493" style="zoom:50%;" /> 





当绘制一个有不透明和透明物体的场景的时候，大体的原则如下：

1. 先绘制所有不透明的物体。
2. 对所有透明的物体排序，按从远到近绘制所有透明的物体。





更高级的技术还有次序无关透明度(Order Independent Transparency, OIT)

