#include <array>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>


using std::string;
using std::vector;

string::size_type find_char(const string &str, char ch, string::size_type &count);
void reset(int *i);
void reset(int &i);
void print(const char *constPointer);
void print(const int *begin, const int *end);
void print(const int ia[], size_t size);
void print(const int (*matrix)[3], size_t rowSize);
void error_msg(std::initializer_list<string> msg);
void error_msg(string errCode, std::initializer_list<string> msg);
// void foo(std::parm_list, ...);

/*
 * 6.2 参数传递
 *
 * + 6.2.1 传递参数
 * + 6.2.2 传引用参数
 * + 6.2.3 const形参 和 实参
 * + 6.2.4 数组形参
 * + 6.2.5 main: 处理命令行选项
 * + 6.2.6 含有可变形参的函数
 */
int main() {
    /*
        每次调用函数，关于形参、实参几个步骤：
            1. 调用函数
            2. 创建形参
            3. 传入实参
            4. 用实参初始化形参
        所以，形参的类型决定了形参和实参交互的方式
            - 如果形参是引用类型，调用参数后形参和实参绑定
            - 如果是非引用类型，将实参的值拷贝后，赋值给形参
        两个概念：
            1. 引用传递 passed by reference
                形参是引用类型，我们说实参被引用传递，或者被传引用调用
            2. 传引用调用 called by reference

            3. 传值调用 called by value
                形参是非引用类型，实参的值被拷贝给形参，形参实参是两个独立的对象。我们说实参被值传递，或者函数被传值调用
     */

    /**
     * 6.2.1 传值参数
     *
     * + 指针形参
     *
     *  指针形参和值形参一样，在调用函数时都是先拷贝再赋值给实参
     *  注意：
     *      在函数中，尽量使用引用类型的形参，代替指针形参
     */

    /**
     * 6.2.2 传引用参数
     *
     * + 使用引用，避免拷贝
     * + 使用引用形参，返回额外信息
     */
    /*
        + 使用引用避免拷贝
            拷贝大的类类型对象，或容器对象比较低效，甚至有的类类型（IO类型）不支持拷贝操作，只能通过引用形参访问
     */
    /*
        + 使用引用形参返回额外信息
            见 find_char 函数
     */

    /**
     * 6.2.3 const形参和实参
     * 
     * + 指针或引用形参与const
     * + 尽量使用常量引用
     */
    /* 
        + 指针或引用形参与const
     */
    int int301 = 0;
    const int cInt301 = int301;
    string::size_type ctr = 0;
    reset(&int301);  // 调用形参为 int* 的reset
    // reset(&cInt301); // error 不能用 const int对象 初始化 int*
    reset(int301);  // 调用形参为 int& 的reset
    // reset(cInt301); // error 没有匹配的函数 // 不能用 const int 初始化 int*｜int&
    // reset(42); // error 没有匹配的函数 // 不能用 42 初始化 int*｜int&
    // reset(ctr); // error 没有匹配的函数 // 不能用 size_type 初始化 int*｜int&
    // 正确 可以用字面值初始化const string&
    find_char("Hello World!", 'o', ctr);

    /* 
        + 尽量使用常量引用
            - 如find_char("Hello World!", 'o', ctr);没有报错，是因为find_char第一个形参是常量引用，支持字面量初始化
            - 如果find_char在另一个函数中调用，也必须传递常量引用
     */

    /**
     * 6.2.4 数组形参
     * 
     * + 数组形参，只能传递指针
     * + 使用标记指定数组长度
     * + 使用标准库规范
     * + 显式传递一个表示数组大小的形参
     * + 数组形参和const
     * + 数组引用形参
     * + 传递多维数组
     */
    /* 
        + 数组形参只能传递指针
            以下三种写法是等价的：
                - void printf(const int*)
                - void printf(const int[])
                - void printf(const int[10])
     */

    /* 
        因为数组是以指针形式传递的，函数并不知道数组长度
        + 使用标记指定数组长度
     */
    const char chars401[] = {'C', '+', '+'};
    print(chars401);
    /* 
        + 标准库规范 begin end
     */
    const int ints401[] = {1, 2, 3, 4, 5, 6};
    print(std::begin(ints401), std::end(ints401));
    /* 
        + 显式传递一个表示数组大小的形参
     */
    const int ints402[] = {1, 2, 3};
    size_t size = std::end(ints402) - std::begin(ints402);
    print(ints402, size);

    /* 
        数组形参 和 const
            - 当不需要修改数组中元素的值，用const
            - 需要修改，不用const
     */

    /* 
        传递多维数组
     */
    const int ints403[][3] = {{1, 3, 4}, {3, 5, 7}, {7, 9, 0}};
    print(ints403, 3);

    /**
     * 6.2.5 main：处理命令行选项
     * 
     * main函数的接收参数
     * 
     * main(int argc, char *argv[])
     * 
     */

    /**
     * 6.2.6 含有可变形参的函数
     *  场景：无法预知应该向函数传递几个实参
     * 
     * + initializer_list形参
     * + 省略符形参
     */
    /* 
        + initializer_list形参
            - 在同名头文件中
     */
    /* 
        initializer_list 提供的操作
            - initializer_list<T> lst; // 默认初始化：T类型元素的空列表
            - initializer_list<T> lst{a, b, c...}; // lst的元素数量和初始值一样多 // lst的元素是对应初始值的副本 // 列表中的元素是const
            - lst2(lst1) // 拷贝或将一个initializer_list对象
            - lst2 = lst // 原始列表和副本共享元素
            - lst.size()
            - lst.begin()
            - lst.end()
     */
    std::initializer_list<string> ls601;
    std::initializer_list<int> li601;
    error_msg({"functionX", "ok"});
    error_msg("400", {"functionX", "ok"});

    /* 
        + 省略符形参
            省略符...
            场景：访问吗某些特殊的C代码，这些代码使用了varags的C标准库功能
     */

    return 0;
}

