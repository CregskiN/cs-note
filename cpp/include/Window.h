#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include <string>

#include "Window.h"

// extern std::ostream &storeOn(std::ostream &, Screen &);
// extern BitMap &storeOn(BitMap &, Screen &); // 不能接受 BitMap 版本的 storeON
// 作为友元

class Screen {
   public:
    using pos = std::string::size_type;  // 类型成员 // typedef
    friend class Window_mgr;
    friend std::ostream &storeOn(std::ostream &, Screen &);

    Screen() = default;
    Screen(pos ht, pos wd, char c)
        : height(ht), width(wd), contents(ht * wd, c){};

    void some_member() const;
    char get() const { return contents[cursor]; };
    inline char get(pos ht, pos wd) const;
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &move(pos r, pos c);

    Screen &display(std::ostream &os) {
        do_display(os);
        return *this;
    }  // 根据是否是 const 对象，调用指定函数
    const Screen &display(std::ostream &os) const {
        do_display(os);
        return *this;
    }

   private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    mutable size_t access_ctr;  // 即使在const对象内，也可以修改
    void do_display(std::ostream &os) const { os << contents; }
};

void Screen::some_member() const { ++access_ctr; }

char Screen::get(pos r, pos c) const {  // 在类内部声明了 inline
    pos row = r * width;
    return contents[row + c];
}

inline Screen &Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r, pos col, char ch) {
    contents[r * width + col] = ch;
    return *this;
}

inline Screen &Screen::move(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}

#endif