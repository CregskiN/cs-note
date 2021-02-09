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
    + 类的基本思想：数据抽象 data abstraction 和 封装 encapsulation

    + 数据抽象：一种依赖于 接口 interface 和 实现 implementation 分离的变成技术
    + 类的接口：包括用户所能执行的操作
    + 类的实现：包括类的数据成员、负责接口实现的函数体、定义类所需的各种私有函数

    + 封装：实现了（数据抽象）类的接口和实现的分离。类的用户只能使用接口而无法访问实现部分

    + 类想要实现数据抽象和封装，需要定义一个数据抽象类型 abstract data type
 */

/*
 * 7.1 定义抽象数据类型
 * 
 * + 7.1.1 设计 Sales_data 类
 * + 7.1.2 定义改进的 Sales_data 类
 * + 7.1.3 定义类相关的非成员函数
 * + 7.1.4 构造函数
 * + 7.1.5 拷贝、赋值和析构
 */
int main() {
    /**
     * 7.1.1 设计 Sales_data 类
     * 
     * + 使用改进的 Sales_data 类
     * + 引入const成员函数
     */

    /* 
        Sales_data 的接口应包含：
            isbn 成员函数：用于返回对象的ISBN编号
            combine 成员函数：用于将一个Sales_data对象加到另一个对象上
            add 函数：执行两个Sales_data的加法
            read 函数：将数据从istream读入到Sales_data对象中
            print 函数：将Sales_data对象的值，输出到ostream
     */

    /* 
        + 使用改进的 Sales_data 类
            读入的数据 {book1, book1, book2, book3} isbn相同的订单是连续的
     */
    // Sales_data total;                            // 保存当前求和结果
    // if (read(std::cin, total)) {                 // 读入第一笔交易
    //     Sales_data trans;                        // 保存下一条交易数据的变量
    //     while (read(std::cin, trans)) {          // 读入剩余交易
    //         if (total.isbn() == trans.isbn()) {  // 检查isbn
    //             total.combine(trans);            // isbn相同，更新total
    //         } else {
    //             print(std::cout, total) << std::endl;  // isbn不同，输出total
    //             total = trans;                         // 处理下一本书
    //         }
    //     }
    //     print(std::cout, total) << std::endl;  // 输出最后一条交易记录
    // } else {
    //     std::cerr << "No data?!" << std::endl;  // 没有用户输入：通知用户
    // }

    /**
     * 7.1.2 定义改进的 Sales_data 类
     * 
     * + 定义成员函数
     * + 引入 this
     * + 引入 const成员函数
     * + 类作用域和成员函数
     * + 在类的外部定义成员函数
     * + 定义一个返回this对象的函数
     */
    /* 
        + 定义成员函数
            声明必须在类内，定义可以在类内或类外
     */

    /* 
        + 引入 this
            (*this).bookNo 等价于 this->bookNo
            Sales_data *this 是一个普通指针
     */
    int intVal201 = 41;
    const int *ptr201 = &intVal201;

    // const int intVal202 = 44;
    // int *ptr202 = &intVal202; // error 普通指针 不能指向 常量对象

    /* 
        + 引入const成员函数
            std::string isbn() const { return this->bookNo; } 
            - const 作用是：修改隐式this指针的类型（默认情况下是是 Sales_data *this）
            - 也就是说：不能把this 指向一个常量对象。也即：不能通过把this绑定到常量对象，从而使用常量对象调用成员函数
            - 这样的函数称为 常量成员函数
     */

    /* 
        + 类作用域和成员函数
            - 编译器有两步操作：
                1. 编译类内的成员声明
                2. 编译成员函数体
                因此，先于 bookNo 声明的 isbn() 函数体内可以获得 bookNo
     */

    /* 
        + 在类的外部定义成员函数
            - 声明在内，定义可内可外
            - 在外部的形参列表、形参列表后的const必须一致
     */

    /* 
        + 定义一个返回this对象的函数
            return *this
     */

    /**
     * 7.1.3 定义类相关的非成员函数
     * 
     * + 定义 print read
     * + 定义 add
     */

    /**
     * 7.1.4
     * 
     * + 合成的默认构造参数
     * + 某些类不能依赖于合成的默认构造参数
     * + 定义 Sales_data 的构造函数
     * + =default 的含义
     * + 构造函数初始值列表
     * + 在类的外部定义构造函数
     */
    /* 
        + 合成的默认构造函数
            - 类可以有多个构造函数
            - 不能声明称const的
            - Sales_data total; 执行了默认初始化，默认构造函数 default constructor
     */
    
    /* 
        + 某些类不能依赖于合成的默认构造函数
            1. 只有没有定义构造函数，编译器才会合成一个默认构造函数（依据：如果一个类在某种情况下需要控制对象初始化，那么很可能任何情况下都需要初始化）
            2. 合成的默认构造函数可能执行错误的操作
            3. 有时编译器无法为类合成默认构造函数（类内包含其他类类型的成员，且这个类没有默认构造函数）
     */

    /* 
        + 定义 Sales_data 的构造函数
     */

    /* 
        + =default 含义
            - Sales_data() = default; // 默认构造函数
            - 定义=default原因：我们既需要其他构造函数，也需要默认构造函数。且这个构造函数作用等同于之前的合成默认构造函数
            - Sales_data() = default; 之所以对 Sales_data 有用，是因为内置类型的成员提供了初始值，这也是C++11编译器所支持的
            - 如果编译器不支持=default，则默认构造函数应该使用 构造函数初始值列表 来是初始化每个类的每个成员
     */

    /* 
        + 构造函数初始值列表
            - Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n) {}   
            - : bookNo(s), units_sold(n), revenue(p * n) {} 称为构造函数初始值列表 constructor initialize list
            - 构造函数初始值列表 负责为 新创建的对象的成员赋初值

            - Sales_data(const std::string &s) : bookNo(s) {}
            - 只接收一个参数，等价于 Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(0), revenue(0.0) {}

            - 通常情况下，如果C++编译器支持类内初始值，应该使用类内初始值
            - 不支持类内初始值，可以使用 构造函数初始值列表
            - 注意：以上两个示例的 构造函数初始值列表函数体是空的，因为不需要在初始化时做什么操作
     */

    /* 
        + 在类的外部定义构造函数
     */

    /**
     * 7.1.5 拷贝、赋值、析构
     * 
     * + 某些类不能依赖于合成的版本
     */

    /* 
        - 关于类的操作：
        1. 类的初始化
        2. 类的拷贝、赋值、销毁对象
            类的赋值：赋值运算符=
            对象的销毁：局部对象，在块结束时销毁。vector容器被销毁，期内的对象也被销毁
        - 我们不主动定义这些操作，则编译器将自动合成。如赋值，会对每个成员数据赋值
     */
    // 如下边代码：
    // total = trans;
    // 等价于：
    // total.bookNo = trans.bookNo;
    // total.units_sold = trans.units_sold;
    // total.revenue = trans.revenue;

    /* 
        + 某些类不能依赖于合成的版本
            - 编译器能自动合成 拷贝、赋值、销毁 的操作。当类需要分配类对象之外的资源，合成版本会失效。如管理动态内存的类通常不能依赖于上述操作的合成版本
            - 值得注意的是
                需要动态内存的类，能使用 vector对象 或者 stirng对象 管理必要的存储空间，能避免分配、释放内存带来的复杂性
                
     */




    return 0;
}
