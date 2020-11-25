/* 
  1.5 类简介



 */
#include <iostream>
#include "Sales_item.h"


int main(){

  Sales_item book;
  
  // 读入ISBN号，售出的册数、销售价格
  std::cin >> book;
  
  // 写入ISBN号，售出的册数、总销售额、平均价格
  std::cout << book << std::endl;

  return 0;
}
