#include <array>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

void log_vector(vector<int> data);
/*
 * 3.5 数组
 *
 * + 3.5.1 定义和初始化内置数组
 * + 3.5.2 访问数组元素
 * + 3.5.3 指针和数组
 * + 3.5.4 C风格字符串
 * + 3.5.5 与旧代码的接口
 */
int main() {
    /**
     * 3.5.1 定义和初始化内置数组
     *
     * + 显式初始化数组元素
     * + 字符数组的特殊性
     * + 不允许拷贝和赋值
     * + 理解复杂的数组声明
     */
    /*
        形如 a[d]，d必须是常量表达式
       常量表达式：值不会改变、在编译过程中得到计算结果的表达式。如字面值，以及用字面值初始化的const对象
        + 数组的元素应为对象，不能是引用
        + 不能用auto推断数组的类型
     */
    /*
        + 显式初始化数组元素：列表初始化
     */
    const unsigned size = 3;
    int arr101[size] = {0, 1, 2};
    int arr102[] = {0, 1, 2};   // 列表初始化，可以不写数组容量
    int arr103[5] = {0, 1, 2};  // 未显式初始化，用默认值填充
    string arr104[3] = {"hi", "bye"};  // 默认值填充
    // int arr105[2] = {1, 2, 3};         // error 多余的自动舍弃

    /*
        + 字符数组的特殊性
            可用字符串字面值初始化，注意：字符串结尾的空字符也会拷贝进去
     */
    char arr106[] = {'C', '+', '+'};        // 无空字符
    char arr107[] = {'C', '+', '+', '\0'};  // 有空字符
    char arr108[] = "C++";  // 自动添加字符串结尾的空字符到数组
    // const char arr109[6] = "Daniel"; // error 数组空间不足

    /*
        + 不允许拷贝和赋值
     */
    int arr109[] = {1, 2, 3};
    // int arr110[] = arr109;  // error 不能使用一个数组，初始化另一个数组
    // arr110 = arr109;  // error 不能把一个数组直接赋值给另一个数组

    /*
        + 理解复杂的数组声明
            - 能存放大多数类型对象的容器
            - 数组本身也是对象，可以有引用绑定到数组，有指针指向数组
     */
    int arr111[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *ptrs101[10];  // 指针数组：包含10个元素，每个元素都是指向int的指针
    // int &refs[10] = /* ? */ // 错误，不存在引用数组，因为引用不是对象
    int(*ptrArr101)[10] = &arr111;  // 指向有10个元素的数组 的指针
    int(&arrRef101)[10] = arr111;   // 引用 绑定到 有10个元素的数组
    int *(&arrRef102)[10] = ptrs101;
    /*
        默认情况下，类型修饰符从右往左依次绑定，以ptrs101为例
            - 大小为10的数组
            - 名字是ptrs101
            - 数组中存放的是指向int的指针
        但对于数组，从内向外阅读，再从右往左更好理解，以ptrArr101为例
            - 括号：*ptrArr101 意味着 ptrArr101 是个指针
            - 右：ptrArr101 是指向大小为10的数组的指针
            - 左：该数组的元素，是int对象
        对于更复杂的，可是按上面的解读，以arrRef102为例：
            - 括号： arrRef102 是个引用
            - 右：arrRef102引用 绑定到 有10个元素的数组
            - 左：该数组的元素，是指向int的指针
     */

    /**
     * 3.5.2 访问数组元素
     *
     * + size_t 数组下标的类型
     * + 检查下标的值 不能超出数组大小，否则有缓冲区溢出
     */

    /**
     * 3.5.3 指针和数组
     *
     * + 编译器把数组转为指针
     * + 指针也是迭代器
     * + 标准库函数 begin end
     * + 指针运算
     * + 解引用和指针运算的交互
     * + 下标和指针
     */

    /*
        + 编译器把数组转为指针
            - 取地址符& 可以用于任意对象，而数组中的元素也是对象
            - 使用数组名时，自动转为指针，不用取地址符
     */
    string arr301[] = {"one", "two", "three"};
    string *ptr301 = &arr301[0];
    string *ptr302 = arr301;

    /*
        + 指针也是迭代器
            - 指向数组元素的指针拥有更多功能
     */
    int arr302[] = {0, 2, 4, 6, 8, 10, 1, 3, 5, 7};
    int *ptr303 = arr302;               // 指向数组的指针
    std::cout << *ptr303 << std::endl;  // 0
    ++ptr303;
    std::cout << *ptr303 << std::endl;  // 2
    // 指向数组元素的指针 可以模拟迭代器用法
    // 但模拟尾后迭代器需要注意
    int *ptr304 = &arr302[10];
    // 不能解引用，不能递增

    /*
        + 标准库函数 begin end
     */
    int arr303[] = {0, 2, 4, 6, 8, 10, 1, 3, 5, 7};
    int *beginPtr301 = std::begin(arr303);
    int *endPtr301 = std::end(arr303);

    /*
        + 指针运算
            - 迭代器支持的运算，指向数组元素的指针全部支持
            - ptr1 - ptr2 返回的类型 ptrdiff_t 带符号的类型
     */

    /*
        + 解引用和指针运算的交互
            - *(ptr + 4) // 指针向后移4个元素
            - *ptr + 4 // 当前指针指向的元素，值+4
     */

    /*
        + 下标和指针
            - 对数组使用下标运算符，会转换为指针移动的形式
            - 数组使用下标运算符，支持负值。而vector string 不支持
     */
    int intArr301[] = {0, 2, 4, 6, 8};
    int int301 = intArr301[2];  // 转换为 *(intArr301 + 2)

    /**
     * 3.5.4 C风格字符串
     *
     * + C标准库String函数
     * + 比较字符串
     * + 目标字符串的大小由调用者决定
     */
    /*
        以 \0 结尾的字符数组，就是C风格字符串
     */
    /*
        + C标准库String函数
            - strlen(p) 返回p的长度（不包含\0）
            - strcmp(p1, p2)
       比较相等性，若p1>p2返回正值，p1<p2返回负值，p1==p2返回0
            - strcat(p1, p2) 将p2拼接到p1后，返回p1
            - strcpy(p1, p2) 将p2拷贝给p1，返回p1
     */
    char charArr401[] = {'C', '+', '+'};
    std::cout << strlen(charArr401) << std::endl;
    /*
        + 比较字符串 使用 strcmp(p1, p2)
     */
    /*
        + 目标字符串的大小由调用者决定
            strcat(p1, p2) 如果拼接后，p1的长度不足以容纳p1 p2，会发生安全泄漏
     */

    /**
     * 3.5.5 与旧代码的接口
     *
     * + 混用 string对象 和 C风格字符串
     * + 使用数组初始化vector对象
     */
    /*
        + 混用string对象和C风格字符串
            - c_str()
     */
    string str401("hellow");  // 用字面值初始化string对象
    string str402 = "world";
    string str403;
    str403 = str401 + " " + str402;
    const char *str404 = str403.c_str();  // 转化为C风格字符串
    /*
        + 使用数组初始化vector对象
            - 允许使用数组初始化vector对象，但反过来不行
     */
    int int_arr[] = {0, 1, 2, 3, 4, 5, 6};
    vector<int> int_vector(std::begin(int_arr), std::end(int_arr));
    log_vector(int_vector); // {0, 1, 2, 3, 4, 5, 6}
    

    return 0;
}

void log_vector(vector<int> data) {
    for (auto d : data) {
        std::cout << d;
    }
    std::cout << "\n";
}
