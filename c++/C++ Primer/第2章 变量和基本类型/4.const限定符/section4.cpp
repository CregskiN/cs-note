#include <math.h>
#include <iostream>

int intValue = 40;
const int constIntValue = 44;
/*
 *  2.4 const 限定符
 * 场景：常量，不改变const的值
 * + const 初始化
 * + const的引用
 * + 指针 和 const
 * + 顶层const
 * + constexpr 和 常量表达式
 */

int getSize();

int main() {
    /**
     * const初始化
     *  有以下情况：
     * + 运行时初始化 bingo
     * + 编译时初始化 bingo
     * + 将其他变量值拷贝给const变量
     */
    // 运行时初始化
    const int cIntVal0 = getSize();  // bingo
    // 编译时初始化
    const int cIntVal1 = 42;  // bingo
    // 非const -> const
    int intVal0 = 2;
    const int cIntVal2 = intVal0;

    /*
     * 2.4.1 const的引用
     * 把引用绑定到一个const对象上，称为对常量的引用 reference to const
     * note: "给const对象起个别名"
     *
     * + 初始化 和 对const的引用
     * + 对const的引用 可能 引用一个非const的对象
     */
    const int cInt1 = 1024;
    const int &cRefInt1 = cInt1;  // 对const的引用
    // cRefInt1 = 42; // error 引用不是对象，不能修改
    // int &refInt2 = cInt1; // error 非常量引用 不能引用 常量对象

    // const引用初始化
    // 在 2.3.1 提到：引用的类型必须与其所引用的对象一致
    // 但有两个意外：此处是其中一个
    // 在初始化常量引用时，允许用"任意表达式"作为初始值，只要该"表达式的结果"能转换成"引用的类型"
    int int3 = 42;
    const int &cRefInt3 = int3;  // 常量引用 绑定到 "非常量对象"
    const int &cRefInt4 = 42;    // 常量引用 绑定到 字面量
    const int &cRefInt5 = cRefInt3 * 2;  // 常量引用 绑定到 表达式
    const double cDouble1 = 3.14;
    const int &cRefDouble1 =
        cDouble1;  // 常量引用 绑定到 可转化为引用的类型的对象

    // 注意：
    // 常量引用 仅仅对 引用可参与的操作
    // 做了限定，而对引用所绑定的对象是不是常量，未做限定

    /*
     * 2.4.2 指针和const
     * 指针可 指向 常量对象、非常量对象，
     * 其中，指向常量对象的指针 pointer to const 必须用 const 修饰
     *
     * + const 指针
     */

    const double pi = 3.14;
    // double *ptr = &pi; // error 指向常量对象 的 指针，必须用const修饰
    const double *cptr = &pi;
    // *cptr = 42; // error 指向常量的指针 不能修改 指向的对象的值
    double dval = 3.14;
    cptr = &dval;  // 指向常量的指针 指向 非常量对象
    // *cptr = pi * 2; // error 指向常量的指针 指向 非常量对象，不能修改对象的值

    // note：
    // 1. 指针有两种：指向常量的指针、一般指针；值有两种：常量值、非常量值
    // 2. 指向常量的指针 可以指向 常量值｜非常量值；一般指针 仅可以指向 非常量值
    // 3. const指针 只能指向常量对象

    // const指针
    // const pointer 常量指针
    // 指针是对象而引用不是，因此：
    // 1. 可以定义：指向常量的指针、常量指针、指向常量的引用
    // 2. 而不能定义 常量引用

    // *const 常量指针，即不变的是指针存贮的值，而不是指针指向对象的值

    int errNumb = 0;
    int *const curErr = &errNumb;  // curErr 将一直指向 errNumb
    // curErr 本身是个常量对象
    *curErr = errNumb * 2;
    const double pi1 = 3.1415926;
    const double *const pip = &pi1;  // pip 是一个指向常量对象的常量指针 const pointer

    // 总结：

    int val = 200;             // 定义非常量
    const int constVal = 100;  // 定义常量

    // reference 引用
    int &ref1 = val;  // 引用 绑定了 非常量
    // int &ref2 = constVal; // ERROR 引用 绑定了 常量 // 引用 不能绑定 常量
    // reference to const 对常量的引用
    const int &referenceToConst1 = val;  // 对常量的引用 绑定了 非常量
    const int &referenceToConst2 = constVal;  // 对常量的引用 绑定了 常量

    // pointer 指针
    int *pointer1 = &val;  // 指针 指向了 非常量
    // int *pointer2 = &constVal; // ERROR 指针 指向了 常量 // 指针 不能指向
    // 常量 pointer to const 指向常量的指针
    // 指向常量的指针可以指向常量、非常量，但不能用于改变其所指对象的值
    const int *pointerToConst1 = &val;  // 指向常量的指针 指向了 非常量
    const int *pointerToConst2 = &constVal;  // 指向常量的指针 指向了 常量
    // const pointer 常量指针
    // 指针本身是常量，即指针本身存储的值（地址）不能改变
    int *const constPointer1 = &val;  // 常量指针 指向了 非常量
    // int *const constPointer2 = &constVal; // ERROR 常量指针 指向了 常量 //
    // 常量指针 不能指向 常量
    const int *const constPointer3 = &constVal;  // 指向常量的常量指针 指向了 常量

    /**
     * 2.4.3 顶层const
     * 指针本身有两种：常量指针、指向常量的指针
     * 对象有两种：常量对象、非常量对象
     *
     * 顶层const：top-level const，表示指针本身是常量
     * 底层const：low-level const，表示指针指向的对象是常量
     * 
     * + 执行对象拷贝操作时，
     */
    int int30 = 0;
    int int31 = 31;
    int *const constPointer30 = &int30;  // constPointer 是 顶层const
    // constPointer30 = &int31; // error 不能改变constPointer的值
    const int constInt30 = 42;  // constInt 是 顶层const
    const int constInt31 = 43;  // constInt 是 顶层const
    // constInt30 = 44; // error 不能改变constInt的值
    const int *pointerToConst30 = &constInt30;  // pointerToConst 是 底层const
    // pointerToConst30 = &constInt31;  // pointerToConst 的值可以改变
    // *pointerToConst30 = 44; // error 但 底层const 指向的对象的值 不能改变
    const int *const constPointerToConst30 = pointerToConst30; // *const 是 顶层const，const 是底层const
    const int &constReferenceToConst = constInt30; // 用于声明引用的const 都是 底层const

    // 顶层const 和 底层const 在对象拷贝时的不同
    // 1. 如果拷入对象和拷贝对象是同一个，未改变值，没啥影响
    int30 = constInt30; // int = 顶层const，无影响
    std::cout << pointerToConst30 << std::endl;  // 0x7ffee5294444
    std::cout << constPointerToConst30 << std::endl; // 0x7ffee5294444
    pointerToConst30 = constPointerToConst30;
    
    // 2. 拷入对象和拷出对象具有相同的底层const｜两个对象的数据类型可以相互转化（非常量可转化为常量）
    // int *pointer30 = constPointerToConst30; // error constPointerToConst有底层const，而pointer没有
    pointerToConst30 = constPointerToConst30; // pointerToConst 和 constPointerToConst 都是 底层const
    pointerToConst30 = &int30; // 正确：int* 能转化为 const int*
    // int &reference30 = constInt30; // error 只有 对常量的引用 可以绑定到 int常量，而普通引用不行
    const int &reference31 = int30; // const int& 可以绑定到 int 上


    /**
     * 2.4.4 constexpr 和 常量表达式
     * 常量表达式const expression：值不会改变，且在编译过程中就能得到计算结果的表达式
     * 如：字面值、用常量表达式初始化的const对象
     * 
     * + constexpr变量
     * + 字面值类型
     * + 指针 和 constexpr
     */
    // 常量表达式
    // 一个对象（或表达式）是不是常量表达式，由数据类型、初始值共同决定
    const int max_files = 20; // max_files 是常量表达式
    const int limit = max_files + 1; // limit 是常量表达式。
    int staff_size = 27; // staff_size 不是常量表达式。普通的int，而不是 const int
    const int sz = getSize(); // sz 不是常量表达式。在运行过程中获得，而不是编译过程中

    // constexpr 变量
    // 作用：C++11规定，用constexpr，以让编译器验证变量是否是常量表达式
    constexpr int mf = 20; // 是常量表达式
    constexpr int l = mf + 1; // 是常量表达式
    // constexpr int s = getSize(); // error: constexpr variable 's' must be initialized by a constant expression

    // 字面值类型
    // 常量表达式的值，需要在编译时计算，因此对 声明constexpr是用到的类型必须有所限制
    // 因为这些类型简单，值显而易见，称为字面值类型 literal type
    /* 
        到目前，
        属于字面值类型的有：算数类型、引用、指针
        不属于字面值类型的有：自定义类，IO库，string类。 不能定义成 constexpr
     */
    /* 
        规定：
            1. 一个constexpr指针的初始值必须是 nullptr｜0｜存储与某个固定地址中的对象
            2. 函数体内的变量并非存放在固定地址中，因此 constexpr指针 不能指向函数体内的成员变量
            3. 所有函数体外的对象，都能用 constexpr指针 指向
     */

    // 指针 和 constexpr
    /* 
        规定：
            1. 对于 constexpr指针，常量表达式的限定，只对指针本身有效，而对指针指向的值无效
            2. constexpr限定的指针，是常量指针
            3. 函数体内的对象，不能用constexpr指针指向（包括main函数）
     */
    int int40 = 0;
    const int *pointer40 = nullptr; // 指向常量的指针 可以指向函数体内部的常量对象
    // const int *pointer41 = &int40; // 指向常量的指针 不能指向非常量

    // constexpr限定的常量指针
    constexpr int *pointer42 = nullptr;
    // constexpr int *pointer42 = &int40; // int40 在main函数内定义，不能用constexpr限定的指针指向
    constexpr int *pointer43 = &intValue; // intValue 在main函数外定义，可以被constexpr限定的指针指向
    

    return 0;
}

int getSize() { return 100; }
