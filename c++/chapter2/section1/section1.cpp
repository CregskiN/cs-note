/*
  2.1 基本内置类型
    2.1.1 基本类型
      算术类型
        字符型
          char 字符 8bit
          wchar_t 宽字符 16bit
          char16_t Unicode字符 16bit
          char32_t Unicode字符 32bit
        整型型
          short 短整型 16bit
          int 整型 16bit
          long 长整型 32bit
          long long 长整型 64bit
        浮点型
          float 单精度浮点数 6位有效数字。通常32bit
          double 双精度浮点数 16位有效数字。通常64bit
          long double 扩展精度浮点数。通常 96bit or 128bit
        C++语言规定：
          int >= short
          long >= int
          long long >= long
          bool长度不定
          float
          double
          long double
        按符号型、无符号型分类
          带符号 int、short、long、long long
          无符号 加 unsigned
        字符型char分为三类：
          char、signed char、unsigned char
      空类型 void

    2.1.2 类型转换
 
    2.1.3 字面量常量

 */
#include <iostream>
#include <math.h>

int section2() {

  // bool b = 42;
  // std::cout << b << std::endl; // 1

  // int i = b;
  // std::cout << i << std::endl; // 1

  // i = 3.14;
  // std::cout << i << std::endl; // 3

  // double pi = i;
  // std::cout << pi << std::endl; // 3.0

  // unsigned char c = -1;
  // std::cout << c << std::endl; // 255

  // signed char c2 = 256;
  // std::cout << c2 << std::endl;

  // int i = 42;
  // if (i) {
  //   i = 0;
  // }
  // std::cout << i << std::endl;

    

  return 0;
}
