/*
  1.4 控制流
  while
  for
  读取数量不定的输入cin数据

  编译阶段，找出的错误 
    syntax error 语法错误
    type error 类型错误
    declaration error 声明错误
  
  if
  
 */

#include <iostream>

int main() {
  int sum = 0, value = 0;

  while (std::cin >> value) {
    sum += value;
  }
  std::cout << "Sum is: " << sum << std::endl;

  return 0;
}