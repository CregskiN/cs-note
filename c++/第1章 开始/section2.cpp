/* 
  1.2 初识输入输出
  <iostream> = istream + ostream
  istream 标准输入对象 
    cin
  ostream 标准输出对象 
    cout 
    cerr 
    clog
  
 */

#include <iostream>

int main(){
  // std::cout << "Enter two numbers:" << std::endl;
  // int v1 = 0, v2 = 0;
  // std::cin >> v1 >> v2;
  // std::cout << "The sum of " << v1 << " and " << v2 << " is " << v1 + v2 << std::endl;

  std::cout << "/*" << std::endl;
  std::cout << "*/" << std::endl;
  std::cout << "/* \"*/\" */" << std::endl;
  // std::cout << /* "*/" /* "/*" */;

  return 0;
}
