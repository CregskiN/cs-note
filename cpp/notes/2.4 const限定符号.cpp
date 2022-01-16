#include <array>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

 int buffer_size = 10000;

using std::string; 
using std::vector;

int main() {
    /*
        2.4.1 const的引用
        对常量的引用 / 常量引用 const int & ri = 10;
            限制通过引用对对象的操作，而不是对象本身是不是 const

        2.4.2 const 和 指针
        + 指向常量的指针
        + 常量指针：
        + 指向常量的常量指针
     */
    int val = 10;
    int val2 = 100;
    const int *p2c = &val;  // 指向常量的指针：仅自认为指向对象是常量
    // *p = 20; // ❌ 不能通过该指针对对象操作
    // p2c = &val2; // ✅ 但可改变地址

    int *const cp = &val;  // 常量指针：仅指针地址是常量
    // *cp = 20; // ✅ 可以通过指针操作对象
    // cp = &val2; // ❌ 不能改变指针地址
    // std::cout << *cp << std::endl; 

    // const int *const cp2c = &val; // 指向常量的常量指针：指针地址是常量、指向对象是常量

    constexpr int cv = 1000;
    constexpr int *q = nullptr;
    constexpr const int *q2 = &buffer_size;

    return 0;
}
