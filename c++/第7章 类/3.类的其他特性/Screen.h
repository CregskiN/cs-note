#ifndef SCREEN_CREGSKIN_H
#define SCREEN_CREGSKIN_H

#include <iostream>
#include <string>

#include "Window_mgr.h"

extern std::ostream &storeOn(std::ostream &, Screen &);
extern BitMap &storeOn(BitMap &, Screen &);

class Screen {
    // friend class Window_mgr; // Window_mgr可以访问Screen中所有成员
    friend void Window_mgr::clear(ScreenIndex);
    friend std::ostream &storeOn(std::ostream &, Screen &);

   public:
    typedef std::string::size_type pos;  // 把pos定义成public成员
    typedef std::string string;

    Screen() = default;  // 因为有下边的构造函数，所以需要显式标明编译器自动合成一个默认构造函数
    Screen(pos h, pos w, char c) : height(h), width(w), contents(h * w, c) {}

    // 设置某位置字符
    Screen &set(char);
    Screen &set(pos, pos, char);
    // 获取某位置字符
    char get() const { return this->contents[cursor]; }  // 隐式内联 // 声明在类内的成员函数，默认是隐式的
    char get(pos height, pos width) const;               // 显式内联
    // 移动光标
    Screen &move(pos r, pos c);  // 可以在类外定义部分，把函数定义为内联
    // 在屏幕上打印 contents 内容
    Screen &display(std::ostream &os);
    const Screen &display(std::ostream &os) const;

    void some_member() const;

   private:
    pos cursor = 0;             // 光标位置单位：字符
    pos height = 0;             // 窗口高度，单位：字符
    pos width = 0;              // 窗口宽度，单位：字符
    string contents;            // 显示内容，以字符串形式存储 // 一点思考，确实应该用字符串存储而不是二维数组
    mutable size_t access_ctr;  // 统计成员函数被调用的次数

    void do_display(std::ostream &os) const;
};

void Screen::do_display(std::ostream &os) const {
    os << contents;
}

/**
 * @brief （普通成员函数）显示Screen内容
 * 
 * @param os 
 * @return Screen& 
 */
inline Screen &Screen::display(std::ostream &os) {
    do_display(os);
    return *this;
}

/**
 * @brief （const成员函数）返回一个常量引用
 * 
 * @return const Screen& 
 */
inline const Screen &Screen::display(std::ostream &os) const {
    do_display(os);
    return *this;
}

/**
 * @brief 设置当前光标位置字符
 * 
 * @param c 字符
 * @return Screen& 
 */
inline Screen &Screen::set(char c) {
    contents[cursor] = c;  // FIXME: 此处可能需要 cursor++
    return *this;
}

/**
 * @brief 设置指定位置的字符
 * 
 * @param r 行号
 * @param col 列号
 * @param ch 字符
 * @return Screen& 
 */
inline Screen &Screen::set(pos r, pos col, char ch) {
    contents[r * width + col] = ch;
    return *this;
}

/**
 * @brief 移动光标到 [row, column] 位置
 * 
 * @param row 
 * @param column 
 * @return Screen& 
 */
inline Screen &Screen::move(pos r, pos c) {
    pos row = r * width;  // 计算行的位置
    cursor = row + c;
    return *this;
}

/**
 * @brief 获取 [row. column] 位置的字符
 * 
 * @param row 
 * @param column 
 * @return char 
 */
inline char Screen::get(pos r, pos c) const {
    pos row = r * width;
    return contents[row + c];
}

/**
 * @brief 
 * 
 */
inline void Screen::some_member() const {
    ++access_ctr;
}



#endif
