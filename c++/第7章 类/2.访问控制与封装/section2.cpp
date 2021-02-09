#include <array>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Sales_data.h"

using std::string;
using std::vector;

/*
 * 7.2 访问控制与封装
 * 
 * + 7.2.1 友元
 */
int main() {
    /* 
        + 访问说明符
            - public 说明符之后的成员，可以被类的成员函数访问
            - private 说明符之后的成员，可以被类的成员函数访问，但是不能被使用该类的代码访问
     */

    /* 
        + 使用class和struct关键字
            - 不同：访问权限不同
                class可以设置public和private，struct默认public
     */

    /**
     * 7.2.1 友元 friend
     * 
     */

    /* 
        场景：非成员函数 无法访问 成员数据，也就是说 read、print 无法访问 bookNo、units_sold、revenue
        如果需要其他类或者函数，访问他的非公有成员，需要把其他类或函数变为 友元
     */






    return 0;
}