/**
 * @brief
 *
 * @param str
 * @param ch 指定字符
 * @param count 字符出现的位置
 * @return string::size_type
 */
string::size_type find_char(const string &str, char ch, string::size_type &count) {
    auto res = str.size();  // 第一次出现的位置
    count = 0;              // 总共出现的次数
    for (decltype(res) i = 0; i != str.size(); ++i) {
        if (str[i] == ch) {
            if (res == str.size()) {  // 如果还没记录过ch位置
                res = i;              // 就记录一下
                ++count;
            } else {  // 如果记录过ch位置
                ++count;
            }
        }
    }
    return res;
}

void reset(int *i) {
    i = 0;
}
void reset(int &i) {
    i = 0;
}

/**
 * @brief 参考对C风格字符串的处理，有局限性
 * 
 * @param constPointer 
 */
void print(const char *constPointer) {
    if (constPointer) {
        while (*constPointer) {
            std::cout << *constPointer;
            ++constPointer;
        }
    }
    std::cout << "\n";
}

/**
 * @brief 标准库规范，类似迭代器
 * 
 * @param begin 
 * @param end 
 */
void print(const int *begin, const int *end) {
    while (begin != end) {
        std::cout << *begin++ << " ";
        std::cout << "\n";
    }
}

/**
 * @brief 显式接受一个数组长度的参数
 * 
 * @param ia 
 * @param size 
 */
void print(const int ia[], size_t size) {
    for (size_t i = 0; i != size; ++i) {
        std::cout << ia[i] << " ";
    }
    std::cout << "\n";
}

/**
 * @brief 
 * 
 * @param matrix 是一个指针、是一个指向包含10个元素的数组的指针、是一个指向包含10个int元素的数组的指针
 * @param rowSize 行数
 */
void print(const int (*matrix)[3], size_t rowSize) {
    for (size_t i = 0; i < 3; ++i) {
        const int *row = matrix[i];
        print(row, rowSize);
    }
}

void error_msg(std::initializer_list<string> msg) {
    for (auto begin = msg.begin(); begin != msg.end(); ++begin) {
        std::cout << *begin << " ";
    }
    std::cout << "\n";
}

void error_msg(string errCode, std::initializer_list<string> msg) {
    std::cout << "ERROR: " << errCode << std::endl;
    for (auto begin = msg.begin(); begin != msg.end(); ++begin) {
        std::cout << *begin << " ";
    }
    std::cout << "\n";
}

// void foo(parm_list, ...){}
