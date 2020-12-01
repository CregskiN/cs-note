#include <iostream>

int main(){
  std::cout << "hello world from main.cpp\n" << std::endl;
  return 0;
}

/* 
  g++ main.cpp # 预处理、编译、汇编、链接
  ./a.out # 运行可执行文件

  echo $? # 获取a.out运行后的返回结果（0）
 */