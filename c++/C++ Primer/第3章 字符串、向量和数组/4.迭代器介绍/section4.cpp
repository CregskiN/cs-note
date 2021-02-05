#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

int binary_search(vector<int> data, int num);

/*
 * 3.4 迭代器介绍
 *
 * + 3.4.1 使用迭代器
 * + 3.4.2 迭代器运算
 */
int main() {
    /*
        + 下标运算符[] 可用于访问
       string、vector，还有一种更通用的机制实现同样目的：迭代器iterator
        + 所有标准库容器都支持迭代器，但只有少数支持 下标运算符[]
        + string不属于容器类型，但string支持很多容器类型类似的操作，如迭代器

        what？
        + 容器通用的一种访问方式
        why？
        + 类似指针，可以间接访问对象
        + 迭代器的对象，是容器中的元素或string中的字符

     */

    /**
     * 3.4.1 使用迭代器
     *
     * + begin end成员
     * + 迭代器运算符
     * + 将迭代器从一个元素移动到另一个元素
     * + 迭代器类型
     * + begin 和 end 运算符
     * + 某些对vector对象的操作，会使迭代器失效
     */
    /*
        迭代器有成员函数 begin、end
            尾后 off the end：尾元素的下一个位置 one past the end

            begin 负责返回第一个元素的迭代器
            end 返回尾后迭代器 off-the-end iterator，简称尾迭代器
     */
    vector<int> vec101(10, 0);
    auto b = vec101.begin();
    auto e = vec101.end();
    // 如果容器为空，begin() end() 返回同一个迭代器，尾后迭代器

    /*
        迭代器运算符
        + iter // 返回迭代器所指元素的索引
        + iter->me // 解引用iter并获取该元素的名为mem的成员，等价于(*iter).mem
        + ++iter // 令iter指示容器中的下一个元素
        + --iter // 令iter指示容器中上一个元素
        + iter1 == iter2 //
       判断两个迭代器是否相等，如果指示的是同一个元素｜同为尾迭代器，则相等
     */
    string str101 = "some string";
    if (str101.begin() != str101.end()) {  // 判空
        auto iter = str101.begin();
        *iter = toupper(*iter);
    }
    std::cout << str101 << std::endl;  // Some string

    /*
        将迭代器从一个元素移动到另一个迭代器
        + 使用递增运算符++
     */
    for (auto iter = str101.begin(); iter != str101.end() && !isspace(*iter);
         iter++) {
        *iter = toupper(*iter);
    }
    std::cout << str101 << std::endl;  // SOME string

    /*
        迭代器类型
            iterator
            const_iterator
     */
    // iterator 可读可写
    vector<int>::iterator iter101;
    string::iterator iter102;
    // const_iterator 只读
    vector<int>::const_iterator iter103;
    string::const_iterator iter104;
    // 根据 vector对象、string对象 是不是常量，决定迭代器类型 一般auto

    /*
        begin 和 end 运算符
            + begin end 返回的迭代器类型是
       iterator还是const_iterator，由对象是不是常量决定
     */
    vector<int> vec102;
    const vector<int> vec103;
    // 默认行为
    vector<int>::iterator iter105 = vec102.begin();        // iterator
    vector<int>::const_iterator iter106 = vec103.begin();  // const_iterator
    // 有时候需要确定的类型 cbegin cend
    vector<int>::const_iterator iter107 = vec102.cbegin();
    vector<int>::const_iterator iter108 = vec103.cbegin();

    /*
        结合解引用和成员访问操作
     */
    vector<string> vec104 = {"123", "456"};
    vector<string>::iterator iter109 = vec104.begin();
    std::cout << (*iter109).empty() << std::endl;  // 0
    // C++的箭头运算符-> 把解引用和访问成员两个操作结合
    // (*iter).empty() 等价于 iter->empty()
    std::cout << iter109->empty() << std::endl;  // 0

    vector<string> text = {"hello", "", "world!"};
    for (auto iter = text.cbegin(); iter != text.cend() && !iter->empty();
         iter++) {
        std::cout << (*iter) << std::endl;
    }

    /*
        某些对vector对象的操作，会使迭代器失效
            + 不能在 范围for 中向vector添加元素
            + 不能改变 vector 的容量
     */

    /**
     * 3.4.2 迭代器运算
     *
     * + 迭代器的算术运算
     * + 使用迭代器运算
     */
    /*
        迭代器的算术运算
            + iter + n
            + iter - n
            + iter += n
            + iter -= n
            + iter1 - iter2 // 左小右大
            + > < >= <= // 迭代器越往后越大
     */
    // 算术运算的类型是 difference_type
    vector<int> vec201 = {1, 2, 3, 4};
    auto BsubE = vec201.begin() - vec201.end();  // -4

    vector<int> data = {1, 2, 3, 4, 5};
    std::cout << binary_search(data, 3) << std::endl; // 2

    

    return 0;
}

/**
 * @brief 用迭代器实现的二分搜索
 *
 * @param data
 * @param num
 * @return int
 */
int binary_search(vector<int> data, int num) {
    auto beginIter = data.begin(), endIter = data.end();
    auto midIter = data.begin() + (endIter - beginIter) / 2;
    while (midIter != endIter && *midIter != num) {
        if (num < *midIter) {
            endIter = midIter;
        } else {
            beginIter = midIter + 1;
        }
        midIter = beginIter + (endIter - beginIter) / 2;
    }
    return midIter - data.begin();
}
