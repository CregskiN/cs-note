/*
  2.2

 */
#include <iostream>
#include <math.h>

int main() {
  
  // 2.3.1 引用
//  int i = 1024, i2 = 2048;
//  int &r = i, r2 = i2;
//  int i3 = 1024, &ri = i3;
//  int &r3 = i3, &r4 = i2;
//  std::cout << r << "  " << r3 << std::endl;
//  int &rvall = 1.01; // 错误做法
  
  // 2.3.2 指针
  // 指针定义
//  int *ip1, *ip2;
//  double dp, *dp2;

//  int ival = 42;
  
  // 指针存储某对象的地址
  // 使用&取地址符，获取指针指向的地址
//  int *p = &ival;
  
  // 指针不能指向引用，因为引用不是对象，没有实际地址
  
  // 指针类型和指向的对象类型严格一致
//  double dval;
//  double *pd = &dval;
//  double *pd2 = pd;
  
//  int *pi = pd; // 错误：指针、对象类型不匹配
//  pi = &dual; // 错误：指针、对象类型不匹配
  
  /**
   指针的值：
   1. 指向一个对象
   2. 指向紧邻对象所占空间的下一个位置
   3. 空指针，意味着没有指向任何对象
   4. 无效指针
   */
  
  /**
   利用指针访问对象
   解引用符 *，得出所指对象。
   如果给解引用结果赋值，实际上是给指针所指的对象赋值
   */
//  int ival = 42;
//  int *p = &ival;
//  std::cout << *p << std::endl; // 42
//  *p = 4;
//  std::cout << *p << std::endl; // 4
  
  /**
   符号的多重含义 *和&
   */
//  int i = 42;
//  int &r = i; // 声明整型r引用，指向对象i
//  int *p; // 声明整型指针p
//  p = &i; // 整型指针p存储整型内存i的地址
//  *p = i; // 解引用符 整型指针指向的内存的值 = i
//  int &r2 = *p; // 定义整型引用 指向 整型指针p指向的内存的值
  
  /**
   空指针
   */
  // 生成空指针
//  int *p1 = nullptr; // 等价于 int *p1 = 0;
//  std::cout << p1 << std::endl; // 0x0
//  int *p2 = 0; // 直接将p2 初始值化为字面量0
//  int *pe = NULL; // 等价于 *p3 = 0;
  
  
  /**
   赋值和指针
   指针和引用都能对其他对象间接访问，但是
   引用在声明之初，指向对象，不可更改
   指针可以
   */
  int i = 42;
  int *pi = 0; // 声明一个整型指针pi // 给指针赋值 地址0x0 // 但没有指向任何对象
  int *pi2 = &i; // pi2存放着变量i的地址 // pi2是指向对象为42
  std::cout << *pi2 << std::endl; // 42 // 输出指针pi2所指的对象
  std::cout << pi2 << std::endl; // 0x 7ffe efbf f568
  
  int *pi3; // pi3 无法确定
  pi3 = pi2; // pi3->i pi2->i
  pi2 = 0; // pi2->0 pi3->???
  std::cout << *pi3 << std::endl; // 42
  /**
   注意区分，改变的是指针的值，还是指针指向对象的值
   */
  
  /**
   其他指针操作
   */
  
  return 0;
}
