#include <array>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cassert>

using std::string;
using std::vector;


string screen(string::size_type width = 80, string::size_type height = 80, char background = ' ');
inline const string &shorterString(const string &str1, const string &str2);

/*
 * 6.5 特殊用途语言特性
 * 
 * + 6.5.1 默认实参
 * + 6.5.2 内联函数和constexpr函数
 * + 6.5.3 调试帮助
 */
int main() {
    /**
     * 6.5.1 默认实参
     * 
     */
    std::cout << screen() << std::endl;  // width=80,height=80,background=
    std::cout << screen(45) << std::endl;
    std::cout << screen('?') << std::endl;
    // std::cout << screen(, , '?') << std::endl; // error 只能省略第一个以外的参数

    /**
     * 6.5.2 内联函数和constexpr函数
     * 
     * + 内联函数可避免函数调用的开销
     * + constexpr函数
     */

    /* 
        + 内联函数可避免函数调用的开销
            - 调用函数的流程
                保存寄存器，并在返回时恢复；可能需要拷贝实参；程序转向一个新的位置执行
     */
    string str101 = "hello";
    string &str102 = str101;
    string str103 = "world!";
    string &str104 = str102;
    std::cout << shorterString(str102, str104) << std::endl;  // hello

    /**
     * 6.5.3 调试帮助
     *  场景：在开发阶段执行一部分调试代码如cout，发布阶段自动屏蔽
     * 
     * + assert预处理宏
     * + NDEBUG预处理变量
     */
    /* 
        + assert预处理宏
            - assert(expr)
            - 如果expr为0，输出信息并终止程序；如果expr为1
     */
    /* 
        + NDEBUG预处理变量
            - 如果未定义NDEBUG，则assert什么都不做，定义了NDEBUG，assert执行
            - 有两种控制调试状态开关的方法
                #define NDEBUG 关闭调试
                gcc -D NEDBUG main.c 编译器选项
     */

    return 0;
}

/**
 * @brief 返回屏幕信息
 * 
 * @param width 
 * @param height 
 * @param background 
 * @return string 
 */
string screen(string::size_type width, string::size_type height, char background) {
    string res = "width=";
    res += std::to_string(width);
    res += ",height=";
    res += std::to_string(height);
    res += ",background=";
    res += background;
    return res;
}

/**
 * @brief 返回较短字符串的常量引用
 * 
 * @param str1 
 * @param str2 
 * @return const string& 
 */
inline const string &shorterString(const string &str1, const string &str2) {
    return str1.size() < str2.size() ? str2 : str1;
}