
#include <array>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::string;
using std::vector;

/*
 * 4.11 类型转换
 * 
 * + 4.11.1 算数转换
 * + 4.11.2 其他隐式类型转换
 * + 4.11.3 显式转换
 */
int main() {
    /**
     * 4.11.3 显式转换
     * 
     * + 命名的强制类型转换
     * + static_cast
     * + const_cast
     * + reinterpret_cast
     * + 旧式的强制类型转换
     */
    /* 
        强制类型转换cast
     */
    int int301, int302;
    double slope = int301 / int302;  // int被显式转换为double
    // 本质上非常危险

    /* 
        + 命名的强制类型转换
            cast-name<type>(expression)
            - cast_name 是static_cast | dyamic_cast | const_cast | reinterpret_cast
            - type 转换的目标类型
            - expression 是要转换的值
     */
    const int constIntVal = 42;          // 顶层const
    const int *lowConst = &constIntVal;  // 底层const
    int intVal = 44;
    int *const topConst = &intVal;              // 顶层const
    const int *const TopAndLowConst = &intVal;  // 外顶层 内底层 const

    /* 
        + static_cast
            - 功能：改变 顶层const 的数据类型
            - 局限：底层const无法转换
            任何具有明确定义的类型转换，只要不包含底层const都可以使用static_cast
     */
    // 对 顶层const 类型转换 bingo
    // double *const topConst301 = static_cast<double *>(topConst); // error 因为topConst指向的是int，改变指针类型很危险
    double constIntVal301 = static_cast<double>(constIntVal);

    // 对 底层const 类型转换 
    // const double *lowConst301 = static_cast<const double *>(lowConst);

    /* 
        + const_cast
            - 功能：改变底层const的类型，同时也是唯一去除const的操作符
            - 局限：只能改变底层const
            - 常用于有函数重载的上下文中
     */
    int *lowConst302 = const_cast<int *>(lowConst);  // 把 int *const 变成 int*
    // *lowConst302 = 1024;
    // std::cout << *lowConst302 << std::endl; // 1024

    /* 
        + reinterpret_cast
            - 功能：为运算对象的位模式提供较低层次上的重新解释
            - 非常危险！
     */

    return 0;
}
