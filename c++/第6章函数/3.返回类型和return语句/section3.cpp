
#include <array>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::string;
using std::vector;

int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};

string make_plural(size_t ctr, const string &word, const string &ending);
const string &shorterString(const string &s1, const string &s2);
const string &manip();
vector<string> process();
int (*func_arr(int i))[10];
auto func_tail(int i) -> int (*)[10];

/*
 * 6.3 返回类型 和 return语句
 * 
 * + 6.3.1 无返回值的函数
 * + 6.3.2 有返回值的函数
 * + 6.3.3 返回数组指针
 */
int main() {
    /**
     * 6.3.1 无返回值函数
     * 
     */

    /**
     * 6.3.2 有返回值函数
     * 
     * + 值是如何被返回的
     * + 不要返回局部对象的引用或指针
     * + 引用返回左值
     * + 列表初始化返回值
     * + 主函数main的返回值
     * + 递归
     */
    /* 
        + 值是如何被返回的
            - 返回的值用于初始化调用点的一个临时量，该临时量就是函数调用的结果
            - 如果函数返回的引用，那就不再复制，直接返回原引用
     */
    const string res201 = make_plural(10, "hero", "es");

    const string &str201 = "hello";
    const string &str202 = "world!";
    const string &str203 = shorterString(str201, str202);
    std::cout << (str201 == str203) << std::endl;  // 1

    /* 
        + 不要返回局部对象的引用或指针
            函数完成后，占用的存储空间被释放，因此，局部变量的引用/指针，将不再指向有效区域
     */
    // std::cout << manip() << std::endl; // �L��`'�����L��!�sa�L��`'���`

    /* 
        + 引用返回左值
     */

    /* 
        + 列表初始化返回值
     */
    vector<string> strs201 = process();

    /* 
        + 主函数min的返回值
            - 为了让main函数返回值与机器无关，cstlib头文件定义了两个预处理变量
            - EXIT_FAILURE
            + EXIT_SUCCESS
     */

    /* 
        + 递归
     */

    /**
     * 6.3.3 返回数组指针
     * 
     * + 声明一个返回数组指针的函数
     * + 使用尾置返回类型
     * + 使用decltype
     */

    /* 
        + 声明一个返回数组指针的函数
     */
    int arr301[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int(*ptr301)[10] = func_arr(10);

    /* 
        + 使用尾置返回类型
     */
    int(*ptr302)[10] = func_tail(10);

    /* 
        + 使用decltype
     */

    return 0;
}

/**
 * @brief 如果ctr>1，返回 word 复数形式
 * 
 * @param ctr 
 * @param word 
 * @param ending 
 * @return string 
 */
string make_plural(size_t ctr, const string &word, const string &ending) {
    return (ctr > 1) ? word + ending : word;
}

/**
 * @brief 返回较短的string对象
 * 
 * @param s1 
 * @param s2 
 * @return const string& 
 */
const string &shorterString(const string &s1, const string &s2) {
    return s1.size() <= s2.size() ? s1 : s2;
}

/**
 * @brief 
 * 
 * @return const string& 
 */
const string &manip() {
    string res = " ";
    if (!res.empty()) {
        return res;
    } else {
        return "Empty";
    }
}

vector<string> process() {
    string expected;
    string actual;
    if (expected.empty()) {
        return {};
    } else if (expected == actual) {
        return {"functionX", "okey"};
    } else {
        return {"functionX", expected, actual};
    }
}

/**
 * @brief 一个返回数组指针的函数
 * 
 * + func(int i) # 调用func函数需要一个int类型实参
 * + (*func(int i)) # 可以对函数调用结果执行解引用
 * + (*func(int i))[10] # 解引用func()将得到一个大小为10 的数组
 * + int (*func(int i))[10] # 数组中的元素是int型
 * 
 * @return int(*)[10] 
 */
int (*func_arr(int i))[10] {}

/**
 * @brief 
 * 
 * @return int (*)[10] 
 * 
 * + 返回类型
 * + (*) 指针
 * + 指针指向有10个元素的数组
 * + 指针指向有10个整形元素的数组
 * 
 */
auto func_tail(int i) -> int (*)[10] {}

/**
 * @brief 返回一个指向数组的指针 
 * 
 * @param i 
 * @return decltype(odd)* 
 */
decltype(odd) *arrPtr(int i) {
    return (i % 2) ? &odd : &even;
}