#include <array>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Sales_data.h"
#include "Screen.h"
#include "Window_mgr.h"

using std::string;
using std::vector;

/*
 * 7.3 类的其他特性
 * 
 * + 7.3.1 类成员再探
 * + 7.3.2 返回*this的成员函数
 * + 7.3.3 类类型
 * + 7.3.4 友元再探
 */
int main() {
    /**
     * 7.3.1 类成员再探
     * 
     * + 定义一个类型成员
     * + Screen类 的成员函数
     * + 令成员作为内联函数
     * + 重载成员函数
     * + 可变数据成员
     * + 类数据成员的初始值
     */
    /* 
        + 定义一个类型成员
            - Screen类：表示显示器的一个窗口
                * 
     */
    /* 
        + Screen类的成员函数
     */

    /* 
        + 令成员作为内联函数
            - 声明在类内的成员函数，默认是内联的
     */

    /* 
        + 重载成员函数
     */
    Screen myscreen;
    char ch = myscreen.get();
    ch = myscreen.get(0, 0);

    /* 
        + 可变数据成员
            场景：需要改变类的某个数据成员，包括const成员函数内
            可变数据成员 mutable data member：mutable 
            - 用处？
                在一个常量对象，的const成员函数内，改变该对象某成员数据的值
     */

    /* 
        + 类数据成员初始值，两种写法
            - std::vector<Screen> screens = {Screen(24, 80, ' ')};
            - std::vector<Screen> screens{Screen(24, 80, ' ')};
     */

    /**
     * 7.3.2 返回*this的成员函数
     * 
     * + 从const成员函数返回*this
     * + 基于const的重载
     */
    /* 
        Screen &Screen::move(Screen::pos r, Screen::pos c)
            返回类型是 Screen&，是对象本身的引用，而不是对象的副本
     */
    myscreen.move(4, 0).set('#');

    // myscreen.display().set('*'); // error 由于display()返回的是const Screen&，而set()不是const成员函数，所以不能在const Screen上调用set
    // Screen screen2;
    // screen2.set('a');

    /* 
        + 基于const的重载
            - 通过区分const成员函数，可以对函数重载
                对于常量对象，只能用const成员函数
                对于非常量对象，可以用const成员函数和普通函数
            - 所以，对非常量对象，非常量版本的成员函数是更好选择
     */
    // 调用 display 返回的对象是否是const，取决于调用display的对象是否是const
    Screen &screen = myscreen.display(std::cout);
    const Screen screen201;
    const Screen &obj202 = screen201.display(std::cout);

    /**
     * 7.3.3 类类型
     * 
     * + 类的声明
     */
    /* 
        Sales_data item1;
        等价于
        class Sales_data item1;
     */
    /* 
        + 类的声明
            - 前向声明 forward declaration：class Screen; 只声明，不定义
            - 前向声明 属于 不完全类型 incomplete type，也就是说我们知道Screen是一个类类型，但不知道有哪些成员

     */

    /**
     * 7.3.4 友元再探
     * 
     * + 类之间的友元关系
     * + 令成员函数作为友元
     * + 函数重载和友元
     * + 友元声明和作用域
     */

    /* 
        - 非成员函数可定义为友元
        - 其他类可定义为友元
        - 其他类的成员函数也可以定义为友元
        - 友元函数能定义在类的内部，且隐式内联
     */
    /* 
        + 类之间的友元关系
            - 场景：Window_mgr类需要清除某Screen类的内容，需要调用Screen::clear()，而clear需要访问Screen对象的私有成员
            - 解决办法：把Window_mgr指定成Screen的友元
            - 注意：友元不存在传递性，即Screen的友元是Window_mgr，而Window_mgr的友元与Screen无关
     */

    /* 
        + 令成员函数作为友元
            - 场景：Window_mgr中成员函数clear需要访问Screen，可以只让clear称为Screen的友元
            - 必须遵循的设计方式：
                1. 定义Window_mgr，其中声明clear但不能定义 // 在clear使用Screen的成员之前必须声明Screen
                2. 定义Screen，包括友元clear声明
                3. 定义clear // 此时可以访问Screen的成员
     */

    /* 
        + 函数重载和友元
            - 场景：对所有同名重载函数 分别声明友元
     */

    /* 
        + 友元声明和作用域
            struct X {
                friend void f() { //友元函数可以定义在类内部
                }
                X() { f(); }  // error f 还没有声明
                void g();
                void h();
            };
            void X::g() { return f(); }  // error f 还没有声明
            void f();                    // 声明那个定义在X中的函数
            void X::h() { return f(); }  // 正确：现在 f 声明在作用域中了
     */


    return 0;
}
