#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

/*
 * 3.3 标准库类型 vector
 *
 * + 3.3.1 定义和初始化vector对象
 * + 3.3.2 向vector对象中添加元素
 * + 3.3.3 其他vector操作
 */
int main() {
    /*
        + 标准库类型vector表示对象的集合，其中所有对象的类型都相同
        + vector集合中每个对象都有一个与之对应的索引，用于访问对象
        + 容器 container：因为vector容纳其他对象，所以称为
     */
    /*
        + C++有类模版class template，也有函数模版
        + vector 属于类模版
        + 编译器根据模版创建类或函数的过程，称为实例化instantiation
        + 编译器实例化，需要指定将模版实例化为何种类型（参考java的泛型）
        + 如果vector容器内元素还是vector
            旧版编译器写法 vector<vector<int> >
            C++11 写法 vector<vector<int>> 差了一个空格
     */
    vector<int> vec000;
    vector<vector<string>> vec001;

    /**
     * 3.3.1 定义和初始化vector对象
     *
     * + 定义vector七种方法
     * + 列表初始化vector对象
     * + 创建指定数量的元素
     * + 值初始化
     * + 列表初始值还是元素数量？
     */
    // 定义vector
    typedef int T;
    vector<T> vec101;
    vector<T> vec102(vec101);
    vector<T> vec103 = vec102;
    vector<T> vec104(10, 123);
    vector<T> vec105(10);
    vector<T> vec106{1, 2, 3, 4};
    vector<T> vec107 = {1, 2, 3, 4};

    /*
        列表初始化vector对象
     */
    vector<string> articles = {"a", "b", "cde"};

    /*
        创建包含指定数量元素的vector容器
     */
    vector<int> vec108(10, -1);        // 10 个 -1
    vector<string> vec109(10, "hi!");  // 10 个 "hi!"

    /*
        列表初始值 和 创建指定数量的元素
     */
    // 正常用法
    vector<int> vec110(10);     // 10 个元素 值为0
    vector<int> vec111{10};     // 1 个元素，值为 10
    vector<int> vec112(10, 1);  //
    vector<int> vec113{10, 1};  //

    // 当用花括号，不能执行列表初始化，编译器用默认初始值构造
    // vector<string> vec114("hi!");  // error
    vector<string> vec115{"hi!"};     // 列表初始化
    vector<string> vec116{10};        // 10 个 默认初始化元素
    vector<string> vec117{10, "hi"};  // 10 个 "hi"

    /**
     * 3.3.2 向 vector对象添加元素
     *  初始化有两种：1. 直接初始化 2. 列表初始化
     *
     * + push_back 压到末尾
     *
     */
    vector<int> vec201;
    vec201.push_back(10);

    // 因为 vector 创建时，无需指定大小。所以不应用for 遍历vector

    /**
     * 3.3.3 其他vector操作
     *
     * + v.empty() 判空
     * + v.size() 返回元素个数
     * + v.push_back()
     * + v[n]
     * + v1 = v2 用v2中的元素拷贝覆盖v1
     * + v1 = {a, b, c...} 用列表元素替换v1
     * + v1 == v2 // 当且仅当v1 v2元素数量相同、对应位置元素相同，
     * + < <= > >= 以字典顺序比较
     */
    /*
        + 可用 范围for 遍历 vector
        + 不能用 vec[1] 添加元素，只可以访问
     */

    vector<unsigned> scores(11, 0);  // 11个分数段 0-9,10-19....90-99,100
    vector<unsigned> grades = {42, 65, 95, 100, 39, 67, 95,
                               76, 88, 76, 83,  92, 76, 93};
    for (auto grade : grades) {
        scores[grade / 10]++;
    }
    // for(int i = 0; i < scores.size(); i++){
    //     std::cout << scores[i] << "  ";
    // }

    










    return 0;
}
