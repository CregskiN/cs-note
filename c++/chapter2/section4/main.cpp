/*
  2.4 const
    1. const的引用
      意义是：禁止使用引用改变对象值
    2. 指针和const
    3. 顶层const
    4. constexpr和常量表达式

 */
#include <iostream>
#include <math.h>

int main() {
  /*
    1. const的引用
      意义：引用绑定不可修改、引用指向的值不可修改
      引用 绑定到 const对象 => 称为对常量引用 reference to const
      引用(const引用、普通引用) 绑定到 值(const对象、普通对象、表达式、字面量)
      引用(const) 绑定到 值(与引用不同类型)

   */
  // 引用(const引用、普通引用) 初始化 值(const对象、普通对象、表达式、字面量)
  // const引用 初始化 const对象
  const int ci1 = 1024;
  const int &cri1 = ci1;
  std::cout << "cri1: " << cri1 << std::endl;
  // 修改引用绑定的对象的值 失败
  // cri1 = ci1 * 2; // error: 表达式必须是可修改的左值

  // 普通引用 初始化 const对象 失败 // 普通引用 不能绑定 常量对象
  // int &ri1 = ci1;
  // std::cout << "ri1: " << ri1 << std::endl;
  // 修改引用的值 失败
  // ri1 = ci1 * 2; // error: 表达式必须是可修改的左值

  // 对const引用 初始化 普通对象
  int i2 = 2048;
  int i22 = 1000;
  const int &cri2 = i2;
  std::cout << "cri2: " << cri2 << std::endl;
  // 修改
  // cri2 = i22; // error: 表达式必须是可修改的左值
  // 普通引用 初始化 普通对象
  // 略
  // const引用 初始化 表达式
  const int &cri3 = i2 * 2;
  std::cout << "cri3: " << cri3 << std::endl;
  // 修改
  // cri2 = 1000;
  // 普通引用 初始化 表达式
  // int &ri3 = i2*2; // error: 非常量引用的初始值必须为左值
  // const引用 初始化 字面量
  const int &cri4 = 3072;
  std::cout << "cri4: " << cri4 << std::endl;
  // 普通引用 初始化 字面量
  // int &ci4 = 3072; // error: 非常量引用的初始值必须为左值

  // 引用(const) 绑定到 值(与引用不同类型)
  // 原规定：引用类型 与 对象类型 必须一致，但有两个意外：
  // 1. const引用初始化值，可以是表达式，但表达式结果必须能转换为const的类型
  const double dv1 = 3.14;
  const int &cri5 = dv1;
  std::cout << "cri5: " << cri5 << std::endl; // cri5: 3
  // 原理：
  /*
    // 编译器对
      double dval = 3.14;
      const int &ri = dval;
    // 有如下操作
    // 生成一个临时量
      double dval = 3.14;
      const int temp = dval;
      const int &ri = temp;
      // 最终ri绑定的是中间量
  */
  // 2. const引用初始化值，可以是字面量
  const int cri6 = 3.14;
  // cri6 = 6.28;
  std::cout << "cri6: " << cri6 << std::endl; // crd6: 3
  int i7 = 10;
  int &ri7 = i7;
  const int &cri7 = i7;
  ri7 = 20;
  std::cout << "cri7: " << cri7 << std::endl; // cri7: 20

  /*
    2. 指针和const
      指向常量的指针 pointer to const
        指针存储的地址可以改变，但指针指向对象的值不能变
      常量指针 const pointer
        指针存储的地址不能变，指针指向对象的值也不可以变

      意义是：不变的是指针本身的值，而不是指向的对象的值
      指针(常量指针、指向常量的指针) 指向 对象(常量、非常量)

   */
  double odval = 3.33;

  // pointer to const指向常量的指针 指向 非常量对象
  double tem1 = 1.11;
  const double *ptem1 = &tem1;
  std::cout << *ptem1 << std::endl; // 1.11
  // 修改 pointer to const 指向的 非常量对象的值 失败
  // *ptem = 2.22;
  // ptem1 = &odval;
  // std::cout << "ptem1: " << *ptem1 << std::endl; // ptem1: 3.33

  // pointer to const 指向常量的指针 指向 常量对象
  const double temp2 = 2.22;
  const double *ptem2 = &temp2;
  // 修改 pointer to const 指向 常量对象的值 失败
  // *ptem2 = 3.33; // ptem2: 2.22
  ptem2 = &odval; // ptem2: 3.33
  std::cout << "ptem2: " << *ptem2 << std::endl;

  // 总结：pointer to const 存储的地址可以改变，但指针指向对象的值不能变

  int oival = 1000;
  // const pointer 常量指针 指向 非常量对象
  int errNumb = 0;
  int *const curErr = &errNumb;
  *curErr = 1; // 修改 const poiner 指向非常量对象的值 成功
  // curErr = &oival; // 修改 const pointer 存储的地址 失败
  std::cout << *curErr << std::endl; // 1

  // const pointer 常量指针 指向 常量对象
  const double pi1 = 3.14;
  const double pi2 = 1.234;
  const double *const ppi1 = &pi1;
  // *ppi1 = 3.3333; // 修改const pointer 指向对象的值 失败
  // ppi1 = &pi2; // 修改const pointer 存储的地址 失败

  // 总结：指针存储的地址不能变，指针指向对象的值也不可以变

  /* 
    reference to const：引用绑定到const对象
      1. 绑定关系不能改变
      2. 不能使用引用改变绑定对象的值
    pointer to const：指向常量的指针
      1. 绑定关系可以改变
      2. 指向对象的值是否可修改，取决于对象是否是const
    const pointer：常量指针
      1. 绑定关系不可改变
      2. 指向对象是否可修改，取决于对象是否是const

   */

  /* 
    3. 顶层 const
      1. 顶层const，top-level const：
        表示指针本身是个常量 const pointer
      2. 底层const，low-level const：
        表示指针/引用 指向对象是个常量 pointer to const、reference to const

   */
  int i = 0;
  int ii = 10;
  int *const p1 = &i; // pointer to const // p1是顶层const // 不能改变p1的值
  // p1 = &ii; // p1顶层const的值不能改变
  

  const int ci = 42; // ci是顶层const // 不能改变ci的值
  const int cii = 44;
  const int *p2 = &ci; // pointer to const // p2是底层const // 允许改变p2的值
  p2 = &ii;
  p2 = &cii;
  // *p2 = 1; // 底层const 不能改变

  const int *const p3 = p2; // const pointer // 右const为顶层const，左const为底层const
  // *p3 = 3; // 底层const 指向对象 不能修改
  // p3 = &ii; // 顶层const 指针不能修改

  const int &r = ci; // reference to const // 底层const
  // r = 22; // 底层const 不能修改

  i = ci; // ci是底层const，
  p2 = p3;
  // 放弃


  /* 
    4. constexpr 和 常量表达式
   */
  


  return 0;
}
