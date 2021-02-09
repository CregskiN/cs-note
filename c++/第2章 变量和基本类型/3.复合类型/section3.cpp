/*
  2.3 复合类型 compond type

  2.3.1 引用(左引用值 lvalue reference)

  2.3.2 指针

  2.3.3 理解复合类型的声明

 */
#include <math.h>

#include <iostream>

const int bufferSize = 512;
int getBufferSize();

int main() {
    // 引用
    // + 引用即别名，不是对象
    // + 引用的定义
    //  &
    //  初始值必须是对象
    //  引用的数据类型、值的数据类型必须相同
    // &
    int int1 = 1024, int2 = 2048;
    int &r1 = int1, r2 = int2;
    int int3 = 1024, &ri = int3;
    int &r3 = int3, &r4 = int2;
    // 初始值必须是对象
    // int &refValue4 = 10;
    // 引用的数据类型、值的数据类型必须相同
    // double double1 = 3.14;
    // int &r5 = double1;

    /*
     * 指针
     * + &取地址符：获取对象的地址
     * + 指针的值
     * 指向对象｜指向紧邻对象所占空间的下一个位置｜空指针｜无效指针（上三种意外的情况）
     * + *解地址符：使用指针访问对象
     * + 空指针
     * + 赋值与指针
     * + 其他指针操作
     * + void*指针
     *
     */
    // &取地址符：获取对象地址
    int intVal1 = 42;
    int *p = &intVal1;  // p存储了intVal1的地址、p是指向变量intVal1的指针
    // 指针的值（即地址）
    double doubleVal1 = 3.14;
    double *pDouble1 = &doubleVal1;  // 指向对象（变量）
    double *pDouble2 = pDouble1;     // 指向对象（另一个指针）
    // *解地址符：利用指针访问对象
    std::cout << *pDouble1 << std::endl;
    // 空指针
    int *pInt1 =
        nullptr;  // C++11常用 特殊类型的字面值，可以被转换成任意其他的指针类型
    int *pInt2 = 0;     // 指针初始化为字面量0生成空指针
    int *pInt3 = NULL;  // 预处理变量 preprocessor variable，
                        // 在头文件cstdlib中定义，值为0

    // int zero = 0;
    // int *pInt1 = zero; // error，即使zero对象值为0，也不能当作0初始化给指针

    // 赋值和指针
    /*
     * 指针、引用都能间接访问对象，但二者在实现上有不同
     * 指针本身是对象、引用本身不是对象
     * 指针与其存放的地址之间没有限制
     * 引用绑定的对象只能是初始对象，不能变
     */
    int *pInt4 = 0;                    // p4 指针初始化空指针
    int intVal5 = 42;                  // i5 初始化
    int *pInt5 = &intVal5;             // p5初始化 指向 i5
    int *pInt6;                        // p6 指针未初始化
    pInt6 = pInt5;                     // p5存储的地址 赋值给 p6
    pInt5 = 0;                         // p5 赋值空指针
    std::cout << *pInt6 << std::endl;  // 42
    pInt5 = &intVal5;                  // p5指向intVal5
    *pInt5 = 0;                        // p5指向对象的值为5

    // 其他指针操作：条件表达式、算数运算
    int intVal7 = 1024;
    int *pInt7 = 0;
    int *pInt8 = &intVal7;
    if (pInt7) std::cout << "pInt7指向，作为条件表达式为true" << std::endl;
    if (pInt8)  // bingo
        std::cout << "pInt8指向，作为条件表达式为true" << std::endl;

    // void*指针
    // + 存放任意类型的对象
    // + 存放任意类型的指针
    double obj = 3.14, *pDouble3 = &obj;
    void *pVoid = &obj;  // pVoid 的值可以是任意类型对象
    pVoid = pDouble3;    // pv 可以存放任意类型的指针

    /*
     * # 理解复合类型的声明
     *  变量的定义包括：基本数据类型 base type + 一组声明符
     * int *p; // int 是基本数据类型，*是类型修饰符
     *
     * + 指向指针的指针
     * + 指向指针的引用
     */
    // 指向指针的指针
    int intVal10 = 1024;
    int *pInt10 = &intVal10;
    int **ppInt10 = &pInt10;              // ppi -> pi -> i(1024)
    std::cout << *ppInt10 << std::endl;   // 0x7ffee604146c
    std::cout << pInt10 << std::endl;     // 0x7ffee604146c
    std::cout << **ppInt10 << std::endl;  // 1024

    // 指向指针的引用
    int intVal11 = 42;
    int *pInt11;
    int *&refInt11 = pInt11;  // 从右向左读，r引用的是一个int指针
    refInt11 = &intVal11;
    *refInt11 = 0;
    std::cout << *refInt11 << std::endl;  // 0

    // 没有指向引用的指针，因为引用不是对象，指针的值不能是非对象

    return 0;
}
