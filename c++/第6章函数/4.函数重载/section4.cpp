
#include <array>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::string;
using std::vector;

const string &shorterString(const string &str1, const string &str2);
string &shorterString(string &str1, string &str2);

/*
 * 6.4 函数重载
 * 
 * + 6.4.1 重载与作用域
 */
int main() {
    /* 
        + 定义函数重载
     */

    /* 
        + 判断两个形参的是否相同
            - 根据类型判断
            - 重载也是函数名相同，而形参类型不同
     */

    /* 
        + 重载和const形参
            - 一个有顶层const的形参，无法与没有const的形参区分
                Record lookup(Phone phone);
                Record Lookup(const Phone phone); // 重复声明 Record lookup(Phone phone);
                Record lookup(Phone*);
                Record lookup(Phone const*) // 重复声明  Record lookup(Phone*);
            - 如果形参是指针｜引用，可用const区分实现重载。此时是底层const
                Record lookup(Account&);
                Record lookup(const Account&); // 新函数 指向常量的引用
                Record lookup(Account*);
                Record lookup(const Account*); // 新函数 指向常量的指针
     */

    /* 
        + const_cast 和 重载
            - const_cast 改变 底层const 的 类型
     */
    string str101 = "hello";
    string &str102 = str101;
    string str103 = "world!";
    string &str104 = str102;
    std::cout << shorterString(str102, str104) << std::endl; // hello

    /* 
        + 调用重载的函数
            - 函数匹配 function matching：把函数调用于一组重载函数中某一个关联起来，也叫做 重载确定 overload resolution
            - 调用重载函数时，有三种可能结果：
                编译器找到一个与实参最佳匹配 best match 的函数，并生成调用该函数的代码
                找不到匹配的函数，发错 无匹配 no matching 的错误
                有多于一个函数可以匹配，但没有完全匹配，称为 二义性调用 ambiguous call
     */

    /**
     * 6.4.1 重载与作用域
     * 
     * 
     */



    return 0;
}

/**
 * @brief 返回相对短的字符串
 * 
 * @param str1 
 * @param str2 
 * @return const string& 
 */
const string &shorterString(const string &str1, const string &str2) {
    return str1.size() < str2.size() ? str2 : str1;
}

/**
 * @brief 
 * 
 * @param str1 
 * @param str2 
 * @return string& 
 */
string &shorterString(string &str1, string &str2) {
    // 增加const，使用旧函数
    auto &res = shorterString(const_cast<const string &>(str1), const_cast<const string &>(str2));
    // 去除const，返回
    return const_cast<string &>(res);
}
