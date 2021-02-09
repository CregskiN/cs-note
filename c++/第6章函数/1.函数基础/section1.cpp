#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::string;
using std::vector;

size_t count_calls();

/*
 * 6.1 函数基础
 *
 * + 6.1.1 局部对象
 * + 6.1.2 函数声明
 * + 6.1.3 分离式编译
 */
int main() {
    /*
     * + 编写函数
     * + 调用函数
     * + 形参和实参
     * + 函数的形参列表
     * + 函数返回类型
     */

    /**
     * 6.1.1 局部对象
     *
     * + 局部变量 local variable：形参和函数题内部定义的变量统称为局部变量
     * + 自动对象
     * + 局部静态对象
     */

    /* 
        + 自动对象
            - what
                只存在于执行期间的对象，如函数中定义的变量
                块执行结束后，自动对象的值变成为定义的
        + 形参
            - what：是一种自动对象
            - why：传递给函数的实参，被用于初始化形参对应的自动对象
        + 局部静态对象 static
            - what：有时需要令局部变量的生命周期贯穿函数调用及之后的时间
            - how：static
     */
    // 计算函数自身被调用次数
    std::cout << count_calls() << std::endl; // 1
    std::cout << count_calls() << std::endl; // 2

    /**
     * 6.1.2 函数声明
     *
     * + 在头文件中进行函数声明
     */
    /* 
        + 在头文件中进行函数声明
            如sale.h中写函数声明、类声明，在sale.cpp中写函数定义
     */


    /**
     * 6.1.3 分离式编译
     *  场景：每个cpp文件独立编译
     * 
     * + 编译和链接多个源文件
     */
    

    return 0;
}

size_t count_calls(){
    static size_t ctr = 0;
    return ++ctr;
}