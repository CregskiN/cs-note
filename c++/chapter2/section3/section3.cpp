/*
  2.3 复合类型
  引用
  指针
  复合类型的声明

 */
#include <iostream>
#include <math.h>

const int bufferSize = 512;
int getBufferSize();

int main() {

  /*
    引用
   */

  /*
    1. 引用是对象的别名
   */
  // int intVal = 1024;
  // int &refVal = intVal;
  // int &refVal2 = intVal;
  // std::cout << refVal << std::endl; // 1014
  // std::cout << refVal2 << std::endl; // 1024

  /*
    2. 引用的定义
      &
      必须初始化
      值必须为对象
   */
  // 引用定义时必须初始化
  // int refiv1;
  // 引用的值不能是字面量
  // int &refiv = 4096; // 非常量引用的初始值必须为左值

  /*
    指针
      存储对象的地址 取地址符&
      指针的值：对象、紧邻对象所占空间的下一个位置、空指针、无效指针
        指针访问对象值 *
        空指针
        赋值和指针
        其他指针操作
        void*指针
   */
  // 存储对象的地址
  int ival = 42;
  int *p = &ival;

  // 指针访问对象值 *
  std::cout << *p << std::endl; // 42
  // 输出指针的地址值
  std::cout << p << std::endl; // 0x7ffee3d075c8

  // 空指针
  // 实际上存储的地址值是0 预处理器做的处理
  int *p1 = nullptr;
  std::cout << p1 << std::endl; // 0x0
  int *p2 = 0;
  std::cout << p2 << std::endl; // 0x0
  int *p3 = NULL;
  std::cout << p3 << std::endl; // 0x0

  // void* 指针
  // 可以存放任意类型
  void *vp = nullptr;
  vp = &ival;
  double dval = 3.14;
  vp = &dval;
  std::cout << *vp << std::endl; // error 只能存放地址，但不能取对象值

  /*
   3. 复合类型的声明
     定义多个变量
     指向指针的指针

   */
  // 一条语句，定义指针、变量
  int *p1, p2; // p1是指针，p2是int
  // 指向指针的指针
  



  return 0;
}
