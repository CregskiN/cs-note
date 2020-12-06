/*
  2.4 const
 */
#include "file_1.h"
#include <iostream>
#include <math.h>

const int bufferSize = 512;
int getBufferSize();

int main() {
 /*
    2.4.0 多文件使用const变量
    file_1.cc 声明const变量并初始化
    file_1.h 声明变量
    main.cpp inclde file_1.h 就可以直接使用了
   */
  // std::cout << bufferSize << std::endl; // 512

  /*
    2.4.1 const 对常量的引用

   */
  // const int ci = 1014;
  // const int &r1 = ci;
  // r1 = 42; // 错误：r1是对常量的引用，不能修改，也不能初始化为字面量
  // int &r2 = ci; // 错误：非常量引用r2 不能引用常量对象ci
  // std::cout << ci << std::endl;

  /*
    引用类型必须与被引用类型相同，但有例外。
    允许常量引用 绑定 字面量 | 对象 | 一般表达式

    对const的引用，简称常量引用
   */
  // 正确：常量引用 绑定 对象
  int ii = 128;
  int i = 42;
  const int &r1 = i;
  // r1 = 64; // 错误：r1是一个常量引用，不能修改绑定的对象值
  // &r1 = ii; // 错误：r1是一个常量引用，不能指定新的绑定对象
  // 正确：常量引用 绑定 字面量
  // const int &r2 = 42;
  // 正确：常量引用 绑定 一般表达式
  // const int &r3 = r1 * 2;

  // 错误：普通引用 不能绑定 字面量
  // int &r4 = 42; // error: non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'

  // 错误：普通引用 不能绑定 一般表达式
  // int &r5 = r1 * 2; // error: non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
  // int &r6 = i * 2;  // error: non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'

  // 错误：普通引用 不能绑定 常量对象
  // const int cc = 64;
  // int &r7 = cc; // error: binding value of type 'const int' to reference to type 'int' drops 'const' qualifier

  // const double dval = 3.14;
  // const int &r = dval;
  // std::cout << r << std::endl; // 3
  // 实际上编译器进行的操作是：创建一个中间int常量对象，再让int常量引用 绑定 中间常量变量
  // const double dval = 3.14;
  // const int temp = dval;
  // const int &r = temp;
  // std::cout << r << std::endl; // 3

  // int v1 = 10;
  // int v2 = 20;
  // int &vr = v1;
  // vr = v2;
  // std::cout << "vr is " << vr << // 20
  // "\nv1 is " << v1 // 20
  // << "\nv2 is " << v2 // 20
  // << std::endl;


/* 
  2.4.2 指针和const
  指针 指向 常量 or 非常量
  指向常量的指针(pointer to const)不能改变对象的值，要想存储常量对象的地址，只能用pointer to const

 */
  const double pi = 3.14;
  // double *ptr = &pi; // 错误：非常量指针ptr 不能指向 常量对象pi
  const double *cptr = &pi; // 正确：常量指针cptr 可以指向 常量对象pi
  // *cptr = 6.28; // 错误：*cptr只读，不能赋值
  double dval = 9.42;
  cptr = &dval; // 正确：可以改变常量指针指向的对象，但不可改变常量指针指向对象的值？？？？
  std::cout << *cptr << std::endl; // 9.42
  







  return 0;
}
