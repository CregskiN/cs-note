#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::string;
using std::vector;

/*
 * 5.6 try语句块 和 异常处理
 *
 * + 5.6.1 throw表达式
 * + 5.6.2 try语句块
 * + 5.6.3 标准异常
 */
int main() {
    /**
     * 5.6.1 throw表达式
     *
     */

    /**
     * 5.6.2 try语句块
     *
     */

    /**
     * 5.6.3 标准异常
     *      C++标准库的异常类，分布在四个头文件中
     * + exception 定义了最通用的异常类，只报告异常的发生，不提供任何额外信息
     * + stdexcept 定义集中常用异常类
     * + new 定义了 bad_alloc异常类型
     * + type_info 定义了 bad_cast异常类型
     */

    /*
        + stdexcept 定义的异常类
            - exception 最常见的问题
            - runtime_error 只有在运行时才能检测出的问题
            - range_error 运行时错误：生成的结果超出有意义的值域范围
            - overflow_error 运行时错误：计算上溢
            - underflow_error 运行时错误：计算下溢
            - logic_error 程序逻辑错误
            - domain_error  逻辑错误：参数对应的结果值不存在
            - invalid_argument 逻辑错误：无效参数
            - length_error 逻辑错误：试图创建一个超出该类型最大长度的对象
            - out_of_range 逻辑错误：使用一个超出有效范围的值
     */

    try {
        throw std::runtime_error("抛出一个异常");
    } catch (std::runtime_error err) {
        std::cout << err.what() << std::endl; // 抛出一个异常
    }

    return 0;
}
