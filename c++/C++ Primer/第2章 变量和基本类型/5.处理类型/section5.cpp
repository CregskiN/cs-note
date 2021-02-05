#include <math.h>

#include <iostream>

/*
 *  2.5 处理类型
 * 问题：复杂场景下，对于用到的类型有两个痛点：
 * 1. 难于拼写
 * 2. 语义不明。需要翻找上下文
 *
 * + 2.5.1 类型别名
 * + 2.5.2 auto类型说明符
 * + 2.5.3 decltype类型指示符
 */

int getInt();

int main() {
    /**
     * 2.5.1 类型别名 type alias
     *
     * + 两种方法定义类型别名 typedef、using
     * + 指针、常量和类型别名
     */

    // typedef
    typedef double wages;
    typedef wages base, *pointer;
    std::cout << sizeof(wages) << std::endl;    // 8
    std::cout << sizeof(base) << std::endl;     // 8
    std::cout << sizeof(pointer) << std::endl;  // 8

    // using 别名声明 alias declaration
    using D = double;

    /**
     * （1）指针、常量和类型别名
     *
     */
    typedef char *pstring;  // pstring 等价于 char*
    char ch = 'a';
    const pstring cstr = &ch;  // 等价于 char *const 常量指针
    const pstring *ps =
        &cstr;  // 等价于 const char** ps是一个指针，ps指向的对象是
                // 指向char的常量指针
    /*
        此处要理解 const 是对给定类型的修饰，如：
            + pstring 的基本数据类型是指针
            + const pstring 中const修饰的是指针pstring，即“不变的指针”常量指针
        延伸到常量指针、指向常量的指针、指向常量的常量指针的写法
            + char *const constPointer; // 强调 constPointer 指针存储的值不能变
            + const char pointerToConst; // 强调指针指向的对象的类型不能变
            + const char *const constPointerToConst; //
       第一个const强调指针指向的类型不能变，第二个const强调指针存储的值不能变
     */

    /**
     * 2.5.2 auto类型说明符
     * 场景：使用表达式推导出类型，并把表达式的值作为初始值
     *
     * + 复合类型、常量 和 auto
     */
    /*
        auto：C++11，让编译器根据 初始化表达式 分析变量所属的类型
     */
    int val1 = 10;
    double val2 = 3.14;
    auto item = val1 + val2;
    std::cout << sizeof(item) << std::endl;  // 8

    /*
        复合类型、常量 和 auto
            + auto 自动忽略顶层const，保留底层const
            + 可用 const auto 加上顶层const
     */

    /**
     * 2.5.3 decltype类型指示符
     * 场景：希望从表达式中推导出类型，但不使用表达式作为初始值
     *
     * + decltype 和 引用
     *
     */
    int val30 = 30;
    int val31 = 31;
    decltype(getInt()) sum = val31;

    const int ci = 0, &cj = ci;
    decltype(ci) x = 0;  // x 的类型是 const int
    decltype(cj) y = x;  // y 的类型是 const int&
    // decltyp(cj) z; // z 的类型是const int&，必须初始化

    /*
        decltype 和 引用

        decltype()接收的如果是表达式，会转化为引用
     */
    int i = 42, *p = &i, &r = i;
    decltype(r + 0) b; // r+0 结果是int，而不是int&，所以不用初始化
    // decltype(*p) c; // error *p解引用获得的类型是 int* 必须初始化

    /* 
        decltype() 和 decltype(())
     */
    // decltype((i)) d; // error i被视为表达式
    decltype(i) e;

    



    return 0;
}

int getInt() { return 10; }