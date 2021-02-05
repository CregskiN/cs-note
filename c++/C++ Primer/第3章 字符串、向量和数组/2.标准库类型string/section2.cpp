#include <cctype>
#include <iostream>
#include <string>

using std::string;

/*
 * 3.2 标准库类型 string
 *
 * + 3.2.1 定义和初始化string对象
 * + 3.2.2 string对象上的操作
 * + 3.2.3 处理 string对象中的字符
 */
int main() {
    /**
     * 3.2.1 定义 和 初始化string对象
     *
     * + 初始化string
     * + 直接初始化 和 拷贝初始化
     */

    string s11;           // 默认初始化，空串
    string s12(s11);      // s12 是 s11 的副本
    string s13 = s11;     // 等价于 s13(s11)
    string s14("value");  // s14 是 字面值"value"
                          // 的副本（除了字面值最后的那个空字符外）
    string s15 = "value";  // 等价于s14("value")
    string s16(10, 'c');  // 把 s16 初始化为 10个连续的c 组成的字符串

    /*
        直接初始化 和 拷贝初始化
     */
    // 拷贝初始化 copy
    // initialization：编译器把等号右侧字面值，拷贝到新创建的对象中去
    string s17 = "hiya";
    // 直接初始化 direct initialization：不用等号
    string s18("hiya");
    string s19(10, 'c');

    /**
     * 3.2.2 string对象上的操作
     *
     * + 读写 string对象
     * + 读取未知数量的 string对象
     * + 使用 getline 读取一整行
     * + string 的 empty 和 size 操作
     * + string::size_type 类型
     * + 比较 string对象
     * + 为 string对象 赋值
     * + 两个 string对象 相加
     * + 字面值 和 string对象 相加
     *
     */
    /*
        读写 string对象
        I：
            hello world!
        O：
            hello

     */
    std::string s201;
    std::cin >> s201;  // 将string对象读入s，遇到空白为止
    std::cout << s201 << std::endl;

    /*
        读取未知数量的string对象
        I：
            hello world!
        O：
            hello
            world!
     */
    string word;
    while (std::cin >> word) { // 反复读取，直至文件末尾
        std::cout << word << std::endl; // 逐个输出单词
    }

    /*
        使用 getline(std::cin, std::string) 读取一整行
            读完换行符截止，将换行符之前的字符串存入到str
        I：
            hello world!

        O：
            hello world!
     */
    std::string line;
    while (getline(std::cin, line)) {  //
    // 反复从输入流中读取一整行（换行符结尾），直至文件末尾
        std::cout << line << std::endl;
    }

    /*
        string 的 empty 和 size 操作
            empty 字符串判空
            size 字符串长度
     */
    std::string s202 = "123";
    std::string s203 = "";
    std::cout << s202.empty() << std::endl; // 0
    std::cout << s202.size() << std::endl; // 3

    /*
        string::size_type 类型
            + string.size() 返回的值是 string::size_type 类型，unsigned
            + string.size() 与其他数值比较需要注意
     */
    // size_type 与其他值比较
    std::string s204 = "3";
    signed int signedInt = -10;
    if(s204.size() > signedInt){
        std::cout << "\"3\".size() > -10" << std::endl;
    }else {
        std::cout << "\"3\".size() <= -10" << std::endl;
    }
    // "3".size() <= -10 // 意料之外的效果

    /*
        比较 string对象
            + string类中定义了操作符，比较string对象。< <= > >= == !=
            + string对象 比较规则
                - "hello" < "hello world!"
                - "hello" < "helab" 按第一个相异字符"l"和"a"，按字典顺序
     */
    std::string str = "hello";
    std::string phrase = "hello world";
    std::string slang = "Hiya";
    std::cout << (str < phrase) << std::endl; // 1
    std::cout << (str > slang) << std::endl; // 1 // h > H
    std::cout << (slang < phrase) << std::endl; // 1

    /*
        为string对象赋值
     */
    std::string s205(10, 'c'), s206;
    s205 = s206;

    /*
        两个 string对象 相加
     */
    string s207 = "hello ", s208 = "world\n";
    string s209 = s207 + s208;
    std::cout << s209 << std::endl;
    // hello world
    //

    /*
        字面值 和 string对象 相加
            - 标准库允许把 字符字面值、字符串字面值 转化为 string对象
            - string对象 + 字符/字符串字面值 // 合法
            - 字符/字符串字面值 + 字符/字符串字面值 + string对象// 非法
     */
    string s210 = "hello", s211 = "world!";
    string s212 = s210 + " " + s211;
    std::cout << s212 << std::endl;  // hello world!
    string s213 = "hello" + " " + "world"; // error

    /**
     * 3.2.3 处理string对象中的字符
     * 场景：stirng对象中，是否包含某字符、将某字符转换大小写
     *
     * + 处理每个字符 - 使用 范围for语句
     * + 只处理一部分字符
     *      - 用下标迭代
     *      - 用下标执行随机访问
     *      - 用迭代器迭代
     */
    /*
        cctype 头文件中的函数（cctype继承自c语言的ctype.h）
        + isalnum(c)    纯数字？
        + isalpha(c)    纯字母？
        + iscntrl(c)    控制字符？
        + isdigit(c)    数字？
        + isgraph(c)    不是空格，但可以打印？
        + islower(c)    小写字母？
        + isprint(c)    可打印字符？
        + ispunct(c)    标点符号？（不是控制字符、数字、字母、可打印空白）
        + isspace(c)
       空白？（即c是空格、横向制表符、纵向制表符、回车符、换行符、进纸符）
        + isupper(c)    是大写字母？
        + isxdigit(c)   是十六进制数字？
        + tolower(c)    输出小写字母
        + toupper(c)    输出大写字母
     */

    /*
        使用 范围for 处理每个字符
            for(declaration : expression)
                statement
     */
    string str301("some string");
    for (auto c : str301) {
        std::cout << c << std::endl;
    }

    // 实战场景：判断string中标点字符个数
    string str302("hello world!!!");
    decltype(str302.size()) punct_count = 0;
    for (auto c : str302) {
        if (ispunct(c)) {
            punct_count++;
        }
    }
    std::cout << punct_count << std::endl; // 3

    /*
        使用范围for改变字符串中的字符
            需要把 循环变量 定义为 引用类型
     */
    string str304("Hello World!!!");
    for (auto &c : str304) {
        c = toupper(c);
    }
    std::cout << str304 << std::endl; // HELLO WORLD!!!

    /* 
        只处理一部分字符
            - 下标 []的值称为索引
            - 迭代器
     */

    return 0;
}
